
//          Copyright Nathaniel Christen 2018.
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

#include <QPen>

class QGraphicsRectItem;
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

 QMap<Test_Sample*, QGraphicsItem*> sample_map_;

 QGraphicsRectItem* last_selected_item_;

 QPen last_pen_;

 qreal current_z_value_;

public:

 ScignStage_2d_Chart_Dialog(Test_Series* ts,
   int fres, int tres, QWidget* parent);

 ~ScignStage_2d_Chart_Dialog();

public Q_SLOTS:

 void highlight_selected_sample(Test_Sample* samp);
 void highlight(QGraphicsRectItem* qgri);


Q_SIGNALS:

 void sample_selected(Test_Sample* samp);


};


#endif //  SCIGNSTAGE_2D_CHART_DIALOG__H
