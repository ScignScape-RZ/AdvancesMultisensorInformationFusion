
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include <QApplication>


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);
 ScignStage_3d_Chart_Dialog dlg (nullptr);
 dlg.show();
 return qapp.exec();
}
