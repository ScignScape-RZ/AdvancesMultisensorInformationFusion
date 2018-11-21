
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kauvir-code-model.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kcm-scopes/kcm-scope-system.h"
#include "kcm-scopes/kcm-runtime-scope.h"

#include "kcm-type-object.h"
#include "kcm-expression.h"
#include "kcm-statement.h"
#include "kcm-source-function.h"

#include "kcm-channel-group.h"

#include "kcm-overloadable-symbol.h"

#include "kcm-scopes/kcm-lexical-scope.h"

#include "kcm-proxy-scope.h"

#include "kcm-command-package/kcm-command-package.h"
#include "kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-bridge.h"

#include "kcm-channel-bridge.h"

#include "kcm-callable-value.h"

#include "kcm-block.h"
#include "kcm-file.h"


USING_KANS(KCM)
USING_KANS(Kauvir)
USING_KANS(CMD)



Kauvir_Code_Model::Kauvir_Code_Model()
  : expression_code_count_(0),
    type_system_(new Kauvir_Type_System),
    current_lexical_scope_(new KCM_Lexical_Scope),
    current_proxy_scope_(new  KCM_Proxy_Scope),
    current_file_(nullptr), direct_eval_fn_(nullptr),
    make_kcm_command_package_from_channel_group_fn_(nullptr),
    make_kcm_command_package_fn_(nullptr),
 envv_fn_(nullptr), kph_generator_(nullptr),
 runtime_scope_id_count_(0)
{
 runtime_scope_ids_.push({0,0});

 channel_names_ = {&channel_names_set_, &channel_names_map_};

 type_string_reps_[&type_system_->type_object__auto_expr()] = "auto_expr";
 type_string_reps_[&type_system_->type_object__str()] = "str";
 type_string_reps_[&type_system_->type_object__u8()] = "u8";
 type_string_reps_[&type_system_->type_object__u32()] = "u32";
 type_string_reps_[&type_system_->type_object__u64()] = "u64";
 type_string_reps_[&type_system_->type_object__opaque_lisp_value()] = "olv";

 lisp_report_synax_.flags.compress_fluxe_channel = true;
 lisp_report_synax_.flags.merge_fuxe_and_lambda = true;
 lisp_report_synax_.flags.expand_array_indicators = true;

 detailed_report_synax_.flags.identify_channel_names = true;
 detailed_report_synax_.flags.identify_types = true;
 detailed_report_synax_.flags.surround_type_expressions = true;
 detailed_report_synax_.flags.write_empty_lambda_channel = true;

 detailed_report_synax_.channel_kind_codes()[KCM_Channel::Kinds::Fuxe] = "fuxe";
 detailed_report_synax_.channel_kind_codes()[KCM_Channel::Kinds::Lambda] = "lambda";
 detailed_report_synax_.channel_kind_codes()[KCM_Channel::Kinds::Sigma] = "sigma";

 detailed_report_synax_.channel_kind_codes()[KCM_Channel::Kinds::CTOR_Mem] = "ctor-mem";
 detailed_report_synax_.channel_kind_codes()[KCM_Channel::Kinds::CTOR_Ret] = "ctor-ret";

 // //  is this affected by 32/64?
 generic_anon_callable_value_type_object_ =
   new KCM_Type_Object(&type_system_->type_object__kcm_callable_value(), DEFAULT_PTR_BYTE_CODE);
 callable_lisp_deferred_value_type_object_ =
   new KCM_Type_Object(&type_system_->type_object__callable_lisp_deferred_value(), DEFAULT_PTR_BYTE_CODE);
 argument_vector_type_object_ =
   new KCM_Type_Object(&type_system_->type_object__argument_vector(), 9);


 kcm_type_object_map_ = {{
   {&type_system_->type_object__u8(),
     new KCM_Type_Object(&type_system_->type_object__u8(), 1)},
   {&type_system_->type_object__u32(),
     new KCM_Type_Object(&type_system_->type_object__u32(), 4)},
   {&type_system_->type_object__u64(),
     new KCM_Type_Object(&type_system_->type_object__u64(), 8)},

   {&type_system_->type_object__str(),
     new KCM_Type_Object(&type_system_->type_object__str(), DEFAULT_PTR_BYTE_CODE)},

   {&type_system_->type_object__opaque_lisp_value(),
     new KCM_Type_Object(&type_system_->type_object__opaque_lisp_value(), 8)},


   {&type_system_->type_object__kcm_callable_value(),
     generic_anon_callable_value_type_object_},
   {&type_system_->type_object__callable_lisp_deferred_value(),
     callable_lisp_deferred_value_type_object_},
   {&type_system_->type_object__argument_vector(),
     argument_vector_type_object_},
  }};

 type_object_string_map_ = {{
   {"u8", get_kcm_type_by_kauvir_type_object(&type_system_->type_object__u8())},
   {"u32", get_kcm_type_by_kauvir_type_object(&type_system_->type_object__u32())},
   {"u64", get_kcm_type_by_kauvir_type_object(&type_system_->type_object__u64())},
   {"str", get_kcm_type_by_kauvir_type_object(&type_system_->type_object__str())},
   {"olv", get_kcm_type_by_kauvir_type_object(&type_system_->type_object__opaque_lisp_value())},
  }};

}


