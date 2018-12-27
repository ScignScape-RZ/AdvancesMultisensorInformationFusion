
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_TYPE_OBJECT__H
#define RZ_TYPE_OBJECT__H

#include "accessors.h"

#include <QString>

#include "flags.h"

#include "rzns.h"

#include <functional>

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-core/kernel/rz-re-dominion.h"

USING_RZNS(RECore)

RZNS_(GBuild)

class RZ_Type_Object
{
public:

 flags_(1)
  bool is_direct_value:1;

 _flags


 enum Considerations {
  Ok, Fallthrough, To_String, To_Lisp_String, To_Cpp_String
 };

 typedef std::function<Considerations(Considerations,
  RE_Galaxy::Root_Vertex_type, RE_Galaxy::Root_Vertex_type)> Callback_type;

private:
 int id_;
 QString name_;
 QString cpp_name_;

 Callback_type* callback_;

public:

 ACCESSORS(int ,id)
 ACCESSORS(QString ,name)
 ACCESSORS(Callback_type* ,callback)

 RZ_Type_Object(QString name, QString cpp_name, int id);
 QString value_to_string(RE_Galaxy::Root_Vertex_type v) const;
 QString value_to_lisp_string(RE_Galaxy::Root_Vertex_type v) const;
 QString value_to_cpp_string(RE_Galaxy::Root_Vertex_type v) const;
 QString name_to_cpp_string() const;
};

_RZNS(GBuild)

#endif //RZ_TYPE_OBJECT__H
