
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SERIES_TREEWIDGET__H
#define SERIES_TREEWIDGET__H

#include <QTreeWidget>

#include "accessors.h"

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)
KANS_CLASS_DECLARE(DSM ,Test_Series)

USING_KANS(DSM)

//QSNS_(ScignStage)
//?namespace QScign { namespace ScignStage {


class Series_TreeWidget : public QTreeWidget
{
 Q_OBJECT

public:
  enum class Sort_Options { Index = 0, Flow = 1,
    Temperature = 2, Oxy = 3 };

private:

 QVector<Test_Sample*>* samples_;

 Sort_Options sorted_by_;

public:

 ACCESSORS(QVector<Test_Sample*>* ,samples)
 ACCESSORS(Sort_Options ,sorted_by)

 void highlight_3rd_line(int index);
 void highlight_3rd_line(int index, QColor clr);
 void unhighlight_3rd_line(int index);


 Series_TreeWidget(Test_Series* ts, Sort_Options so, QWidget* parent = nullptr);
 ~Series_TreeWidget();

Q_SIGNALS:

 void column_context_menu_requested(const QPoint& qp, int col);
 void row_context_menu_requested(const QPoint& qp, int row, int col);

};

//_QSNS(ScignStage)

#endif  // SERIES_TREEWIDGET__H
