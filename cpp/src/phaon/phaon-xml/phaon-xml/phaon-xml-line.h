
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_XML_LINE__H
#define PHAON_XML_LINE__H


#include "kans.h"


#include <QString>

class QXmlStreamAttributes;


KANS_(PhaonXML)


struct Phaon_XML_Line
{
 virtual QString to_string() = 0;
};


struct ch_Line : Phaon_XML_Line
{
 int code;
 QString name;
 virtual QString to_string() Q_DECL_OVERRIDE;
};

struct ty_Line : Phaon_XML_Line
{
 int code;
 QString name;
 virtual QString to_string() Q_DECL_OVERRIDE;
};

struct pkg_Line : Phaon_XML_Line
{
 int code;
 virtual QString to_string() Q_DECL_OVERRIDE;
};

struct fuxe_Line : Phaon_XML_Line
{
 QString name;
 virtual QString to_string() Q_DECL_OVERRIDE;
};

struct arg_Line : Phaon_XML_Line
{
 int code;
 int ch_code;
 int ty_code;
 QString text;
 virtual QString to_string() Q_DECL_OVERRIDE;
};







_KANS(PhaonLib)


#endif //PHAON_XML_LINE__H
