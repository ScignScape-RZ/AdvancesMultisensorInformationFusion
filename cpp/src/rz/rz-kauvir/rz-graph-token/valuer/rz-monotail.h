
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_MONOTAIL__H
#define RZ_MONOTAIL__H

#include "rzns.h"

RZNS_(GVal)

struct RZ_Monotail;
RZ_Monotail& RZ_The_Monotail();

struct RZ_Monotail
{
 static RZ_Monotail* instance()
 {
  static RZ_Monotail m;
  return &m;
 }

 friend RZ_Monotail& RZ_The_Monotail();

 template<typename T>
 friend T& operator<<(T& t, const RZ_Monotail&)
 {
  return t;
 }

 friend RZ_Monotail& operator<<(const RZ_Monotail&, const RZ_Monotail&)
 {
  return *RZ_Monotail::instance();
 }

};


_RZNS(GVal)


#endif //RZ_MONOTAIL__H
