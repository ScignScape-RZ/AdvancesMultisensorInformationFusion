
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#include "ScignStage-2d-chart-dialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QDirIterator>
#include <QGroupBox>


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QMenu>
#include <QScrollBar>

#include <QDebug>

#include "styles.h"


#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include "textio.h"


USING_KANS(TextIO)

ScignStage_2d_Chart_Dialog::ScignStage_2d_Chart_Dialog(Test_Series* ts,
  int fres, int tres, QWidget* parent)
 : QDialog(parent), last_selected_item_(nullptr), current_z_value_(1)
{

 button_box_ = new QDialogButtonBox(this);

 //?url_label_ = new QLabel(this);
  //?url_label_->setText(url);

// name_qle_ = new QLineEdit(this);

 button_ok_ = new QPushButton("OK");
 //? button_proceed_ = new QPushButton("Proceed");
 button_cancel_ = new QPushButton("Close");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 //?button_proceed_->setDefault(false);
 //?button_proceed_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 //?button_ok_->setEnabled(false);

 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);
 //?button_box_->addButton(button_proceed_, QDialogButtonBox::ApplyRole);
 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);


 //?connect(button_proceed_, SIGNAL(clicked()), this, SLOT(proceed()));
 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout();

 int max_w = 900 * (1 + (fres / 30));
 int max_h = 900 * (1 + (tres / 30));

 cell_w_ = max_w / fres;
 cell_h_ = max_h / tres;

 fres_ = fres;
 tres_ = tres;


 // //  adjust so maxes are multiples of cell dimensions
 max_w = cell_w_ * fres;
 max_h = cell_h_ * tres;

 main_scene_ = new QGraphicsScene;

 QPen grey_pen = QPen(QColor(180,180,190));
 grey_pen.setWidth(2);

 QPen red_pen = QPen(QColor(190,80,20));
 QPen brown_pen = QPen(QColor(130,80,20));

 QPen blue_pen = QPen(QColor(130,80,220));
 blue_pen.setWidth(2);
 QPen yellow_pen = QPen(QColor(220,180,50,190));
 yellow_pen.setWidth(2);
 blue_pen.setDashPattern({1,4,3,4});

 main_scene_->addLine(-50, -50, max_w + 50, -50, blue_pen);
 main_scene_->addLine(-50, -50, -50, max_h + 50, blue_pen);
 main_scene_->addLine(max_w + 50, -50, max_w + 50, max_h + 50, blue_pen);
 main_scene_->addLine(-50, max_h + 50, max_w + 50, max_h + 50, blue_pen);

 main_scene_->addLine(-50, -50, max_w + 50, -50, yellow_pen);
 main_scene_->addLine(-50, -50, -50, max_h + 50, yellow_pen);
 main_scene_->addLine(max_w + 50, -50, max_w + 50, max_h + 50, yellow_pen);
 main_scene_->addLine(-50, max_h + 50, max_w + 50, max_h + 50, yellow_pen);

 //grey_pen.setWidth(2);

 double flow_min, flow_cell_span, temperature_min, temperature_cell_span;

 ts->get_cell_coords(fres, tres, flow_min,
   flow_cell_span, temperature_min, temperature_cell_span);

 for(int i = 0; i <= fres; ++i)
 {
  main_scene_->addLine(i * cell_w_, 0, i * cell_w_, max_h, grey_pen);

  QGraphicsSimpleTextItem* qgsti = main_scene_->addSimpleText(QString::number(i));
  qgsti->setPen(brown_pen);
  if(i < 10)
    qgsti->setX(i * cell_w_ - 4);
  else
    qgsti->setX(i * cell_w_ - 8);
  qgsti->setY(-15);

  QGraphicsSimpleTextItem* qgsti1 = main_scene_->addSimpleText(
    QString::number(flow_min + (i * flow_cell_span)).leftJustified(5,
    '_', true));
  qgsti1->setPen(red_pen);
  qgsti1->setY(-30);
  qgsti1->setX(i * cell_w_ - 12);

  QGraphicsSimpleTextItem* qgstib = main_scene_->addSimpleText(QString::number(i));
  qgstib->setPen(brown_pen);
  if(i < 10)
    qgstib->setX(i * cell_w_ - 4);
  else
    qgstib->setX(i * cell_w_ - 8);
  qgstib->setY(max_h + 15);

  QGraphicsSimpleTextItem* qgstib1 = main_scene_->addSimpleText(
    QString::number(flow_min + (i * flow_cell_span)).leftJustified(5,
    '_', true));
  qgstib1->setPen(red_pen);
  qgstib1->setY(max_h + 30);
  qgstib1->setX(i * cell_w_ - 12);

 }

 for(int j = 0; j <= tres; ++j)
 {
  main_scene_->addLine(0, j * cell_h_, max_w, j * cell_h_, grey_pen);

  QGraphicsSimpleTextItem* qgsti = main_scene_->addSimpleText(QString::number(j));
  qgsti->setPen(brown_pen);
  qgsti->setX(-25);
  qgsti->setY(j * cell_h_ - 7);

  QGraphicsSimpleTextItem* qgsti1 = main_scene_->addSimpleText(
    QString::number(temperature_min + (j * temperature_cell_span)).leftJustified(5,
    '0', true));
  qgsti1->setPen(red_pen);
  qgsti1->setX(-40);
  qgsti1->setY(j * cell_h_ + 4);

  QGraphicsSimpleTextItem* qgstir = main_scene_->addSimpleText(QString::number(j));
  qgstir->setPen(brown_pen);
  qgstir->setX(max_w + 15);
  qgstir->setY(j * cell_h_ - 7);

  QGraphicsSimpleTextItem* qgstir1 = main_scene_->addSimpleText(
    QString::number(temperature_min + (j * temperature_cell_span)).leftJustified(5,
    '0', true));
  qgstir1->setPen(red_pen);
  qgstir1->setX(max_w + 15);
  qgstir1->setY(j * cell_h_ + 4);


 }

 QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>> qm;
 ts->cells_to_qmap(fres, tres, qm);


 for(int i = 0; i <= fres; ++i)
 {
  for(int j = 0; j <= tres; ++j)
  {
   //int rank = 0;

   //QStringList brcodes = {"b", "r", "g", "bg", "rg"};

   for(QPair<Cell_Info*, double> pr : qm.value({i, j}, {}))
   {

    int c = pr.first->fmacro;
    int r = pr.first->tmacro;
    double cmi = pr.first->fmicro;
    double rmi = pr.first->tmicro;

    double cc = (double(c) + cmi) * cell_w_;
    double rr = (double(r) + rmi) * cell_h_;

    qreal rectw = qMin(cell_w_ / 5, 10);
    qreal recth = qMin(cell_h_ / 5, 10);

    int col = (pr.second * 225) + 30;

//    int red = brcodes[rank].contains('r')? 255 : col;
//    int green = brcodes[rank].contains('g')? 255 : col;
//    int blue = brcodes[rank].contains('b')? 255 : col;

//    if(rank < brcodes.size() - 1)
//     ++rank;

    QColor clr1 = QColor(col, 255 - col, 0, 200);
    QColor clr2 = QColor(90, 90, 255, 100);

    QPen qpen(clr2);
    qpen.setWidth(6);

    QBrush qbr(clr1);

    QGraphicsRectItem* qgri = main_scene_->addRect(cc - rectw, rr - recth, rectw*2, recth*2,
      qpen, qbr);

    QRectF qrf = qgri->rect();
    qgri->setData(2, qVariantFromValue<QRectF>(qrf));
    qgri->setData(3, (quint8) Item_States::Normal);

    qgri->setFlag(QGraphicsItem::ItemIsSelectable);

    sample_map_[pr.first->sample] = qgri;

    if(pr.first->sample->index() == 1)
    {
     qDebug() << (quint64) qgri;
    }
    //items_by_grid_pos_.insertMulti({i,j}, {qgri->rect(),qgri});

    QVariant qvar = QVariant::fromValue((void*) pr.first->sample);
    qgri->setData(1, qvar);
   }
  }
 }

 connect(main_scene_, &QGraphicsScene::selectionChanged,
  [this]
 {
  QList<QGraphicsItem*> sis = main_scene_->selectedItems();
  if(sis.size() == 1)
  {
   QGraphicsItem* qgi = sis.first();
   Test_Sample* samp = (Test_Sample*) qgi->data(1).value<void*>();//sample_map_.value(qgi);
   if(samp)
   {
    QGraphicsRectItem* qgri = qgraphicsitem_cast<QGraphicsRectItem*>(qgi);
    highlight(qgri);

    qDebug() << QString("%1: %2 %3 %4").arg(samp->index())
      .arg(samp->flow().getDouble())  .arg(samp->temperature_adj())
      .arg(samp->oxy());
    Q_EMIT(sample_selected(this, samp));
   }
  }
 });


 main_view_ = new QGraphicsView(main_scene_);

 main_view_->setContextMenuPolicy(Qt::CustomContextMenu);
 connect(main_view_, &QGraphicsView::customContextMenuRequested,
   [this, fres, tres](const QPoint& qp)
 {
  QPointF qpf = main_view_->mapToScene(qp);
  qDebug() << qpf;

  int f = qpf.x()/cell_w_;
  int t = qpf.y()/cell_h_;

  QMenu* qm = new QMenu(this);
  qm->addAction("Scroll to Top Left",
    [this]()
  {
   main_view_->centerOn(0, 0);
  });

  qm->addAction("Contract Nearby Items (1 cell)",
    [this, f, t]()
  {
   contract_items(f, t, 1);
  });
  qm->addAction("Contract Nearby Items (2x2 cells)",
    [this, f, t]()
  {
   contract_items(f, t, 2);
  });
  qm->addAction("Contract Nearby Items (2xAll cells)",
    [this, f, t, fres]()
  {
   contract_items(0, t, fres, 2);
  });
  qm->addAction("Contract Nearby Items (4x4 cells)",
    [this, f, t]()
  {
   contract_items(f-1, t-1, 4);
  });
  qm->addAction("Contract Nearby Items (8x8 cells)",
    [this, f, t]()
  {
   contract_items(f-2, t-2, 8);
  });
  qm->addAction("Contract (All cells)",
    [this, f, t, fres, tres]()
  {
   contract_items(0, 0, fres, tres);
  });

  qm->addAction("Uncontract Nearby Items (1 cell)",
    [this, f, t]()
  {
   uncontract_items(f, t, 1);
  });
  qm->addAction("Uncontract Nearby Items (2x2 cells)",
    [this, f, t]()
  {
   uncontract_items(f, t, 2);
  });
  qm->addAction("Uncontract Nearby Items (2xAll cells)",
    [this, f, t, fres]()
  {
   uncontract_items(0, t, fres, 2);
  });
  qm->addAction("Uncontract Nearby Items (4x4 cells)",
    [this, f, t]()
  {
   uncontract_items(f-1, t-1, 4);
  });
  qm->addAction("Uncontract Nearby Items (8x8 cells)",
    [this, f, t]()
  {
   uncontract_items(f-2, t-2, 8);
  });
  qm->addAction("Uncontract (All cells)",
    [this, f, t, fres, tres]()
  {
   uncontract_items(0, 0, fres, tres);
  });

  qm->addAction("Highlight Oxygen = 93",
    [this]()
  {
   highlight_items_by_oxy(93);
  });
  qm->addAction("Highlight Oxygen = 90",
    [this]()
  {
   highlight_items_by_oxy(90);
  });
  qm->addAction("Highlight Oxygen = 87",
    [this]()
  {
   highlight_items_by_oxy(87);
  });
  qm->addAction("Highlight Oxygen = 80",
    [this]()
  {
   highlight_items_by_oxy(80);
  });


  QPoint g = main_view_->mapToGlobal(qp);
  qm->popup(g);
 });


 main_layout_->addWidget(main_view_);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);

 //fore_panel_
}


