
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-source-function.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)

KCM_Source_Function::KCM_Source_Function(KCM_Channel_Group* kcg)
  :  kcg_(kcg), cl_object_(0)
{
}

