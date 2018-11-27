
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
  int fres, int tres, double olift, QWidget* parent)
 : QDialog(parent), last_selected_item_(nullptr)
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

 for(int i = 0; i <= fres; ++i)
 {
  scene->addLine(i * cell_w, 0, i * cell_w, max_h);
 }

 for(int j = 0; j <= tres; ++j)
 {
  scene->addLine(0, j * cell_h, max_w, j * cell_h);
 }

 QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>> qm;
 ts->cells_to_qmap(fres, tres, qm);

 for(int i = 0; i <= fres; ++i)
 {
  for(int j = 0; j <= tres; ++j)
  {
   int rank = 0;

   QStringList brcodes = {"b", "r", "g", "bg", "rg"};

   for(QPair<Cell_Info*, double> pr : qm.value({i, j}, {}))
   {

    int c = pr.first->fmacro;
    int r = pr.first->tmacro;
    double cmi = pr.first->fmicro;
    double rmi = pr.first->tmicro;

    double cc = (double(c) + cmi) * cell_w;
    double rr = (double(r) + rmi) * cell_h;

    qreal rectw = cell_w / 4;
    qreal recth = cell_h / 4;

    int col = (pr.second * 225) + 30;

    int red = brcodes[rank].contains('r')? 255 : col;
    int green = brcodes[rank].contains('g')? 255 : col;
    int blue = brcodes[rank].contains('b')? 255 : col;

    if(rank < brcodes.size() - 1)
     ++rank;

    QBrush qbr(QColor(red, green, blue, 200));

    QGraphicsRectItem* qgri = scene->addRect(cc - rectw, rr - recth, rectw*2, recth*2,
      QPen(), qbr);

    qgri->setFlag(QGraphicsItem::ItemIsSelectable);

    sample_map_[qgri] = pr.first->sample;
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
   Test_Sample* samp = sample_map_.value(qgi);
   if(samp)
   {
    qDebug() << QString("%1: %2 %3 %4").arg(samp->index())
      .arg(samp->flow().getDouble())  .arg(samp->temperature_adj())
      .arg(samp->oxy());
   }
  }
 });


 QGraphicsView* view = new QGraphicsView(scene);


 main_layout_->addWidget(view);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
}

ScignStage_2d_Chart_Dialog::~ScignStage_2d_Chart_Dialog()
{

}

