
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-value-holder.h"

#include "types/rz-type-object.h"

#include "rzns.h"


USING_RZNS(GBuild)

RZ_Lisp_Graph_Value_Holder::RZ_Lisp_Graph_Value_Holder()
 : value_(nullptr),
   type_object_(nullptr)
{

}

void RZ_Lisp_Graph_Value_Holder::set_typecode(RZ_Run_Types::Enum e)
{

}


int RZ_Lisp_Graph_Value_Holder::typecode()
{
 return type_object_->id();
}


QString RZ_Lisp_Graph_Value_Holder::to_lisp_string() const
{
 if(type_object_)
 {
  return type_object_->value_to_lisp_string(value_);
 }
 return QString();

}

QString RZ_Lisp_Graph_Value_Holder::type_to_string() const
{
 if(type_object_)
 {
  return type_object_->name_to_cpp_string();
 }
 return QString();
}

QString RZ_Lisp_Graph_Value_Holder::to_string_with_type(QString& type) const
{
 if(type_object_)
 {
  type = type_object_->name_to_cpp_string();
  return type_object_->value_to_string(value_);
 }
 return QString();
}

QString RZ_Lisp_Graph_Value_Holder::to_string() const
{
 if(type_object_)
 {
  return type_object_->value_to_string(value_);
 }
 return QString();
}

QString RZ_Lisp_Graph_Value_Holder::to_cpp_string() const
{
 if(type_object_)
 {
  return type_object_->value_to_cpp_string(value_);
 }
 return QString();
}
