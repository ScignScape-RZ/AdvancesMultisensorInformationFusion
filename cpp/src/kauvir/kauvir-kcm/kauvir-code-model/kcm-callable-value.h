
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CALLABLE_VALUE__H
#define KCM_CALLABLE_VALUE__H


#include <QString>

#include "kans.h"

#include "accessors.h"

KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)

USING_KANS(CMD)

KANS_(KCM)

class KCM_Type_Object;


class KCM_Callable_Value
{
 QString as_qstring_;
 void* as_pVoid_;

 const KCM_Type_Object* kto_;

 KCM_Command_Runtime_Router* kcrr_;

public:

 explicit KCM_Callable_Value(QString as_qstring);

 explicit KCM_Callable_Value(void* as_pVoid);

 KCM_Callable_Value(void* as_pVoid, QString type);

 KCM_Callable_Value();

 ACCESSORS(QString ,as_qstring)
 ACCESSORS(void* ,as_pVoid)
 ACCESSORS(const KCM_Type_Object* ,kto)
 ACCESSORS(KCM_Command_Runtime_Router* ,kcrr)

};


_KANS(KCM)

#endif //KCM_CALLABLE_VALUE__H
