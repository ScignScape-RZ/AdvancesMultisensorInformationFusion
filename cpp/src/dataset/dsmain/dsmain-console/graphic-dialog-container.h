
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef GRAPHIC_DIALOG_CONTAINER__H
#define GRAPHIC_DIALOG_CONTAINER__H

#include <QObject>

#include <QMap>

class ScignStage_2d_Chart_Dialog;
class ScignStage_3d_Chart_Dialog;
class QDialog;

class ScignStage_Tree_Table_Dialog;

class Graphic_Dialog_Container : public QObject
{
 Q_OBJECT

 QMap<QString, QDialog*> graphics_;

 ScignStage_Tree_Table_Dialog* parent_dialog_;

public:

 Graphic_Dialog_Container(ScignStage_Tree_Table_Dialog* parent_dialog);
 ~Graphic_Dialog_Container();


public Q_SLOTS:

 void handle_graphic_open_requested(quint8, quint8, quint8, bool deco);
 void handle_graphic_close_requested(quint8, quint8, quint8);


};

#endif  // GRAPHIC_DIALOG_CONTAINER__H
