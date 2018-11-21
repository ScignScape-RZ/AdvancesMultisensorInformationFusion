
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-expression.h"

#include "kans.h"

#include "kcm-channel-group.h"

#include "kauvir-code-model.h"-

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Expression::KCM_Expression(QString kcm_code, KCM_Channel_Group* channel_group)
  :  kcm_code_(kcm_code), kauvir_type_object_(nullptr),
     channel_group_(channel_group), implied_statement_(nullptr),
     ref_anon_(nullptr)
{
}


KCM_Expression::KCM_Expression(KCM_Channel_Group* channel_group)
  :  kauvir_type_object_(nullptr), channel_group_(channel_group),
     implied_statement_(nullptr), ref_anon_(nullptr)
{
}

KCM_Expression::KCM_Expression(KCM_Statement* implied_statement)
  :  kauvir_type_object_(nullptr), channel_group_(nullptr),
     implied_statement_(implied_statement), ref_anon_(nullptr)
{

}

void KCM_Expression::report(QTextStream& qts, Kauvir_Code_Model& kcm,
  KCM_Report_Syntax& kcrs)
{
 if(channel_group_)
 {
  channel_group_->report(qts, kcm, kcrs, KCM_Channel::Code_Environments::Expression);
 }
}

