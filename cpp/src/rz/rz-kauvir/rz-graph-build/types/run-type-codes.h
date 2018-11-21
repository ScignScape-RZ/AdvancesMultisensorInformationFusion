
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RUN_TYPE_CODES__H
#define RUN_TYPE_CODES__H


#include "rzns.h"


RZNS_(GBuild)


class RZ_Symbol;


#define RZ_RUN_TYPE(enum_name, name, cpp_name, _name, fam) \
 template<> \
 struct RZ_Run_Type<RZ_Run_Types::enum_name> \
 { \
  typedef cpp_name Type; \
  static const RZ_Type_Families::Enum Type_Family = RZ_Type_Families::fam; \
 }; \
 template<> \
 struct RZ_Run_Type_Code<cpp_name> \
 { \
  static const RZ_Run_Types::Enum Value = RZ_Run_Types::enum_name; \
 };


#define RZ_RUN_TYPE_NS(ns_name, enum_name, name, cpp_name, _name, fam) \
 RZ_RUN_TYPE(enum_name, name, cpp_name, _name, fam)

#include "types/type-codes.h"

#undef RZ_RUN_TYPE
#undef RZ_RUN_TYPE_NS



_RZNS(GBuild)


#endif //RUN_TYPE_CODES__H
