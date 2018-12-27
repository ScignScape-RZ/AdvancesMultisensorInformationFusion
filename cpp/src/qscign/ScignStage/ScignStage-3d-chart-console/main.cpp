
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include <QApplication>

#include <QSurface3DSeries>
#include <Q3DSurface>

#include "ScignStage-tree-table/scignstage-tree-table-dialog.h"

#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include "kans.h"

#include <QThread>


USING_KANS(DSM)

using namespace QtDataVisualization;


int main(int argc, char **argv)
{

 QApplication qapp(argc, argv);

 Test_Series ts;
 ts.parse_data(DATA_FOLDER "/t1.txt");

 ts.init_cells(25, 25);
 ts.init_ranks();

 ScignStage_3d_Chart_Dialog dlg3d(&ts, 25, 25, nullptr);

 dlg3d.show();
 return qapp.exec();
}
