
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-lexical-scope.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-type-system.h"


USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Lexical_Scope::KCM_Lexical_Scope(KCM_Lexical_Scope* parent)
  :  parent_(parent), associated_block_(nullptr), last_key_for_storing_(0)
{

}

KCM_Lexical_Scope::KCM_Lexical_Scope(QString file_path)
  :  file_path_(file_path), parent_(nullptr), associated_block_(nullptr), last_key_for_storing_(0)
{

}

void KCM_Lexical_Scope::increment_key_for_storing()
{
 ++last_key_for_storing_;
}

void KCM_Lexical_Scope::store_key(QString key, quint64 clo)
{
 keys_for_storing_.insert(key, clo);
}

quint64 KCM_Lexical_Scope::find_held_lisp_list(QString key)
{
 return keys_for_storing_.value(key);
}

void KCM_Lexical_Scope::add_symbol(QString symbol_name, const KCM_Type_Object* kto)
{
 symbols_.insert(symbol_name, kto);
}

const KCM_Type_Object* KCM_Lexical_Scope::get_type_object_from_symbol_name(QString symbol_name)
{
 return symbols_.value(symbol_name);
}

const KCM_Type_Object* KCM_Lexical_Scope::get_type_object_from_symbol_name(QString symbol_name, bool& found)
{
 if(symbols_.contains(symbol_name))
 {
  found = true;
  return symbols_.value(symbol_name);
 }
 found = false;
 return nullptr;
}

void KCM_Lexical_Scope::hold_runtime_value(const QPair< QPair<KCM_Expression*, int>, QPair<int, int> >& coords,
  const KCM_Type_Object* kto, QString value_encoding, QString key)
{
 // // key has two levels of coords ...
 nested_expression_store_[coords] = {kto, {value_encoding, key} };
 nested_expression_key_index_[key] = coords.first;

 if(coords.first.second > 0)
   nested_expression_key_index_map_[coords.first.second] = {coords.first.first, coords.second};
}

quint64 KCM_Lexical_Scope::find_held_value_by_hdcode(int hdcode)
{
 QPair<KCM_Expression*, QPair<int, int>> pr = nested_expression_key_index_map_.value(hdcode,
   {nullptr, {0,0}});
 if(pr.first)
 {
  auto fnd = nested_expression_store_.find({{pr.first, hdcode}, pr.second});
  if(fnd != nested_expression_store_.end())
  {
   QPair<const KCM_Type_Object*, QPair<QString, QString>> v = fnd.value();
   QString v1 = v.second.first;
   QString v2 = v.second.second;
   return keys_for_storing_.value(v1);
  }
 }
 return 0;
}

void KCM_Lexical_Scope::hold_deferred(const QPair<KCM_Expression*,
  QPair<int, int> >& coords,
  const KCM_Type_Object* qto, int hdcode, quint64 clo_value)
{
 held_deferred_store_[coords] = {qto, {hdcode, clo_value}};
}



KCM_Expression* KCM_Lexical_Scope::get_kcm_expression_from_nested_key(QString key)
{
 return nested_expression_key_index_.value(key).first;
}


const KCM_Type_Object* KCM_Lexical_Scope::find_runtime_value(KCM_Expression* kcx,
  int level, int index, QString& encoded_value, QPair<int, quint64>& qclo_value, int hdcode)
{
 if(nested_expression_store_.contains({ {kcx,hdcode}, {level, index}}))
 {
  encoded_value = nested_expression_store_.value({{kcx,hdcode}, {level, index}}).second.first;
  return nested_expression_store_.value({{kcx,hdcode}, {level, index}}).first;
 }
 if(held_deferred_store_.contains({kcx, {level, index}}))
 {
  qclo_value = held_deferred_store_.value({kcx, {level, index}}).second;
  encoded_value = "\\cldv";
  return held_deferred_store_.value({kcx, {level, index}}).first;
 }
 return nullptr;
}


