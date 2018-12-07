
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#include "application-model-test-dialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QDirIterator>
#include <QGroupBox>

#include <QFormLayout>
#include <QCheckBox>
#include <QScrollArea>
#include <QFrame>

#include <QMessageBox>
#include <QDesktopServices>
#include <QMenu>
#include <QUrl>


#include <QDebug>

#include "styles.h"

#include "application-model/application-test-model.h"

#include "kauvir-phaon/kph-command-package.h"

//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

USING_KANS(Phaon)


#include "textio.h"
USING_KANS(TextIO)

Application_Model_Test_Dialog::Application_Model_Test_Dialog(
  Application_Test_Model* apptm,
  QMap<QString, QString>&& tests, QWidget* parent)
  : QDialog(parent), tests_(tests), apptm_(apptm)
{
 button_box_ = new QDialogButtonBox(this);

 //?url_label_ = new QLabel(this);
  //?url_label_->setText(url);

// name_qle_ = new QLineEdit(this);

 button_ok_ = new QPushButton("OK");
 //? button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 //?button_proceed_->setDefault(false);
 //?button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 //?button_ok_->setEnabled(false);

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 //?button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);


 //?connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout;

 main_form_layout_ = new QFormLayout;

 QMapIterator<QString, QString> it(tests);

 while(it.hasNext())
 {
  it.next();
  QString file = it.value();
  QString desc = it.key();
  QCheckBox* ckb = new QCheckBox(file, this);
  QString text = load_file(file);
  KPH_Command_Package::read_docus(text, docus_[ckb]);
  qDebug() << "D: " << docus_[ckb]["test"];
  ckb->setTristate();
  main_form_layout_->addRow(desc, ckb);

  ckb->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ckb, &QCheckBox::customContextMenuRequested,
    [this, ckb, file, desc](const QPoint& p)
  {
   QMenu* qm = new QMenu(this);
   qm->addAction("View Documentation",
     [this, ckb, file, desc]()
   {
    QString d = QString("%1: %2").arg(desc).arg(docus_[ckb]["test"]);
    QMessageBox::information(this, file, d);
   });
   qm->addAction("Toggle Test Result",
     [this, ckb, file, desc]()
   {
    toggle_result(ckb, file);
   });
   qm->addAction("Repeat Test",
     [this, ckb, file, desc]()
   {
    do_run_test(ckb, file, desc);
   });
   qm->addAction("Show in Folder",
     [this, file]()
   {
    QFileInfo qfi(file);
    QDesktopServices::openUrl( QUrl::fromLocalFile( qfi.absoluteDir().absolutePath() ) );
   });

   QString sf = docus_[ckb]["origin"];
   if(!sf.isEmpty())
   {
    qm->addAction("Show Origin (Script) Folder",
      [sf]()
    {
     desktop_open_folder(sf);
    });
   }

   qm->popup(ckb->mapToGlobal(p));
  });

  connect(ckb, &QCheckBox::toggled, [this, file, ckb, desc](bool b)
  {
   if(b)
   {
    do_run_test(ckb, file, desc);
   }
  });
 }

 main_scroll_area_ = new QScrollArea(this);
 main_form_frame_ = new QFrame(this);
 main_form_frame_->setLayout(main_form_layout_);
 //main_scroll_area_->setWidgetResizable(true);
 main_scroll_area_->setWidget(main_form_frame_);

 main_layout_->addWidget(main_scroll_area_);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
}

void Application_Model_Test_Dialog::desktop_open_folder(QString qs)
{
 if(qs.startsWith('@'))
 {
  qs.replace(0, 1, '/');
  qs.prepend(ARCHIVE_ROOT_FOLDER);
 }

 QString ap;

 QFileInfo qfi(qs);

 if(qfi.isDir())
 {
  if(!qs.endsWith('/'))
  {
   qs += "/";
   qfi = QFileInfo(qs);
  }
  ap = qfi.absolutePath();
 }
 else
   ap = qfi.absoluteDir().absolutePath();

 QDesktopServices::openUrl(QUrl::fromLocalFile(ap));
}

void Application_Model_Test_Dialog::do_run_test(QCheckBox* ckb, QString file, QString desc)
{
 ckb->setCheckState(Qt::PartiallyChecked);
 //qDebug() << file;
 apptm_->run_kph_test(file, [this, ckb, desc, file]
 {
  check_test_result(desc, ckb, file);
 },  [this, ckb]
 {
  QString about = "The test did not finish running (note: this does not"
    " mean it failed).  Check that TCP is active in the main application.";
  QMessageBox qmb;
  qmb.setText(about);
  qmb.addButton("Ok", QMessageBox::NoRole);
  qmb.exec();
  ckb->setCheckState(Qt::Unchecked);
 });
}

Application_Model_Test_Dialog::~Application_Model_Test_Dialog()
{

}



void Application_Model_Test_Dialog::check_test_result(QString desc,
  QCheckBox* ckb, QString file)
{
 QString ask = QString("Test %1: Pass or Fail?").arg(desc);
 QMessageBox qmb;
 qmb.setText(ask);
 qmb.setIcon(QMessageBox::Question);
 qmb.setWindowTitle("Test Returned");
 QAbstractButton* yes = qmb.addButton("Pass", QMessageBox::YesRole);
 qmb.addButton("Fail", QMessageBox::NoRole);

 qmb.exec();
 if(qmb.clickedButton() == yes)
   set_result_yes(ckb, file);
 else
   set_result_no(ckb, file);
}

void Application_Model_Test_Dialog::set_result_yes(QCheckBox* ckb, QString file)
{
 QString ind = QString("QCheckBox::indicator:checked"
   "{image: url(%1);width:24px;height: 20px;}").arg(DEFAULT_ICON_FOLDER "/yes.png");
 ckb->setCheckState(Qt::Checked);
 ckb->setStyleSheet(ind);
 results_[file] = ind;
}

void Application_Model_Test_Dialog::set_result_no(QCheckBox* ckb, QString file)
{
 QString ind = QString("QCheckBox::indicator:checked"
   "{image: url(%1);width:15px;height: 15px;}").arg(DEFAULT_ICON_FOLDER "/no.png");
 ckb->setCheckState(Qt::Checked);
 ckb->setStyleSheet(ind);
 results_[file] = ind;
}

void Application_Model_Test_Dialog::toggle_result(QCheckBox* ckb, QString file)
{
 if(results_[file].endsWith("no.png"))
   set_result_yes(ckb, file);
 else
   set_result_no(ckb, file);
}