KCM_Type_Object* Kauvir_Code_Model::create_and_register_type_object(QString name, int bc)
{
 KCM_Type_Object* result = create_type_object(name);
 result->set_byte_code(bc);
 type_object_string_map_.insert(name, result);
 return result;
}


KCM_Type_Object* Kauvir_Code_Model::create_and_register_type_object(QString name)
{
 if(name.endsWith('*'))
 {
  return create_and_register_type_object(name, DEFAULT_PTR_BYTE_CODE);
 }
 else
 {
  return create_and_register_type_object(name, 8);
 }
}


KCM_Type_Object* Kauvir_Code_Model::create_type_object(QString name)
{
 Kauvir_Type_Object* kto = new Kauvir_Type_Object(name);
 KCM_Type_Object* result = new KCM_Type_Object(kto);

 if(name.endsWith('*'))
 {
  int pid = QMetaType::type(name.toLatin1());
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    kto->set_pqmo(pqmo);
   }
  }
  name.chop(1);
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   result->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    kto->set_qmo(qmo);
   }
  }
 }
 else
 {
  int id = QMetaType::type(name.toLatin1());
  if(id != QMetaType::UnknownType)
  {
   result->set_qmetatype_ptr_code(id);
   const QMetaObject* qmo = QMetaType::metaObjectForType(id);
   if(qmo)
   {
    kto->set_qmo(qmo);
   }
  }
  int pid = QMetaType::type( (name + "*").toLatin1() );
  if(pid != QMetaType::UnknownType)
  {
   const QMetaObject* pqmo = QMetaType::metaObjectForType(pid);
   if(pqmo)
   {
    kto->set_pqmo(pqmo);
    result->set_qmetatype_ptr_code(pid);
    // // kto->check_register_variant_and_metatype_info(QVariant::UserType, pid);
   }
  }
 }
 return result;
}

const KCM_Type_Object* Kauvir_Code_Model::get_or_add_kcm_type(QString type_name)
{
 const KCM_Type_Object* result = type_object_string_map_.value(type_name);
 if(!result)
 {
  result = create_and_register_type_object(type_name);
 }
 return result;
}

const KCM_Type_Object* Kauvir_Code_Model::get_kcm_type_by_type_name(QString type_name)
{
 // // just for now ...
 if(type_name == "int")
 {
  return type_object_string_map_.value("u32");
 }

 else if(type_name.startsWith("@-"))
 {
  type_name = type_name.mid(2);
  const KCM_Type_Object* inner = get_or_add_kcm_type(type_name);
  KCM_Type_Object* result = inner->base_clone();
  result->set_array_length(-1);
  result->set_modifier(KCM_Type_Object::Modifiers::Pointer);
  return result;
 }
 else if(type_name.startsWith("@*"))
 {
  int ind = type_name.indexOf('-', 2);
  int array_length = type_name.mid(2, ind - 2).toInt();
  type_name = type_name.mid(ind + 1);
  const KCM_Type_Object* inner = get_or_add_kcm_type(type_name);
  KCM_Type_Object* result = inner->base_clone();
  result->set_array_length(array_length);
  result->set_modifier(KCM_Type_Object::Modifiers::Pointer);
  return result;
 }
 else
 {
  return get_or_add_kcm_type(type_name);
 }
}

