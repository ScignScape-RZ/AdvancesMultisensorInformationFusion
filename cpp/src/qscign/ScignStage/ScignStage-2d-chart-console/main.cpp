
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

#include <QApplication>

#include <QSurface3DSeries>
#include <Q3DSurface>

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

 ScignStage_2d_Chart_Dialog dlg(&ts, 25, 25, 1.0f/13, nullptr);

 dlg.show();
 return qapp.exec();
}
