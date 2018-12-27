
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_PACKAGE__H
#define KCM_COMMAND_PACKAGE__H

#include "kans.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "accessors.h"

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Overloadable_Symbol)
KANS_CLASS_DECLARE(KCM ,KCM_Expression)

USING_KANS(KCM)

KANS_(CMD)

class KCM_Command_Package : public KCM_Channel_Group
{
 KCM_Overloadable_Symbol* output_symbol_;

 const KCM_Type_Object* bind_kto_;
 QString bind_val_;
 QObject* bind_qob_;

 KCM_Expression* kcm_expression_;

public:

 KCM_Command_Package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names);

 KCM_Command_Package(const KCM_Channel_Group& kcg);

 KCM_Command_Package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names,
   const KCM_Type_Object* kto, QString val, QObject* bind_qob);

 ACCESSORS(KCM_Overloadable_Symbol* ,output_symbol)

 ACCESSORS(KCM_Expression* ,kcm_expression)

 ACCESSORS(const KCM_Type_Object* ,bind_kto)
 ACCESSORS(QString ,bind_val)
 ACCESSORS(QObject* ,bind_qob)

 QString* bind_val_as_pointer()
 {
  return &bind_val_;
 }

 QString output_symbol_name();


 QString report_channel(KCM_Channel::Kinds k, QString prefix, QString suffix,
   Kauvir_Code_Model& kcm, QString sep, QString last_sep, QString on_empty) const;

 QString report_sigma(Kauvir_Code_Model& kcm, QString sep, QString last_sep, QString on_empty) const;
 QString report_fuxe(Kauvir_Code_Model& kcm, QString sep, QString last_sep, QString on_empty) const;
 QString report_lambda(Kauvir_Code_Model& kcm, QString sep, QString last_sep, QString on_empty) const;


};

_KANS(CMD)


#endif //KCM_COMMAND_PACKAGE__H