const KCM_Type_Object* Kauvir_Code_Model::type_object_by_qregistered_type_name(QString tn)
{
 const KCM_Type_Object* result = type_object_string_map_.value(tn);
 if(!result)
 {
  QString ptn = tn + '*';
  int type_id = QMetaType::type(ptn.toLatin1());
  Kauvir_Type_Object* kto = new Kauvir_Type_Object(tn);
  kto->check_register_variant_and_metatype_info(QVariant::UserType, type_id);
  result = new KCM_Type_Object(kto);
 }
 return result;
}

const KCM_Type_Object* Kauvir_Code_Model::type_object_by_qobject_type_name(QString tn)
{
 const KCM_Type_Object* result = type_object_string_map_.value(tn);
 if(!result)
 {
  QString ptn = tn + '*';
  int type_id = QMetaType::type(ptn.toLatin1());
  if(type_id != QMetaType::UnknownType)
  {
   const QMetaObject* qmo = QMetaType::metaObjectForType(type_id);
   if(qmo)
   {
    Kauvir_Type_Object* kto = new Kauvir_Type_Object(tn);
    kto->set_pqmo(qmo);
    result = new KCM_Type_Object(kto);
   }
  }
 }
 return result;
}

void Kauvir_Code_Model::prepare_anon_fdef_expression(const KCM_Type_Object* kto, QString anon_code)
{
 KCM_Callable_Value* kcv = new KCM_Callable_Value;
 kcv->set_kto(kto);
 current_anon_codes_[anon_code] = kcv;
}

void Kauvir_Code_Model::kcg_add_lambda_carrier_of_anon_fdef(KCM_Channel_Group* kcg, QString anon_code)
{
 // // does the anon_code suffice for the value?
 kcg->add_lambda_carrier_via_typed_literal(generic_anon_callable_value_type_object_, anon_code);
}


const KCM_Type_Object* Kauvir_Code_Model::get_kcm_type_by_kauvir_type_object(const Kauvir_Type_Object* kto)
{
 const KCM_Type_Object* result = kcm_type_object_map_.value(kto);
 if(!result)
 {
  result = new KCM_Type_Object(kto);
  kcm_type_object_map_.insert(kto, result);
 }
 return result;
}

QString Kauvir_Code_Model::make_kcm_code()
{
 ++expression_code_count_;
 return QString("\\.%1").arg(expression_code_count_);
}

void Kauvir_Code_Model::join_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb)
{
 // is this all?
 kcs->set_nested_block(kcb);
}

KCM_Command_Package* Kauvir_Code_Model::statement_to_command_package(KCM_Statement* kcs)
{
 KCM_Expression* kce = kcs->expression();
 KCM_Command_Package* result;

 if(kce)
 {
  if(make_kcm_command_package_from_channel_group_fn_)
  {
   result = make_kcm_command_package_from_channel_group_fn_(*kce->channel_group());
   result->set_kcm_expression(kce);
  }
 }
 else
 {
  if(make_kcm_command_package_fn_)
  {
   result = make_kcm_command_package_fn_(channel_names_, kcs->bind_kto(), kcs->bind_val(), kcs->bind_qob());
   result->set_kcm_expression(kce);
  }
 }

 switch(kcs->statement_kind())
 {
 case KCM_Statement::Statement_Kinds::Type_Binding_With_Expression:
 case KCM_Statement::Statement_Kinds::Type_Binding_With_Token:
 case KCM_Statement::Statement_Kinds::Type_Binding_With_Block:
 case KCM_Statement::Statement_Kinds::Type_Binding_With_QObject:
  {
   KCM_Overloadable_Symbol& sym = kcs->symbol();
   result->set_output_symbol(&sym);
  }
 break;
 default: break;

 }

 return result;
}

void Kauvir_Code_Model::init_scope_system()
{
 scope_system_->join_lexical_scope(current_lexical_scope_);
}

KCM_Runtime_Scope* Kauvir_Code_Model::get_current_runtime_scope()
{
 return scope_system_->current_scope();
}