void ScignStage_2d_Chart_Dialog::uncontract_items(quint8 f, quint8 t)
{
// if(contracteds_.count({f,t}) == 0)
//   return;

 QVector<QGraphicsRectItem*>* vs = contracteds_.value({f,t});

 if(!vs)
   return;

 for(QGraphicsRectItem* qgri: *vs)
 {
  QRectF qrf = qgri->data(2).value<QRectF>();
  uncontract_graphic(qgri, qrf);
 }
 contracteds_.remove({f,t});
 delete vs;
}

void ScignStage_2d_Chart_Dialog::highlight_items_by_oxy(quint8 oxy)
{
 contract_items(0, 0, fres_, tres_);

 QMapIterator<Test_Sample*, QGraphicsItem*> it(sample_map_);
 while(it.hasNext())
 {
  it.next();
  Test_Sample* samp = it.key();
  QGraphicsItem* qgi = it.value();

  if(QGraphicsRectItem* qgri = qgraphicsitem_cast<QGraphicsRectItem*>(qgi))
  {
   if(samp->oxy() == oxy)
   {
    QRectF qrf = qgri->data(2).value<QRectF>();
    uncontract_graphic(qgri, qrf);
    QPen pen = qgri->pen();
    pen.setColor(QColor({0, 145,185,200}));
    qgri->setPen(pen);

    Item_States ist = Item_States::Highlight_Oxy;

    qgri->setData(3, (quint8) ist);

   }
  }
 }
 main_scene_->update();
 main_view_->update();
}

