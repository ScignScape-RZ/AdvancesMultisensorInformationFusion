
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "config-dialog.h"

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

#include <QMessageBox>
#include <QDebug>

#include <QHeaderView>



Config_Dialog::Config_Dialog(QWidget* parent)
  : QDialog(parent)
{

 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");
 button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_proceed_->setDefault(false);
 button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

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

 main_grid_layout_ = new QGridLayout;

 ss3d_check_box_ = new QCheckBox("Use 3d graphics", this);
 main_grid_layout_->addWidget(ss3d_check_box_, 0, 0);

 kph_check_box_ = new QCheckBox("Use Kauvir/Phaon and TCP (for tests)", this);
 main_grid_layout_->addWidget(kph_check_box_, 0, 1, 1, 2);

 xpdf_check_box_ = new QCheckBox("Use XPDF", this);
 main_grid_layout_->addWidget(xpdf_check_box_, 1, 0, 2, 2, Qt::AlignRight);

 xpdf_qt_libs_check_box_ = new QCheckBox("Qt PNG/FreeType libraries", this);
 main_grid_layout_->addWidget(xpdf_qt_libs_check_box_, 1, 2);

 xpdf_system_libs_check_box_ = new QCheckBox("System PNG/FreeType libraries", this);
 main_grid_layout_->addWidget(xpdf_system_libs_check_box_, 2, 2);

 xpdf_qt_libs_check_box_->setEnabled(false);
 xpdf_system_libs_check_box_->setEnabled(false);

 connect(xpdf_check_box_, &QCheckBox::toggled, [this](bool b)
 {
  xpdf_qt_libs_check_box_->setEnabled(b);
  xpdf_system_libs_check_box_->setEnabled(b);
  if(b)
  {
   QString ac = get_apply_code();
   if(ac.contains('s') || ac.contains('q'))
     return;
   xpdf_qt_libs_check_box_->setChecked(true);
  }
 });

 main_layout_->addLayout(main_grid_layout_);


 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

}

QString Config_Dialog::get_apply_code()
{
 QString result;
 if(xpdf_check_box_->isChecked())
   result += "x";
 if(xpdf_qt_libs_check_box_->isChecked())
   result += "q";
 if(xpdf_system_libs_check_box_->isChecked())
   result += "s";
 if(kph_check_box_->isChecked())
   result += "k";
 if(ss3d_check_box_->isChecked())
   result += "3";
 return result;
}

Config_Dialog::~Config_Dialog()
{

}

void Config_Dialog::proceed()
{
 //Q_EMIT(accepted(this));
}

void Config_Dialog::cancel()
{
 Q_EMIT(rejected());
 Q_EMIT(canceled(this));
 Q_EMIT(rejected());
 close();
}

void Config_Dialog::accept()
{
 Q_EMIT(accepted(this));
}
