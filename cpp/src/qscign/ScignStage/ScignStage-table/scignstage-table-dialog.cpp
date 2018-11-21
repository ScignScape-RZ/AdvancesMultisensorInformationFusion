
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "scignstage-audio-dialog.h"

#include "styles.h"




#include <QApplication>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QButtonGroup>
#include <QScrollArea>
#include <QFileDialog>
#include <QTabWidget>
#include <QSplitter>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QDirIterator>

#include <QPlainTextEdit>
#include <QTextStream>

#include <QtMultimedia/QMediaPlayer>

#include <QPainter>
#include <QPushButton>
#include <QLabel>

#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QTableWidget>
#include <QGraphicsPixmapItem>

#include <QMessageBox>
#include <QDebug>
#include <QClipboard>

#include <QProcess>

#include <QGraphicsView>
#include <QScrollArea>
#include <QTcpServer>
#include <QNetworkAccessManager>

#include <QHeaderView>

#include <QMenu>
#include <QAction>

#include <QListWidget>

#include "dsmain/test-series.h"
#include "dsmain/test-sample.h"
#include "dsmain/audio-sample.h"
#include "dsmain/assessment-scores-average.h"

#include "xpdf-bridge.h"

#include "dsmain/test-sentence.h"

#include "PhaonLib/phaon-runner.h"

#include "kauvir-phaon/kph-command-package.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kauvir-code-model.h"

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(Phaon)

//USING_QSNS(ScignStage)


ScignStage_Audio_Dialog::ScignStage_Audio_Dialog(XPDF_Bridge* xpdf_bridge,
  Test_Series* ts,
  QWidget* parent)
  : QDialog(parent), xpdf_bridge_(xpdf_bridge), player_(nullptr), last_sample_(nullptr),
    last_highlight_(nullptr), xpdf_process_(nullptr), tcp_server_(nullptr),
    phr_(nullptr), phr_init_function_(nullptr), screenshot_function_(nullptr),
 current_tcp_msecs_(0),
    xpdf_port_(0), current_index_(-1), max_index_(0), current_volume_(50)
{
 // // setup RZW

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setEnabled(false);

 // // unless this is being embedded ...
 button_proceed_->setEnabled(false);
 button_cancel_->setText("Close");

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_proceed_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(cancel()));

 main_layout_ = new QVBoxLayout;


 top_buttons_layout_ = new QHBoxLayout;

 take_screenshot_button_ = new QPushButton("Screenshot", this);

 activate_tcp_button_ = new QPushButton("Activate TCP", this);

 take_screenshot_button_->setStyleSheet(colorful_button_style_sheet_());
 activate_tcp_button_->setStyleSheet(colorful_button_style_sheet_());

 connect(take_screenshot_button_, SIGNAL(clicked()),
   this, SLOT(handle_take_screenshot_requested()));

 connect(activate_tcp_button_, SIGNAL(clicked()),
   this, SLOT(activate_tcp_requested()));

 top_buttons_layout_->addStretch();

 top_buttons_layout_->addWidget(activate_tcp_button_);

 top_buttons_layout_->addWidget(take_screenshot_button_);

 main_layout_->addLayout(top_buttons_layout_);

 middle_layout_ = new QHBoxLayout;

 // //   Foreground
 main_frame_ = new QFrame(this);

 main_frame_->setMinimumHeight(250);

 main_frame_->setMinimumWidth(300);

 main_frame_->setContextMenuPolicy(Qt::CustomContextMenu);

 main_grid_layout_ = new QGridLayout;

 int r = 0;

 files_.resize(ts->samples().size());

 max_index_ = files_.size() - 1;

 samples_ = &ts->samples();

 QStringList theaders {
  "Test 1",
  "Test 2"
 };

 QStringList headers {
  "File Name", "S-MOS",
  "N-MOS", "G-MOS",
  "S-MOS", "N-MOS", "G-MOS"
 };

 int cc = 1;
 for(QString h : theaders)
 {
  QLabel* lbl = new QLabel(h, this);
  main_grid_layout_->addWidget(lbl, 0, cc, 1, 3);
  cc += 3;
 }

 cc = 0;
 for(QString h : headers)
 {
  QLabel* lbl = new QLabel(h, this);
  main_grid_layout_->addWidget(lbl, 1, cc);
  ++cc;
 }



 for(Test_Sample* sa : ts->samples())
 {
  QString f = sa->audio_sample()->file_name();

  QLabel* lbl = new QLabel(f, this);
  sample_to_label_map_[sa] = {lbl, r};

  main_grid_layout_->addWidget(lbl, r + 2, 0);

  files_[r] = f;

  QStringList qsl;
  sa->assessment_scores()->to_strings(qsl);

  QStringList lqsl;
  sa->assessment_scores_with_load()->to_strings(lqsl);

  int c = 1;
  for(QString qs : qsl)
  {
   main_grid_layout_->addWidget(new QLabel(qs), r + 2, c);
   ++c;
  }
  for(QString qs : lqsl)
  {
   main_grid_layout_->addWidget(new QLabel(qs), r + 2, c);
   ++c;
  }

  ++r;
 }

 main_frame_->setLayout(main_grid_layout_);

 grid_scroll_area_ = new QScrollArea(this);
 grid_scroll_area_->setWidget(main_frame_);

 grid_scroll_area_->setMaximumHeight(200);

 middle_layout_->addWidget(grid_scroll_area_);

 connect(main_frame_, &QTableWidget::customContextMenuRequested, [this](const QPoint& qp)
 {
  qDebug() << qp;

  QWidget* qw = QApplication::widgetAt(main_frame_->mapToGlobal(qp));

  if(qw)
  {
   if(qw->parent() == main_frame_)
   {
    int i = main_grid_layout_->indexOf(qw);
    if(i != -1)
    {
     int r, c, rs, cs;
     main_grid_layout_->getItemPosition(i, &r, &c, &rs, &cs);
     run_message_by_grid_position(qp, r, c);

    }
   }
  }

 });

 main_layout_->addLayout(middle_layout_);

 sentence_label_ = new QLabel("(sentence text)", this);

 main_layout_->addWidget(sentence_label_);

 nav_panel_ = new NAV_Audio1D_Panel(0, 100, 50, this);

 connect(nav_panel_, SIGNAL(sample_up_requested()),
   this, SLOT(handle_sample_up()));

 connect(nav_panel_, SIGNAL(sample_down_requested()),
   this, SLOT(handle_sample_down()));

 connect(nav_panel_, SIGNAL(peer_up_requested()),
   this, SLOT(handle_peer_up()));

 connect(nav_panel_, SIGNAL(peer_down_requested()),
   this, SLOT(handle_peer_down()));

 connect(nav_panel_, SIGNAL(sample_first_requested()),
   this, SLOT(handle_sample_first()));

 connect(nav_panel_, SIGNAL(sample_replay_requested()),
   this, SLOT(handle_sample_replay()));


 connect(nav_panel_, SIGNAL(volume_change_requested(int)),
   this, SLOT(handle_volume_change_requested(int)));

 main_layout_->addWidget(nav_panel_);



 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

