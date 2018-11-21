
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-empty-tuple.h"


USING_RZNS(GBuild)

RZ_Lisp_Empty_Tuple::RZ_Lisp_Empty_Tuple(Empty_Tuple_Kinds kind, tNode* node)
  : kind_(kind), node_(node)
{}

QString RZ_Lisp_Empty_Tuple::get_string_value()
{
 switch(kind_)
 {
 case Empty_Tuple_Kind_Not_Recognized:
  return "";
 case Empty_List:
  return "()";
 case Empty_Code_Block:
  return "{}";
 case Empty_Vector:
  return "[]";
 case Empty_Map:
  return ".{}";
 case Empty_Dot_List:
  return ".()";
 case Empty_Double_Dot_List:
  return "..()";
 case Empty_Dot_Vector:
  return ".[]";
 case Empty_Double_Dot_Vector:
  return "..[]";
 case Empty_Double_Dot_Map:
  return "..{}";
 }
}

QString RZ_Lisp_Empty_Tuple::get_lisp_out()
{
 switch(kind_)
 {
 case Empty_Tuple_Kind_Not_Recognized:
  return "";
 case Empty_List:
  return "()";
 case Empty_Code_Block:
  return "(rz::ebl)";
 case Empty_Vector:
  return "(rz::vec)";
 case Empty_Map:
  return "(rz::map)";
 case Empty_Dot_List:
  return "(rz::lambda-channel)";
 case Empty_Double_Dot_List:
  return "(rz::return-channel)";
 case Empty_Dot_Vector:
  return "(rz::sigma-channel)";
 case Empty_Double_Dot_Vector:
  return "(rz::error-channel)";
 case Empty_Double_Dot_Map:
  return "(rz::capture-channel)";
 }

}

