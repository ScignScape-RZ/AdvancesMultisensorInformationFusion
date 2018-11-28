
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SERIES_TREEWIDGET__H
#define SERIES_TREEWIDGET__H

#include <QTreeWidget>

#include "qsns.h"

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

 enum class Sort_Options { Index, Flow, Temperature, Oxy };

 Series_TreeWidget(Test_Series* ts, Sort_Options so, QWidget* parent = nullptr);
 ~Series_TreeWidget();


};

//_QSNS(ScignStage)

#endif  // SERIES_TREEWIDGET__H