#ifdef USING_XPDF
 // // xpdf connections ...
 if(xpdf_bridge_)
 {
  connect(xpdf_bridge_, SIGNAL(xpdf_is_ready()),
    this, SLOT(handle_xpdf_is_ready()));
 }
#endif // USING_XPDF

}

void ScignStage_Audio_Dialog::handle_take_screenshot_requested()
{
 Q_EMIT(take_screenshot_requested());
 if(screenshot_function_)
   screenshot_function_();
}

void ScignStage_Audio_Dialog::check_phr()
{
#ifdef USING_KPH
 if(!phr_)
 {
  phr_ = new Phaon_Runner;
  if(phr_init_function_)
    phr_init_function_(*phr_);
 }
#endif
}

// // KAI
void ScignStage_Audio_Dialog::test_msgbox(QString msg)
{
 QString m = QString("Received Message: %1").arg(msg);
 QMessageBox::information(this, "Test OK", m);
}

void ScignStage_Audio_Dialog::play_sample(int index)
{
 current_index_ = index;
 play_file_at_current_index();
}

void ScignStage_Audio_Dialog::play_next_sample()
{
 handle_sample_down();
}

void ScignStage_Audio_Dialog::play_next_sample_in_peer_group()
{
 handle_peer_down();
}

void ScignStage_Audio_Dialog::play_previous_sample()
{
 handle_sample_up();
}

void ScignStage_Audio_Dialog::play_previous_sample_in_peer_group()
{
 handle_peer_up();
}

void ScignStage_Audio_Dialog::show_sentence_text(int index)
{
 Test_Sample* ts = samples_->at(index);
 sentence_label_->setText(ts->sentence()->raw_text().replace('_', ' '));
}

