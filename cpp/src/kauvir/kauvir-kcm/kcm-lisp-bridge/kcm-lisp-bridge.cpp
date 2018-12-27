
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-lisp-bridge.h"

#include "kcm-lisp-eval.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kcm-statement.h"
#include "kauvir-code-model/kcm-block.h"
#include "kauvir-code-model/kcm-channel.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kcm-lisp-runtime-argument.h"

#include "kcm-scopes/kcm-runtime-scope.h"
#include "kcm-scopes/kcm-scope-system.h"

#include "kauvir-code-model/kcm-source-function.h"


#include <QFile>
#include <QDebug>

USING_KANS(KCL)

KCM_Lisp_Bridge::KCM_Lisp_Bridge()
{

}


KCM_Lisp_Bridge::KCM_Lisp_Bridge(const KCM_Lisp_Bridge& rhs)
  :  kcm_(rhs.kcm_)
{

}

void KCM_Lisp_Bridge::init_kcm()
{
 kcm_ = new Kauvir_Code_Model;
}

KCM_Channel_Group* KCM_Lisp_Bridge::new_KCM_Channel_Group()
{
 return new KCM_Channel_Group(kcm_->channel_names());
}


Kauvir_Type_System* KCM_Lisp_Bridge::get_type_system()
{
 return kcm_->type_system();
}

KCM_File* KCM_Lisp_Bridge::kcm_create_and_enter_file(QString file_path)
{
 return kcm_->create_and_enter_file(file_path);
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object_from_channel_group(KCM_Channel_Group* kcg)
{
 return kcm_->type_object_from_channel_group(*kcg);
}

int KCM_Lisp_Bridge::kcm_add_overloadable_type_binding(QString symbol_name, KCM_Type_Object* kto)
{
 return kcm_->add_overloadable_type_binding(symbol_name, kto);
}

void KCM_Lisp_Bridge::kcs_set_annotation(KCM_Statement* kcs, QString text)
{
 kcs->set_annotation(text);
}

void KCM_Lisp_Bridge::kcm_add_statement_to_file(KCM_Statement* kcs, KCM_File* kcf)
{
 kcm_->add_statement_to_file(kcs, kcf);
}

KCM_Block* KCM_Lisp_Bridge::kcm_create_and_enter_block()
{
 return kcm_->create_and_enter_block();
}

void KCM_Lisp_Bridge::kcg_lambda_carrier_from_result_channel(KCM_Channel_Group* kcg, int level, int index)
{
 kcg->add_lambda_carrier_from_result_channel(level, index);
}


void KCM_Lisp_Bridge::kcm_finalize_fdef(quint64 clo, QString symbol_name)
{
 kcm_->finalize_fdef(clo, symbol_name);
}

void KCM_Lisp_Bridge::kcm_prepare_nested_expression(KCM_Expression* kcx, int level, int index)
{
 kcm_->prepare_nested_expression(kcx, level, index);
}

void KCM_Lisp_Bridge::kcm_prepare_nested_defer_expression(KCM_Expression* kcx,
  int hdcode, int level, int index)
{
 kcm_->prepare_nested_defer_expression(kcx, hdcode, level, index);
}

void KCM_Lisp_Bridge::kcm_hold_deferred(int hdcode, quint64 qclo)
{
 kcm_->hold_deferred(hdcode, qclo);
}

void KCM_Lisp_Bridge::_kcm_hold_opaque_lisp_value(QString key, Opaque_Lisp_Value olv)
{
 // // does the cl_object fall out of scope somehow?
 const KCM_Type_Object* kto;
 QString encoded_value;
 KCM_Lisp_Eval::Opaque_Lisp_Value_Types olvt;
 KCM_Lisp_Eval::parse_opaque_lisp_value(olv, olvt, encoded_value);
 switch(olvt)
 {
 case KCM_Lisp_Eval::Opaque_Lisp_Value_Types::Fixnum_U32:
  kto = kcm_type_object__u32();
  break;
 case KCM_Lisp_Eval::Opaque_Lisp_Value_Types::Str:
  kto = kcm_type_object__str();
  break;
 default:
  kto = nullptr;
  break;
 }
 if(olvt == KCM_Lisp_Eval::Opaque_Lisp_Value_Types::Held_List)
 {
  kcm_->hold_runtime_list(key, (quint64) olv.value);
 }
 if(kto)
 {
  kcm_->hold_runtime_value(key, kto, encoded_value);
 }
}

void KCM_Lisp_Bridge::kcm_finalize_nested_form_group(KCM_Expression* kcx)
{
 //?
}


quint64 KCM_Lisp_Bridge::get_interpreted_value_of_symbol(QString symbol_name, QString& mode)
{
 KCM_Scope_System* scopes = kcm_->scope_system();
 const KCM_Type_Object* kto;
 quint64 v = KCM_Lisp_Bridge::get_value_of_symbol(symbol_name, scopes, &kto);
 if(kto->is_number_like())
 {
  mode = "fixnum";
  return *((quint64*) v);
 }
 if(kto->is_string_like())
 {
  QString* qs = (QString*) *(quint64*) v;
  mode = "str";
  return (quint64) qs;
 }
 return v;
}


quint64 KCM_Lisp_Bridge::get_value_of_symbol(QString symbol_name,
  KCM_Scope_System* scopes, const KCM_Type_Object** rkto)
{
 const KCM_Type_Object* kto = nullptr;
 const KCM_Type_Object* ckto = nullptr;
 KCM_Expression* kcx = nullptr;
 QString encoded_value;
 QPair<int, quint64> qclo_value;

 void* raw_value = scopes->find_raw_value_from_current_scope(symbol_name,
   nullptr, kcx,
   kto, ckto, encoded_value, qclo_value, rkto);

 quint64 result = (quint64) raw_value;

 return result;

}


quint64 KCM_Lisp_Bridge::get_value_of_symbol(QString symbol_name)
{
 KCM_Scope_System* scopes = kcm_->scope_system();

 return KCM_Lisp_Bridge::get_value_of_symbol(symbol_name, scopes);
}

void KCM_Lisp_Bridge::_kcg_add_result_to_lambda_channel_bridge(Opaque_Lisp_Value olv1, Opaque_Lisp_Value olv2)
{
 KCM_Channel_Group* kcg = (KCM_Channel_Group*) KCM_Lisp_Eval::opaque_lisp_value_to_pVoid(olv1);
 const KCM_Type_Object* kto;
 QString encoded_value;
 KCM_Lisp_Eval::Opaque_Lisp_Value_Types olvt;
 KCM_Lisp_Eval::parse_opaque_lisp_value(olv2, olvt, encoded_value);
 switch(olvt)
 {
 case KCM_Lisp_Eval::Opaque_Lisp_Value_Types::Fixnum_U32:
  kto = kcm_type_object__u32();
  break;
 case KCM_Lisp_Eval::Opaque_Lisp_Value_Types::Str:
  kto = kcm_type_object__str();
  break;
 default:
  kto = nullptr;
  break;
 }
 if(kto)
 {
  kcg_add_lambda_carrier_via_typed_opaque_value(kcg, kto, encoded_value);
 }
}

void KCM_Lisp_Bridge::kcm_leave_block(KCM_Block* kcb)
{
 return kcm_->leave_block(kcb);
}

void KCM_Lisp_Bridge::kcm_join_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb)
{
 kcm_->join_statement_to_block(kcs, kcb);
}