void Kauvir_Code_Model::finalize_anon_fdef(quint64 clo, QString symbol_name)
{
 // //  have to pull up the nested because do is wrapped in an expression ...

 // //  stack or queue?
 //QPair< QPair<KCM_Expression*, int>, QPair<int, int> > pr = current_nested_expression_coords_.pop();
 //QPair< QPair<KCM_Expression*, int>, QPair<int, int> > pr = current_nested_expression_coords_.dequeue();

 // is this always ok?
 QPair< QPair<KCM_Expression*, int>, QPair<int, int> > pr = current_nested_expression_coords_[get_current_runtime_scope_id()].takeLast();

 if(KCM_Callable_Value* kcv = current_anon_codes_.value(symbol_name))
 {
  //scope_system_->find_raw_value_from_current_scope();

  KCM_Expression* kcx = pr.first.first;

  int level = pr.second.first;
  int index = pr.second.second;

  // // should this always be hard-coded?
   //   intended to match bind_code ...
  QString tempcode = QString(":##%1-%2").arg(level).arg(index);


  kcv->set_as_pVoid((void*) clo);
  kcx->set_ref_anon(kcv);

  scope_system_->hold_temporary_bridge_value(tempcode, (quint64) kcv, generic_anon_callable_value_type_object_);


 }

}

void Kauvir_Code_Model::finalize_fdef(quint64 clo, QString symbol_name)
{
 if(symbol_name.startsWith("<anon>"))
 {
  finalize_anon_fdef(clo, symbol_name);
  return;
 }
 KCM_Runtime_Scope* scope = get_current_runtime_scope();
 //.
 KCM_Source_Function* ksf = scope->find_source_function_value(symbol_name);
 ksf->set_cl_object(clo);
}

void Kauvir_Code_Model::load_bridge(KCM_Channel_Bridge* bridge)
{
 bridge->set_proxy_scope(current_proxy_scope_);
 current_proxy_scope_->set_kcm_channel_bridge(bridge);
}


void Kauvir_Code_Model::direct_eval(KCM_Command_Package* cpkg, KCM_Lisp_Bridge* bridge)
{
 if(direct_eval_fn_)
 {
  direct_eval_fn_(this, cpkg, bridge);
 }
}

KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement(QString symbol_name, int index)
{
 KCM_Statement* kcs = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding,
   KCM_Overloadable_Symbol(symbol_name, index));
 return kcs;
}

KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement(QString symbol_name)
{
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding,
   symbol_name);
 return result;
}

KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement(QString symbol_name, KCM_Expression* kcx)
{
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding_With_Expression,
   symbol_name, kcx);
 return result;
}

void Kauvir_Code_Model::enter_runtime_scope(KCM_Lisp_Bridge& bridge)
{
 runtime_scope_ids_.push({++runtime_scope_id_count_,0});
}

void Kauvir_Code_Model::leave_runtime_scope(KCM_Lisp_Bridge& bridge)
{
 runtime_scope_ids_.pop();
 ++runtime_scope_ids_.top().second;
}

void Kauvir_Code_Model::prepare_proxy_symbol(QString symbol_name, const KCM_Type_Object* kto)
{
 current_proxy_scope_->add_proxy_symbol(symbol_name, kto);
}

void Kauvir_Code_Model::init_proxy_symbol(QString symbol_name, QString proxy_coords_code)
{
 current_proxy_scope_->init_proxy_symbol(symbol_name, proxy_coords_code);
}


KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement_with_nested_block(QString symbol_name, const KCM_Type_Object* kto)
{
 // // todo account for different kinds of scope via _::_ constructions ...
 QString scoped_symbol_name = symbol_name;
 scoped_symbol_name.prepend(':');
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding_With_Block,
   symbol_name, kto, scoped_symbol_name);
 return result;
}

KCM_Statement* Kauvir_Code_Model::promote_overloadable_function_type_binding_to_statement(QString symbol_name, const KCM_Type_Object* kto)
{
 // // todo account for different kinds of scope via _::_ constructions ...
// // anything different here?
 QString scoped_symbol_name = symbol_name;
 scoped_symbol_name.prepend("&:");
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding,
   symbol_name, kto, scoped_symbol_name);
 return result;
}


KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement_with_token(QString symbol_name,
  const KCM_Type_Object* kto, QString val)
{
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding_With_Token,
   symbol_name, kto, val);
 return result;
}

KCM_Statement* Kauvir_Code_Model::promote_type_binding_to_statement_with_qobject(QString symbol_name,
  const KCM_Type_Object* kto, QObject* qob)
{
 KCM_Statement* result = new KCM_Statement(KCM_Statement::Statement_Kinds::Type_Binding_With_QObject,
   symbol_name, kto, qob);
 return result;
}


