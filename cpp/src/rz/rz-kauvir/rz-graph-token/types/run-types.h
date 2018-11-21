
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RUN_TYPES__H
#define RUN_TYPES__H

// from rz-graph-token
#include "rz-graph-token/valuer/rz-monotail.h"

#include "type-families.h"


#include <QDebug>
#include <QMap>

#include "rzns.h"


USING_RZNS(GVal)


RZNS_(GBuild)

class RZ_Lisp_Graph_Result_Holder;

typedef int tyId;

struct RZ_Type_Not_Set
{
 friend bool operator==(const RZ_Type_Not_Set& lhs, const RZ_Type_Not_Set& rhs)
 {
  return false;
 }

 template<typename T>
 friend bool operator<(const T& lhs, const RZ_Type_Not_Set& rhs)
 {
  return false;
 }

 template<typename T>
 friend bool operator>(const T& lhs, const RZ_Type_Not_Set& rhs)
 {
  return false;
 }

 template<typename T>
 friend bool operator<(const RZ_Type_Not_Set& lhs, const T& rhs)
 {
  return false;
 }

 template<typename T>
 friend bool operator>(const RZ_Type_Not_Set& lhs, const T& rhs)
 {
  return false;
 }


 operator bool()
 {
  return false;
 }

 template<typename T>
 friend RZ_Monotail& operator+ (T& t, const RZ_Type_Not_Set&)
 {
  return RZ::GVal::RZ_The_Monotail();
 }

 template<typename T>
 friend RZ_Monotail& operator+ (const RZ_Type_Not_Set&, T& t)
 {
  return RZ_The_Monotail();
 }

 friend RZ_Lisp_Graph_Result_Holder& operator<< (RZ_Lisp_Graph_Result_Holder& rh, const RZ_Type_Not_Set&)
 {
  return rh;
 }


 friend QDebug operator<< (QDebug qd, const RZ_Type_Not_Set&)
 {
  return qd;
 }

 template<typename T>
 friend T& operator<< (T& t, const RZ_Type_Not_Set&)
 {
  return t;
 }

 friend RZ_Monotail& operator+ (RZ_Type_Not_Set&, RZ_Type_Not_Set&)
 {
  return RZ_The_Monotail();
 }
};

struct RZ_Run_Types
{
 enum Enum
 {
  #include "run-type-list.h"
 };

 static void add_tyid(tyId t, Enum e)
 {
  tyid_Enum_map()[t] = e;
  Enum_tyid_map()[e] = t;
 }
 static tyId get_tyid_from_code(Enum e)
 {
  return Enum_tyid_map()[e];
 }
 static Enum get_code_from_tyid(tyId t)
 {
  return tyid_Enum_map()[t];
 }

 static QMap<tyId, Enum>& tyid_Enum_map()
 {
  static QMap<tyId, Enum> map;
  return map;
 }

 static QMap<Enum, tyId>& Enum_tyid_map()
 {
  static QMap<Enum, tyId> map;
  return map;
 }

};

template<typename RUN_Type>
struct RZ_Run_Type_Code
{
 static const RZ_Run_Types::Enum Value = RZ_Run_Types::Not_Set;
};


template<typename RUN_Type>
struct RZ_Type_Family_Code
{
 static const RZ_Type_Families::Enum Value = RZ_Type_Families::Generic;
};


template<int Code>
struct RZ_Run_Type
{
 typedef RZ_Type_Not_Set Type;
 static const RZ_Type_Families::Enum Type_Family = RZ_Type_Families::Generic;
};



_RZNS(GBuild)


#endif //RUN_TYPES__H
