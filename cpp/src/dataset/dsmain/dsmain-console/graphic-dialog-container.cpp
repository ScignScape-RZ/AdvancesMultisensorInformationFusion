
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "graphic-dialog-container.h"

#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include "ScignStage-tree-table/ScignStage-tree-table-dialog.h"


#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include <QDebug>


using namespace QtDataVisualization;

Graphic_Dialog_Container::Graphic_Dialog_Container(ScignStage_Tree_Table_Dialog* parent_dialog)
  :  parent_dialog_(parent_dialog)
//  ,
//     graphic_2d_25x25_(nullptr),
//     graphic_3d_25x25_(nullptr),
//     graphic_2d_110x75_(nullptr),
//     graphic_3d_110x75_(nullptr)
//     graphic_2d_10x10_(nullptr),
//     graphic_3d_10x10_(nullptr)
{
 //oldwf_ = parent_dialog_->windowFlags();
}

Graphic_Dialog_Container::~Graphic_Dialog_Container() {}

void Graphic_Dialog_Container::handle_graphic_open_requested(quint8 d, quint8 r, quint8 c)
{
 QString code = QString("%1:%2x%3").arg(d).arg(r).arg(c);

 if(!graphics_.contains(code))
 {
  parent_dialog_->series()->check_init_cells(r, c);
  if(d == 2)
  {
   ScignStage_2d_Chart_Dialog* dlg = new ScignStage_2d_Chart_Dialog(
     parent_dialog_->series(), r, c, parent_dialog_);
   connect(dlg, SIGNAL(sample_selected(QWidget*, Test_Sample*)),
     parent_dialog_, SLOT(browse_to_selected_sample(QWidget*, Test_Sample*)));
   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
     dlg, SLOT(highlight_selected_sample(Test_Sample*)));
   connect(parent_dialog_, SIGNAL( external_sample_highlighted(QWidget*, Test_Sample*)),
     dlg, SLOT(external_highlight_selected_sample(QWidget*, Test_Sample*)));

   connect(dlg, &QDialog::accepted, [this, dlg]
   {
    dlg->show();
    parent_dialog_->setWindowFlags(
      parent_dialog_->windowFlags() | Qt::WindowStaysOnTopHint);
    parent_dialog_->show();
   });
   connect(dlg, &QDialog::rejected, [this, code]
   {
    parent_dialog_->uncheck_graphic(code);
   });

   graphics_[code] = dlg;
  }
  else if(d == 3)
  {
   ScignStage_3d_Chart_Dialog* dlg = new ScignStage_3d_Chart_Dialog(
     parent_dialog_->series(), r, c, parent_dialog_);
   connect(dlg, SIGNAL(sample_selected(QWidget*, Test_Sample*)),
     parent_dialog_, SLOT(browse_to_selected_sample(QWidget*, Test_Sample*)));
   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
     dlg, SLOT(highlight_selected_sample(Test_Sample*)));
   connect(parent_dialog_, SIGNAL( external_sample_highlighted(QWidget*, Test_Sample*)),
     dlg, SLOT(external_highlight_selected_sample(QWidget*, Test_Sample*)));



   connect(dlg, &QDialog::accepted, [this, dlg]
   {
    dlg->show();
    parent_dialog_->setWindowFlags(
      parent_dialog_->windowFlags() | Qt::WindowStaysOnTopHint);
    parent_dialog_->show();
   });
   connect(dlg, &QDialog::rejected, [this, code]
   {
    parent_dialog_->uncheck_graphic(code);
   });

   graphics_[code] = dlg;
  }
  else
    return;
 }

 parent_dialog_->setWindowFlags(parent_dialog_->windowFlags()
   &(~Qt::WindowStaysOnTopHint));
 parent_dialog_->show();
 graphics_[code]->show();

 // qDebug() << d << r << c;

// quint32 code = (r*1000) + (d*1000000) + c;
// qDebug() << code;

// switch(code)
// {
// case 2110075:
//  if(!graphic_2d_110x75_)
//  {
//   parent_dialog_->series()->check_init_cells(55, 37);

//   graphic_2d_110x75_ = new ScignStage_2d_Chart_Dialog(
//     parent_dialog_->series(), 55, 37, parent_dialog_);

//   connect(graphic_2d_110x75_, SIGNAL(sample_selected(Test_Sample*)),
//     parent_dialog_, SLOT(browse_to_selected_sample(Test_Sample*)));

//   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
//     graphic_2d_110x75_, SLOT(highlight_selected_sample(Test_Sample*)));
//  }
//  graphic_2d_110x75_->show();
//  break;

// case 2025025:
//  if(!graphic_2d_25x25_)
//  {
//   graphic_2d_25x25_ = new ScignStage_2d_Chart_Dialog(
//     parent_dialog_->series(), 25, 25, parent_dialog_);

//   connect(graphic_2d_25x25_, SIGNAL(sample_selected(Test_Sample*)),
//     parent_dialog_, SLOT(browse_to_selected_sample(Test_Sample*)));

//   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
//     graphic_2d_25x25_, SLOT(highlight_selected_sample(Test_Sample*)));
//  }
//  graphic_2d_25x25_->show();
//  break;
// case 3025025:
//  if(!graphic_3d_25x25_)
//  {
//   graphic_3d_25x25_ = new ScignStage_3d_Chart_Dialog(
//     parent_dialog_->series(), 25, 25, parent_dialog_);

//   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
//     graphic_3d_25x25_, SLOT(external_selected(Test_Sample*)));

//   graphic_3d_25x25_->selected_cb = [this](Test_Sample* samp)
//   {
//    qDebug() << "samp: " << samp->index();
//    parent_dialog_->browse_to_selected_sample(samp);
//   };
//  }
//  graphic_3d_25x25_->show();
//  break;
// default:
//  break;
// }

}

void Graphic_Dialog_Container::handle_graphic_close_requested(quint8 d, quint8 r, quint8 c)
{
 QString code = QString("%1:%2x%3").arg(d).arg(r).arg(c);
 if(QWidget* w = graphics_.value(code))
 {
  w->hide();
 }
}
