
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_2D_CHART_DIALOG__H
#define SCIGNSTAGE_2D_CHART_DIALOG__H

#include <QDialog>
#include <QVector>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMap>

class QGraphicsItem;
//class QGraphicsSceneHoverEvent;

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)
KANS_CLASS_DECLARE(DSM ,Test_Series)

USING_KANS(DSM)

//struct Clickable_Graphics_Item : public QGraphicsRectItem
//{
// // Q_DECLARE_OVERRIDE
// Clickable_Graphics_Item();

// void hoverEnterEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
// void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
// void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
//};


class ScignStage_2d_Chart_Dialog : public QDialog
{
 Q_OBJECT

 //Fore_Geometric1D_Panel fore_panel_;
 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QMap<QGraphicsItem*, Test_Sample*> sample_map_;

 QGraphicsItem* last_selected_item_;


public:

 ScignStage_2d_Chart_Dialog(Test_Series* ts,
   int fres, int tres, double olift, QWidget* parent);

 ~ScignStage_2d_Chart_Dialog();

public Q_SLOTS:



};


#endif //  SCIGNSTAGE_2D_CHART_DIALOG__H
