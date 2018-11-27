
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include <QApplication>

#include <QSurface3DSeries>
#include <Q3DSurface>

#include "dsmain/test-sample.h"

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


 QVector<Test_Sample*> ts;
 Test_Sample::read_samples_from_file(DATA_FOLDER "/t1.txt", ts);

 QApplication qapp(argc, argv);

 ScignStage_3d_Chart_Dialog dlg(&ts, DATA_FOLDER "/t21.txt", nullptr);
 dlg.show();
 return qapp.exec();
}
