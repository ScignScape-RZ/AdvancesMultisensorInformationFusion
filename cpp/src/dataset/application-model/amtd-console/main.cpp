
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

 Application_Model_Test_Dialog dlg(&apptm, {{

   {"Expand Sample", DEFAULT_KPH_FOLDER "/dataset/raw/expand-sample.kph"},

   {"Copy Flow Ranks", DEFAULT_KPH_FOLDER "/dataset/raw/copy-flow-column-ranks.kph"},
   {"Copy Flow Values", DEFAULT_KPH_FOLDER "/dataset/raw/copy-flow-column-values.kph"},

   {"Copy Temperature Ranks", DEFAULT_KPH_FOLDER "/dataset/raw/copy-temperature-column-ranks.kph"},
   {"Copy Temperature Values", DEFAULT_KPH_FOLDER "/dataset/raw/copy-temperature-column-values.kph"},

   {"Copy Oxygen Ranks", DEFAULT_KPH_FOLDER "/dataset/raw/copy-oxy-column-ranks.kph"},
   {"Copy Oxygen Values", DEFAULT_KPH_FOLDER "/dataset/raw/copy-oxy-column-values.kph"},

   {"Show 2d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-3x3.kph"},
   {"Show 2d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-12x12.kph"},
   {"Show 2d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-25x25.kph"},
   {"Show 2d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-2-35x75.kph"},

   {"Hide 2d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-2-3x3.kph"},
   {"Hide 2d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-2-12x12.kph"},
   {"Hide 2d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-2-25x25.kph"},
   {"Hide 2d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-2-35x75.kph"},


   {"Show 3d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-3x3.kph"},
   {"Show 3d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-12x12.kph"},
   {"Show 3d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-25x25.kph"},
   {"Show 3d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/show-graphic-3-35x75.kph"},

   {"Hide 3d Graphic (3x3)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-3-3x3.kph"},
   {"Hide 3d Graphic (12x12)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-3-12x12.kph"},
   {"Hide 3d Graphic (25x25)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-3-25x25.kph"},
   {"Hide 3d Graphic (35x75)", DEFAULT_KPH_FOLDER "/dataset/raw/hide-graphic-3-35x75.kph"},

   }}, nullptr);

 dlg.show();

 return qapp.exec();
}
