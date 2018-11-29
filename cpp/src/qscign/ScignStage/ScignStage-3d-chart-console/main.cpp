
//          Copyright Nathaniel Christen 2017.
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
// QGuiApplication app(argc, argv);

// Q3DSurface surface;
// surface.setFlags(surface.flags() ^ Qt::FramelessWindowHint);
// QSurfaceDataArray *data = new QSurfaceDataArray;
// QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
// QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;

// *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
// *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
// *data << dataRow1 << dataRow2;

// QSurface3DSeries *series = new QSurface3DSeries;
// series->dataProxy()->resetArray(data);
// surface.addSeries(series);
// surface.show();

// return app.exec();


 QApplication qapp(argc, argv);

 Test_Series ts;
 ts.parse_data(DATA_FOLDER "/t1.txt");

 ts.init_cells(25, 25);
 ts.init_ranks();

 ScignStage_3d_Chart_Dialog dlg3d(&ts, 25, 25, nullptr);


 dlg3d.show();

 ScignStage_Tree_Table_Dialog dlg (nullptr, &ts);

 dlg.show();

// QApplication::connect(&dlg, &ScignStage_Tree_Table_Dialog::sample_highlighted,
//   [&dlg3d](Test_Sample* samp)
// {
//  dlg3d.external_selected(samp);
// });

 QApplication::connect(&dlg, SIGNAL(sample_highlighted(Test_Sample*)),
   &dlg3d, SLOT(external_selected(Test_Sample*)));

// dlg3d.connect(&dlg3d, SIGNAL(sample_selected(Test_Sample*)),
//  &dlg, SLOT(browse_to_selected_sample(Test_Sample*)));


 dlg3d.selected_cb = [&dlg](Test_Sample* samp)
 {
  qDebug() << "samp: " << samp->index();
  dlg.browse_to_selected_sample(samp);
 };

 return qapp.exec();
}
