
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-runtime-scope.h"

#include "kcm-lexical-scope.h"

#include "kans.h"

USING_KANS(CMD)


KCM_Runtime_Scope::KCM_Runtime_Scope(KCM_Runtime_Scope* parent_scope)
  :  parent_scope_(parent_scope), associated_lexical_scope_(nullptr)
{

}

KCM_Source_Function* KCM_Runtime_Scope::find_source_function_value(QString symbol_name)
{
 // this so far does not account for overloads ...
 if(values_.contains(symbol_name))
 {
  return (KCM_Source_Function*) values_[symbol_name].first().second;
 }
 return nullptr;
}


void KCM_Runtime_Scope::add_string_value(QString symbol_name, const KCM_Type_Object* kto, QString s)
{
 QString* qs = new QString(s);
 str_ptrs_.push_back(qs);
 add_value(symbol_name, kto, (quint64) qs);
}

void KCM_Runtime_Scope::add_value(QString symbol_name, const KCM_Type_Object* kto, quint64 v)
{
 // automatically insert the keys when needed ...
 values_[symbol_name][kto] = {nullptr, v};
}

quint64 KCM_Runtime_Scope::find_held_lisp_list(QString key)
{
 if(associated_lexical_scope_)
 {
  return associated_lexical_scope_->find_held_lisp_list(key);
 }
 return 0;
}

void KCM_Runtime_Scope::add_declared_fn_type(QString str, const KCM_Type_Object* kto)
{
 declared_fn_types_[str].push_back(kto);
}

const KCM_Type_Object* KCM_Runtime_Scope::get_type_object_from_symbol_name(QString symbol_name)
{
 if(associated_lexical_scope_)
 {
  const KCM_Type_Object* result;
  bool found;
  result = associated_lexical_scope_->get_type_object_from_symbol_name(symbol_name, found);
  if(found)
  {
   return result;
  }
 }
 if(declared_fn_types_.contains(symbol_name))
 {
  if(!declared_fn_types_[symbol_name].isEmpty())
  {
   return declared_fn_types_[symbol_name].first();
  }
 }
 if(parent_scope_)
 {
  return parent_scope_->get_type_object_from_symbol_name(symbol_name);
 }
 return nullptr;
}

quint64 KCM_Runtime_Scope::find_held_value_by_hdcode(int hdcode)
{
 if(associated_lexical_scope_)
 {
  return associated_lexical_scope_->find_held_value_by_hdcode(hdcode);
 }
 return 0;
}

void KCM_Runtime_Scope::find_value(QString symbol_name, KCM_Expression* kcm_expression,
  quint64*& v,
  const KCM_Type_Object*& kto, const KCM_Type_Object*& ckto,
  QString& encoded_value, QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto)
{
 if(associated_lexical_scope_)
 {
  if(skto)
    *skto = associated_lexical_scope_->
    get_type_object_from_symbol_name(symbol_name);
 }

 if(values_.contains(symbol_name))
 {
  const QMap<const KCM_Type_Object*, QPair<const KCM_Type_Object*, quint64> >& qm =
    values_[symbol_name];
  kto = qm.begin().key();
  ckto = qm.begin().value().first;
  v = const_cast<quint64*>( &qm.begin().value().second );
 }
 else if(symbol_name.startsWith(":##"))
 {
  int cut = symbol_name.indexOf('-');

  int level = symbol_name.mid(3, cut - 3).toInt();
  int index = symbol_name.mid(cut + 1).toInt();
  if(associated_lexical_scope_)
  {
   kto = associated_lexical_scope_->
     find_runtime_value(kcm_expression, level, index, encoded_value, qclo_value);

   // // kto being nullptr means nested_expression_store_ couldn't
    //   find the expression/index pair ...

   // //  just to indicate we're using the encoding ...
   v = (quint64*) &encoded_value;
  }
 }
 else if(symbol_name.startsWith("#hold<"))
 {
  if(!kcm_expression)
  {
   kcm_expression = associated_lexical_scope_->get_kcm_expression_from_nested_key(symbol_name);
  }

  int cut = symbol_name.indexOf('-');

  QString levels = symbol_name.mid(6, cut - 6);
  QString indexs = symbol_name.mid(cut + 1);
  indexs.chop(1);

  int level = levels.toInt();
  int index = indexs.toInt();
  if(associated_lexical_scope_)
  {
   kto = associated_lexical_scope_->
     find_runtime_value(kcm_expression, level, index, encoded_value, qclo_value);

   // // kto being nullptr means nested_expression_store_ couldn't
    //   find the expression/index pair ...

   // //  just to indicate we're using the encoding ...
   v = (quint64*) &encoded_value;
  }
 }
}



