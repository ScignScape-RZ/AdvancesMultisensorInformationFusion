
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "graphic-dialog-container.h"

#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"
#include "ScignStage-tree-table/ScignStage-tree-table-dialog.h"

#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include <QDebug>

Graphic_Dialog_Container::Graphic_Dialog_Container(ScignStage_Tree_Table_Dialog* parent_dialog)
  :  parent_dialog_(parent_dialog),
     graphic_2d_25x25_(nullptr),
     graphic_3d_25x25_(nullptr),
     graphic_2d_10x10_(nullptr),
     graphic_3d_10x10_(nullptr)
{

}

Graphic_Dialog_Container::~Graphic_Dialog_Container() {}

void Graphic_Dialog_Container::handle_graphic_open_requested(quint8 d, quint8 r, quint8 c)
{
 qDebug() << d << r << c;

 quint32 code = (r*1000) + (d*1000000) + c;
 qDebug() << code;

 switch(code)
 {
 case 2025025:
  if(!graphic_2d_25x25_)
  {
   graphic_2d_25x25_ = new ScignStage_2d_Chart_Dialog(
     parent_dialog_->series(), 25, 25, 0, parent_dialog_);

   connect(graphic_2d_25x25_, SIGNAL(sample_selected(Test_Sample*)),
     parent_dialog_, SLOT(browse_to_selected_sample(Test_Sample*)));

   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
     graphic_2d_25x25_, SLOT(highlight_selected_sample(Test_Sample*)));
  }

  graphic_2d_25x25_->show();
 }

}

void Graphic_Dialog_Container::handle_graphic_close_requested(quint8 d, quint8 r, quint8 c)
{

}
