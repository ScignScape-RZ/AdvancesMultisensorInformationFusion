
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

#include "styles.h"


//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "textio.h"


USING_KANS(TextIO)

Application_Model_Test_Dialog::Application_Model_Test_Dialog(
  QMap<QString, QString>&& tests, QWidget* parent)
  : QDialog(parent), tests_(tests)
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
  QCheckBox* ckb = new QCheckBox(it.value(), this);
  main_form_layout_->addRow(it.key(), ckb);

 }



 main_layout_->addLayout(main_form_layout_);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
}

Application_Model_Test_Dialog::~Application_Model_Test_Dialog()
{

}

