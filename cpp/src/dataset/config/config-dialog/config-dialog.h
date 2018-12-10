
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef CONFIG_DIALOG__H
#define CONFIG_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>

#include <functional>

#include "accessors.h"
#include "qsns.h"


#include <functional>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)
KANS_CLASS_DECLARE(DSM ,Test_Series)


USING_KANS(DSM)

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QGridLayout;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;

class QCheckBox;


class Config_Dialog : public QDialog
{

 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;


 QGridLayout* main_grid_layout_;
 QVBoxLayout* main_layout_;

 QCheckBox* ss3d_check_box_;
 QCheckBox* kph_check_box_;
 QCheckBox* xpdf_check_box_;
 QCheckBox* xpdf_qt_libs_check_box_;
 QCheckBox* xpdf_system_libs_check_box_;

 QString get_apply_code();

public:

 Config_Dialog(QWidget* parent);

 ~Config_Dialog();


Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);


public Q_SLOTS:

 void accept();
 void cancel();
 void proceed();

};



#endif  // CONFIG_DIALOG__H


