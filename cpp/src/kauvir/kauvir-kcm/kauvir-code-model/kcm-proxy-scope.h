
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_PROXY_SCOPE__H
#define KCM_PROXY_SCOPE__H


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

class KCM_Expression;
class KCM_Channel_Bridge;

class KCM_Proxy_Scope
{
 KCM_Proxy_Scope* parent_;
 KCM_Channel_Bridge* kcm_channel_bridge_;

 QMap<QString, QPair<const KCM_Type_Object*, QString>> proxy_symbols_;


public:

 KCM_Proxy_Scope(KCM_Proxy_Scope* parent = nullptr);

 ACCESSORS(KCM_Channel_Bridge* ,kcm_channel_bridge)

 void add_proxy_symbol(QString symbol_name, const KCM_Type_Object* kto);
 void init_proxy_symbol(QString symbol_name, QString proxy_coords_code);

 QString find_proxy_coords_for_symbol_name(QString symbol_name, const KCM_Type_Object*& kto);
};


_KANS(KCM)


#endif //KCM_PROXY_SCOPE__H

