
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "scignstage-tree-table-dialog.h"

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

#include <QTreeWidget>

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

#include "dsmain/test-sample.h"


#include "xpdf-bridge.h"


#include "PhaonLib/phaon-runner.h"

#include "kauvir-phaon/kph-command-package.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kauvir-code-model.h"

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(Phaon)

//USING_QSNS(ScignStage)


ScignStage_Tree_Table_Dialog::ScignStage_Tree_Table_Dialog(XPDF_Bridge* xpdf_bridge,
  QVector<Test_Sample*>* samples, QWidget* parent)
  : QDialog(parent), xpdf_bridge_(xpdf_bridge),
    samples_(samples), tcp_server_(nullptr),
    phr_(nullptr), phr_init_function_(nullptr),
    screenshot_function_(nullptr), current_sample_(nullptr)
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


 main_tree_widget_ = new QTreeWidget(this);

 if(samples)
 {

  int r = 0;

  QStringList headers {
   "Index",
   "Flow",
   "Time With\n / Average",
   "Time Against\n / Delta",
   "Temperature C\u00b0\n / K\u00b0",
   "Oxygen \n (calculated)"
  };

  main_tree_widget_->setColumnCount(6);
  main_tree_widget_->setHeaderLabels(headers);

  main_tree_widget_->setColumnWidth(0, 50);
  main_tree_widget_->setColumnWidth(1, 65);
  main_tree_widget_->setColumnWidth(2, 105);
  main_tree_widget_->setColumnWidth(3, 105);
  main_tree_widget_->setColumnWidth(4, 135);
  main_tree_widget_->setColumnWidth(5, 65);

  main_tree_widget_->header()->setStretchLastSection(false);
  main_tree_widget_->header()->setSectionResizeMode(5, QHeaderView::Stretch);

  int c = 0;
  for(Test_Sample* samp : *samples_)
  {
   ++c;

   QStringList qsl;

   qsl.push_back(QString::number(samp->index()));
   qsl.push_back(QString::number(samp->flow().getDouble()));
   qsl.push_back(QString::number(samp->time_with_flow().getDouble()));
   qsl.push_back(QString::number(samp->time_against_flow().getDouble()));

   QString s = QString::number(samp->temperature_adj());
   s.insert(s.size() - 2, '.');
   qsl.push_back(s);

   QTreeWidgetItem* twi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     qsl);

   QStringList sqsl {{"", ""}};

   sqsl.push_back(" " + QString::number(samp->average_time().getDouble()));
   sqsl.push_back(" " + QString::number(samp->delta_time().getDouble()));
   sqsl.push_back(" " + QString::number(samp->temperature_kelvin().getDouble()));
   sqsl.push_back(" " + QString::number(samp->oxy()));

   QTreeWidgetItem* stwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     sqsl);

   twi->addChild(stwi);

   main_tree_widget_->addTopLevelItem(twi);

   //twi->setData(0, Qt::UserRole, QVariant::fromValue(group)
  }
 }

 main_tree_widget_->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(main_tree_widget_, &QTreeWidget::customContextMenuRequested, [this](const QPoint& qp)
 {
  QTreeWidgetItem* twi = main_tree_widget_->itemAt(qp);
  QModelIndex qmi = main_tree_widget_->indexAt(qp);
  qDebug() << qmi.column();

  run_tree_context_menu(qp, qmi.column(), qmi.row());

 });

 main_tree_widget_->header()->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(main_tree_widget_->header(), &QTreeWidget::customContextMenuRequested, [this](const QPoint& qp)
 {
//  QModelIndex qmi = main_tree_widget_->indexAt(qp);
//  qDebug() << qmi.column();

  int col = main_tree_widget_->header()->logicalIndexAt(qp);

  run_tree_context_menu(qp, col);

 });


 middle_layout_->addWidget(main_tree_widget_);

 main_layout_->addLayout(middle_layout_);

 nav_panel_ = new NAV_Tree_Table1D_Panel(this);

 connect(nav_panel_, SIGNAL(sample_up_requested()),
   this, SLOT(handle_sample_up()));

 connect(nav_panel_, SIGNAL(sample_down_requested()),
   this, SLOT(handle_sample_down()));

 connect(nav_panel_, SIGNAL(sample_first_requested()),
   this, SLOT(handle_sample_first()));

 connect(nav_panel_, SIGNAL(peer_up_requested()),
   this, SLOT(handle_peer_up()));

 connect(nav_panel_, SIGNAL(peer_down_requested()),
   this, SLOT(handle_peer_down()));

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

