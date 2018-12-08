
//          Copyright Nathaniel Christen 2018.
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

#include "styles.h"


#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include "textio.h"


USING_KANS(TextIO)

ScignStage_3d_Chart_Dialog::ScignStage_3d_Chart_Dialog(Test_Series* ts,
  int fres, int tres, QWidget* parent)
 : QDialog(parent), selected_cb(nullptr), held_external_selected_(nullptr)
{
 button_box_ = new QDialogButtonBox(this);

 button_ok_ = new QPushButton("OK");

 button_cancel_ = new QPushButton("Cancel");

 button_ok_->setDefault(false);
 button_ok_->setAutoDefault(false);

 button_cancel_->setDefault(true);

 button_ok_->setStyleSheet(basic_button_style_sheet_());
 button_cancel_->setStyleSheet(basic_button_style_sheet_());


 button_box_->addButton(button_ok_, QDialogButtonBox::AcceptRole);

 button_box_->addButton(button_cancel_, QDialogButtonBox::RejectRole);

 connect(button_box_, SIGNAL(accepted()), this, SLOT(accept()));
 connect(button_box_, SIGNAL(rejected()), this, SLOT(close()));

 main_layout_ = new QVBoxLayout();

 Q3DBars* bars = new Q3DBars;
 QWidget* container = QWidget::createWindowContainer(bars);

 bars->rowAxis()->setRange(0, fres);
 bars->columnAxis()->setRange(0, tres);

 QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>> qm;

 ts->cells_to_qmap(fres, tres, qm);

 series_ = new QBar3DSeries;
 for(int i = 0; i <= fres; ++i)
 {
  QBarDataRow* r = new QBarDataRow;
  r->resize(tres + 1);
  for(int j = 0; j <= tres; ++j)
  {
   if(qm.contains({i, j}))
   {
    Test_Sample* samp = qm[{i, j}].first().first->sample;
    sample_map_[{i, j}] = {samp, nullptr};
    inv_sample_map_[{0, samp}] = {i, j};

    (*r)[j].setValue(qm[{i, j}].first().second);

   }
   else
     (*r)[j].setValue(0);
  }
  series_->dataProxy()->addRow(r);
 }

 QLinearGradient bar_gradient(0, 0, 1, 100);
 bar_gradient.setColorAt(1.0, Qt::red);
 bar_gradient.setColorAt(0.0, Qt::green);

 series_->setBaseGradient(bar_gradient);

#ifdef EXTRA_GRAPHICS_FEATURES
 series_->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
#else
 series_->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
#endif

#ifdef SER2
 less_series_ = new QBar3DSeries;
 for(int i = 0; i <= fres; ++i)
 {
  QBarDataRow* r = new QBarDataRow;
  r->resize(tres + 1);
  for(int j = 0; j <= tres; ++j)
  {
   if(qm.contains({i, j}) && qm[{i, j}].size() > 1)
   {
    Test_Sample* samp = qm[{i, j}].first().first->sample;
    sample_map_[{i, j}].second = samp;
    inv_sample_map_[{1, samp}] = {i, j};
    (*r)[j].setValue(qm[{i, j}].last().second);
   }
   else
     (*r)[j].setValue(0);
  }
  less_series_->dataProxy()->addRow(r);
 }

 QLinearGradient bar_gradient1(0, 0, 1, 100);
 bar_gradient1.setColorAt(0.0, Qt::blue);
 bar_gradient1.setColorAt(1.0, Qt::yellow);

 less_series_->setBaseGradient(bar_gradient1);

#ifdef EXTRA_GRAPHICS_FEATURES
 less_series_->setColorStyle(Q3DTheme::ColorStyleRangeGradient);
#else
 less_series_->setColorStyle(Q3DTheme::ColorStyleObjectGradient);
#endif

 less_series_->setMesh(QAbstract3DSeries::MeshCylinder);
 //
 //series1->setMesh(QAbstract3DSeries::MeshCube);
 //series1->setMeshAngle(25);
#endif

 bars->addSeries(series_);

#ifdef SER2
 bars->addSeries(less_series_);
#endif

 connect(series_, &QBar3DSeries::selectedBarChanged, [this]
   (const QPoint &qp)
 {
  handle_selection_change(0, qp);
 });


#ifdef SER2
 connect(less_series_, &QBar3DSeries::selectedBarChanged, [this]
   (const QPoint &qp)
 {
  handle_selection_change(1, qp);
 });
#endif




#ifdef EXTRA_GRAPHICS_FEATURES
 QCategory3DAxis* rax = new QCategory3DAxis;
 rax->setTitle("Flow");
 rax->setTitleVisible(true);
 bars->setRowAxis(rax);

 series->setItemLabelFormat(QStringLiteral("Flow - @colLabel @rowLabel: @valueLabel"));

#endif


 bars->show();

 container->setMinimumHeight(300);
 container->setMinimumWidth(500);

 main_layout_->addWidget(container);
 main_layout_->addWidget(button_box_);

 setLayout(main_layout_);
}


void ScignStage_3d_Chart_Dialog::handle_selection_change(int series,
  const QPoint &qp)
{
 Test_Sample* samp = series?sample_map_[{qp.x(), qp.y()}].second:
   sample_map_[{qp.x(), qp.y()}].first;
 if(held_external_selected_)
 {
  if(samp == held_external_selected_)
  {
   held_external_selected_ = nullptr;
   return;
  }
  held_external_selected_ = nullptr;
 }
 if(samp)
   selected_cb(samp);
}

void ScignStage_3d_Chart_Dialog::external_selected(Test_Sample* samp)
{
 if(inv_sample_map_.contains({0,samp}))
 {
  held_external_selected_ = samp;
  series_->setSelectedBar(
  {inv_sample_map_[{0,samp}].first, inv_sample_map_[{0,samp}].second});
 }
 else if(inv_sample_map_.contains({1,samp}))
 { //?
//  held_external_selected_ = samp;
//  series_->setSelectedBar(
//  {inv_sample_map_[samp].first, inv_sample_map_[samp].second});
 }
}



ScignStage_3d_Chart_Dialog::~ScignStage_3d_Chart_Dialog()
{

}