void ScignStage_2d_Chart_Dialog::uncontract_graphic(QGraphicsRectItem* qgri, QRectF& qrf)
{
 Item_States ist = (Item_States) qgri->data(3).value<quint8>();

 switch(ist)
 {
 case Item_States::Normal:
 case Item_States::Highlight:
 case Item_States::Highlight_Oxy:
     return; // already uncontracted

 case Item_States::Contracted:
  ist = Item_States::Normal; break;
 case Item_States::Highlight_Contracted:
  ist = Item_States::Highlight; break;
 case Item_States::Highlight_Oxy_Contracted:
  ist = Item_States::Highlight_Oxy; break;
 }

 qgri->setData(3, (quint8) ist);

 QPen pen = qgri->pen();

// if(pen.width() == 6)
//   return; // already uncontracted
// if(pen.width() == 10)
//   return; // already uncontracted

 if(pen.width() == 5)
   pen.setWidth(10); // selected
 else
   pen.setWidth(6);

 qgri->setPen(pen);
 qgri->setRect(qrf);

 qgri->update();
}

void ScignStage_2d_Chart_Dialog::contract_graphic(QGraphicsRectItem* qgri)
{
 Item_States ist = (Item_States) qgri->data(3).value<quint8>();

 switch(ist)
 {
 case Item_States::Contracted:
 case Item_States::Highlight_Contracted:
 case Item_States::Highlight_Oxy_Contracted:
   return; // already contracted

 case Item_States::Normal: ist = Item_States::Contracted; break;
 case Item_States::Highlight: ist = Item_States::Highlight_Contracted; break;
 case Item_States::Highlight_Oxy: ist = Item_States::Highlight_Oxy_Contracted; break;
 }

 qgri->setData(3, (quint8) ist);

 QPen pen = qgri->pen();

// if(pen.width() == 1)
//   return; // already contracted
// if(pen.width() == 5)
//   return; // already contracted

 if(pen.width() == 10)
   pen.setWidth(5); // selected
 else
   pen.setWidth(1);
 qgri->setPen(pen);

 QRectF qrf = qgri->rect();

 //contracteds_.insertMulti({f,t}, {qgri->rect(),qgri});

 QRectF qrfa = qrf.adjusted(qrf.width()/3, qrf.height()/3,
   -qrf.width()/3, -qrf.height()/3);
 qgri->setRect(qrfa);
 qgri->update();
}


