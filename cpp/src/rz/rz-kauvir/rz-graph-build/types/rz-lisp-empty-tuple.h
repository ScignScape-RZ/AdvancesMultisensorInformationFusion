
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_EMPTY_TUPLE__H
#define RZ_LISP_EMPTY_TUPLE__H

#include <QDebug>

#include "accessors.h"

#include "rzns.h"


RZNS_(GBuild)

class RZ_Lisp_Token;
class RZ_Lisp_Core_Valuer;
class RZ_Lisp_Node;
class RZ_Lisp_Query;
class RZ_Lisp_Frame;
class RZ_Lisp_Generator;

class RZ_Lisp_Empty_Tuple
{
 typedef RZ_Lisp_Node tNode;

public:

 enum Empty_Tuple_Kinds {
   Empty_Tuple_Kind_Not_Recognized,
   Empty_List, Empty_Code_Block,
   Empty_Vector, Empty_Map,
   Empty_Dot_List, Empty_Double_Dot_List,
   Empty_Dot_Vector, Empty_Double_Dot_Vector,
   Empty_Double_Dot_Map

 };

private:

 Empty_Tuple_Kinds kind_;
 tNode* node_;


public:

 ACCESSORS(Empty_Tuple_Kinds ,kind)
 ACCESSORS(tNode* ,node)

 RZ_Lisp_Empty_Tuple(Empty_Tuple_Kinds kind, tNode* node = nullptr);

 QString get_string_value();
 QString get_lisp_out();

 template<typename T>
 friend void operator<<(T& t, const Empty_Tuple_Kinds&)
 {
 }

 friend void operator<<(QDebug qd, RZ_Lisp_Empty_Tuple& rhs)
 {
  qd << rhs.get_string_value();
 }

 QString write_signature_and_entry(RZ_Lisp_Generator* lisp_generator);


};

_RZNS(GBuild)

#endif //RZ_LISP_EMPTY_TUPLE__H
