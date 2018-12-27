
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "graphic-dialog-container.h"

#include "defines.h"

#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

#include "ScignStage-tree-table/scignstage-tree-table-dialog.h"

#include <QMessageBox>


#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include <QDebug>


using namespace QtDataVisualization;

Graphic_Dialog_Container::Graphic_Dialog_Container(ScignStage_Tree_Table_Dialog* parent_dialog)
  :  parent_dialog_(parent_dialog)
{

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
#ifdef USING_SCIGNSTAGE_3D

   ScignStage_3d_Chart_Dialog* dlg = new ScignStage_3d_Chart_Dialog(
     parent_dialog_->series(), r, c, parent_dialog_);

   connect(dlg, SIGNAL(sample_selected(QWidget*, Test_Sample*)),
     parent_dialog_, SLOT(browse_to_selected_sample(QWidget*, Test_Sample*)));
   connect(parent_dialog_, SIGNAL(sample_highlighted(Test_Sample*)),
     dlg, SLOT(external_selected(Test_Sample*)));
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

#else
  QMessageBox::critical(nullptr, "3D not Supported",
    "The 3D data visualization components are not including in this build "
    "of the data set application.  Please try using a different build "
    "strategy (like build-quick) to use these components.");
  return;
#endif  //  USING_SCIGNSTAGE_3D
  }
  else
    return;
 }

 parent_dialog_->setWindowFlags(parent_dialog_->windowFlags()
   &(~Qt::WindowStaysOnTopHint));
 parent_dialog_->show();
 graphics_[code]->show();
}

void Graphic_Dialog_Container::handle_graphic_close_requested(quint8 d, quint8 r, quint8 c)
{
 QString code = QString("%1:%2x%3").arg(d).arg(r).arg(c);
 if(QWidget* w = graphics_.value(code))
 {
  w->hide();
 }
}
