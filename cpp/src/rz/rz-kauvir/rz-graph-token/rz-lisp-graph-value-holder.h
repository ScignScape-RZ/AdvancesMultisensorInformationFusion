
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_VALUE_HOLDER__H
#define RZ_LISP_GRAPH_VALUE_HOLDER__H

#include "accessors.h"
#include "flags.h"

#include "types/rz-type-object.h"

#include "relae-graph/relae-caon-ptr.h"

#include "types/run-types.h"

#include <QString>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-core/kernel/rz-re-dominion.h"

USING_RZNS(RECore)

RZNS_(GBuild)


class RZ_Lisp_Graph_Value_Holder
{
private:

 RE_Galaxy::Root_Vertex_type value_;
 caon_ptr<RZ_Type_Object> type_object_;

public:

 ACCESSORS__GET(RE_Galaxy::Root_Vertex_type ,value)
 ACCESSORS(caon_ptr<RZ_Type_Object> ,type_object)

   template<typename T>
   void set_value(caon_ptr<T> t)
   {
#ifdef NO_CAON
    value_ = reinterpret_cast<RE_Galaxy::Root_Vertex_type> ( t );
#else
    value_ = t.template caon_cast<RE_Galaxy::Root_Vertex_type>();
#endif
   }


 template<typename T>
 void set_direct_value(T t)
 {
#ifdef NO_CAON
  value_ = t;
#else
  value_.set_direct_value(t);
#endif //NO_CAON
 }

 template<typename T>
 void set_raw_value(T t)
 {
#ifdef NO_CAON
  value_ = t;
#else
  value_.set_raw_value(t);
#endif //NO_CAON
 }

 void set_typecode(RZ_Run_Types::Enum e);


 template<typename T>
 caon_ptr<T> pRestore()
 {
#ifdef NO_CAON
  return reinterpret_cast<T*>(value_);
#else
  return value_.template caon_cast<T>();
#endif //NO_CAON
 }

 template<typename T>
 caon_ptr<T> pRetrieve()
 {
  if(type_object_->flags.is_direct_value)
  {
#ifdef NO_CAON
   return reinterpret_cast<caon_ptr<T> > (value_);
#else
   return value_.raw_direct_value();
#endif //NO_CAON
  }
  return pRestore<T>();
 }

 template<typename T>
 T& retrieve()
 {
  return *pRetrieve<T>();
 }


 template<typename T>
 void write_value_to(T& t)
 {}

 QString to_cpp_string() const;
 QString to_string() const;
 QString to_lisp_string() const;
 QString to_string_with_type(QString& type) const;
 QString type_to_string() const;


 RZ_Lisp_Graph_Value_Holder();

 int typecode();
};

_RZNS(GBuild)

#endif //RZ_LISP_GRAPH_VALUE_HOLDER__H
