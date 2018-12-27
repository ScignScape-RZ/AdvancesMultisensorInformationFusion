
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "scignstage-clickable-label.h"

#include "qsns.h"

USING_QSNS(ScignStage)


ScignStage_Clickable_Label::ScignStage_Clickable_Label(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ScignStage_Clickable_Label::~ScignStage_Clickable_Label() {}


void ScignStage_Clickable_Label::mousePressEvent(QMouseEvent* event)
{
 Q_EMIT(clicked());
}

