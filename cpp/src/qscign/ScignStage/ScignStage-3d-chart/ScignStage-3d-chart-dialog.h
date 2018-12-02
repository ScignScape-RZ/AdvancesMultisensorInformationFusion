
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_3D_CHART_DIALOG__H
#define SCIGNSTAGE_3D_CHART_DIALOG__H

#include <QDialog>
#include <QVector>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QMap>

#include <functional>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)
KANS_CLASS_DECLARE(DSM ,Test_Series)

USING_KANS(DSM)

namespace QtDataVisualization { class QBar3DSeries; }


class ScignStage_3d_Chart_Dialog : public QDialog
{
 Q_OBJECT

 //Fore_Geometric1D_Panel fore_panel_;
 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;

 QMap<QPair<int, int>, QPair<Test_Sample*, Test_Sample*>> sample_map_;
 QMap<QPair<int, Test_Sample*>, QPair<int, int>> inv_sample_map_;

 QtDataVisualization::QBar3DSeries* series_;

//#define SER2
#ifdef SER2
 QtDataVisualization::QBar3DSeries* less_series_;
#endif

 void handle_selection_change(int series, const QPoint &qp);

public:

 std::function<void (Test_Sample*)> selected_cb;

 ScignStage_3d_Chart_Dialog(Test_Series* ts,
   int fres, int tres, QWidget* parent);

 Test_Sample* held_external_selected_;

 ~ScignStage_3d_Chart_Dialog();

Q_SIGNALS:
//signals:

 void sample_selected(Test_Sample*);

public Q_SLOTS:

 void external_selected(Test_Sample* samp);


};


#endif //  SCIGNSTAGE_3D_CHART_DIALOG__H
