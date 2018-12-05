
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-model-test-dialog/application-model-test-dialog.h"

#include <QApplication>

//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "kans.h"

#include <QThread>


USING_KANS(DSM)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);


 //  QCheckBox* ckb = new QCheckBox(DEFAULT_KPH_FOLDER "/t1.txt", this);
 //  main_form_layout_->addRow("Test 1", ckb);

 Application_Model_Test_Dialog dlg({{
   {"Test 1", DEFAULT_KPH_FOLDER "/t1.txt"}
   }}, nullptr);

 dlg.show();

 return qapp.exec();
}