void KCM_Lisp_Bridge::kcg_clear_all(KCM_Channel_Group* kcg)
{
 kcg->clear_all();
}

void KCM_Lisp_Bridge::kcg_clear_all_but_sigma(KCM_Channel_Group* kcg)
{
 kcg->clear_all_but_sigma();
}

KCM_Expression* KCM_Lisp_Bridge::kcm_dissolve_to_nested_expression(KCM_Channel_Group* kcg)
{
 return kcm_->dissolve_to_nested_expression(*kcg);
}

KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_with_modifiers(KCM_Type_Object* kto, QString mods)
{
 KCM_Type_Object::Modifiers ms = KCM_Type_Object::get_modifier_by_string(mods);
 if(ms == KCM_Type_Object::Modifiers::N_A)
 {
  qDebug() << "Unrecognized type modifier: " << mods;
  return kto;
 }
 return kcm_->type_with_modifiers(kto, ms);
}

KCM_Expression* KCM_Lisp_Bridge::kcm_dissolve_to_precoded_nested_expression(KCM_Channel_Group* kcg, QString kcm_code)
{
 return kcm_->dissolve_to_nested_expression(*kcg, kcm_code);
}



KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_with_array_length(KCM_Type_Object* kto, int len)
{
 return kcm_->type_with_array_length(kto, len);
}

void KCM_Lisp_Bridge::kcm_kcg_add_fuxe_carrier(KCM_Channel_Group* kcg, const KCM_Type_Object* kto, QString symbol_name)
{
 kcm_->kcg_add_fuxe_carrier(kcg, kto, symbol_name);
}


const KCM_Type_Object* KCM_Lisp_Bridge::kcm_get_kcm_type_by_kauvir_type_object(Kauvir_Type_Object* kto)
{
 return kcm_->get_kcm_type_by_kauvir_type_object(kto);
}

