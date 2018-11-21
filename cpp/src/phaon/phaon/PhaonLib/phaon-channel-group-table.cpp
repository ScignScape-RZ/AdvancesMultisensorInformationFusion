
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phaon-channel-group-table.h"


#include "kauvir-code-model/kcm-channel-group.h"

#include "kans.h"

#include <QQueue>

USING_KANS(Kauvir)
USING_KANS(CMD)

USING_KANS(PhaonLib)


Phaon_Channel_Group_Table::Phaon_Channel_Group_Table(Kauvir_Type_System& type_system)
  :  type_system_(type_system)
{

}



KCM_Channel_Group* Phaon_Channel_Group_Table::find_channel_group(const KCM_Channel_Group& channels)
{
 if(group_pointers_.contains(channels))
 {
  return group_pointers_.value(channels);
 }
 KCM_Channel_Group* result = new KCM_Channel_Group(channels);
 group_pointers_[channels] = result;
 return result;
}
