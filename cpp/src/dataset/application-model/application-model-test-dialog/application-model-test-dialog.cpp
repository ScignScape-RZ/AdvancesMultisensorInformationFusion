
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

#include <QMessageBox>

#include <QDebug>

#include "styles.h"

#include "application-model/application-test-model.h"

//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

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
  ckb->setTristate();
  main_form_layout_->addRow(desc, ckb);
  connect(ckb, &QCheckBox::toggled, [this, file, ckb, desc](bool b)
  {
   if(b)
   {
    ckb->setCheckState(Qt::PartiallyChecked);

    qDebug() << file;
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
  });
 }



 main_layout_->addLayout(main_form_layout_);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
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
 //qmb.setDetailedText(ask);
 qmb.setWindowTitle("Test Returned");
 QAbstractButton* yes = qmb.addButton("Pass", QMessageBox::YesRole);
 qmb.addButton("Fail", QMessageBox::NoRole);

 qmb.exec();
 if(qmb.clickedButton() == yes)
 {
  QString ind = QString("QCheckBox::indicator:checked"
    "{image: url(%1);width:24px;height: 20px;}").arg(DEFAULT_ICON_FOLDER "/yes.png");
  //ckb->setData(1, ind);
  ckb->setCheckState(Qt::Checked);
  ckb->setStyleSheet(ind);
  results_[file] = ind;
 }
 else
 {
  QString ind = QString("QCheckBox::indicator:checked"
    "{image: url(%1);width:15px;height: 15px;}").arg(DEFAULT_ICON_FOLDER "/no.png");
  //ckb->setData(1, ind);
  ckb->setCheckState(Qt::Checked);
  ckb->setStyleSheet(ind);
  results_[file] = ind;
 }
}
