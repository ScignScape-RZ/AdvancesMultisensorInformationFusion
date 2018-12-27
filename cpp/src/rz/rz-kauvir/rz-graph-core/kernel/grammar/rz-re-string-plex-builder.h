
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_STRING_PLEX_BUILDER__H
#define RZ_RE_STRING_PLEX_BUILDER__H

#include <QMap>
#include <QString>

#include "relae-graph/relae-caon-ptr.h"

#include "accessors.h"

#include "rzns.h"
RZNS_(RECore)

class RE_Node;

class RZ_String_Plex_Builder
{
 QMap<QString, QString> parts_;

 QString current_key_;

 caon_ptr<RE_Node> tuple_info_node_;

public:

 RZ_String_Plex_Builder(caon_ptr<RE_Node> tuple_info_node);

 ACCESSORS(QString ,current_key)
 ACCESSORS(caon_ptr<RE_Node> ,tuple_info_node)

 void add_part(QString key, QString value);
 QString get_part(QString key);
 void add_part(QString value);
};


_RZNS(RECore)

#endif //RZ_RE_STRING_PLEX_BUILDER__H



