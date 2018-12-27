
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CHANNEL_GROUP__H
#define KCM_CHANNEL_GROUP__H


#include "kans.h"

#include "accessors.h"

#include "kcm-channel.h"

#include <QVector>
#include <QTextStream>
#include <QSet>

KANS_(KCM)


class KCM_Type_Object;
class KCM_Channel_Furnisher;

class KCM_Channel_Group
{
 KCM_Channel_Furnisher* furnisher_;

protected:

 QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names_;

 QMap<QString*, KCM_Channel> channels_;

 QString* get_channel_name_pointer(QString name, KCM_Channel::Kinds k = KCM_Channel::Kinds::N_A);

 QSet<QString*>& channel_names_set()
 {
  return *channel_names_.first;
 }

 QMap<KCM_Channel::Kinds, QString*>& channel_names_map()
 {
  return *channel_names_.second;
 }

 const QMap<KCM_Channel::Kinds, QString*>& channel_names_map() const
 {
  return *channel_names_.second;
 }


private:

 void set_kinds();

 typedef QPair<const KCM_Type_Object*, const KCM_Type_Object*> kcm_type_object_pair_type;

public:

 KCM_Channel_Group(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names);

 KCM_Channel_Group(const KCM_Channel_Group& rhs);

 ACCESSORS(KCM_Channel_Furnisher* ,furnisher)

 void channel_names_to_codes(QMap<QString, QPair<int, const KCM_Channel*>>& qmap);


 void init_channel_counts(const QMap<QString, int>& channel_counts);
 void init_carrier(Kauvir_Code_Model& kcm, QString channel_name,
    int pos, QString type_name, QString* value, QString symbol_name = QString());

 int get_lambda_byte_code();
 int get_sigma_lambda_byte_code();

 KCM_Channel& fuxe_ch();
 KCM_Channel& lambda_ch();
 KCM_Channel& result_ch();
 KCM_Channel& sigma_ch();
 KCM_Channel& error_ch();
 KCM_Channel& capture_ch();


 friend bool operator<(const KCM_Channel_Group& lhs, const KCM_Channel_Group& rhs)
 {
  if(lhs.channels_.size() == rhs.channels_.size())
  {
   QMapIterator<QString*, KCM_Channel> lit(lhs.channels_);
   QMapIterator<QString*, KCM_Channel> rit(rhs.channels_);
   while(lit.hasNext())
   {
    lit.next();
    rit.next();
    if(*lit.key() == *rit.key())
    {
     if(lit.value() < rit.value())
       return true;
     if(rit.value() < lit.value())
       return true;
    }
    else if(*lit.key() < *rit.key())
      return true;
    else return false;
   }
  }
  else if(lhs.channels_.size() < rhs.channels_.size())
  {
   return true;
  }
  return false;
 }

 void add_fuxe_carrier(const KCM_Type_Object* type_object);
 void add_fuxe_carrier(QString symbol_name);

 void add_empty_lambda_channel();
 void add_empty_result_channel();
 void add_empty_error_channel();
 void add_empty_capture_channel();

 void add_lambda_carrier_via_scoped_symbol(QString symbol_name, KCM_Runtime_Scope* scope);

 void add_lambda_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString(), KCM_Runtime_Scope* scope = nullptr);

 void add_sigma_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
                        QString symbol_name = QString());

 void add_capture_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
                          QString symbol_name = QString());

 void add_result_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString());

 void add_lambda_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_sigma_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_result_carrier(kcm_type_object_pair_type tos, QString value_name);

 void add_lambda_carrier_via_bind_symbol(const KCM_Type_Object* kto, QString symbol_name);

 void add_lambda_carrier_via_symbol(QString value_name);
 void add_lambda_carrier_via_symbol(const KCM_Type_Object* kto, QString value_name);
 void add_lambda_carrier_via_typed_scoped_symbol(const KCM_Type_Object* kto, QString value_name, KCM_Runtime_Scope* scope);

 void add_lambda_carrier_via_literal(QString value_name);

 void add_lambda_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name);
 void add_lambda_carrier_from_result_channel(int level, int index);

 void add_lambda_carrier_via_typed_opaque_value(const KCM_Type_Object* kto, QString value_encoding);

 void add_lambda_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
   QString value_name, const KCM_Type_Object* ckto);

 void add_lambda_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object);
 void add_lambda_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object);

 void add_sigma_carrier_via_symbol(QString value_name);
 void add_sigma_carrier_via_literal(QString value_name);

 void add_sigma_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name);
 void add_sigma_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
   QString value_name, const KCM_Type_Object* ckto);

 void add_sigma_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* kto,
    const KCM_Type_Object* ckto);
 void add_sigma_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object);

 void clear_all();

 void clear_all_but_sigma();

 KCM_Channel_Group* branch_copy();

 void report(QVector<KCM_Channel::Kinds> ks, QTextStream& qts, Kauvir_Code_Model& kcm,
   KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv);

 void report(QTextStream& qts, Kauvir_Code_Model& kcm,
   KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv);

 void check_report(KCM_Channel::Kinds k, QTextStream& qts, Kauvir_Code_Model& kcm,
   KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv);



};


_KANS(KCM)


#endif //KCM_CHANNEL_GROUP__H
