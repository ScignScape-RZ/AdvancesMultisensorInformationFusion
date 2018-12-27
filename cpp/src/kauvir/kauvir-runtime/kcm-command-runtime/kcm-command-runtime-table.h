
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_RUNTIME_TABLE__H
#define KCM_COMMAND_RUNTIME_TABLE__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QSet>

#include "kans.h"
#include "accessors.h"

#include "kauvir-type-system/kauvir-universal-class.h"
#include "kauvir-type-system/kauvir-type-system.h"


#include "PhaonLib/phaon-function.h"
#include "PhaonLib/phaon-symbol-scope.h"

#include "kauvir-code-model/kcm-function-package.h"



KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)
USING_KANS(Kauvir)

USING_KANS(PhaonLib)


KANS_(CMD)

class KCM_Command_Runtime_Table : public Phaon_Symbol_Scope
{
 QMap<KCM_Channel_Group, KCM_Channel_Group*> group_pointers_;
 KCM_Channel_Group* find_channel_group(const KCM_Channel_Group& channels);

 QMultiMap<QString, QPair<KCM_Channel_Group*, s1_fng_type>> s1_declared_functions_generic_;

 QMultiMap<QString, QString> declared_types_;

 Kauvir_Type_System& type_system_;

public:

 KCM_Command_Runtime_Table(Kauvir_Type_System& type_system);

 ACCESSORS__GET(Kauvir_Type_System& ,type_system)

 void add_declared_function_package(QString name, Phaon_Function phf);

 KCM_Channel_Group* add_s1_declared_function(QString name, const KCM_Channel_Group& channels);

 inline static void strip_hyphens(QString& s)
 {
  s.replace('-', '_');
 }

 template<typename FN_type>
 void add_s1_declared_function(QString name, KCM_Channel_Group* kcg, FN_type fn)
 {
  strip_hyphens(name);
  s1_declared_functions_generic_.insert(name, {kcg, (s1_fng_type)fn});
 }

 s1_fng_type find_s1_declared_function_0(QString name,
   KCM_Channel_Group* kcg, const KCM_Type_Object** pkto);

 template<typename FN_Type>
 void init_phaon_function(const KCM_Channel_Group& g,
    QString name, int head_code, FN_Type pfn)
 {
  KCM_Channel_Group* kcg = find_channel_group(g);

  caon_ptr<KCM_Function_Package> kfp = new KCM_Function_Package(kcg);
  kfp->init_byte_code(head_code);

  Phaon_Function phf(pfn);

  phf.augment(kfp);

  add_declared_function_package(name, phf);
 }

};

_KANS(CMD)

#endif //KCM_COMMAND_RUNTIME_TABLE__H
