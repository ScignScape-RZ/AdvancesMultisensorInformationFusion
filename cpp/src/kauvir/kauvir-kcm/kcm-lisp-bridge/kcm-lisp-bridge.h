
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LISP_BRIDGE__H
#define KCM_LISP_BRIDGE__H

#include "kans.h"

#include "defines.h"


#ifdef USING_ECL


#include <QObject>

#include "kauvir-code-model/kauvir-code-model.h"

USING_KANS(KCM)

KANS_CLASS_DECLARE(KCM ,KCM_Source_Function)

KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
USING_KANS(CMD)


class KCM_Lisp_Bridge : public QObject
{
Q_OBJECT

 Kauvir_Code_Model* kcm_;

public:

 Q_INVOKABLE KCM_Lisp_Bridge();

 ACCESSORS(Kauvir_Code_Model* ,kcm)

 KCM_Lisp_Bridge(const KCM_Lisp_Bridge& rhs);

 void init_kcm();

 void run_source_function(KCM_Command_Runtime_Router& kcrr, KCM_Source_Function& ksf);

 static void bridge_run_source_function(KCM_Lisp_Bridge* _this,
   KCM_Command_Runtime_Router& kcrr, KCM_Source_Function& ksf)
 {
  _this->run_source_function(kcrr, ksf);
 }

 Q_INVOKABLE Kauvir_Type_System* get_type_system();

 Q_INVOKABLE const KCM_Type_Object* kcm_type_object_from_channel_group(KCM_Channel_Group* kcg);

 Q_INVOKABLE int kcm_add_overloadable_type_binding(QString symbol_name, KCM_Type_Object* kto);

 Q_INVOKABLE KCM_Statement* kcm_promote_overloadable_type_binding_to_statement(QString symbol_name, int oli);

 Q_INVOKABLE KCM_Statement* kcm_promote_type_binding_to_statement_with_expression(QString symbol_name, KCM_Expression* kcx);
 Q_INVOKABLE KCM_Statement* kcm_promote_type_binding_to_statement(QString symbol_name);

 Q_INVOKABLE KCM_Statement* kcm_promote_overloadable_function_type_binding_to_statement(QString symbol_name, const KCM_Type_Object* kto);

 Q_INVOKABLE KCM_Statement* kcm_promote_type_binding_to_statement_with_token(
   QString symbol_name, KCM_Type_Object* kto, QString val);

 Q_INVOKABLE void kcs_set_annotation(KCM_Statement* ksc, QString text);
 Q_INVOKABLE void kcm_add_statement_to_file(KCM_Statement* kcs, KCM_File* kcf);

