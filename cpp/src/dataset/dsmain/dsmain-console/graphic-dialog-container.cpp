
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "graphic-dialog-container.h"

#include <QDebug>

Graphic_Dialog_Container::Graphic_Dialog_Container()
{

}

Graphic_Dialog_Container::~Graphic_Dialog_Container() {}

void Graphic_Dialog_Container::handle_graphic_open_requested(quint8 d, quint8 r, quint8 c)
{
 qDebug() << d << r << c;
}

void Graphic_Dialog_Container::handle_graphic_close_requested(quint8 d, quint8 r, quint8 c)
{

}
