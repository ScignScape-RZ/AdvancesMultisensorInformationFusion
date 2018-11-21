
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-scope-system.h"
#include "kcm-runtime-scope.h"

#include "kans.h"

USING_KANS(CMD)


KCM_Scope_System::KCM_Scope_System()
  :  current_scope_(new KCM_Runtime_Scope(nullptr))
{

}

const KCM_Type_Object* KCM_Scope_System::get_type_object_from_symbol_name(QString sn)
{
 return current_scope_->get_type_object_from_symbol_name(sn);
}


quint64 KCM_Scope_System::find_temporary_bridge_value(QString code, const KCM_Type_Object*& kto)
{
 if(temporary_bridge_values_.contains(code))
 {
  QPair<quint64, const KCM_Type_Object*> pr = temporary_bridge_values_.value(code);
  kto = pr.second;

  // always erase?
  temporary_bridge_values_.remove(code);

  return pr.first;
 }
 return 0;
}

void KCM_Scope_System::hold_temporary_bridge_value(QString code, quint64 value, const KCM_Type_Object* kto)
{
 temporary_bridge_values_.insert(code, {value, kto});
}


void KCM_Scope_System::join_lexical_scope(KCM_Lexical_Scope* associated_lexical_scope)
{
 current_scope_->set_associated_lexical_scope(associated_lexical_scope);
}

void KCM_Scope_System::enter_scope()
{
 current_scope_ = new KCM_Runtime_Scope(current_scope_);
}

quint64* KCM_Scope_System::find_raw_value_from_current_scope(QString bind_code,
  void*(*efn)(void*), KCM_Expression* kcm_expression, const KCM_Type_Object*& kto,
  const KCM_Type_Object*& ckto, QString& encoded_value, QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto)
{
 if(bind_code.startsWith("#*"))
 {
  if(efn)
  {
   QString n = bind_code.mid(2);
   void* v = (*efn)(&n);
   return (quint64*) v;
  }
 }
 return find_raw_value_from_scope(current_scope_, bind_code,
   kcm_expression, kto, ckto, encoded_value, qclo_value, skto);
}

KCM_Source_Function* KCM_Scope_System::find_source_function_from_current_scope(QString local_name)
{
 return (KCM_Source_Function*) current_scope_->find_source_function_value(local_name);
}


quint64 KCM_Scope_System::find_held_lisp_list_from_current_scope(QString key)
{
 return current_scope_->find_held_lisp_list(key);
}

quint64 KCM_Scope_System::find_held_value_by_hdcode(int hdcode)
{
 return current_scope_->find_held_value_by_hdcode(hdcode);
}

quint64* KCM_Scope_System::find_raw_value_from_scope(KCM_Runtime_Scope* scope,
  QString bind_code, KCM_Expression* kcm_expression, const KCM_Type_Object*& kto,
  const KCM_Type_Object*& ckto, QString& encoded_value, QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto)
{
 quint64* result;
 scope->find_value(bind_code, kcm_expression, result, kto, ckto, encoded_value, qclo_value, skto);
 if(!result)
 {
  KCM_Runtime_Scope* parent_scope = scope->parent_scope();
  if(parent_scope)
   return find_raw_value_from_scope(parent_scope, bind_code, kcm_expression, kto, ckto, encoded_value,
     qclo_value, skto);
  return nullptr;
 }
 return result;
}

void KCM_Scope_System::leave_scope()
{
 current_scope_ = current_scope_->parent_scope();
}