void ScignStage_Tree_Table_Dialog::browse_to_selected_sample(Test_Sample* samp)
{
 if(current_sample_)
   unhighlight(current_sample_);
 highlight_scroll_to_sample(samp);
 current_sample_ = samp;
}

void ScignStage_Tree_Table_Dialog::highlight_scroll_to_sample(Test_Sample* samp)
{
 int index = samp->index() - 1;
 QTreeWidgetItem* twi = main_tree_widget_->topLevelItem(index);
 highlight(twi);
 int max = qMin(index + 4, samples_->size() - 1);

 QTreeWidgetItem* mtwi = main_tree_widget_->topLevelItem(max);

 main_tree_widget_->scrollToItem(mtwi);
 main_tree_widget_->scrollToItem(twi);
}


void ScignStage_Tree_Table_Dialog::highlight(Test_Sample* samp)
{
 highlight(main_tree_widget_->topLevelItem(samp->index() - 1));
}

void ScignStage_Tree_Table_Dialog::unhighlight(Test_Sample* samp)
{
 unhighlight(main_tree_widget_->topLevelItem(samp->index() - 1));
}

void ScignStage_Tree_Table_Dialog::highlight(QTreeWidgetItem* twi)
{
 twi->setExpanded(true);
 for(int i = 0; i < 6; ++i)
   twi->setForeground(i, QBrush("darkRed"));
}

void ScignStage_Tree_Table_Dialog::run_tree_context_menu(const QPoint& qp,
  int col, int row)
{
 run_tree_context_menu(qp, 0, col,
 [this](int page)
 {

 },
 [this](int col)
 {
  QString copy;
  for(Test_Sample* samp : *samples_)
  {
   switch (col)
   {
   case 0:
    copy += QString("%1\n").arg(samp->flow().getDouble());
    break;
   case 1:
    copy += QString("%1\n").arg(samp->time_with_flow().getDouble());
    break;
   }
  }
  QApplication::clipboard()->setText(copy);
 }, row,
 row? [this](int row)
 {
  Test_Sample* samp = samples_->at(row);
  QString qs = QString("%1 %2 %3 %4 %5")
    .arg(samp->flow().getDouble())
    .arg(samp->time_with_flow().getDouble())
    .arg(samp->time_against_flow().getDouble())
    .arg(samp->temperature_adj()/100)
    .arg(samp->oxy());
  QApplication::clipboard()->setText(qs);
 }:(std::function<void(int)>)nullptr,
 row? [this](int row)
 {
  if(current_sample_)
  {
   unhighlight(current_sample_);
  }
  current_sample_ = samples_->at(row);
  highlight(current_sample_);
 }:(std::function<void(int)>)nullptr
 );
}

void ScignStage_Tree_Table_Dialog::run_tree_context_menu(const QPoint& qp,
  int page, int col,
  std::function<void(int)> pdf_fn, std::function<void(int)> copyc_fn,
  int row, std::function<void(int)> copyr_fn,
  std::function<void(int)> highlight_fn)
{
 QMenu* qm = new QMenu(this);
 qm->addAction("Show in Document (requires XPDF)",
   [pdf_fn, page](){pdf_fn(page);});
 qm->addAction("Copy Column to Clipboard",
   [copyc_fn, col](){copyc_fn(col);});

 if(row)
 {
  if(copyr_fn)
    qm->addAction("Copy Row to Clipboard",
    [copyr_fn, row](){copyr_fn(row);});

  if(highlight_fn)
    qm->addAction("Highlight (scroll from here)",
    [highlight_fn, row](){highlight_fn(row);});
 }

 QPoint g = main_tree_widget_->mapToGlobal(qp);
 qm->popup(g);
}



void ScignStage_Tree_Table_Dialog::handle_peer_down()
{

}

void ScignStage_Tree_Table_Dialog::handle_peer_up()
{

}

