
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-env.h"

#include "kcm-scopes/kcm-scope-system.h"

#include <QDebug>

KCM_Env::KCM_Env(Kauvir_Code_Model* kcm)
  :  scopes_(nullptr), kcm_(kcm), report_channel_group_fn_(nullptr),
     kph_gen_fn_(nullptr)
{

}

void KCM_Env::report_channel_group(KCM_Channel_Group* kcg)
{
 if(report_channel_group_fn_)
 {
  report_channel_group_fn_(kcm_, kcg);
 }
}

void KCM_Env::kph_gen(KCM_Channel_Group* kcg, QString subs, QString fn,
  QString* text, QMap<QString, QString> docus)
{
 if(kph_gen_fn_)
 {
  kph_gen_fn_(kcm_, kcg, subs, fn, text, docus);
 }
}

void KCM_Env::kph_gen(KCM_Channel_Group* kcg, QString fn,
  QString* text, QMap<QString, QString> docus)
{
 if(kph_gen_fn_)
 {
  kph_gen_fn_(kcm_, kcg, QString(), fn, text, docus);
 }
}

