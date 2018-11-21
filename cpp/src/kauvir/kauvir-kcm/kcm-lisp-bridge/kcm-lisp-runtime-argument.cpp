
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-lisp-runtime-argument.h"

#include <QMetaMethod>
#include <QDebug>

#include "object.hpp"

USING_KANS(KCL)

KCM_Lisp_Runtime_Argument::KCM_Lisp_Runtime_Argument(QString string)
  :  string_(string), pVoid_( (void*) 1)
{

}

KCM_Lisp_Runtime_Argument::KCM_Lisp_Runtime_Argument(quint64 cl_object)
  :  cl_object_(cl_object), pVoid_( (void*) 2)
{

}

KCM_Lisp_Runtime_Argument::KCM_Lisp_Runtime_Argument(void* pVoid)
  :  pVoid_(pVoid)
{

}

KCM_Lisp_Runtime_Argument::Kinds KCM_Lisp_Runtime_Argument::get_kind() const
{
 if( (quint64) pVoid_ == 1)
 {
  return Kinds::String;
 }
 else if( (quint64) pVoid_ == 2)
 {
  return Kinds::Cl_Object;
 }
 else if( (quint64) pVoid_ == 3)
 {
  return Kinds::Opaque_Lisp_Value;
 }
 else
 {
  return Kinds::PVoid;
 }
}

void KCM_Lisp_Runtime_Argument::set_as_fixnum(int i)
{
 cl_object_ = (quint64) cl_cxx::to_cl_object<int>(i);
 pVoid_ =  (void*) 2;
}

void** KCM_Lisp_Runtime_Argument::pointer_for_qarg()
{
 switch(get_kind())
 {
 case Kinds::String:
  return (void**)&string_;
 case Kinds::Cl_Object:
  return (void**)&cl_object_;
 case Kinds::Opaque_Lisp_Value:
  return (void**)&cl_object_;
 default:
  return &pVoid_;
 }
}


void KCM_Lisp_Runtime_Argument::set_string(QString str)
{
 string_ = str;
 pVoid_ =  (void*) 1;
}

void KCM_Lisp_Runtime_Argument::set_cl_object(quint64 cl_object)
{
 cl_object_ = cl_object;
 pVoid_ =  (void*) 2;
}

void KCM_Lisp_Runtime_Argument::set_opaque_lisp_value(quint64 cl_object)
{
 cl_object_ = cl_object;
 pVoid_ =  (void*) 3;
}
