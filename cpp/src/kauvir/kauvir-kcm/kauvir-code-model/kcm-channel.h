
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CHANNEL__H
#define KCM_CHANNEL__H


#include "kans.h"

#include "accessors.h"

#include "kcm-carrier.h"

#include <QVector>

#include <QTextStream>


KANS_CLASS_DECLARE(CMD ,KCM_Runtime_Scope)

KANS_(KCM)

class KCM_Type_Object;

class KCM_Channel
{

public:

 enum class Kinds {
  N_A, Fuxe, Lambda, Sigma, Array, Capture, Gamma, Result, Error,
  Preempt_Any, Preempt_Return, Preempt_Continue, Preempt_Break,
  CTOR_Mem, CTOR_Ret
 };

 enum class Code_Environments {
  N_A, Fuxe, Expression, Statement, File, Macro, Class
 };

private:

 Kinds kind_;

 QVector<KCM_Carrier> carriers_;

public:

 KCM_Channel();

 friend bool operator <(const KCM_Channel& lhs, const KCM_Channel& rhs)
 {
  return lhs.carriers() < rhs.carriers();
 }

 ACCESSORS(Kinds ,kind)
 ACCESSORS__RGET(QVector<KCM_Carrier> ,carriers)
 ACCESSORS__CONST_RGET(QVector<KCM_Carrier> ,carriers)


 void resize_to(int sz);

 void get_carrier_at_position(int position, KCM_Carrier& result);

 KCM_Carrier* get_carrier_at_position(int position);
 const KCM_Carrier* get_carrier_at_position(int position) const;

 const KCM_Type_Object* type_object_at_position(int position);

 void add_carrier(QPair<const KCM_Type_Object*, const KCM_Type_Object*> tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol = QString(), KCM_Runtime_Scope* scope = nullptr);

 void copy_from(const KCM_Channel& kch);


 void report(QTextStream& qts, Kauvir_Code_Model& kcm,
   KCM_Report_Syntax& kcrs, Code_Environments cenv);

 QString kind_to_string(KCM_Report_Syntax& kcrs);

 static Kinds get_channel_kind_by_string(QString key);



};


_KANS(KCM)


#endif //KCM_CHANNEL__H