void ScignStage_Audio_Dialog::show_distractor_text(int index)
{
 Test_Sample* ts = samples_->at(index);
 nav_panel_->set_distractor_text(ts->distractor_to_string());
}

void ScignStage_Audio_Dialog::highlight_sample(int index)
{
 if(last_highlight_)
   last_highlight_->setStyleSheet("QLabel{background:none;}");
 Test_Sample* ts = samples_->at(index);
 QLabel* lbl = sample_to_label_map_[ts].first;
 lbl->setStyleSheet("QLabel{background:yellow;}");
}

void ScignStage_Audio_Dialog::highlight_peers(int index)
{
 Test_Sample* ts = samples_->at(index);
 QVector<Test_Sample*>* apl = ts->sentence()->applicable_samples_ptr();

 for(Test_Sample* tsa : *apl)
 {
  if(tsa == ts)
    continue;
  QLabel* lbl = sample_to_label_map_[tsa].first;
  lbl->setStyleSheet("QLabel{background:pink;}");
 }

}


void ScignStage_Audio_Dialog::test_to_string(QString& result, bool wl)
{
 if(!samples_) return;
 int sz = samples_->size() * 18;
 result.resize(sz, ' ');
 int index = 0;

 for(Test_Sample* ts : *samples_)
 {
  Assessment_Scores_Average* scores = wl? ts->assessment_scores() :
    ts->assessment_scores_with_load();
  QString qs = QString::number(scores->speech_nondistortion(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 6;
  qs = QString::number(scores->background_nondisruption(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 6;
  qs = QString::number(scores->overall_quality(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 5;
  result.replace(index, 1, '\n');
  ++index;
 }
}

void ScignStage_Audio_Dialog::smos_to_string(QString& result, bool wl)
{
 if(!samples_) return;
 int sz = samples_->size() * 6;
 result.resize(sz, '0');
 int index = 0;

 for(Test_Sample* ts : *samples_)
 {
  Assessment_Scores_Average* scores = wl? ts->assessment_scores() :
    ts->assessment_scores_with_load();
  QString qs = QString::number(scores->speech_nondistortion(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 5;
  result.replace(index, 1, '\n');
  ++index;
 }
}

void ScignStage_Audio_Dialog::nmos_to_string(QString& result, bool wl)
{
 if(!samples_) return;
 int sz = samples_->size() * 6;
 result.resize(sz, '0');
 int index = 0;
 for(Test_Sample* ts : *samples_)
 {
  Assessment_Scores_Average* scores = wl? ts->assessment_scores() :
    ts->assessment_scores_with_load();
  QString qs = QString::number(scores->background_nondisruption(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 5;
  result.replace(index, 1, '\n');
  ++index;
 }
}


void ScignStage_Audio_Dialog::gmos_to_string(QString& result, bool wl)
{
 if(!samples_) return;
 int sz = samples_->size() * 6;
 result.resize(sz, '0');
 int index = 0;
 for(Test_Sample* ts : *samples_)
 {
  Assessment_Scores_Average* scores = wl? ts->assessment_scores() :
    ts->assessment_scores_with_load();
  QString qs = QString::number(scores->overall_quality(),
    'f', 3);
  result.replace(index, 5, qs);
  index += 5;
  result.replace(index, 1, '\n');
  ++index;
 }
}

void ScignStage_Audio_Dialog::save_to_user_select_file(QString text)
{
 QString f = QFileDialog::getSaveFileName();
 if(!f.isEmpty())
 {
  save_file(f, text);
 }
}

void ScignStage_Audio_Dialog::run_smos_message(const QPoint& p, int col)
{
 run_about_context_menu(p, col, [this]
 {
  bool proceed = ask_pdf_proceed("smos");
  if(proceed)
  {
   open_pdf_file(ABOUT_FILE_FOLDER "/main.pdf", 3);
  }
 },[this, col]
 {
  QString qs;
  smos_to_string(qs, col > 3);
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(qs);
 },[this, col]
 {
  QString qs;
  smos_to_string(qs, col > 3);
  save_to_user_select_file(qs);
 });
}

void ScignStage_Audio_Dialog::run_nmos_message(const QPoint& p, int col)
{
 run_about_context_menu(p, col, [this]
 {
  bool proceed = ask_pdf_proceed("nmos");
  if(proceed)
  {
   open_pdf_file(ABOUT_FILE_FOLDER "/main.pdf", 3);
  }
 },[this, col]
 {
  QString qs;
  nmos_to_string(qs, col > 3);
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(qs);
 },[this, col]
 {
  QString qs;
  nmos_to_string(qs, col > 3);
  save_to_user_select_file(qs);
 });
}

void ScignStage_Audio_Dialog::run_gmos_message(const QPoint& p, int col)
{
 run_about_context_menu(p, col, [this]
 {
  bool proceed = ask_pdf_proceed("gmos");
  if(proceed)
  {
   open_pdf_file(ABOUT_FILE_FOLDER "/main.pdf", 3);
  }
 },[this, col]
 {
  QString qs;
  gmos_to_string(qs, col > 3);
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(qs);
 },[this, col]
 {
  QString qs;
  gmos_to_string(qs, col > 3);
  save_to_user_select_file(qs);
 });
}

QString ScignStage_Audio_Dialog::load_about_file(QString name)
{
 return load_file(QString("%1/%2.txt")
   .arg(ABOUT_FILE_FOLDER).arg(name)).replace('\n', ' ').simplified();
}

bool ScignStage_Audio_Dialog::ask_pdf_proceed(QString name)
{
 QString about = load_about_file(name);
 QMessageBox qmb;
 qmb.setText(about);
 QAbstractButton* yes = qmb.addButton(QString("More ..."), QMessageBox::YesRole);
 qmb.addButton("Cancel", QMessageBox::NoRole);

 qmb.exec();

 return qmb.clickedButton() == yes;
}

void ScignStage_Audio_Dialog::run_test_with_load_message(const QPoint& p, int col)
{
 run_about_context_menu(p, col, [this]
 {
  bool proceed = ask_pdf_proceed("test2");
  if(proceed)
  {
   open_pdf_file(ABOUT_FILE_FOLDER "/main.pdf", 2);
  }
 },[this, col]
 {
  QString qs;
  test_to_string(qs, col > 3);
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(qs);
 },[this, col]
 {
  QString qs;
  test_to_string(qs, col > 3);
  save_to_user_select_file(qs);
 });
}

void ScignStage_Audio_Dialog::run_about_context_menu(const QPoint& p, int col,
  std::function<void()> about_fn,
  std::function<void()> copy_fn,  std::function<void()> save_fn)
{
 QMenu* qm = new QMenu(this);
 qm->addAction("About ...", about_fn);
 qm->addAction("Copy Data to Clipboard", copy_fn);
 qm->addAction("Save Data to File", save_fn);
 QPoint g = mapToGlobal(p);
 qm->popup(g);
}

void ScignStage_Audio_Dialog::run_sample_context_menu(const QPoint& p,
   std::function<void()> play_fn,
   std::function<void()> copy_fn)
{
 QMenu* qm = new QMenu(this);
 qm->addAction("Play ...", play_fn);
 qm->addAction("Copy Path to Clipboard", copy_fn);
 QPoint g = main_frame_->mapToGlobal(p);
 qm->popup(g);
}

void ScignStage_Audio_Dialog::run_test_no_load_message(const QPoint& p, int col)
{
 run_about_context_menu(p, col, [this]
 {
  bool proceed = ask_pdf_proceed("test1");
  if(proceed)
  {
   open_pdf_file(ABOUT_FILE_FOLDER "/main.pdf", 2);
  }
 },[this, col]
 {
  QString qs;
  test_to_string(qs, col > 3);
  QClipboard* clipboard = QApplication::clipboard();
  clipboard->setText(qs);
 },[this, col]
 {
  QString qs;
  test_to_string(qs, col > 3);
  save_to_user_select_file(qs);
 });
}

void ScignStage_Audio_Dialog::run_message_by_grid_position(const QPoint& p, int r, int c)
{
 static QMap<QPair<int, int>, void(ScignStage_Audio_Dialog::*)(const QPoint&, int col)>
   static_map {{
   {{0, 1}, &ScignStage_Audio_Dialog::run_test_no_load_message},
   {{0, 4}, &ScignStage_Audio_Dialog::run_test_with_load_message},

   {{1, 1}, &ScignStage_Audio_Dialog::run_smos_message},
   {{1, 4}, &ScignStage_Audio_Dialog::run_smos_message},

   {{1, 2}, &ScignStage_Audio_Dialog::run_nmos_message},
   {{1, 5}, &ScignStage_Audio_Dialog::run_nmos_message},

   {{1, 3}, &ScignStage_Audio_Dialog::run_gmos_message},
   {{1, 6}, &ScignStage_Audio_Dialog::run_gmos_message},
  }};

 auto it = static_map.find({r, c});
 if(it != static_map.end())
 {
  (this->**it)(p, c);
  return;
 }

 if(c == 0)
 {
  run_sample_context_menu(p, [this, r]
  {
   current_index_ = r - 2;
   play_file_at_current_index();
  },[this, r]
  {
   QString f = files_[r - 2];
   QString path = SAMPLES_FOLDER "/" + f;

   QClipboard* clipboard = QApplication::clipboard();
   clipboard->setText(path);
  });
 }
}

void ScignStage_Audio_Dialog::send_xpdf_msg(QString msg)
{
 if(xpdf_bridge_)
   xpdf_bridge_->take_message(msg);
}

void ScignStage_Audio_Dialog::open_pdf_file(QString name, int page)
{
#ifdef USING_XPDF
 check_launch_xpdf([this, name, page]()
 {
  send_xpdf_msg(QString("open:%1;%2").arg(name).arg(page));
 },[this, name, page]()
 {
  held_xpdf_msg_ = QString("open:%1;%2").arg(name).arg(page);
 });
#else
 QMessageBox::information(this, "XPDF Needed",
   "You need to build the customized XPDF library "
   "to view PDF files from this application.  See "
   "build-order.txt for more information."
 );
#endif
}

void ScignStage_Audio_Dialog::run_kph(const QByteArray& qba)
{
#ifdef USING_KPH
 check_phr();

 KPH_Command_Package khp;
 khp.absorb_data(qba);

 Kauvir_Code_Model& kcm = phr_->get_kcm();

 KCM_Channel_Group kcg(kcm.channel_names());

 khp.init_channel_group(kcm, kcg);
 phr_->run(kcg);
#endif
}

void ScignStage_Audio_Dialog::run_msg(QString msg, QByteArray qba)
{
 qDebug() << QString("received: %1").arg(msg);

 if(msg == "kph")
 {
  run_kph(qba);
 }
}

bool ScignStage_Audio_Dialog::xpdf_is_ready()
{
 if(xpdf_bridge_)
   return xpdf_bridge_->is_ready();
 return false;
}

void ScignStage_Audio_Dialog::handle_xpdf_is_ready()
{
 if(!held_xpdf_msg_.isEmpty())
 {
  send_xpdf_msg(held_xpdf_msg_);
  held_xpdf_msg_.clear();
 }
}

void ScignStage_Audio_Dialog::check_launch_xpdf(std::function<void()> fn,
  std::function<void()> waitfn)
{
 if(xpdf_is_ready())
 {
  fn();
  return;
 }

 if(xpdf_bridge_)
 {
  xpdf_bridge_->init();
  waitfn();
  return;
 }
}


void ScignStage_Audio_Dialog::activate_tcp_requested()
{
#ifdef USING_KPH
 QString waiting_message;

 if(tcp_server_)
 {
  waiting_message = QString("TCP is already started, using IP: %1\nport: %2\n\n")
    .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());
  QMessageBox::information(this, "Already Activated", waiting_message);
  return;
 }
 tcp_server_ = new QTcpServer();
 QMap<qintptr, QByteArray>* temps = new QMap<qintptr, QByteArray>();

 int port = 18261; // // r z 1

 if (!tcp_server_->listen(QHostAddress::LocalHost, port))
 {
  QMessageBox::critical(this, "TCP Initialization Failed",
                         QString("Could not use port: %1.")
                         .arg(tcp_server_->errorString()));
 }
 else
 {
  waiting_message = QString("Using IP: %1\nport: %2\n\n")
     .arg(tcp_server_->serverAddress().toString()).arg(tcp_server_->serverPort());

  QMessageBox::information(this, "TCP is Started",
                            QString(waiting_message));
 }

 QObject::connect(tcp_server_, &QTcpServer::newConnection, [this, temps]
 {
  QTcpSocket* clientConnection = tcp_server_->nextPendingConnection();
  QObject::connect(clientConnection, &QAbstractSocket::disconnected,
    clientConnection, &QObject::deleteLater);
  clientConnection->write("OK");
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this, temps]
  {
   qintptr sd = clientConnection->socketDescriptor();
   QByteArray received;
   while(clientConnection->bytesAvailable())
   {
    received.append(clientConnection->readAll());
   }
   if(received.endsWith("<//>"))
   {
    received.chop(4);
    QByteArray qba = (*temps)[sd];
    qba.append(received);
    temps->remove(sd);

    int index = qba.indexOf("<<>>");

    if(index != -1)
    {
     int i1 = qba.indexOf('@', index);
     int i2 = qba.indexOf(':', i1);
     QString msg = QString::fromLatin1(qba.mid(index + 4, i1 - index - 4));
     QByteArray ms = qba.mid(i1 + 1, i2 - i1 - 2);
     quint64 msecs = ms.toLongLong();
     if(msecs != current_tcp_msecs_)
     {
      current_tcp_msecs_ = msecs;
      run_msg( msg, qba.mid(i2 + 1) );
     }
    }
    clientConnection->write("END");
   }
   else
   {
    (*temps)[sd] += received;
   }
  });
 });
#else
 QMessageBox::information(this, "Kauvir/Phaon Needed",
   QString(
     "To use TCP for testing/demoing \"Kernel Application Interface\" "
     "functions you need to build several additional libraries "
     "(see the build-order.txt file for Qt project files and %1, line %2).")
     .arg(__FILE__).arg(__LINE__)
 );
#endif
}

void ScignStage_Audio_Dialog::play_file_at_current_index()
{
 // //  2 headers rows
 int current_row = current_index_ + 2;

 nav_panel_->set_sample_text(current_index_ + 1);

 QString f = files_[current_index_];

 if(last_highlight_)
   last_highlight_->setStyleSheet("QLabel{background:none;}");

 if(last_sample_)
 {
  QVector<Test_Sample*>* lapl = last_sample_->sentence()->applicable_samples_ptr();

  for(Test_Sample* ltsa : *lapl)
  {
   QLabel* lbl = sample_to_label_map_[ltsa].first;
   lbl->setStyleSheet("QLabel{background:none;}");
  }
 }

 last_sample_ = samples_->at(current_index_);
 sentence_label_->setText(last_sample_->sentence()->raw_text().replace('_', ' '));

 nav_panel_->set_distractor_text(last_sample_->distractor_to_string());

 QVector<Test_Sample*>* apl = last_sample_->sentence()->applicable_samples_ptr();

 for(Test_Sample* tsa : *apl)
 {
  QLabel* lbl = sample_to_label_map_[tsa].first;
  lbl->setStyleSheet("QLabel{background:pink;}");
 }

 last_highlight_ = main_grid_layout_->itemAtPosition(current_row, 0)->widget();
 last_highlight_->setStyleSheet("QLabel{background:yellow;}");

 grid_scroll_area_->ensureWidgetVisible(last_highlight_);

 if(!player_)
   player_ = new QMediaPlayer;

 QString path = SAMPLES_FOLDER "/" + f;

 player_->setMedia(QUrl::fromLocalFile(path));
 player_->setVolume(current_volume_);
 player_->play();

}

void ScignStage_Audio_Dialog::handle_volume_change_requested(int v)
{
 current_volume_ = v;
 player_->setVolume(current_volume_);
}

void ScignStage_Audio_Dialog::handle_sample_down()
{
 if(current_index_ == max_index_)
   current_index_ = 0;
 else
   ++current_index_;

 play_file_at_current_index();

}

void ScignStage_Audio_Dialog::handle_peer_up()
{
 QVector<Test_Sample*>* peers = last_sample_->get_peer_samples();
 int i = last_sample_->index_in_peer_set();
 Test_Sample* samp;
 if(i == 0)
   samp = peers->last();
 else
   samp = peers->value(i-1);
 current_index_ = sample_to_label_map_[samp].second;
 play_file_at_current_index();
}

void ScignStage_Audio_Dialog::handle_peer_down()
{
 if(!last_sample_)
 {
  handle_sample_first();
  return;
 }
 QVector<Test_Sample*>* peers = last_sample_->get_peer_samples();
 int i = last_sample_->index_in_peer_set() + 1;
 Test_Sample* samp = peers->value(i, peers->value(0));
 current_index_ = sample_to_label_map_[samp].second;
 play_file_at_current_index();
}


void ScignStage_Audio_Dialog::handle_sample_up()
{
 if(current_index_ == 0)
   current_index_ = max_index_;
 else
   --current_index_;

 play_file_at_current_index();

}


ScignStage_Audio_Dialog::~ScignStage_Audio_Dialog()
{
 //  //  Child widgets should delete automatically ...
}

void ScignStage_Audio_Dialog::handle_sample_replay()
{
 play_file_at_current_index();
}

void ScignStage_Audio_Dialog::handle_sample_first()
{
 current_index_ = 0;
 play_file_at_current_index();
}



void ScignStage_Audio_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void ScignStage_Audio_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
