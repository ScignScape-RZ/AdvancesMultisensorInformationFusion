
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-runtime-table.h"


#include "kauvir-code-model/kcm-channel-group.h"

#include "kans.h"

#include <QQueue>

USING_KANS(Kauvir)
USING_KANS(CMD)




KCM_Command_Runtime_Table::KCM_Command_Runtime_Table(Kauvir_Type_System& type_system)
  :  type_system_(type_system)
{

}


void KCM_Command_Runtime_Table::add_declared_function_package(QString name, Phaon_Function phf)
{
 strip_hyphens(name);
 (*this)[name].push_back(phf);
}


KCM_Channel_Group* KCM_Command_Runtime_Table::find_channel_group(const KCM_Channel_Group& channels)
{
 if(group_pointers_.contains(channels))
 {
  return group_pointers_.value(channels);
 }
 KCM_Channel_Group* result = new KCM_Channel_Group(channels);
 group_pointers_[channels] = result;
 return result;
}

s1_fng_type KCM_Command_Runtime_Table::find_s1_declared_function_0(QString name,
  KCM_Channel_Group* kcg, const KCM_Type_Object** pkto)
{
 for(QPair<KCM_Channel_Group*, s1_fng_type> pr : s1_declared_functions_generic_.values(name))
 {
  if(pkto)
  {
   KCM_Channel_Group* k_ = pr.first;
   KCM_Channel& result = k_->result_ch();
   if(!result.carriers().isEmpty())
   {
    KCM_Carrier r1;
    result.get_carrier_at_position(0, r1);
    *pkto = r1.type_object();
   }
   else
   {
    *pkto = nullptr;
   }
  }
  return (s1_fng_type)(pr.second);
 }
 return nullptr;
}
