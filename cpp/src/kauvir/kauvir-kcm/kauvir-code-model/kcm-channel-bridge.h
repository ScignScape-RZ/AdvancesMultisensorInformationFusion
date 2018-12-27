
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CHANNEL_BRIDGE__H
#define KCM_CHANNEL_BRIDGE__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QMap>

KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_System)
USING_KANS(Kauvir)

KANS_(KCM)


class KCM_Type_Object;
class KCM_Channel_Group;
class KCM_Block;
class KCM_Carrier;

class KCM_Expression;

class KCM_Proxy_Scope;

class KCM_Channel_Bridge
{
 KCM_Channel_Group* channel_group_;
 KCM_Proxy_Scope* proxy_scope_;

public:

 KCM_Channel_Bridge(KCM_Channel_Group* channel_group);

 ACCESSORS(KCM_Channel_Group* ,channel_group)
 ACCESSORS(KCM_Proxy_Scope* ,proxy_scope)

 KCM_Carrier* get_carrier_by_proxy_coords_code(QString pxyc);

};


_KANS(KCM)


#endif //KCM_LEXICAL_SCOPE__H

