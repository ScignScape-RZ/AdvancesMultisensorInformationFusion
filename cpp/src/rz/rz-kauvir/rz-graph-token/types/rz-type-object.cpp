
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-type-object.h"


#include "rzns.h"

USING_RZNS(GBuild)


RZ_Type_Object::RZ_Type_Object(QString name, QString cpp_name, int id)
 : Flags(0), id_(id), name_(name), cpp_name_(cpp_name), callback_(nullptr)
{

}


QString RZ_Type_Object::name_to_cpp_string() const
{
 return cpp_name_;
}


QString RZ_Type_Object::value_to_string(RE_Galaxy::Root_Vertex_type v) const
{
 if(callback_)
 {
  QString result;
  Considerations c = (*callback_)(To_String, v,
   caon_root_cast<RE_Galaxy>(&result));

  if(c == Ok)
  {
   return result;
  }
 }
 if(flags.is_direct_value)
 {
  // //  Assumes always using fixnum encoding
  size_t actual_num = v.get_fixnum();
  QString result = QString::number(actual_num);
  return result;
 }
 else
  return QString("<%1>").arg(name_);
}


QString RZ_Type_Object::value_to_lisp_string(RE_Galaxy::Root_Vertex_type v) const
{
 if(callback_)
 {
  QString result;
  Considerations c = (*callback_)(To_Lisp_String, v,
   caon_root_cast<RE_Galaxy>(&result));
  if(c == Ok)
   return result;
 }
 if(flags.is_direct_value)
 {
  return QString::number(v.raw_direct_value());
 }
 else
  return QString("<%1>").arg(name_);
}


QString RZ_Type_Object::value_to_cpp_string(RE_Galaxy::Root_Vertex_type v) const
{
 if(callback_)
 {
  QString result;
  Considerations c = (*callback_)(To_Cpp_String, v,
   caon_root_cast<RE_Galaxy>(&result));
  if(c == Ok)
   return result;
 }
 if(flags.is_direct_value)
 {
  return QString::number(v.raw_direct_value());
 }
 else
  return QString("<%1>").arg(name_);
}

