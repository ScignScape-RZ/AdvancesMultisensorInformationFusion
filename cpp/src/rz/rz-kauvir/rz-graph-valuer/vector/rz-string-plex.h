
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_STRING_PLEX__H
#define RZ_STRING_PLEX__H

#include "rz-typedefs.h"
#include "flags.h"
#include "accessors.h"


#include "relae-graph/relae-caon-ptr.h"


#include <QDebug>
#include <QVector>
#include <QStringList>
#include <QList>
#include <QMap>
#include <QMultiMap>


#include "rzns.h"


RZNS_(RECore)

class RE_Node;
class RE_Tuple_Info;
class RZ_String_Plex_Builder;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GBuild)

class RZ_Type_Object;
class RZ_Lisp_Token;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GVal)

class RZ_String;

class RZ_Lisp_Graph_Valuer;


class RZ_String_Plex
{
 typedef RE_Node tNode;

private:

 caon_ptr<RE_Tuple_Info> tuple_info_;
 caon_ptr<RZ_Lisp_Token> token_representation_;

 caon_ptr<RZ_String_Plex_Builder> builder_;


public:

 RZ_String_Plex(caon_ptr<RE_Tuple_Info> tuple_info,
  RZ_Type_Object& rto, caon_ptr<RZ_String_Plex_Builder> builder);


 ACCESSORS(caon_ptr<RE_Tuple_Info> ,tuple_info)
 ACCESSORS(caon_ptr<RZ_Lisp_Token> ,token_representation)

 caon_ptr<tNode> get_call_entry_node();
 QString get_value(QString key);

 template<typename T>
 friend T& operator<<(T& t, const RZ_String_Plex& rhs)
 {
//?  return t << rhs.to_string();
 }


 friend void operator<<(QDebug lhs, const RZ_String_Plex& rhs)
 {
//?  tString s = rhs.to_string();
//?  lhs << s;
 }

};

_RZNS(GVal)

#endif //RZ_STRING_PLEX__H
