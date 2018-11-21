
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KAUVIR_TYPE_SYSTEM__H
#define KAUVIR_TYPE_SYSTEM__H


#include "kans.h"

#include "accessors.h"

#include "kauvir-type-object.h"

#include <QVector>

KANS_(Kauvir)

class Kauvir_Type_System
{
 Kauvir_Type_Object type_object__auto_expr_;

 Kauvir_Type_Object type_object__str_;
 Kauvir_Type_Object type_object__u8_;
 Kauvir_Type_Object type_object__s8_;
 Kauvir_Type_Object type_object__u32_;
 Kauvir_Type_Object type_object__s32_;
 Kauvir_Type_Object type_object__u64_;
 Kauvir_Type_Object type_object__s64_;

 Kauvir_Type_Object type_object__opaque_lisp_value_;

 Kauvir_Type_Object type_object__callable_lisp_value_;
 Kauvir_Type_Object type_object__callable_lisp_function_;
 Kauvir_Type_Object type_object__callable_lisp_code_;

 Kauvir_Type_Object type_object__opaque_void_pointer_;

 Kauvir_Type_Object type_object__kcm_callable_value_;
 Kauvir_Type_Object type_object__callable_lisp_deferred_value_;
 Kauvir_Type_Object type_object__argument_vector_;

public:


 Kauvir_Type_System();


 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__auto_expr)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__str)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__u8)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__s8)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__u32)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__s32)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__u64)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__s64)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__opaque_lisp_value)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__opaque_void_pointer)

 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__callable_lisp_function)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__callable_lisp_value)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__callable_lisp_code)

 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__kcm_callable_value)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__callable_lisp_deferred_value)
 ACCESSORS__CONST_RGET(Kauvir_Type_Object ,type_object__argument_vector)

};


_KANS(Kauvir)


#endif //KAUVIR_TYPE_SYSTEM__H


