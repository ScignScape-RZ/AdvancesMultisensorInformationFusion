
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-channel-bridge.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kcm-channel-group.h"

#include "kcm-type-object.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Channel_Bridge::KCM_Channel_Bridge(KCM_Channel_Group* channel_group)
  :  channel_group_(channel_group), proxy_scope_(nullptr)
{

}

KCM_Carrier* KCM_Channel_Bridge::get_carrier_by_proxy_coords_code(QString pxyc)
{
 if(!channel_group_)
 {
  return nullptr;
 }
 if(pxyc.isEmpty())
 {
  return nullptr;
 }
 QChar c0 = pxyc[0];
 int index = pxyc.mid(1).toInt();

 if(index == 0)
 {
  return nullptr;
 }

 --index;

 switch(c0.toLatin1())
 {
 case 'L': return channel_group_->lambda_ch().get_carrier_at_position(index);
 default: break;
 }

 return nullptr;

}


