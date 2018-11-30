
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef GRAPHIC_DIALOG_CONTAINER__H
#define GRAPHIC_DIALOG_CONTAINER__H

#include <QObject>

class Graphic_Dialog_Container : public QObject
{
 Q_OBJECT

public:

 Graphic_Dialog_Container();
 ~Graphic_Dialog_Container();


public Q_SLOTS:

 void handle_graphic_open_requested(quint8, quint8, quint8);
 void handle_graphic_close_requested(quint8, quint8, quint8);


};

#endif  // GRAPHIC_DIALOG_CONTAINER__H
