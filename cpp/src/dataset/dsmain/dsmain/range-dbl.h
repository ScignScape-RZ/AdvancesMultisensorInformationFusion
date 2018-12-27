
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RANGE_DBL__H
#define RANGE_DBL__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>


KANS_(DSM)

template<typename T, typename R, R low, R high>
class Range_Dbl
{
 T raw_;

public:

 Range_Dbl(T r) : raw_(r) {}

 typedef bool precon_states;

 static precon_states precon_check(T r)
 {
  return (r >= low) && (r <= high);
 }

 template<typename pT>
 static void precon_branch(precon_states tps, pT& pt)
 {
  if(tps)
   pt = (void*) &cocon;
  else
   pt = nullptr;
 }

 static Range_Dbl cocon(T r) { return Range_Dbl(r); }

 operator T() { return raw_; }
 void operator=(T r) { raw_ = r; }

};


_KANS(DSM)

#endif // RANGE_DBL__H
