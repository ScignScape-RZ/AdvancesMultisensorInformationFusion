
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_CHANNEL_GROUP_TABLE__H
#define PHAON_CHANNEL_GROUP_TABLE__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QSet>

#include "kans.h"
#include "accessors.h"

#include "kauvir-type-system/kauvir-universal-class.h"
#include "kauvir-type-system/kauvir-type-system.h"

#include "relae-graph/relae-caon-ptr.h"

#include "phaon-function.h"

#include "kauvir-code-model/kcm-function-package.h"
#include "phaon-symbol-scope.h"

KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)
USING_KANS(Kauvir)

KANS_(PhaonLib)

class Phaon_Channel_Group_Table
{
 QMap<KCM_Channel_Group, KCM_Channel_Group*> group_pointers_;


 QMultiMap<QString, QString> declared_types_;

 Kauvir_Type_System& type_system_;


public:

 Phaon_Channel_Group_Table(Kauvir_Type_System& type_system);

 ACCESSORS__GET(Kauvir_Type_System& ,type_system)

 KCM_Channel_Group* find_channel_group(const KCM_Channel_Group& channels);

 template<typename FN_Type>
 void init_phaon_function(const KCM_Channel_Group& g, Phaon_Symbol_Scope& pss,
    QString name, int head_code, FN_Type pfn)
 {
  KCM_Channel_Group* kcg = find_channel_group(g);

  Phaon_Function phf(pfn);

  caon_ptr<KCM_Function_Package> kfp = new KCM_Function_Package(kcg);
  kfp->init_byte_code(head_code);

  phf.augment(kfp);

  pss[name].push_back(phf);

 }


};

_KANS(PhaonLib)

#endif //PHAON_CHANNEL_GROUP_TABLE__H
