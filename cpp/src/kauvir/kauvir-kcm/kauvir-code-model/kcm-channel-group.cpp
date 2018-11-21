
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-channel-group.h"

#include "kauvir-code-model.h"

#include "kcm-type-object.h"

#include "kans.h"

USING_KANS(KCM)

KCM_Channel_Group::KCM_Channel_Group(QPair<QSet<QString*>*,
  QMap<KCM_Channel::Kinds, QString*>*>& channel_names)
  :  furnisher_(nullptr), channel_names_(channel_names)
{
}

KCM_Channel_Group::KCM_Channel_Group(const KCM_Channel_Group& rhs)
  :  furnisher_(rhs.furnisher()), channels_(rhs.channels_),
  channel_names_(rhs.channel_names_)
{
}


void KCM_Channel_Group::set_kinds()
{
 QMapIterator<KCM_Channel::Kinds, QString*> it(channel_names_map());
 while(it.hasNext())
 {
  it.next();
  KCM_Channel::Kinds k = it.key();
  QString* qs = it.value();
  auto cit = channels_.find(qs);
  if(cit != channels_.end())
  {
   cit.value().set_kind(k);
  }
 }
}

void KCM_Channel_Group::clear_all_but_sigma()
{
 QList<QString*> keys = channels_.keys();
 for(QString* qs : keys)
 {
  if(*qs != "sigma")
  {
   channels_.remove(qs);
  }
 }
}

void KCM_Channel_Group::clear_all()
{
 channels_.clear();
}

QString* KCM_Channel_Group::get_channel_name_pointer(QString name, KCM_Channel::Kinds k)
{
 if(k != KCM_Channel::Kinds::N_A)
 {
  QString* result = channel_names_map().value(k);
  if(result)
    return result;
 }
 for(QString* qs : channel_names_set())
 {
  if(*qs == name)
  {
   if(k != KCM_Channel::Kinds::N_A)
     channel_names_map()[k] = qs;
   return qs;
  }
 }
 QString* result = new QString(name);
 channel_names_set().insert(result);
 if(k != KCM_Channel::Kinds::N_A)
   channel_names_map()[k] = result;
 return result;
}


void KCM_Channel_Group::channel_names_to_codes(QMap<QString,
  QPair<int, const KCM_Channel*>>& qmap)
{
 int channel_code_count = 1;
 QMapIterator<QString*, KCM_Channel> it(channels_);
 while(it.hasNext())
 {
  it.next();

  // // assumes kind will not always be initialized ...
  if( (it.value().kind() == KCM_Channel::Kinds::Fuxe)
      || (*it.key() == "fuxe") )
  {
   qmap[*it.key()] = {0, &it.value()};
   continue;
  }
  qmap[*it.key()] = {channel_code_count, &it.value()};
  ++channel_code_count;
 }
}


KCM_Channel& KCM_Channel_Group::fuxe_ch()
{
 QString* qs = get_channel_name_pointer("fuxe", KCM_Channel::Kinds::Fuxe);
 return channels_[qs];
}


KCM_Channel& KCM_Channel_Group::lambda_ch()
{
 QString* qs = get_channel_name_pointer("lambda", KCM_Channel::Kinds::Lambda);
 return channels_[qs];
}

KCM_Channel& KCM_Channel_Group::result_ch()
{
 QString* qs = get_channel_name_pointer("result", KCM_Channel::Kinds::Result);
 return channels_[qs];
}

KCM_Channel& KCM_Channel_Group::sigma_ch()
{
 QString* qs = get_channel_name_pointer("sigma", KCM_Channel::Kinds::Sigma);
 return channels_[qs];
}

KCM_Channel& KCM_Channel_Group::error_ch()
{
 QString* qs = get_channel_name_pointer("error", KCM_Channel::Kinds::Error);
 return channels_[qs];
}

KCM_Channel& KCM_Channel_Group::capture_ch()
{
 QString* qs = get_channel_name_pointer("capture", KCM_Channel::Kinds::Capture);
 return channels_[qs];
}

void KCM_Channel_Group::add_fuxe_carrier(const KCM_Type_Object* type_object)
{
 fuxe_ch().add_carrier({type_object, nullptr}, KCM_Carrier::Effect_Protocols::Run_Chief, QString());
}

void KCM_Channel_Group::add_fuxe_carrier(QString symbol_name)
{
 fuxe_ch().add_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Run_Chief, symbol_name);
}

void KCM_Channel_Group::add_empty_lambda_channel()
{
 lambda_ch();
}

void KCM_Channel_Group::add_empty_result_channel()
{
 result_ch();
}

void KCM_Channel_Group::add_empty_error_channel()
{
 error_ch();
}

void KCM_Channel_Group::add_empty_capture_channel()
{
 capture_ch();
}

