
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#include "ScignStage-3d-chart-dialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QDirIterator>
#include <QGroupBox>

#include <QScatter3DSeries>
#include <Q3DScatter>

#include <QBar3DSeries>
#include <Q3DBars>

#include <QSurface3DSeries>
#include <Q3DSurface>


using namespace QtDataVisualization;

//#include <QtDataVisualization>

#include "styles.h"


#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include "textio.h"


USING_KANS(TextIO)

ScignStage_3d_Chart_Dialog::ScignStage_3d_Chart_Dialog(Test_Series* ts,
  int fres, int tres, double olift, QWidget* parent)
 : QDialog(parent)
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

  Q3DBars* bars = new Q3DBars;
  QWidget* container = QWidget::createWindowContainer(bars);
  //bars->setFlags(bars.flags() ^ Qt::FramelessWindowHint);
  bars->rowAxis()->setRange(0, fres);
  bars->columnAxis()->setRange(0, tres);

  QMap<QPair<int, int>, float> qm;

  ts->cells_to_qmap(fres, tres, qm);

  QBar3DSeries *series = new QBar3DSeries;
  for(int i = 0; i <= fres; ++i)
  {
   QBarDataRow* r = new QBarDataRow;
   for(int j = 0; j <= tres; ++j)
   {
    if(qm.contains({i, j}))
      *r << qm[{i, j}] + olift;
    else
      *r << 0;
   }
   series->dataProxy()->addRow(r);
  }

   QLinearGradient barGradient(0, 0, 1, 100);
   barGradient.setColorAt(1.0, Qt::white);
   barGradient.setColorAt(0.0, Qt::black);

   series->setBaseGradient(barGradient);
   series->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
   series->setMesh(QAbstract3DSeries::MeshCylinder);

//  QVector<QBarDataRow*> rows;
//  for(int i = 0; i < 20; ++i)
//  {
//   QBarDataRow* r = new QBarDataRow;
//   for(int j = 0; j < 10; ++j)
//   {
//    *r << qm.value({j, i}, 0.0f);
//   }
//   rows.push_back(r);
//   series->dataProxy()->addRow(r);
//  }

//  QBarDataRow *data = new QBarDataRow;
//  *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
//  series->dataProxy()->addRow(data);

  bars->addSeries(series);
  bars->show();

  container->setMinimumHeight(300);
  container->setMinimumWidth(500);

 main_layout_->addWidget(container);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
 //fore_panel_
}

ScignStage_3d_Chart_Dialog::~ScignStage_3d_Chart_Dialog()
{

}



//Q3DSurface* surface = new Q3DSurface;
//QWidget* container = QWidget::createWindowContainer(surface);

//QSurfaceDataArray *data = new QSurfaceDataArray;
//QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
//QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;



//// *dataRow1 << QVector3D(0.054f, 0.491f, 0.93f)
////   << QVector3D(10.89f, 0.489f, 0.93f);

//// *dataRow2 << QVector3D(0.0f, 0.0f, 0.0f) << QVector3D(1.0f, 1.2f, 1.0f);

//*dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
//*dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);

//*data << dataRow1 << dataRow2;

//QSurface3DSeries *series = new QSurface3DSeries;
//series->dataProxy()->resetArray(data);
//surface->addSeries(series);
//surface->show();

//container->setMinimumHeight(300);
//container->setMinimumWidth(500);

//for(QString qs : qsl)
//{
// QStringList qsl = qs.simplified().split(' ');
// if(qsl.isEmpty())
//   continue;
// QVector<float>* qv = new QVector<float>;
// for(QString qs : qsl)
// {
//  *qv << qs.toFloat();
// }
// rowsv.push_back(qv);
// if(qv->size() > maxcsz)
//   maxcsz = qv->size();
//}

// Q3DBars graph;
// QBar3DSeries *series = new QBar3DSeries;
//// QLinearGradient barGradient(0, 0, 1, 100);
//// barGradient.setColorAt(1.0, Qt::white);
//// barGradient.setColorAt(0.0, Qt::black);

//// series->setBaseGradient(barGradient);
//// series->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
//// series->setMesh(QAbstract3DSeries::MeshCylinder);


// QBarDataRow *data = new QBarDataRow;
// *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
// series->dataProxy()->addRow(data);

// graph.addSeries(series);
// graph.show();

// Q3DScatter* scatter = new Q3DScatter;
// QWidget* container = QWidget::createWindowContainer(scatter);
// scatter->rowAxis()->setRange(-1, 1);
// scatter->columnAxis()->setRange(-1, 1);
// QScatter3DSeries *series = new QScatter3DSeries;
// QScatterDataArray data;
// data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
// series->dataProxy()->addItems(data);
// scatter->addSeries(series);


// Q3DBars* bars = new Q3DBars;
// QWidget* container = QWidget::createWindowContainer(bars);
// //bars->setFlags(bars.flags() ^ Qt::FramelessWindowHint);
// bars->rowAxis()->setRange(0, 4);
// bars->columnAxis()->setRange(0, 4);
// QBar3DSeries *series = new QBar3DSeries;

//  QLinearGradient barGradient(0, 0, 1, 100);
//  barGradient.setColorAt(1.0, Qt::white);
//  barGradient.setColorAt(0.0, Qt::black);

//  series->setBaseGradient(barGradient);
//  series->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
//  series->setMesh(QAbstract3DSeries::MeshCylinder);


// QBarDataRow *data = new QBarDataRow;
// *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
// series->dataProxy()->addRow(data);
// bars->addSeries(series);
// bars->show();
// scatter->show();

// QMap<QPair<double, int>, int> qm;

// for(Test_Sample* samp : *samples)
// {
//  qm.insert({samp->flow().getDouble(), samp->temperature_adj()}, samp->oxy());
// }

// QMap<QPair<int, int>, double> qm;
// for(Test_Sample* samp : *samples)
// {
//  int ta = samp->temperature_adj()/100;
//  int fl = int(samp->flow().getDouble() * 2);
//  qm.insert({ta,fl}, samp->oxy()/10);
// }

// QString rs = load_file(path);

// QStringList qsl = rs.split('\n');

// //QVector<QVector<int>*> rowsv;
// //int maxcsz = 0;

// QMap<QPair<int, int>, int> qm;

// QStringList min_max = qsl.takeFirst().simplified().split(' ');

// int fl_min = min_max[0].toInt();
// int fl_max = min_max[1].toInt();
// int ta_min = min_max[2].toInt();
// int ta_max = min_max[3].toInt();
// int oxy_min = min_max[4].toInt();
// int oxy_max = min_max[5].toInt();

// for(QString qs : qsl)
// {
//  if(qs.isEmpty())
//    continue;
//  QStringList qsl = qs.simplified().split(' ');
//  if(qsl.isEmpty())
//    continue;
//  qm.insert({qsl[0].toInt(), qsl[1].toInt()}, qsl[2].toInt());
// }


// //  QVector<QBarDataRow*> rows;
// //  for(int i = 0; i < 20; ++i)
// //  {
// //   QBarDataRow* r = new QBarDataRow;
// //   for(int j = 0; j < 10; ++j)
// //   {
// //    *r << qm.value({j, i}, 0.0f);
// //   }
// //   rows.push_back(r);
// //   series->dataProxy()->addRow(r);
// //  }
