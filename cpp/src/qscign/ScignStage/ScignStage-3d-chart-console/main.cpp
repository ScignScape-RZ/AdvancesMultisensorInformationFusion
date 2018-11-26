
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include <QApplication>

#include <QBar3DSeries>
#include <Q3DBars>

using namespace QtDataVisualization;


int main(int argc, char **argv)
{
// QGuiApplication app(argc, argv);

 QApplication qapp(argc, argv);

// Q3DBars bars;
// bars.setFlags(bars.flags() ^ Qt::FramelessWindowHint);
// bars.rowAxis()->setRange(0, 4);
// bars.columnAxis()->setRange(0, 4);
// QBar3DSeries *series = new QBar3DSeries;
// QBarDataRow *data = new QBarDataRow;
// *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
// series->dataProxy()->addRow(data);
// bars.addSeries(series);
// bars.show();

// return app.exec();

 ScignStage_3d_Chart_Dialog dlg (nullptr);
 dlg.show();
 return qapp.exec();
}