void ScignStage_2d_Chart_Dialog::contract_items(quint8 f, quint8 t)
{
 QVector<QGraphicsRectItem*>* qv = contracteds_.value({f,t});

 if(qv)
 {
  for(QGraphicsRectItem* qgri : *qv)
  {
   contract_graphic(qgri);
  }
  return;
 }


 QList<QGraphicsItem*> items = main_scene_->items(f*cell_w_, t*cell_h_,
    cell_w_, cell_h_, Qt::IntersectsItemShape, Qt::DescendingOrder);

 qv = new QVector<QGraphicsRectItem*>;//(items.toVector());

 for(QGraphicsItem* qgi: items)
 {
  if(QGraphicsRectItem* qgri = qgraphicsitem_cast<QGraphicsRectItem*>(qgi))
  {
   qv->push_back(qgri);
   contract_graphic(qgri);
  }
 }

 contracteds_[{f,t}] = qv;

#ifdef HIDE
 QList<QPair<QRectF, QGraphicsRectItem*>> vs = items_by_grid_pos_.values({f,t});

 contraceteds_[{f,t}] = vs.size();

 for(QPair<QRectF, QGraphicsItem*> pr: vs)
 {
  if(QGraphicsRectItem* qgri = qgraphicsitem_cast<QGraphicsRectItem*>(pr.second))
  {
   QPen pen = qgri->pen();
   if(pen.width() == 10)
     pen.setWidth(5); // selected
   else
     pen.setWidth(1);
   qgri->setPen(pen);

   QRectF qrf = qgri->rect();

   QRectF qrfa = qrf.adjusted(qrf.width()/3, qrf.height()/3,
     -qrf.width()/3, -qrf.height()/3);
   qgri->setRect(qrfa);
  }
 }
#endif// HIDE
}

