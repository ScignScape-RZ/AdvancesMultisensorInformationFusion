
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TYPE_FAMILIES__H
#define TYPE_FAMILIES__H

#include "rz-lisp-graph-typedefs.h"

#include <QMap>

#include "rzns.h"

RZNS_(GBuild)

struct RZ_Type_Families
{
 typedef int Enum;

  static const int Internal = 255;

  static const int Generic = 0;
  static const int Core_Operative = 1;
  static const int Core_Class = 2;
  static const int Core_Extension = 3;

  static const int Generic__Generic = 4;
  static const int Generic__Core_Operative = 5;
  static const int Generic__Core_Class = 6;
  static const int Generic__Core_Extension = 7;

  static const int Core_Operative__Generic = 8;
  static const int Core_Operative__Core_Operative = 9;
  static const int Core_Operative__Core_Class = 10;
  static const int Core_Operative__Core_Extension = 11;

  static const int Core_Class__Generic = 12;
  static const int Core_Class__Core_Operative = 13;
  static const int Core_Class__Core_Class = 14;
  static const int Core_Class__Core_Extension = 15;

  static const int Core_Extension__Generic = 16;
  static const int Core_Extension__Core_Operative = 17;
  static const int Core_Extension__Core_Class = 18;
  static const int Core_Extension__Core_Extension = 19;

 static void register_tyid(tyId t, Enum e)
 {
  tyid_Enum_map()[t] = e;
 }

 static Enum get_family_from_tyid(tyId t)
 {
  return tyid_Enum_map()[t];
 }

 static constexpr RZ_Type_Families::Enum merge(RZ_Type_Families::Enum lhs, RZ_Type_Families::Enum rhs)
 {
  return (lhs == RZ_Type_Families::Internal)? rhs
   : (rhs == RZ_Type_Families::Internal)? lhs
   : number_of_families + number_of_families*lhs + rhs;
 }

private:
 static const int number_of_families = 4;

 static QMap<tyId, Enum>& tyid_Enum_map()
 {
  static QMap<tyId, Enum> map;
  return map;
 }


};

_RZNS(GBuild)

#endif //TYPE_FAMILIES__H