void ScignStage_Tree_Table_Dialog::handle_sample_down()
{
 int index;
 if(current_sample_)
 {
  index = current_sample_->index() - 1;
  //main_tree_widget_->topLevelItem(index)->setExpanded(false);
  unhighlight(main_tree_widget_->topLevelItem(index));
  ++index;
  if(index == samples_->size())
  {
   index = 0;
   current_sample_ = samples_->first();
  }
  else
  {
   current_sample_ = samples_->at(index);
  }
 }
 else
 {
  index = 0;
  current_sample_ = samples_->first();
 }
 emit_highlight();
 QTreeWidgetItem* twi = main_tree_widget_->topLevelItem(index);
 highlight(twi);
 int max = qMin(index + 4, samples_->size() - 1);

 QTreeWidgetItem* mtwi = main_tree_widget_->topLevelItem(max);

 main_tree_widget_->scrollToItem(mtwi);
 main_tree_widget_->scrollToItem(twi);
}

void ScignStage_Tree_Table_Dialog::emit_highlight()
{
 Q_EMIT(sample_highlighted(current_sample_));
}

void ScignStage_Tree_Table_Dialog::unhighlight(QTreeWidgetItem* twi)
{
 twi->setExpanded(false);
 for(int i = 0; i < 6; ++i)
   twi->setForeground(i, QBrush("black"));
}

void ScignStage_Tree_Table_Dialog::handle_sample_up()
{
 int index;
 if(current_sample_)
 {
  index = current_sample_->index() - 1;
  unhighlight(main_tree_widget_->topLevelItem(index));
  if(index == 0)
  {
   index = samples_->size() - 1;
   current_sample_ = samples_->last();
  }
  else
  {
   --index;
   current_sample_ = samples_->at(index);
  }
 }
 else
 {
  index = samples_->size() - 1;
  current_sample_ = samples_->last();
 }
 emit_highlight();
 QTreeWidgetItem* twi = main_tree_widget_->topLevelItem(index);

 highlight(twi);

 int max = qMin(index + 4, samples_->size() - 1);

 QTreeWidgetItem* mtwi = main_tree_widget_->topLevelItem(max);

 main_tree_widget_->scrollToItem(mtwi);
 main_tree_widget_->scrollToItem(twi);
}

void ScignStage_Tree_Table_Dialog::handle_sample_first()
{
 if(current_sample_)
 {
  unhighlight(current_sample_);
 }
 current_sample_ = samples_->first();
 emit_highlight();

 QTreeWidgetItem* twi = main_tree_widget_->topLevelItem(0);
 highlight(twi);
 main_tree_widget_->scrollToItem(twi);
}

void ScignStage_Tree_Table_Dialog::handle_take_screenshot_requested()
{
 Q_EMIT(take_screenshot_requested());
 if(screenshot_function_)
   screenshot_function_();
}

void ScignStage_Tree_Table_Dialog::check_phr()
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
void ScignStage_Tree_Table_Dialog::test_msgbox(QString msg)
{
 QString m = QString("Received Message: %1").arg(msg);
 QMessageBox::information(this, "Test OK", m);
}


QString ScignStage_Tree_Table_Dialog::load_about_file(QString name)
{
 return load_file(QString("%1/%2.txt")
   .arg(ABOUT_FILE_FOLDER).arg(name)).replace('\n', ' ').simplified();
}

bool ScignStage_Tree_Table_Dialog::ask_pdf_proceed(QString name)
{
 QString about = load_about_file(name);
 QMessageBox qmb;
 qmb.setText(about);
 QAbstractButton* yes = qmb.addButton(QString("More ..."), QMessageBox::YesRole);
 qmb.addButton("Cancel", QMessageBox::NoRole);

 qmb.exec();

 return qmb.clickedButton() == yes;
}


bool ScignStage_Tree_Table_Dialog::xpdf_is_ready()
{
 if(xpdf_bridge_)
   return xpdf_bridge_->is_ready();
 return false;
}

ScignStage_Tree_Table_Dialog::~ScignStage_Tree_Table_Dialog()
{

}

void ScignStage_Tree_Table_Dialog::handle_xpdf_is_ready()
{
 if(!held_xpdf_msg_.isEmpty())
 {
  //?send_xpdf_msg(held_xpdf_msg_);
  held_xpdf_msg_.clear();
 }
}

void ScignStage_Tree_Table_Dialog::check_launch_xpdf(std::function<void()> fn,
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


void ScignStage_Tree_Table_Dialog::activate_tcp_requested()
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

void ScignStage_Tree_Table_Dialog::play_file_at_current_index()
{

}

void ScignStage_Tree_Table_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void ScignStage_Tree_Table_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
