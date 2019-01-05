
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

#include "ScignStage-tree-table/scignstage-tree-table-dialog.h"


#include <QApplication>

#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include "kans.h"

#include <QThread>


USING_KANS(DSM)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);

 qapp.setWindowIcon(QIcon(DEFAULT_ICON_FOLDER "/app-icon.svg"));


 Test_Series ts;
 ts.parse_data(DATA_FOLDER "/t1.txt");

 ts.init_cells(25, 25);

 ts.init_ranks();

 ScignStage_2d_Chart_Dialog dlg2d(&ts, 25, 25, nullptr);

 dlg2d.show();

 ScignStage_Tree_Table_Dialog dlg (nullptr, &ts);
 dlg.show();

 QApplication::connect(&dlg2d, SIGNAL(sample_selected(Test_Sample*)),
   &dlg, SLOT(browse_to_selected_sample(Test_Sample*)));

 QApplication::connect(&dlg, SIGNAL(sample_highlighted(Test_Sample*)),
   &dlg2d, SLOT(highlight_selected_sample(Test_Sample*)));


 return qapp.exec();
}