void KCM_Channel_Group::add_result_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 result_ch().add_carrier(tos, ep, symbol_name);
}


void KCM_Channel_Group::add_lambda_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name, KCM_Runtime_Scope* scope)
{
 lambda_ch().add_carrier(tos, ep, symbol_name, scope);
}


void KCM_Channel_Group::add_sigma_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 sigma_ch().add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_symbol_with_cast(QString value_name,
  const KCM_Type_Object* kto, const KCM_Type_Object* ckto)
{
 add_sigma_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::init_carrier(Kauvir_Code_Model& kcm, QString channel_name, int pos,
  QString type_name, QString* value, QString symbol_name)
{
 QString* qs = get_channel_name_pointer(channel_name);
 KCM_Carrier* kcc = channels_[qs].get_carrier_at_position(pos - 1);
 const KCM_Type_Object* kto = kcm.get_kcm_type_by_type_name(type_name);
 kcc->set_type_object(kto);
 if(value)
   kcc->set_value_string(*value);
 else
   kcc->set_symbol(symbol_name);
}

void KCM_Channel_Group::init_channel_counts(const QMap<QString, int>& channel_counts)
{
 QMapIterator<QString, int> it(channel_counts);
 while (it.hasNext())
 {
  it.next();
  QString* qs = get_channel_name_pointer(it.key());
  channels_[qs].resize_to(it.value());
 }
}



int KCM_Channel_Group::get_lambda_byte_code()
{
 int result = 9;
 for(const KCM_Carrier& c : lambda_ch().carriers())
 {
  result *= 10;
  result += c.type_object()->byte_code();
 }
 return result;
}


int KCM_Channel_Group::get_sigma_lambda_byte_code()
{
 int result = 9;
 for(const KCM_Carrier& c : sigma_ch().carriers())
 {
  result *= 10;
  result += c.type_object()->byte_code();
 }
 for(const KCM_Carrier& c : lambda_ch().carriers())
 {
  result *= 10;
  result += c.type_object()->byte_code();
 }
 return result;
}

void KCM_Channel_Group::add_lambda_carrier_from_result_channel(int level, int index)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted,
   QString(":##%1-%2").arg(level).arg(index));
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_lambda_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_lambda_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_bind_symbol(const KCM_Type_Object* kto, QString symbol_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, symbol_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol(const KCM_Type_Object* kto, QString value_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_scoped_symbol(const KCM_Type_Object* kto,
   QString value_name, KCM_Runtime_Scope* scope)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name, scope);
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol(QString value_name)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_scoped_symbol(QString symbol_name, KCM_Runtime_Scope* scope)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, symbol_name, scope);
}

void KCM_Channel_Group::add_sigma_carrier_via_symbol(QString value_name)
{
 add_sigma_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_opaque_value(const KCM_Type_Object* kto, QString value_encoding)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_encoding);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name)
{
 add_sigma_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
  QString value_name, const KCM_Type_Object* ckto)
{
 add_lambda_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
  QString value_name, const KCM_Type_Object* ckto)
{
 add_sigma_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}


void KCM_Channel_Group::add_lambda_carrier_via_literal(QString value_name)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_literal(QString value_name)
{
 add_sigma_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_lambda_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_lambda_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_sigma_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}


void KCM_Channel_Group::add_result_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_result_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::check_report(KCM_Channel::Kinds k, QTextStream& qts, Kauvir_Code_Model& kcm,
  KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv)
{
 QString* qs = channel_names_map().value(k);
 if(qs)
 {
  auto it = channels_.find(qs);
  if(it != channels_.end())
  {
   it->report(qts, kcm, kcrs, cenv);
  }
 }
}


void KCM_Channel_Group::report(QVector<KCM_Channel::Kinds> ks, QTextStream& qts, Kauvir_Code_Model& kcm,
  KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv)
{
 set_kinds();
 for(KCM_Channel::Kinds k : ks)
 {
  check_report(k, qts, kcm, kcrs, cenv);
 }
}

void KCM_Channel_Group::report(QTextStream& qts, Kauvir_Code_Model& kcm,
  KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv)
{
 report({KCM_Channel::Kinds::Fuxe, KCM_Channel::Kinds::Lambda,
   KCM_Channel::Kinds::Sigma, KCM_Channel::Kinds::Result}, qts, kcm, kcrs, cenv);
}



KCM_Channel_Group* KCM_Channel_Group::branch_copy()
{
 KCM_Channel_Group* result = new KCM_Channel_Group(channel_names_);

 for(QString* qs : channel_names_set())
 {
  if(channels_.contains(qs))
  {
   result->channels_[qs].copy_from(channels_[qs]);
  }
 }
 return result;
}

