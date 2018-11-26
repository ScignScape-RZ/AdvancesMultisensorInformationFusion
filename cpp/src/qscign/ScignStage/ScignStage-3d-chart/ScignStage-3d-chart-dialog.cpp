
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

ScignStage_3d_Chart_Dialog::ScignStage_3d_Chart_Dialog(QWidget* parent)
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


 Q3DSurface* surface = new Q3DSurface;
 QWidget* container = QWidget::createWindowContainer(surface);

 QSurfaceDataArray *data = new QSurfaceDataArray;
 QSurfaceDataRow *dataRow1 = new QSurfaceDataRow;
 QSurfaceDataRow *dataRow2 = new QSurfaceDataRow;

 *dataRow1 << QVector3D(0.0f, 0.1f, 0.5f) << QVector3D(1.0f, 0.5f, 0.5f);
 *dataRow2 << QVector3D(0.0f, 1.8f, 1.0f) << QVector3D(1.0f, 1.2f, 1.0f);
 *data << dataRow1 << dataRow2;

 QSurface3DSeries *series = new QSurface3DSeries;
 series->dataProxy()->resetArray(data);
 surface->addSeries(series);
 surface->show();

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


