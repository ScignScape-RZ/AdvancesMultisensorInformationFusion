
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-string-plex-builder.h"


USING_RZNS(RECore)


RZ_String_Plex_Builder::RZ_String_Plex_Builder(caon_ptr<RE_Node> tuple_info_node)
 : tuple_info_node_(tuple_info_node)
{
}


void RZ_String_Plex_Builder::add_part(QString value)
{
 add_part(current_key_, value);
}


void RZ_String_Plex_Builder::add_part(QString key, QString value)
{
 parts_[key] = value;
}

QString RZ_String_Plex_Builder::get_part(QString key)
{
 return parts_.value(key, QString());
}
