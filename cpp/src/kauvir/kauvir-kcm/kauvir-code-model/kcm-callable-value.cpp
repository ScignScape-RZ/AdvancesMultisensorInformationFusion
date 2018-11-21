
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-callable-value.h"

USING_KANS(KCM)

KCM_Callable_Value::KCM_Callable_Value(QString as_qstring)
  :  as_qstring_ (as_qstring), as_pVoid_(nullptr),
     kto_(nullptr), kcrr_(nullptr)
{

}

KCM_Callable_Value::KCM_Callable_Value(void* as_pVoid, QString type)
 :  as_qstring_(type), as_pVoid_(as_pVoid),
    kto_(nullptr), kcrr_(nullptr)
{

}

KCM_Callable_Value::KCM_Callable_Value(void* as_pVoid)
  :  as_pVoid_(as_pVoid), kto_(nullptr), kcrr_(nullptr)
{

}

KCM_Callable_Value::KCM_Callable_Value()
  :  as_pVoid_(nullptr), kto_(nullptr), kcrr_(nullptr)
{

}
