
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef APPLICATION_MODEL__H
#define APPLICATION_MODEL__H

#include <QObject>

#include <QMap>


class ScignStage_2d_Chart_Dialog;
class ScignStage_3d_Chart_Dialog;
class QDialog;

class ScignStage_Tree_Table_Dialog;

class Application_Model : public QObject
{
 Q_OBJECT

 QMap<QString, QDialog*> graphics_;

 ScignStage_Tree_Table_Dialog* tree_table_dialog_;

public:

 Q_INVOKABLE void hide_graphic(ScignStage_Tree_Table_Dialog* dlg, QString code);
 Q_INVOKABLE void show_graphic(ScignStage_Tree_Table_Dialog* dlg, QString code);
 Q_INVOKABLE void expand_sample(ScignStage_Tree_Table_Dialog* dlg, int index);

 Application_Model(ScignStage_Tree_Table_Dialog* tree_table_dialog);
 ~Application_Model();

};

#endif  // APPLICATION_MODEL__H
