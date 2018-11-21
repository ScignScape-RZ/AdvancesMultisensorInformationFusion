
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-proxy-scope.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kcm-type-object.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Proxy_Scope::KCM_Proxy_Scope(KCM_Proxy_Scope* parent)
  :  parent_(parent), kcm_channel_bridge_(nullptr)
{

}

QString KCM_Proxy_Scope::find_proxy_coords_for_symbol_name(QString symbol_name, const KCM_Type_Object*& kto)
{
 if(proxy_symbols_.contains(symbol_name))
 {
  kto = proxy_symbols_[symbol_name].first;
  return proxy_symbols_[symbol_name].second;
 }
 return QString();
}

void KCM_Proxy_Scope::add_proxy_symbol(QString symbol_name, const KCM_Type_Object* kto)
{
 proxy_symbols_.insert(symbol_name, {kto, QString()});
}

void KCM_Proxy_Scope::init_proxy_symbol(QString symbol_name, QString proxy_coords_code)
{
 proxy_symbols_[symbol_name].second = proxy_coords_code;
}