KCM_Expression* KCM_Lisp_Bridge::kcm_promote_type_binding_to_statement_via_type_default_literal__let(KCM_Channel_Group* kcg, QString symbol_name)
{
 return kcm_->promote_type_binding_to_statement_via_type_default_literal__let(kcg, symbol_name);
}

void KCM_Lisp_Bridge::kcm_add_type_binding(QString symbol_name, const KCM_Type_Object* kto)
{
 kcm_->add_type_binding(symbol_name, kto);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_overloadable_function_type_binding_to_statement(QString symbol_name, const KCM_Type_Object* kto)
{
 return kcm_->promote_overloadable_function_type_binding_to_statement(symbol_name, kto);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_type_binding_to_statement(QString symbol_name)
{
 return kcm_->promote_type_binding_to_statement(symbol_name);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_overloadable_type_binding_to_statement(QString symbol_name, int oli)
{
 return kcm_->promote_type_binding_to_statement(symbol_name, oli);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_type_binding_to_statement_with_expression(QString symbol_name, KCM_Expression* kcx)
{
 return kcm_->promote_type_binding_to_statement(symbol_name, kcx);
}

void KCM_Lisp_Bridge::kcm_add_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb)
{
 kcm_->add_statement_to_block(kcs, kcb);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_symbol_and_type_name(KCM_Channel_Group* kcg,
   QString symbol_name, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 kcg->add_lambda_carrier_via_symbol(kto, symbol_name);
}


void KCM_Lisp_Bridge::kcm_prepare_proxy_symbol(QString symbol_name, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 kcm_->prepare_proxy_symbol(symbol_name, kto);
}

void KCM_Lisp_Bridge::kcm_prepare_anon_fdef_expression(const KCM_Type_Object* kto,
  QString anon_code)
{
 kcm_->prepare_anon_fdef_expression(kto, anon_code);
}

void KCM_Lisp_Bridge::kcm_kcg_add_lambda_carrier_of_anon_fdef(KCM_Channel_Group* kcg, QString anon_code)
{
 kcm_->kcg_add_lambda_carrier_of_anon_fdef(kcg, anon_code);
}

void KCM_Lisp_Bridge::kcm_enter_runtime_scope()
{
 kcm_->enter_runtime_scope(*this);
}

void KCM_Lisp_Bridge::kcm_leave_runtime_scope()
{
 kcm_->leave_runtime_scope(*this);
}

void KCM_Lisp_Bridge::kcm_enter_plebod()
{
 kcm_->enter_plebod();
}

void KCM_Lisp_Bridge::kcm_init_proxy_symbol(QString symbol_name, QString proxy_coords_code)
{
 kcm_->init_proxy_symbol(symbol_name, proxy_coords_code);
}


void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 kcg->add_lambda_carrier({kto, nullptr});
}

void KCM_Lisp_Bridge::kcg_add_sigma_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 kcg->add_sigma_carrier({kto, nullptr});
}


void KCM_Lisp_Bridge::kcg_add_empty_lambda_channel(KCM_Channel_Group* kcg)
{
 kcg->add_empty_lambda_channel();
}

void KCM_Lisp_Bridge::kcg_add_empty_return_channel(KCM_Channel_Group* kcg)
{
 kcg->add_empty_result_channel();
}

void KCM_Lisp_Bridge::kcg_add_empty_error_channel(KCM_Channel_Group* kcg)
{
 kcg->add_empty_error_channel();
}

void KCM_Lisp_Bridge::kcg_add_empty_context_channel(KCM_Channel_Group* kcg)
{
 kcg->add_empty_capture_channel();
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_bind_symbol(KCM_Channel_Group* kcg, QString symbol_name)
{
 const KCM_Type_Object* kto = kcm_->retrieve_type_binding(symbol_name);
 kcg->add_lambda_carrier_via_bind_symbol(kto, symbol_name);
}

void KCM_Lisp_Bridge::kcg_add_return_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 kcg->add_result_carrier({kto, nullptr});
}

void KCM_Lisp_Bridge::kcg_add_result_carrier_via_type_from_bind_symbol(KCM_Channel_Group* kcg, QString symbol_name)
{
 const KCM_Type_Object* kto = kcm_->retrieve_type_binding(symbol_name);
 kcg->add_result_carrier({kto, nullptr});
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_typed_opaque_value(KCM_Channel_Group* kcg,
  const KCM_Type_Object* kto, QString value_encoding)
{
 kcg->add_lambda_carrier_via_typed_opaque_value(kto, value_encoding);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_typed_literal(KCM_Channel_Group* kcg,
  const KCM_Type_Object* kto, QString value)
{
 kcg->add_lambda_carrier_via_typed_literal(kto, value);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_typed_literal_with_cast(KCM_Channel_Group* kcg,
  const KCM_Type_Object* kto, const KCM_Type_Object* ckto, QString value)
{
 kcg->add_lambda_carrier_via_typed_literal_with_cast(kto, value, ckto);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_symbol(KCM_Channel_Group* kcg, QString symbol_name)
{
 kcg->add_lambda_carrier_via_symbol(symbol_name);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_scoped_symbol(KCM_Channel_Group* kcg, QString symbol_name)
{
 KCM_Runtime_Scope* scope = kcm_->get_current_runtime_scope();
 kcg->add_lambda_carrier_via_scoped_symbol(symbol_name, scope);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_scoped_symbol_and_type_name(KCM_Channel_Group* kcg,
   QString symbol_name, QString type_name)
{
 const KCM_Type_Object* kto = kcm_->get_kcm_type_by_type_name(type_name);
 KCM_Runtime_Scope* scope = kcm_->get_current_runtime_scope();
 kcg->add_lambda_carrier_via_typed_scoped_symbol(kto, symbol_name, scope);
}


void KCM_Lisp_Bridge::kcg_add_sigma_carrier_via_symbol(KCM_Channel_Group* kcg, QString symbol_name)
{
 kcg->add_sigma_carrier_via_symbol(symbol_name);
}

void KCM_Lisp_Bridge::kcg_add_sigma_carrier_via_symbol_with_cast(KCM_Channel_Group* kcg,
  QString symbol_name, const KCM_Type_Object* kto, const KCM_Type_Object* ckto)
{
 kcg->add_sigma_carrier_via_symbol_with_cast(symbol_name, kto, ckto);
}

void KCM_Lisp_Bridge::kcg_add_sigma_carrier_via_literal(KCM_Channel_Group* kcg, QString text)
{
 kcg->add_sigma_carrier_via_literal(text);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_expression_to_statement(KCM_Expression* kcx)
{
 return kcm_->promote_expression_to_statement(kcx);
}

KCM_Statement* KCM_Lisp_Bridge::kcm_promote_type_binding_to_statement_with_nested_block(QString symbol_name, KCM_Type_Object* kto)
{
 return kcm_->promote_type_binding_to_statement_with_nested_block(symbol_name, kto);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_symbol_with_cast(KCM_Channel_Group* kcg,
  QString symbol_name, KCM_Type_Object* ckto)
{
 kcg->add_lambda_carrier_via_symbol_with_cast(symbol_name, ckto);
}

void KCM_Lisp_Bridge::kcg_add_lambda_carrier_via_literal(KCM_Channel_Group* kcg, QString text)
{
 kcg->add_lambda_carrier_via_literal(text);
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__u64()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__u64());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__u32()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__u32());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__u8()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__u8());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__s64()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__s64());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__s32()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__s32());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__s8()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__s32());
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object__str()
{
 return kcm_->get_kcm_type_by_kauvir_type_object(&kcm_->type_system()->type_object__str());
}


KCM_Statement* KCM_Lisp_Bridge::kcm_promote_type_binding_to_statement_with_token(QString symbol_name, KCM_Type_Object* kto, QString val)
{
 return kcm_->promote_type_binding_to_statement_with_token(symbol_name, kto, val);
}

void KCM_Lisp_Bridge::run_source_function(KCM_Command_Runtime_Router& kcrr, KCM_Source_Function& ksf)
{
 KCM_Lisp_Eval::run_source_function(kcrr, ksf.cl_object());
}

void KCM_Lisp_Bridge::_kcm_load_bridge(QString key, Opaque_Lisp_Value olv)
{
 KCM_Channel_Bridge* bridge = (KCM_Channel_Bridge*) KCM_Lisp_Eval::opaque_lisp_value_to_pVoid(olv);
 kcm_->load_bridge(bridge);
}

void KCM_Lisp_Bridge::kcm_direct_eval(KCM_Command_Package* cpkg)
{
 kcm_->direct_eval(cpkg, this);
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object_by_qobject_type_name(QString tn)
{
 return kcm_->type_object_by_qobject_type_name(tn);
}

const KCM_Type_Object* KCM_Lisp_Bridge::kcm_type_object_by_qregistered_type_name(QString tn)
{
 return kcm_->type_object_by_qregistered_type_name(tn);
}

void KCM_Lisp_Bridge::kcm_prepare_fdef_clo(KCM_Statement* kcs, int index)
{
 //?kcm_->prepare_fdef_clo(kcs, index);
}

KCM_Command_Package* KCM_Lisp_Bridge::kcm_statement_to_command_package(KCM_Statement* kcs)
{
 return kcm_->statement_to_command_package(kcs);
}

