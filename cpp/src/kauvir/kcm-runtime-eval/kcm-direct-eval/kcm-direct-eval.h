
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_DIRECT_EVAL__H
#define KCM_DIRECT_EVAL__H


#include "kans.h"

#include <QString>
#include <QObject>

#include "kauvir-code-model/kcm-channel.h"

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

KANS_CLASS_DECLARE(KCM ,KCM_Channel_Bridge)


USING_KANS(KCM)

class KCM_Lisp_Bridge;

KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)

USING_KANS(CMD)


void kcm_direct_eval(Kauvir_Code_Model* kcm, KCM_Command_Package* cpkg, KCM_Lisp_Bridge* bridge);

KCM_Command_Package* make_kcm_command_package_from_channel_group(const KCM_Channel_Group& kcg);

KCM_Command_Package* make_kcm_command_package(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names, const KCM_Type_Object* kto, QString val, QObject* qob);

KCM_Channel_Bridge* make_kcm_channel_bridge(KCM_Command_Runtime_Router& kcrr);

#endif //KCM_DIRECT_EVAL__H