KCM_Type_Object* Kauvir_Code_Model::type_with_array_length(KCM_Type_Object* kto, int array_length)
{
 KCM_Type_Object* result = kcm_type_object_array_map_.value({kto, array_length});
 if(!result)
 {
  result = kto->base_clone();
  result->set_array_length(array_length);
  result->set_modifier(kto->modifier());
  kcm_type_object_array_map_.insert({kto, array_length}, result);
 }
 return result;
}


KCM_Type_Object* Kauvir_Code_Model::type_with_modifiers(KCM_Type_Object* kto, KCM_Type_Object::Modifiers modifier)
{
 KCM_Type_Object* result = kcm_type_object_modifier_map_.value({kto, modifier});
 if(!result)
 {
  result = kto->base_clone();
  result->set_array_length(kto->array_length());
  result->set_modifier(modifier);
  kcm_type_object_modifier_map_.insert({kto, modifier}, result);
 }
 return result;
}



const KCM_Type_Object* Kauvir_Code_Model::type_object_from_channel_group(KCM_Channel_Group& kcg)
{
 KCM_Channel_Group* new_kcg = kcg.branch_copy();
 return new KCM_Type_Object(new_kcg);
}

void Kauvir_Code_Model::add_type_binding(QString symbol_name, const KCM_Type_Object* kto)
{
 current_lexical_scope_->add_symbol(symbol_name, kto);
}

KCM_Expression* Kauvir_Code_Model::promote_type_binding_to_statement_via_type_default_literal__let(KCM_Channel_Group* kcg, QString symbol_name)
{
 const KCM_Type_Object* kto = retrieve_type_binding(symbol_name);
 KCM_Statement* kcs = nullptr;
 if(kto)
 {
  // other alternatives?  todo ...
  if(kto->is_string_like())
  {
   kcs = promote_type_binding_to_statement_with_token(symbol_name, kto, "\"\"");
  }
  else
  {
   const QMetaObject* qmo = kto->kauvir_type_object()->qmo();
   int pid = kto->qmetatype_ptr_code();
   if(pid != QMetaType::UnknownType)
   {
    void* pv = QMetaType::create(pid);
    QObject* qob = static_cast<QObject*>(pv);
    kcs = promote_type_binding_to_statement_with_qobject(symbol_name, kto, qob);
   }
   else
   {
    kcs = promote_type_binding_to_statement_with_token(symbol_name, kto, "0");
   }
  }
 }

 // //  this works for when an expression can be actually just a literal
  //    but appear like an expression within a statement, e.g. a value init
 KCM_Expression* result = new KCM_Expression(kcs);

 return result;
}

const KCM_Type_Object* Kauvir_Code_Model::retrieve_type_binding(QString symbol_name)
{
 return current_lexical_scope_->get_type_object_from_symbol_name(symbol_name);
}


int Kauvir_Code_Model::add_overloadable_type_binding(QString symbol_name, KCM_Type_Object* kto)
{
 int result = ++overload_count_[symbol_name];
 current_lexical_scope_->add_symbol(symbol_name, kto);
 current_lexical_scope_->add_symbol(QString("%1#%2").arg(result).arg(symbol_name), kto);
 return result;
}

void Kauvir_Code_Model::hold_dissolve(int code, KCM_Channel_Group& kcg)
{
 KCM_Channel_Group* xkcg = kcg.branch_copy();
 QString kcm_code = make_kcm_code();
 KCM_Expression* kcx = new KCM_Expression(kcm_code, xkcg);
 held_expressions_.insert(code, kcx);
}

KCM_Expression* Kauvir_Code_Model::dissolve_to_expression(KCM_Channel_Group& kcg)
{
 KCM_Channel_Group* xkcg = kcg.branch_copy();
 KCM_Expression* result = new KCM_Expression(xkcg);
 return result;
}

void Kauvir_Code_Model::kcg_add_fuxe_carrier(KCM_Channel_Group* kcg, const KCM_Type_Object* kto, QString symbol_name)
{
 // //  checking for fuxe carriers that generate different names with different ktos ...
 if( (symbol_name == "let") || (symbol_name == "new") )
 {
  if(kto->is_string_like())
  {
   symbol_name.append("_str");
  }
  else
  {
   symbol_name.append("_num");
  }
 }
 kcg->add_fuxe_carrier(symbol_name);
}

KCM_Expression* Kauvir_Code_Model::dissolve_to_nested_expression(KCM_Channel_Group& kcg)
{
 KCM_Channel_Group* xkcg = kcg.branch_copy();
 QString kcm_code = make_kcm_code();
 KCM_Expression* result = new KCM_Expression(kcm_code, xkcg);
 held_expressions_.insert(expression_code_count_, result);
 return result;
}

