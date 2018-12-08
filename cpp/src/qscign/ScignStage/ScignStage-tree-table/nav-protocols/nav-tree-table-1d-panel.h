
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef NAV_Tree_Table1D_PANEL__H
#define NAV_Tree_Table1D_PANEL__H

#include <QObject>

#include <QMetaType>

#include <QList>
#include <QGraphicsScene>
#include <QPoint>

#include <QDialog>

#include <QFrame>



#include "accessors.h"
#include "qsns.h"


class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;

class QCheckBox;


//?QSNS_(ScignStage)
//namespace QScign { namespace ScignStage {


class ScignStage_Clickable_Label;
class ScignStage_Image_Tile;


class NAV_Tree_Table1D_Panel : public QFrame
{
 Q_OBJECT

 QVBoxLayout* main_layout_;
 QHBoxLayout* navigation_layout_;

 ScignStage_Image_Tile* current_sample_;

 QPushButton* sample_up_button_;
 QPushButton* sample_down_button_;

 QPushButton* peer_up_button_;
 QPushButton* peer_down_button_;

 QLabel* sample_first_label_;
 QPushButton* sample_first_button_;

 QLabel* peer_first_label_;
 QPushButton* peer_first_button_;

 QPushButton* deco_button_;
 QHBoxLayout* deco_hlayout_;

 QGroupBox* sample_up_down_group_box_;
 QButtonGroup* sample_up_down_button_group_;

 QGroupBox* peer_up_down_group_box_;
 QButtonGroup* peer_up_down_button_group_;

 QVBoxLayout* peer_up_down_layout_;
 QVBoxLayout* sample_up_down_layout_;

 QHBoxLayout* first_hlayout_;
 QVBoxLayout* first_vlayout_;

 QHBoxLayout* peer_first_hlayout_;

 QGridLayout* ckb_layout_;

 QMap<QString, QCheckBox*> check_boxes_;

 QGroupBox* ckbs_group_box_;

 QMap<QString, QCheckBox*> ckbs_;


public:

 NAV_Tree_Table1D_Panel(QWidget* parent = nullptr);

 ~NAV_Tree_Table1D_Panel();

 void uncheck_graphic(QString code);

Q_SIGNALS:

 void canceled(QDialog*);
 void accepted(QDialog*);

 void peer_up_requested();
 void peer_down_requested();

 void sample_up_requested();
 void sample_down_requested();

 void sample_first_requested();
 void peer_first_requested();

 void graphic_open_requested(quint8, quint8, quint8);
 void graphic_close_requested(quint8, quint8, quint8);


public Q_SLOTS:

};

//_QSNS(ScignStage)


#endif  // NAV_Tree_Table1D_PANEL__H



