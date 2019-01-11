
//          Copyright Nathaniel Christen 2019.
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
class QComboBox;
class QCheckBox;


class Config_Dialog : public QDialog
{
 Q_OBJECT

 QHBoxLayout* minimize_layout_;

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;

 QGroupBox* os_group_box_;
 QHBoxLayout* os_layout_;
 QComboBox* os_combo_box_;
 QCheckBox* b32_checkbox_;
 QCheckBox* b64_checkbox_;
 QButtonGroup* b3264_;

 QGridLayout* compile_options_grid_layout_;
 QGridLayout* roles_grid_layout_;

 QGroupBox* compile_options_group_box_;
 QGroupBox* roles_group_box_;

 QVBoxLayout* main_layout_;

 QCheckBox* ss3d_check_box_;
 QCheckBox* kph_check_box_;
 QCheckBox* xpdf_check_box_;
 QCheckBox* xpdf_qt_libs_check_box_;
 QCheckBox* xpdf_system_libs_check_box_;

 QCheckBox* gen_test_check_box_;
 QCheckBox* kdmi_check_box_;
 QCheckBox* roic_check_box_;
 QCheckBox* xx_check_box_;

 QButtonGroup* qs_button_group_;
 QButtonGroup* main_button_group_;

 QButtonGroup* roles_button_group_;

 QString last_ac_;

 QPushButton* autofill_button_;

 QPushButton* reset_button_;
 QLabel* reset_button_label_;
 QHBoxLayout* reset_button_layout_;

 std::function<void(QString)> proceed_callback_;
 std::function<void()> reset_callback_;

 QString get_apply_code();
 QString get_role_code();

 void autofill_1();
 void autofill_2(bool ss3d = true, bool kph = false,
   bool xx = false, bool roic = false);
 void autofill_3();
 void autofill_4();
 void autofill_5();
 void autofill_6();

public:

 Config_Dialog(QWidget* parent);
 ~Config_Dialog();

 ACCESSORS(std::function<void(QString)> ,proceed_callback)
 ACCESSORS(std::function<void()> ,reset_callback)

 void register_proceed_completed(QString ac);
 void check_proceed_possible();


Q_SIGNALS:

 void canceled(QDialog*);
 void accepted(QDialog*);
 void proceed_requested(QString);
 void reset_requested();

public Q_SLOTS:

 void accept();
 void cancel();
 void proceed();

};



#endif  // CONFIG_DIALOG__H


