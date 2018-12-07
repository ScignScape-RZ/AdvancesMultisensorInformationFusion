
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-model-test-dialog/application-model-test-dialog.h"

#include "application-model/application-test-model.h"

#include <QApplication>

//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "kans.h"

#include <QThread>


USING_KANS(DSM)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);

 Application_Test_Model apptm;

 //  QCheckBox* ckb = new QCheckBox(DEFAULT_KPH_FOLDER "/t1.txt", this);
 //  main_form_layout_->addRow("Test 1", ckb);

 Application_Model_Test_Dialog dlg(&apptm, {{

   {"Expand Sample", DEFAULT_KPH_FOLDER "/dataset/raw/expand-sample.kph"},
   {"Copy Flow", DEFAULT_KPH_FOLDER "/dataset/raw/copy-flow-column.kph"},
   {"Copy Temperature", DEFAULT_KPH_FOLDER "/dataset/raw/copy-temperature-column.kph"},
   {"Copy Oxygen", DEFAULT_KPH_FOLDER "/dataset/raw/copy-oxy-column.kph"},

   {"Show 2d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-3x3.kph"},
   {"Show 2d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-12x12.kph"},
   {"Show 2d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-25x25.kph"},
   {"Show 2d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-35x75.kph"},

   {"Show 3d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-3x3.kph"},
   {"Show 3d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-12x12.kph"},
   {"Show 3d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-25x25.kph"},
   {"Show 3d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-35x75.kph"},

   }}, nullptr);

 dlg.show();

 return qapp.exec();
}
