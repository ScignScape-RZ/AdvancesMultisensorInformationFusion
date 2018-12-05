
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef APPLICATION_MODEL_TEST_DIALOG__H
#define APPLICATION_MODEL_TEST_DIALOG__H

#include <QDialog>
#include <QVector>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMap>

class QFormLayout;

#include <functional>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)
KANS_CLASS_DECLARE(DSM ,Test_Series)

USING_KANS(DSM)

class Application_Model_Test_Dialog : public QDialog
{
 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QFormLayout* main_form_layout_;

 QMap<QString, QString> tests_;


public:


 Application_Model_Test_Dialog(QMap<QString, QString>&& tests, QWidget* parent);

 ~Application_Model_Test_Dialog();

Q_SIGNALS:


public Q_SLOTS:


};


#endif //  APPLICATION_MODEL_TEST_DIALOG__H
