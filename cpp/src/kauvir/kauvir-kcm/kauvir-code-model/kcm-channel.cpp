
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-channel.h"

#include "kcm-report-syntax.h"

#include "kans.h"

USING_KANS(KCM)


KCM_Channel::KCM_Channel()
  : kind_(Kinds::N_A)
{

}

KCM_Channel::Kinds KCM_Channel::get_channel_kind_by_string(QString key)
{
 static QMap<QString, Kinds> static_map{{
  {"Fuxe", Kinds::Fuxe},
  {"Lambda", Kinds::Lambda},
  {"Sigma", Kinds::Sigma},
  {"Array", Kinds::Array},
  {"Capture", Kinds::Capture},
  {"Gamma", Kinds::Gamma},
  {"Result", Kinds::Result},
  {"Error", Kinds::Error},
  {"Preempt_Any", Kinds::Preempt_Any},
  {"Preempt_Return", Kinds::Preempt_Return},
  {"Preempt_Continue", Kinds::Preempt_Continue},
  {"Preempt_Break", Kinds::Preempt_Break},
  {"CTOR_Mem", Kinds::CTOR_Mem},
  {"CTOR_Ret", Kinds::CTOR_Ret},
 }};

 return static_map.value(key, Kinds::N_A);
}


void KCM_Channel::resize_to(int sz)
{
 carriers_.resize(sz);
}

QString KCM_Channel::kind_to_string(KCM_Report_Syntax& kcrs)
{
 return kcrs.get_channel_kind_code(kind_);
}

void KCM_Channel::report(QTextStream& qts,
  Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs, Code_Environments cenv)
{
 if( (cenv == Code_Environments::Statement) &&
  kcrs.flags.arrow_before_result_channel && kind_ == Kinds::Result)
 {
  qts << " -> ";
 }
 if(carriers_.isEmpty())
 {
  QString pre;
  QString post;
  if(kcrs.flags.identify_channel_names)
  {
   pre = QString("[%1").arg(kind_to_string(kcrs));
   post = " ]";
  }

  if(kcrs.flags.write_empty_lambda_channel && kind_ == Kinds::Lambda)
  {
   qts << pre << " <<void>>" << post;
  }
  else if( (cenv == Code_Environments::Statement) &&
   kcrs.flags.write_empty_result_channel && kind_ == Kinds::Result)
  {
   qts << pre << " <<void>>" << post;
  }
  return;
 }

 if(kcrs.flags.merge_fuxe_and_lambda && kind_ == Kinds::Lambda)
 {

 }
 else if(kind_ == Kinds::Fuxe && cenv == Code_Environments::Expression)
 {
  if(kcrs.flags.merge_fuxe_and_lambda)
  {
   qts << '(';
  }
 }
 else if(kind_ == Kinds::Array)
 {
  if(kcrs.flags.expand_array_indicators)
  {
   qts << "(arr ";
  }
  else
  {
   qts << '[';
  }
 }
 else
 {
  qts << '(';
 }

 if(kcrs.flags.identify_channel_names)
 {
  qts << '[' << kind_to_string(kcrs) << "] ";
 }

 int count = 0;
 int max = carriers_.size();
 for(const KCM_Carrier& kcc : carriers_)
 {
  ++count;
  kcc.report(qts, kcm, kcrs);
  if(count < max)
  {
   if(kcrs.flags.comma_separate_channel_carriers)
   {
    qts << ", ";
   }
   else
   {
    qts << ' ';
   }
  }
 }

 if(kcrs.flags.merge_fuxe_and_lambda && kind_ == Kinds::Fuxe)
 {
  qts << ' ';
 }
 else if(kind_ == Kinds::Fuxe && cenv == Code_Environments::Expression)
 {

 }
 else if(kind_ == Kinds::Array)
 {
  if(kcrs.flags.expand_array_indicators)
  {
   qts << ')';
  }
  else
  {
   qts << ']';
  }
 }
 else
 {
  qts << ')';
 }

}


void KCM_Channel::copy_from(const KCM_Channel& kch)
{
 for(const KCM_Carrier& kcc : kch.carriers())
 {
  carriers_.push_back(kcc.branch_copy());
 }
 kind_ = kch.kind();
}


const KCM_Carrier* KCM_Channel::get_carrier_at_position(int position) const
{
 if(position < carriers_.size())
 {
  const KCM_Carrier& kcc = carriers_[position];
  return &kcc;
 }
 return nullptr;
}


KCM_Carrier* KCM_Channel::get_carrier_at_position(int position)
{
 if(position < carriers_.size())
 {
  KCM_Carrier& kcc = carriers_[position];
  return &kcc;
 }
 return nullptr;
}

void KCM_Channel::get_carrier_at_position(int position, KCM_Carrier& result)
{
 if(position < carriers_.size())
 {
  result = carriers_.value(position);
 }
}

const KCM_Type_Object* KCM_Channel::type_object_at_position(int position)
{
 if(position < carriers_.size())
 {
  return carriers_.value(position).type_object();
 }
 return nullptr;
}

void KCM_Channel::add_carrier(QPair<const KCM_Type_Object*, const KCM_Type_Object*> tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol, KCM_Runtime_Scope* scope)
{
 carriers_.push_back(KCM_Carrier(tos.first, ep, symbol, tos.second, scope));
}
