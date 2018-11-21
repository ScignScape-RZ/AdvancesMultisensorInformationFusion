
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-type-object.h"

#include "kauvir-type-system/kauvir-type-object.h"

#include "kauvir-code-model.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Type_Object::KCM_Type_Object(KCM_Channel_Group* channel_group)
  :  kauvir_type_object_(nullptr), channel_group_(channel_group),
     modifier_(Modifiers::N_A), array_length_(0), byte_code_(0)
{
}

KCM_Type_Object::KCM_Type_Object(const Kauvir_Type_Object* kauvir_type_object, int byte_code)
  :  kauvir_type_object_(kauvir_type_object), channel_group_(nullptr),
     modifier_(Modifiers::N_A), array_length_(0), byte_code_(byte_code)
{
}

KCM_Type_Object::KCM_Type_Object()
 :  kauvir_type_object_(nullptr), channel_group_(nullptr),
    modifier_(Modifiers::N_A), array_length_(0), byte_code_(0)
{

}

KCM_Type_Object::Modifiers KCM_Type_Object::get_modifier_by_string(QString str)
{
 static QMap<QString, Modifiers> static_map {{
   {"KCM_Type_Object::Modifiers::Pointer", Modifiers::Pointer},
   {"KCM_Type_Object::Modifiers::Reference", Modifiers::Reference},
   {"KCM_Type_Object::Modifiers::Const", Modifiers::Const},
   {"KCM_Type_Object::Modifiers::Const_Pointer_To_Const", Modifiers::Const_Pointer_To_Const},
   {"KCM_Type_Object::Modifiers::Const_Pointer", Modifiers::Const_Pointer},
   {"KCM_Type_Object::Modifiers::Pointer_To_Const", Modifiers::Pointer_To_Const},
   {"KCM_Type_Object::Modifiers::Const_Reference", Modifiers::Const_Reference},
   {"KCM_Type_Object::Modifiers::Reference_To_Pointer", Modifiers::Reference_To_Pointer}
  }};

 return static_map.value(str, Modifiers::N_A);
}

QString KCM_Type_Object::get_name_string() const
{
 return kauvir_type_object_->name();
}

bool KCM_Type_Object::is_string_like() const
{
 // too primitive, no doubt
 return kauvir_type_object_->name() == "str";
}

bool KCM_Type_Object::is_lisp_list_like() const
{
 // too primitive, no doubt
 return kauvir_type_object_->name() == "opl";
}

bool KCM_Type_Object::is_callable_lisp_deferred_value_like() const
{
 // too primitive, no doubt
 return kauvir_type_object_->name() == "cldv";
}

bool KCM_Type_Object::is_argvec_like() const
{
 // too primitive, no doubt
 return kauvir_type_object_->name() == "argvec";
}

bool KCM_Type_Object::is_number_like() const
{
 // too primitive, no doubt
 return kauvir_type_object_->name() == "u32"
   ||   kauvir_type_object_->name() == "u64"
   ||   kauvir_type_object_->name() == "u8"
   ||   kauvir_type_object_->name() == "int"
   ;
}

KCM_Type_Object* KCM_Type_Object::base_clone() const
{
 KCM_Type_Object* result = new KCM_Type_Object;
 if(channel_group_)
 {
  result->channel_group_ = channel_group_;
 }
 if(kauvir_type_object_)
 {
  result->kauvir_type_object_ = kauvir_type_object_;
 }
 return result;
}

QString KCM_Type_Object::token_report(Kauvir_Code_Model& kcm) const
{
 QString result;
 if(kauvir_type_object_)
 {
  result = kcm.string_rep(kauvir_type_object_);
 }
 if(array_length_ == -1)
 {
  result.prepend('[');
  result.append(']');
 }
 else if(array_length_ > 0)
 {
  result = QString("[%1 * %2]").arg(result).arg(array_length_);
 }
 switch(modifier_)
 {
 case Modifiers::Pointer:
  result.prepend('&');
  break;
 default:
  break;
 }
 return result;
}


void KCM_Type_Object::report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs) const
{
 QString kto_type_rep;
 if(kauvir_type_object_)
 {
  kto_type_rep = kcm.string_rep(kauvir_type_object_);
 }
 if(kcrs.flags.use_thorin_array_types)
 {
  if(array_length_ == -1)
  {
   kto_type_rep.prepend('[');
   kto_type_rep.append(']');
  }
  else if(array_length_ > 0)
  {
   kto_type_rep = QString("[%1 * %2]").arg(kto_type_rep).arg(array_length_);
  }
 }
 switch(modifier_)
 {
 case Modifiers::Pointer:
  kto_type_rep.prepend('&');
  break;
 default:
  break;
 }
 if(kcrs.flags.surround_type_expressions)
 {
  qts << kto_type_rep;
 }
 else
 {
  qts << kto_type_rep;
 }
}



