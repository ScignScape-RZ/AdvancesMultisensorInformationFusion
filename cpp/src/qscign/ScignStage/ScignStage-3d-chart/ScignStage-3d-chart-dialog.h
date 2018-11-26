
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_3D_CHART_DIALOG__H
#define SCIGNSTAGE_3D_CHART_DIALOG__H

#include <QDialog>
#include <QVector>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)


USING_KANS(DSM)

class ScignStage_3d_Chart_Dialog : public QDialog
{
 Q_OBJECT

 //Fore_Geometric1D_Panel fore_panel_;
 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QVBoxLayout* main_layout_;


public:

 ScignStage_3d_Chart_Dialog(QVector<Test_Sample*>* samples,
   QString path, QWidget* parent);

 ~ScignStage_3d_Chart_Dialog();

public Q_SLOTS:



};


#endif //  SCIGNSTAGE_3D_CHART_DIALOG__H
