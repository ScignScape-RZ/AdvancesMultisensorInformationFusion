
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef NAV_AUDIO_1D_PANEL__H
#define NAV_AUDIO_1D_PANEL__H

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


//?QSNS_(ScignStage)
//namespace QScign { namespace ScignStage {


class ScignStage_Clickable_Label;
class ScignStage_Image_Tile;


class NAV_Audio1D_Panel : public QFrame
{
 Q_OBJECT

 QVBoxLayout* main_layout_;
 QHBoxLayout* navigation_layout_;

 ScignStage_Image_Tile* current_sample_;

 QPushButton* sample_up_button_;
 QPushButton* sample_down_button_;


 QPushButton* peer_up_button_;
 QPushButton* peer_down_button_;

 QVBoxLayout* first_replay_note_layout_;
 QHBoxLayout* first_replay_layout_;
 QLabel* first_replay_label_;

 QLabel* sample_first_label_;
 QPushButton* sample_first_button_;

 QLabel* sample_replay_label_;
 QPushButton* sample_replay_button_;

 QVBoxLayout* first_layout_;
 QVBoxLayout* replay_layout_;
 QVBoxLayout* navigation_buttons_up_down_layout_;

 QGroupBox* up_down_group_box_;
 QButtonGroup* up_down_button_group_;

 QVBoxLayout* peer_up_down_layout_;

 QGroupBox* peer_up_down_group_box_;
 QButtonGroup* peer_up_down_button_group_;

 QHBoxLayout* volume_layout_;



 QVBoxLayout* zoom_sample_distractor_layout_;
 QHBoxLayout* sample_distractor_layout_;

 QLabel* sample_label_;
 QLineEdit* sample_line_edit_;
 QLabel* distractor_label_;
 QLineEdit* distractor_line_edit_;

 QSlider* volume_slider_;

 qreal old_zoom_slider_value_;

 int volume_min_;
 int volume_max_;

public:

 NAV_Audio1D_Panel(int vmn, int vmx, int v, QWidget* parent = nullptr);

 ~NAV_Audio1D_Panel();

 void set_sample_text(int r);
 void set_distractor_text(QString qs);

Q_SIGNALS:

 void canceled(QDialog*);
 void accepted(QDialog*);

 void volume_change_requested(int);

 void zoom_in_requested();
 void zoom_out_requested();
 void scale_ratio_change_requested(qreal ratio);

 void peer_up_requested();
 void peer_down_requested();

 void sample_up_requested();
 void sample_down_requested();
 void sample_first_requested();
 void sample_replay_requested();


public Q_SLOTS:

 void zoom_slider_value_changed(int);
 void volume_slider_value_changed(int);

};

//_QSNS(ScignStage)


#endif  // NAV_AUDIO_1D_PANEL__H



