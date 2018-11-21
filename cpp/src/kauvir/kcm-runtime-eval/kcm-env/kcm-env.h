
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_ENV__H
#define KCM_ENV__H


#include "kans.h"

#include "kauvir-type-system/kauvir-universal-class.h"

#include <QString>
#include <functional>


KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)

class KCM_Lisp_Bridge;

KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)

USING_KANS(CMD)

class KCM_Env : public Kauvir_Universal_Class
{
 KCM_Scope_System* scopes_;
 Kauvir_Code_Model* kcm_;

 typedef std::function<void (Kauvir_Code_Model*, KCM_Channel_Group*)> report_channel_group_fn_type;

 report_channel_group_fn_type report_channel_group_fn_;

 typedef std::function<void (Kauvir_Code_Model*,
   KCM_Channel_Group*, QString, QString, QString*)> kph_gen_fn_type;
 kph_gen_fn_type kph_gen_fn_;

public:

 KCM_Env(Kauvir_Code_Model* kcm);

 ACCESSORS(KCM_Scope_System* ,scopes)
 ACCESSORS(Kauvir_Code_Model* ,kcm)
 ACCESSORS(report_channel_group_fn_type ,report_channel_group_fn)
 ACCESSORS(kph_gen_fn_type ,kph_gen_fn)

 void report_channel_group(KCM_Channel_Group* kcg);

 void kph_gen(KCM_Channel_Group* kcg, QString subs, QString fn, QString* text);
 void kph_gen(KCM_Channel_Group* kcg, QString fn, QString* text);
};


#endif //KCM_ENV__H
