
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-package.h"

#include "kauvir-code-model/kcm-carrier.h"
#include "kauvir-code-model/kcm-overloadable-symbol.h"

#include "kans.h"

USING_KANS(CMD)


KCM_Command_Package::KCM_Command_Package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names)
  :  KCM_Channel_Group(channel_names), output_symbol_(nullptr),
     kcm_expression_(nullptr), bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Command_Package::KCM_Command_Package(const KCM_Channel_Group& kcg)
  :  KCM_Channel_Group(kcg), output_symbol_(nullptr),
     kcm_expression_(nullptr), bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Command_Package::KCM_Command_Package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names,
  const KCM_Type_Object* kto, QString val, QObject* bind_qob)
  :  KCM_Channel_Group(channel_names), bind_kto_(kto),
    bind_val_(val), output_symbol_(nullptr),
    kcm_expression_(nullptr), bind_qob_(bind_qob)
{

}


QString KCM_Command_Package::report_sigma(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 return report_channel(KCM_Channel::Kinds::Sigma, "[", "]", kcm, sep, last_sep, on_empty);
}

QString KCM_Command_Package::report_fuxe(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 return report_channel(KCM_Channel::Kinds::Fuxe, "(|", "|)", kcm, sep, last_sep, on_empty);
}

QString KCM_Command_Package::report_channel(KCM_Channel::Kinds k, QString prefix, QString suffix,
  Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 if(QString* qs = channel_names_map().value(k))
 {
  auto it = channels_.find(qs);
  if(it != channels_.end())
  {
   if(it->carriers().isEmpty())
     return on_empty;

   QString result = prefix;
   last_sep.prepend(suffix);
   int max = it->carriers().size() - 1;
   int i = 0;

   for(const KCM_Carrier& kcmc: it->carriers())
   {
    result += kcmc.token_report(kcm);
    result += (i < max)? sep : last_sep;
    ++i;
   }
   return result;
  }
 }
 return on_empty;
}

QString KCM_Command_Package::output_symbol_name()
{
 if(output_symbol_)
  return output_symbol_->symbol_name();
 return QString();
}


QString KCM_Command_Package::report_lambda(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 return report_channel(KCM_Channel::Kinds::Lambda, "", "", kcm, sep, last_sep, on_empty);
}