void ScignStage_2d_Chart_Dialog::contract_items(qint16 f, qint16 t, quint8 frange,
  quint8 trange)
{
 if(f < 0)
   f = 0;
 if(t < 0)
   t = 0;

 if(trange == 0)
   trange = frange;

 for(quint8 i = f; i < f + frange; ++i)
 {
  for(quint8 j = t; j < t + trange; ++j)
  {
   contract_items(i, j);
  }
 }
 main_scene_->update();
 main_view_->update();
}

void ScignStage_2d_Chart_Dialog::uncontract_items(qint16 f, qint16 t,
  quint8 frange, quint8 trange)
{
 if(f < 0)
   f = 0;
 if(t < 0)
   t = 0;

 if(trange == 0)
   trange = frange;

 for(quint8 i = f; i < f + frange; ++i)
 {
  for(quint8 j = t; j < t + frange; ++j)
  {
   uncontract_items(i, j);
  }
 }
 main_scene_->update();
 main_view_->update();
}


void ScignStage_2d_Chart_Dialog::external_highlight_selected_sample(QWidget* qw, Test_Sample* samp)
{
 if(this != qw)
 {
  highlight_selected_sample(samp);
 }

}

void ScignStage_2d_Chart_Dialog::highlight(QGraphicsRectItem* qgri)
{
 if(last_selected_item_)
 {
  last_selected_item_->setPen(last_pen_);
 }

 if(qgri)
 {
  last_selected_item_ = qgri;
  last_pen_ = qgri->pen();
  QPen pen;
  if(last_pen_.width() == 1)
    pen.setWidth(5);
  else
    pen.setWidth(10);
  pen.setColor(QColor(255, 255, 0, 105));
  qgri->setPen(pen);
  qgri->setZValue(current_z_value_);
  qgri->ensureVisible();
  current_z_value_ += 0.1f;
 }
}

void ScignStage_2d_Chart_Dialog::highlight_selected_sample(Test_Sample* samp)
{
 QGraphicsRectItem* qgri = qgraphicsitem_cast<QGraphicsRectItem*>
   (sample_map_.value(samp));

 highlight(qgri);
}

ScignStage_2d_Chart_Dialog::~ScignStage_2d_Chart_Dialog()
{

}

