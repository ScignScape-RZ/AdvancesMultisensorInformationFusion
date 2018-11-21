
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-xml-line.h"


#include "kans.h"

USING_KANS(PhaonXML)

QString ch_Line::to_string()
{
 return QString(";%1:%2\n.\n").arg(name).arg(code);
}

QString ty_Line::to_string()
{
 return QString("@%1::%2\n.\n").arg(name).arg(code);
}

QString pkg_Line::to_string()
{
 return QString("#%1\n.\n").arg(code);
}

QString fuxe_Line::to_string()
{
 return QString("&:%1\n.\n").arg(name);
}

QString arg_Line::to_string()
{
 return QString("%1:%2::%3::::%4\n.\n").arg(ch_code).arg(code)
   .arg(ty_code).arg(text);
}
