
//          Copyright Nathaniel Christen 2017.
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
 button_cancel_ = new QPushButton("Cancel");

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

 int max_w = 800;
 int max_h = 800;

 int cell_w = max_w / fres;
 int cell_h = max_h / tres;

 QGraphicsScene* scene = new QGraphicsScene;

 QPen grey_pen = QPen(QColor(180,180,190));
 grey_pen.setWidth(2);

 QPen red_pen = QPen(QColor(190,80,20));
 QPen brown_pen = QPen(QColor(130,80,20));

 //grey_pen.setWidth(2);

 double flow_min, flow_cell_span, temperature_min, temperature_cell_span;

 ts->get_cell_coords(fres, tres, flow_min,
   flow_cell_span, temperature_min, temperature_cell_span);

 for(int i = 0; i <= fres; ++i)
 {
  scene->addLine(i * cell_w, 0, i * cell_w, max_h, grey_pen);

  QGraphicsSimpleTextItem* qgsti = scene->addSimpleText(QString::number(i));
  qgsti->setPen(brown_pen);
  if(i < 10)
    qgsti->setX(i * cell_w - 4);
  else
    qgsti->setX(i * cell_w - 8);
  qgsti->setY(-15);

  QGraphicsSimpleTextItem* qgsti1 = scene->addSimpleText(
    QString::number(flow_min + (i * flow_cell_span)).leftJustified(5,
    '_', true));
  qgsti1->setPen(red_pen);
  qgsti1->setY(-30);
  qgsti1->setX(i * cell_w - 12);

  QGraphicsSimpleTextItem* qgstib = scene->addSimpleText(QString::number(i));
  qgstib->setPen(brown_pen);
  if(i < 10)
    qgstib->setX(i * cell_w - 4);
  else
    qgstib->setX(i * cell_w - 8);
  qgstib->setY(max_h + 15);

  QGraphicsSimpleTextItem* qgstib1 = scene->addSimpleText(
    QString::number(flow_min + (i * flow_cell_span)).leftJustified(5,
    '_', true));
  qgstib1->setPen(red_pen);
  qgstib1->setY(max_h + 30);
  qgstib1->setX(i * cell_w - 12);

 }

 for(int j = 0; j <= tres; ++j)
 {
  scene->addLine(0, j * cell_h, max_w, j * cell_h, grey_pen);

  QGraphicsSimpleTextItem* qgsti = scene->addSimpleText(QString::number(j));
  qgsti->setPen(brown_pen);
  qgsti->setX(-25);
  qgsti->setY(j * cell_h - 7);

  QGraphicsSimpleTextItem* qgsti1 = scene->addSimpleText(
    QString::number(temperature_min + (j * temperature_cell_span)).leftJustified(5,
    '0', true));
  qgsti1->setPen(red_pen);
  qgsti1->setX(-40);
  qgsti1->setY(j * cell_h + 4);

  QGraphicsSimpleTextItem* qgstir = scene->addSimpleText(QString::number(j));
  qgstir->setPen(brown_pen);
  qgstir->setX(max_w + 15);
  qgstir->setY(j * cell_h - 7);

  QGraphicsSimpleTextItem* qgstir1 = scene->addSimpleText(
    QString::number(temperature_min + (j * temperature_cell_span)).leftJustified(5,
    '0', true));
  qgstir1->setPen(red_pen);
  qgstir1->setX(max_w + 15);
  qgstir1->setY(j * cell_h + 4);


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

    double cc = (double(c) + cmi) * cell_w;
    double rr = (double(r) + rmi) * cell_h;

    qreal rectw = cell_w / 5;
    qreal recth = cell_h / 5;

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

    QGraphicsRectItem* qgri = scene->addRect(cc - rectw, rr - recth, rectw*2, recth*2,
      qpen, qbr);

    qgri->setFlag(QGraphicsItem::ItemIsSelectable);

    sample_map_[pr.first->sample] = qgri;
    QVariant qvar = QVariant::fromValue((void*) pr.first->sample);
    qgri->setData(1, qvar);
   }
  }
 }

 connect(scene, &QGraphicsScene::selectionChanged,
  [this, scene]
 {
  QList<QGraphicsItem*> sis = scene->selectedItems();
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
    Q_EMIT(sample_selected(samp));
   }
  }
 });


 QGraphicsView* view = new QGraphicsView(scene);


 main_layout_->addWidget(view);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
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

