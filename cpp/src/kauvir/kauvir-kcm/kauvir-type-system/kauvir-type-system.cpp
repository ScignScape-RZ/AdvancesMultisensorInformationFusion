
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kauvir-type-system.h"

#include "kans.h"

USING_KANS(Kauvir)


Kauvir_Type_System::Kauvir_Type_System()
  :
    type_object__auto_expr_(Kauvir_Type_Object("ae")),
    type_object__str_(Kauvir_Type_Object("str")),
    type_object__s8_(Kauvir_Type_Object("s8")),
    type_object__u8_(Kauvir_Type_Object("u8")),
    type_object__s32_(Kauvir_Type_Object("s32")),
    type_object__u32_(Kauvir_Type_Object("u32")),
    type_object__s64_(Kauvir_Type_Object("s64")),
    type_object__u64_(Kauvir_Type_Object("u64")),
    type_object__opaque_lisp_value_(Kauvir_Type_Object("opl")),
    type_object__callable_lisp_value_(Kauvir_Type_Object("clv")),
    type_object__callable_lisp_code_(Kauvir_Type_Object("clc")),
    type_object__callable_lisp_function_(Kauvir_Type_Object("clf")),
    type_object__opaque_void_pointer_(Kauvir_Type_Object("opv")),
    type_object__kcm_callable_value_(Kauvir_Type_Object("kcv")),
    type_object__callable_lisp_deferred_value_(Kauvir_Type_Object("cldv")),
    type_object__argument_vector_(Kauvir_Type_Object("argvec"))
{

}



