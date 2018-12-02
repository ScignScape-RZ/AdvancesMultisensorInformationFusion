
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_CLICKABLE_LABEL__H
#define SCIGNSTAGE_CLICKABLE_LABEL__H

#include <QLabel>

#include "qsns.h"

//QSNS_(ScignStage)
//?namespace QScign { namespace ScignStage {


class ScignStage_Clickable_Label : public QLabel
{
    Q_OBJECT

public:
    explicit ScignStage_Clickable_Label(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~ScignStage_Clickable_Label();


 QString path;

Q_SIGNALS:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

};

//_QSNS(ScignStage)

#endif  // SCIGNSTAGE_CLICKABLE_LABEL__H
