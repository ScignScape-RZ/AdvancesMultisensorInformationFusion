
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PRECON__H
#define PRECON__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>


KANS_(DSM)

template<typename T>
struct precon
{
 void* pass_fn;

 precon(T r)
 {
  typename T::precon_states tps = T::precon_check(r);
  T::precon_branch(tps, pass_fn);
 }
};

template<typename T>
struct precon_pr
{
 T data;
 precon<T> pre;
};


_KANS(DSM)

#endif // ASSESSMENT__SCORES__H
