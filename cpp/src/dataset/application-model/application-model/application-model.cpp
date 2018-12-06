
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-model.h"

//#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

//#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include "ScignStage-tree-table/ScignStage-tree-table-dialog.h"


//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "kauvir-phaon/kph-command-package.h"


USING_KANS(Phaon)


#include <QDebug>


Application_Model::Application_Model(ScignStage_Tree_Table_Dialog* tree_table_dialog)
  :  tree_table_dialog_(tree_table_dialog)
{

}

void Application_Model::expand_sample(ScignStage_Tree_Table_Dialog* dlg, int index)
{
 dlg->expand_sample(index);
}

void Application_Model::show_graphic(ScignStage_Tree_Table_Dialog* dlg, QString code)
{
 int d = code.left(1).toInt();
 QString qs1 = code.mid(2);
 int index = qs1.indexOf('x');
 int r = qs1.left(index).toInt();
 int c = qs1.mid(index + 1).toInt();
 dlg->reemit_graphic_open_requested(d,r,c);
}

void Application_Model::hide_graphic(ScignStage_Tree_Table_Dialog* dlg, QString code)
{
 int d = code.left(1).toInt();
 QString qs1 = code.mid(2);
 int index = qs1.indexOf('x');
 int r = qs1.left(index).toInt();
 int c = qs1.mid(index + 1).toInt();
 dlg->reemit_graphic_close_requested(d,r,c);
}

Application_Model::~Application_Model() {}
