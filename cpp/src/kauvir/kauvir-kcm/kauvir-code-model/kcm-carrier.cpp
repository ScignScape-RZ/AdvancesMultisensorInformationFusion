
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-carrier.h"

#include "kans.h"

#include "kcm-type-object.h"

#include "kauvir-code-model.h"

USING_KANS(KCM)


KCM_Carrier::KCM_Carrier(const KCM_Type_Object* type_object,
  Effect_Protocols ep, QString symbol, const KCM_Type_Object* cast_type_object, KCM_Runtime_Scope* scope)
  : Flags(0), type_object_(type_object),
    symbol_(symbol), cast_type_object_(cast_type_object), declaration_scope_(scope)
{
 switch(ep)
 {
 case Effect_Protocols::Write_Mandated:
  flags.write_mandated = true;
  break;

 case Effect_Protocols::Write_Disallowed:
  flags.write_disallowed = true;
  break;

 case Effect_Protocols::Read_Disallowed:
  flags.read_disallowed = true;
  break;

 case Effect_Protocols::Read_Mandated:
  flags.read_mandated = true;
  break;

 case Effect_Protocols::Const_Literal:
  flags.value_string = true;
  break;

 default:
  break;

 }

}

KCM_Carrier::KCM_Carrier(const KCM_Type_Object* type_object, Flags_type flags,
  QString symbol, const KCM_Type_Object* cast_type_object)
  :  type_object_(type_object), Flags(flags),
     symbol_(symbol), cast_type_object_(cast_type_object), declaration_scope_(nullptr)
{

}

KCM_Carrier KCM_Carrier::branch_copy() const
{
 KCM_Carrier result(type_object_, Flags, symbol_, cast_type_object_);
 result.declaration_scope_ = declaration_scope_;
 return result;
}


QString KCM_Carrier::get_src_value() const
{
 if(flags.src_val)
   return src_value_;
 if(flags.value_string)
   return symbol_;
 return symbol_;
}

QString KCM_Carrier::token_report(Kauvir_Code_Model& kcm) const
{
 QString result = symbol_;
 if(type_object_)
 {
  result += '{' + type_object_->token_report(kcm) + '}';
 }
 return result;
}

QString* KCM_Carrier::symbol_as_pointer()
{
 return &symbol_;
}


void KCM_Carrier::report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs) const
{
 if(symbol_.startsWith("\\."))
 {
  kcm.report_expression_from_code(qts, symbol_, kcrs);
  if(kcrs.flags.cast_after_expression)
  {
   if(cast_type_object_)
   {
    qts << " as " << kcm.get_ouput_type_name(kcrs, cast_type_object_);
   }
  }
 }
 else
 {
  if(kcrs.flags.surround_carriers)
  {
   qts << "(" << symbol_ << ")";
  }
  else
  {
   qts << symbol_;
  }
  if(kcrs.flags.identify_types)
  {
   if(type_object_)
   {
    type_object_->report(qts, kcm, kcrs);
   }
  }
  if(kcrs.flags.cast_after_expression)
  {
   if(cast_type_object_)
   {
    qts << " as " << kcm.get_ouput_type_name(kcrs, cast_type_object_);
   }
  }
 }
}