KCM_Expression* Kauvir_Code_Model::dissolve_to_nested_expression(KCM_Channel_Group& kcg, QString kcm_code)
{
 KCM_Channel_Group* xkcg = kcg.branch_copy();
 KCM_Expression* result = new KCM_Expression(kcm_code, xkcg);
 int index = kcm_code.mid(2).toInt();
 held_expressions_[index] = result;
 return result;
}

KCM_Statement* Kauvir_Code_Model::promote_expression_to_statement(KCM_Expression* kcx)
{
 KCM_Statement* result = kcx->implied_statement();
 if(!result)
 {
  result = new KCM_Statement(KCM_Statement::Statement_Kinds::Promoted_Expression, kcx);
 }
 return result;
}

KCM_File* Kauvir_Code_Model::create_and_enter_file(QString file_path)
{
 KCM_File* result = new KCM_File(file_path);
 current_file_ = result;
 return result;
}

void Kauvir_Code_Model::enter_plebod()
{
 current_proxy_scope_ = new KCM_Proxy_Scope(current_proxy_scope_);
}

void Kauvir_Code_Model::prepare_nested_defer_expression(KCM_Expression* kcx,
  int hdcode, int level, int index)
{
 current_held_deferred_coords_.push({kcx, {level, index}});

  // //  stack or queue?
 //current_nested_expression_coords_.push({{kcx, hdcode}, {level, index}});
 current_nested_expression_coords_[get_current_runtime_scope_id()].enqueue({{kcx, hdcode}, {level, index}});

}

QPair<int, int> Kauvir_Code_Model::get_current_runtime_scope_id()
{
 return runtime_scope_ids_.top();
}


void Kauvir_Code_Model::prepare_nested_expression(KCM_Expression* kcx, int level, int index)
{
 // //  stack or queue?
 //current_nested_expression_coords_.push({{kcx, 0}, {level, index}});
 current_nested_expression_coords_[get_current_runtime_scope_id()].enqueue({{kcx, 0}, {level, index}});

}

KCM_Block* Kauvir_Code_Model::create_and_enter_block()
{
 KCM_Lexical_Scope* new_scope = new KCM_Lexical_Scope(current_lexical_scope_);
 KCM_Block* result = new KCM_Block(new_scope);
 new_scope->set_associated_block(result);
 current_lexical_scope_ = new_scope;
 return result;
}

void Kauvir_Code_Model::add_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb)
{
 kcb->add_statement(kcs);
}

void Kauvir_Code_Model::add_statement_to_file(KCM_Statement* kcs, KCM_File* kcf)
{
 kcf->add_statement(kcs);
}

void Kauvir_Code_Model::hold_runtime_list(QString key, quint64 clo)
{
 QString value_encoding = get_key_for_storing(clo);
 const KCM_Type_Object* kto = get_kcm_type_by_kauvir_type_object(&type_system_->type_object__opaque_lisp_value());
 hold_runtime_value(key, kto, value_encoding);
}

QString Kauvir_Code_Model::get_key_for_storing(quint64 clo)
{
 current_lexical_scope_->increment_key_for_storing();
 quint32 key = current_lexical_scope_->last_key_for_storing();
 QString result = QString(".%1.").arg(key);
 current_lexical_scope_->store_key(result, clo);
 return result;
}



void Kauvir_Code_Model::hold_runtime_value(QString key, const KCM_Type_Object* kto, QString value_encoding)
{
 // // always pop?
 //current_lexical_scope_->hold_runtime_value(current_nested_expression_coords_.top(), kto, value_encoding);
 // //  stack or queue?
 //current_lexical_scope_->hold_runtime_value(current_nested_expression_coords_.pop(), kto, value_encoding, key);
 current_lexical_scope_->hold_runtime_value(current_nested_expression_coords_[get_current_runtime_scope_id()].dequeue(), kto, value_encoding, key);
}

void Kauvir_Code_Model::hold_deferred(int hdcode, quint64 clo)
{
 current_lexical_scope_->hold_deferred(current_held_deferred_coords_.pop(),
   callable_lisp_deferred_value_type_object_, hdcode, clo);
}


