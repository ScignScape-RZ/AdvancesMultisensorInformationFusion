
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
#include <QFileDialog>

#include "styles.h"

#include "application-model/application-test-model.h"

#include "kauvir-phaon/kph-command-package.h"

USING_KANS(Phaon)


#include "textio.h"
USING_KANS(TextIO)

Application_Model_Test_Dialog::Application_Model_Test_Dialog(
  Application_Test_Model* apptm,
  QMap<QString, QString>&& tests, QWidget* parent)
  : QDialog(parent), tests_(tests), apptm_(apptm), last_ckb_(nullptr)
{
 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");

 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);

 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

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
   qm->addAction("Save Results",
     [this]()
   {
    save_results();
   });
   qm->addAction("Toggle Test Result",
     [this, ckb, file]()
   {
    toggle_result(ckb, file);
   });
   qm->addAction("Mark Passed",
     [this, ckb, file]()
   {
    last_ckb_ = ckb;
    set_result_yes(ckb, file);
   });
   qm->addAction("Mark Failed",
     [this, ckb, file]()
   {
    last_ckb_ = ckb;
    set_result_no(ckb, file);
   });
   qm->addAction("Run or Repeat Test",
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

void Application_Model_Test_Dialog::save_results()
{
 QString text;
 QMapIterator<QString, QString> it(results_);

 while(it.hasNext())
 {
  it.next();
  QString r;
  if(it.value().endsWith("yes.png"))
  {
   r = "Pass";
  }
  else if(it.value().endsWith("no.png"))
  {
   r = "Fail";
  }
  else
  {
   r = "Incomplete/Unknown";
  }
  text += QString("%1: %2\n").arg(it.key()).arg(r);
 }

 QString fn = QFileDialog::getSaveFileName(this, "Save File",
      ARCHIVE_ROOT_FOLDER,
      "Text files (*.txt)");
 if(!fn.isEmpty())
 {
  save_file(fn, text);
 }
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
 QString icon = DEFAULT_ICON_FOLDER "/yes.png";
 QString ind = QString("QCheckBox::indicator:checked"
   "{image: url(%1);width:24px;height: 20px;}").arg(icon);

 {
  const QSignalBlocker blocker(ckb);
  ckb->setCheckState(Qt::Checked);
  ckb->setStyleSheet(ind);
 }

 results_[file] = icon;
}

void Application_Model_Test_Dialog::set_result_no(QCheckBox* ckb, QString file)
{
 QString icon = DEFAULT_ICON_FOLDER "/no.png";
 QString ind = QString("QCheckBox::indicator:checked"
   "{image: url(%1);width:15px;height: 15px;}").arg(icon);

 {
  const QSignalBlocker blocker(ckb);
  ckb->setCheckState(Qt::Checked);
  ckb->setStyleSheet(ind);
 }

 results_[file] = icon;
}

void Application_Model_Test_Dialog::toggle_result(QCheckBox* ckb, QString file)
{
 if(results_[file].endsWith("no.png"))
   set_result_yes(ckb, file);
 else
   set_result_no(ckb, file);
}
