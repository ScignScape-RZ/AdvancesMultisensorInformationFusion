
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
class QGraphicsView;
class QGraphicsScene;

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

 QGraphicsView* main_view_;

 QGraphicsScene* main_scene_;

 int cell_w_;
 int cell_h_;

 int fres_;
 int tres_;


 void contract_items(qint16 f, qint16 t, quint8 frange,
   quint8 trange = 0);
 void contract_items(quint8 f, quint8 t);

 void contract_graphic(QGraphicsRectItem* qgri);
 void uncontract_graphic(QGraphicsRectItem* qgri, QRectF& qrf);

 void uncontract_items(qint16 f, qint16 t, quint8 range, quint8 trange = 0);
 void uncontract_items(quint8 f, quint8 t);

 void highlight_items_by_oxy(quint8 oxy);

 enum class Item_States { Normal = 0,
    Highlight = 1, Contracted = 2, Highlight_Oxy = 4,
    Highlight_Contracted = 3, Highlight_Oxy_Contracted = 6 };

public:

 ScignStage_2d_Chart_Dialog(Test_Series* ts,
   int fres, int tres, QWidget* parent);

 //QMap<QPair<quint8, quint8>, int> contraceteds_;
 QMap<QPair<quint8, quint8>,
   QVector<QGraphicsRectItem*>*> contracteds_;



 ~ScignStage_2d_Chart_Dialog();

public Q_SLOTS:

 void external_highlight_selected_sample(QWidget* qw, Test_Sample* samp);
 void highlight_selected_sample(Test_Sample* samp);
 void highlight(QGraphicsRectItem* qgri);


Q_SIGNALS:

 void sample_selected(QWidget*, Test_Sample* samp);


};


#endif //  SCIGNSTAGE_2D_CHART_DIALOG__H