void Kauvir_Code_Model::leave_block(KCM_Block* kcb)
{
 KCM_Lexical_Scope* kls = kcb->lexical_scope();
 current_lexical_scope_ = kls->parent();
}

QString Kauvir_Code_Model::string_rep(const Kauvir_Type_Object* kauvir_type_object)
{
 return type_string_reps_.value(kauvir_type_object, "unknown");
}

QString Kauvir_Code_Model::get_type_expression_for_type_object(const KCM_Type_Object* kto)
{
 QString result;
 if(KCM_Channel_Group* kcg = kto->channel_group())
 {
  // //  assuming this means a function-like syntax ...
 }
 return QString();
}

QString Kauvir_Code_Model::get_function_type_keyword_for_type_object(const KCM_Type_Object* kto)
{
 QString result;
 if(KCM_Channel_Group* kcg = kto->channel_group())
 {
  // //  anything other than "fn" here? --
   //    any type with a channel group that wouldn't use "fn"?
  result = "fn";
 }
 return result;
}

void Kauvir_Code_Model::report_expression_from_code(QTextStream& qts, QString code, KCM_Report_Syntax& kcrs)
{
 QString cm2 = code.mid(2);
 int index = cm2.toInt();
 KCM_Expression* kce = held_expressions_.value(index);
 if(kce)
 {
  kce->report(qts, *this, kcrs);
 }
}


QString Kauvir_Code_Model::get_function_type_keyword_for_overloadable_symbol(const KCM_Overloadable_Symbol& kcos, KCM_Lexical_Scope* scope)
{
 QString result;
 const KCM_Type_Object* kto = get_type_object_for_overloadable_symbol(kcos, scope);
 if(kto)
 {
  result = get_function_type_keyword_for_type_object(kto);
 }
 return result;
}

const KCM_Type_Object* Kauvir_Code_Model::get_type_object_for_overloadable_symbol(const KCM_Overloadable_Symbol& kcos, KCM_Lexical_Scope* scope)
{
 if(!scope)
 {
  scope = current_lexical_scope_;
 }
 QString symbol_name = kcos.encode_to_symbol_name();
 return scope->get_type_object_from_symbol_name(symbol_name);
}

QString Kauvir_Code_Model::get_ouput_type_name(KCM_Report_Syntax& kcrs, const KCM_Type_Object* kto)
{
 QString mod;
 switch(kto->modifier())
 {
 case KCM_Type_Object::Modifiers::Pointer:
   mod = "&";
   break;
 default: break;
 }

 QString result = kto->kauvir_type_object()->name();
 if(result.isEmpty())
 {
  // //?
  result = "auto";
 }
 else
 {
  if(result.startsWith('s'))
  {
   result.replace(0, 1, 'i');
  }
 }
 int kal = kto->array_length();
 if(kal != 0)
 {
  if(kcrs.flags.use_thorin_array_types)
  {
   if(kal == -1)
   {
    result = QString("[%1]").arg(result);
   }
   else
   {
    result = QString("[%1*%2]").arg(result).arg(kal);
   }
  }
  else
  {
   if(kal == -1)
   {
    result = QString("(resizable-array %1)").arg(result);
   }
   else
   {
    result = QString("(fixed-size-array %1 %2)").arg(result).arg(kal);
   }
  }
 }
 result.prepend(mod);
 return result;
}

void Kauvir_Code_Model::report_type_expression_for_overloadable_symbol(QTextStream& qts,
  KCM_Report_Syntax& kcrs, const KCM_Overloadable_Symbol& kcos,
  KCM_Channel::Code_Environments cenv, KCM_Lexical_Scope* scope)
{
 const KCM_Type_Object* kto = get_type_object_for_overloadable_symbol(kcos, scope);
 if(kto)
 {
  if(KCM_Channel_Group* kcg = kto->channel_group())
  {
   kcg->report(qts, *this, kcrs, cenv);
  }
  else
  {
   if(kcrs.flags.types_colon_separator)
   {
    qts << ": ";
   }
   qts << get_ouput_type_name(kcrs, kto);
  }
 }
}

QString Kauvir_Code_Model::get_type_expression_for_overloadable_symbol(const KCM_Overloadable_Symbol& kcos, KCM_Lexical_Scope* scope)
{
 QString result;
 const KCM_Type_Object* kto = get_type_object_for_overloadable_symbol(kcos, scope);
 if(kto)
 {
  result = get_type_expression_for_type_object(kto);
 }
 return result;
}
