
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_XML_DOCUMENT__H
#define PHAON_XML_DOCUMENT__H


#include "kans.h"

#include "accessors.h"

#include <QUrl>
#include <QVector>


class QXmlStreamAttributes;


KANS_(PhaonXML)

class Phaon_XML_Line;

class Phaon_XML_Document
{
 QUrl url_;

 enum class Stream_States
 {
  N_A, No_Data, Pre, Post, Entered, Pkg, Arg
 };

 Stream_States state_;

 QVector<Phaon_XML_Line*> lines_;

public:

 Phaon_XML_Document(QUrl url = QUrl());

 ACCESSORS(QUrl ,url)

 bool ok()
 {
  return state_ != Stream_States::No_Data;
 }

 void set_url_from_file(QString f);

 void transpile(QString path);
 void transpile();

 void run_state(QChar tt, QString tagn,
   const QXmlStreamAttributes& attributes, QString txt);

};


_KANS(PhaonLib)


#endif //PHAON_XML_DOCUMENT__H