 Q_INVOKABLE KCM_Block* kcm_create_and_enter_block();
 Q_INVOKABLE void kcm_join_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb);

 Q_INVOKABLE void _kcg_add_result_to_lambda_channel_bridge(Opaque_Lisp_Value olv1, Opaque_Lisp_Value olv2);

 Q_INVOKABLE void kcg_lambda_carrier_from_result_channel(KCM_Channel_Group* kcg, int level, int index);
 Q_INVOKABLE void kcm_prepare_nested_expression(KCM_Expression* kcx, int level, int index);

 Q_INVOKABLE void kcm_prepare_nested_defer_expression(KCM_Expression* kcx,
               int hdcode, int level, int index);

 Q_INVOKABLE void kcm_hold_deferred(int hdcode, quint64 qclo);




 Q_INVOKABLE void _kcm_hold_opaque_lisp_value(QString key, Opaque_Lisp_Value olv);

 Q_INVOKABLE void _kcm_load_bridge(QString key, Opaque_Lisp_Value olv);

 Q_INVOKABLE void kcm_finalize_nested_form_group(KCM_Expression* kcx);

 Q_INVOKABLE void kcm_prepare_anon_fdef_expression(const KCM_Type_Object* kto, QString anon_code);
 Q_INVOKABLE void kcm_kcg_add_lambda_carrier_of_anon_fdef(KCM_Channel_Group* kcg, QString anon_code);


 Q_INVOKABLE void kcm_enter_runtime_scope();
 Q_INVOKABLE void kcm_leave_runtime_scope();

 Q_INVOKABLE void kcg_clear_all(KCM_Channel_Group* kcg);
 Q_INVOKABLE void kcg_clear_all_but_sigma(KCM_Channel_Group* kcg);
 Q_INVOKABLE void kcm_kcg_add_fuxe_carrier(KCM_Channel_Group* kcg, const KCM_Type_Object* kto, QString symbol_name);
 Q_INVOKABLE const KCM_Type_Object* kcm_get_kcm_type_by_kauvir_type_object(Kauvir_Type_Object* kto);

 Q_INVOKABLE void kcm_add_type_binding(QString symbol_name, const KCM_Type_Object* kto);

 Q_INVOKABLE void kcm_prepare_proxy_symbol(QString symbol_name, QString type_name);
 Q_INVOKABLE void kcm_init_proxy_symbol(QString symbol_name, QString proxy_coords_code);

 Q_INVOKABLE void kcm_enter_plebod();

 Q_INVOKABLE void kcm_add_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb);

 Q_INVOKABLE KCM_Expression* kcm_promote_type_binding_to_statement_via_type_default_literal__let(KCM_Channel_Group* kcg, QString symbol_name);

 Q_INVOKABLE void kcm_leave_block(KCM_Block* kcb);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_typed_literal(KCM_Channel_Group* kcg,
   const KCM_Type_Object* kto, QString value);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_typed_opaque_value(KCM_Channel_Group* kcg,
   const KCM_Type_Object* kto, QString value_encoding);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_typed_literal_with_cast(KCM_Channel_Group* kcg,
   const KCM_Type_Object* kto, const KCM_Type_Object* ckto, QString value);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name);

 Q_INVOKABLE void kcg_add_sigma_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name);

 Q_INVOKABLE void kcg_add_empty_lambda_channel(KCM_Channel_Group* kcg);
 Q_INVOKABLE void kcg_add_empty_return_channel(KCM_Channel_Group* kcg);
 Q_INVOKABLE void kcg_add_empty_error_channel(KCM_Channel_Group* kcg);
 Q_INVOKABLE void kcg_add_empty_context_channel(KCM_Channel_Group* kcg);


 Q_INVOKABLE void kcg_add_lambda_carrier_via_symbol_and_type_name(KCM_Channel_Group* kcg,
   QString symbol_name, QString type_name);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_bind_symbol(KCM_Channel_Group* kcg, QString symbol_name);


 Q_INVOKABLE void kcg_add_return_carrier_via_type_name(KCM_Channel_Group* kcg, QString type_name);
 Q_INVOKABLE void kcg_add_result_carrier_via_type_from_bind_symbol(KCM_Channel_Group* kcg, QString symbol_name);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_symbol(KCM_Channel_Group* kcg, QString symbol_name);
 Q_INVOKABLE void kcg_add_lambda_carrier_via_scoped_symbol(KCM_Channel_Group* kcg, QString symbol_name);
 Q_INVOKABLE void kcg_add_lambda_carrier_via_scoped_symbol_and_type_name(KCM_Channel_Group* kcg,
   QString symbol_name, QString type_name);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_symbol_with_cast(KCM_Channel_Group* kcg,
   QString symbol_name, KCM_Type_Object* ckto);

 Q_INVOKABLE KCM_Statement* kcm_promote_expression_to_statement(KCM_Expression* kcx);

 Q_INVOKABLE KCM_Statement* kcm_promote_type_binding_to_statement_with_nested_block(QString symbol_name, KCM_Type_Object* kto);

 Q_INVOKABLE void kcm_prepare_fdef_clo(KCM_Statement* kcs, int index);
 Q_INVOKABLE void kcm_finalize_fdef(quint64 clo, QString symbol_name);

 Q_INVOKABLE void kcg_add_sigma_carrier_via_symbol(KCM_Channel_Group* kcg, QString symbol_name);
 Q_INVOKABLE void kcg_add_sigma_carrier_via_symbol_with_cast(KCM_Channel_Group* kcg,
   QString symbol_name, const KCM_Type_Object* kto, const KCM_Type_Object* ckto);
 Q_INVOKABLE void kcg_add_sigma_carrier_via_literal(KCM_Channel_Group* kcg, QString text);

 Q_INVOKABLE void kcg_add_lambda_carrier_via_literal(KCM_Channel_Group* kcg, QString text);

 Q_INVOKABLE quint64 get_value_of_symbol(QString symbol_name);
 Q_INVOKABLE quint64 get_interpreted_value_of_symbol(QString symbol_name, QString& mode);

 static quint64 get_value_of_symbol(QString symbol_name,
   KCM_Scope_System* scopes, const KCM_Type_Object** rkto = nullptr);

 Q_INVOKABLE void kcm_direct_eval(KCM_Command_Package* cpkg);
 Q_INVOKABLE KCM_Command_Package* kcm_statement_to_command_package(KCM_Statement* kcs);

 Q_INVOKABLE KCM_Expression* kcm_dissolve_to_precoded_nested_expression(KCM_Channel_Group* kcg, QString kcm_code);
 Q_INVOKABLE KCM_Expression* kcm_dissolve_to_nested_expression(KCM_Channel_Group* kcg);

 Q_INVOKABLE KCM_File* kcm_create_and_enter_file(QString file_path);


 Q_INVOKABLE KCM_Type_Object* kcm_type_with_array_length(KCM_Type_Object* kto, int len);
 Q_INVOKABLE KCM_Type_Object* kcm_type_with_modifiers(KCM_Type_Object* kto, QString mods);

 Q_INVOKABLE KCM_Channel_Group* new_KCM_Channel_Group();

 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__u64();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__u32();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__u8();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__s64();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__s32();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__s8();
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object__str();

 Q_INVOKABLE const KCM_Type_Object* kcm_type_object_by_qobject_type_name(QString tn);
 Q_INVOKABLE const KCM_Type_Object* kcm_type_object_by_qregistered_type_name(QString tn);

};

Q_DECLARE_METATYPE(KCM_Lisp_Bridge)
Q_DECLARE_METATYPE(KCM_Lisp_Bridge*)

#else

KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)
KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
USING_KANS(CMD)

KANS_CLASS_DECLARE(KCM ,KCM_Source_Function)
USING_KANS(KCM)

KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_System)
USING_KANS(Kauvir)


struct KCM_Lisp_Bridge
{
 static quint64 get_value_of_symbol(QString symbol_name,
   KCM_Scope_System* scopes, const KCM_Type_Object** rkto = nullptr)
 {
  return 0;
 }

 static void bridge_run_source_function(KCM_Lisp_Bridge* _this,
   KCM_Command_Runtime_Router& kcrr, KCM_Source_Function& ksf)
 {

 }

};

#endif // USING_ECL

#endif //KCM_LISP_BRIDGE__H
