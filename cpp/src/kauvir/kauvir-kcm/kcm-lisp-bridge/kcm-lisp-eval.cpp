
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "defines.h"


#ifdef USING_ECL

#include "kcm-lisp-eval.h"
#include "kcm-lisp-runtime.h"
#include "kcm-lisp-embed-environment.h"

#include "kcm-lisp-runtime-argument.h"

#include "kcm-scopes/kcm-scope-system.h"

#include "rz-dynamo-generator/rz-dynamo-generator.h"

#include "kauvir-code-model/kcm-channel-bridge.h"
#include "kcm-command-runtime/kcm-command-runtime-router.h"




#include <QDebug>

USING_KANS(KCL)

KCM_Lisp_Eval::KCM_Lisp_Eval(KCM_Lisp_Embed_Environment* env)
  :  env_(env), kcm_lisp_runtime_(new KCM_Lisp_Runtime)
{

}

KCM_Lisp_Eval::KCM_Lisp_Eval(KCM_Lisp_Embed_Environment* env, QTextStream& qts)
 :  env_(env), kcm_lisp_runtime_(new KCM_Lisp_Runtime(qts))
{

}



void KCM_Lisp_Eval::minimal_eval(QString eval_text)
{
 cl_cxx_backend::eval_string(eval_text.toLatin1().data());
}

KCM_Lisp_Eval::make_kcm_channel_bridge_fn_type KCM_Lisp_Eval::get_make_kcm_channel_bridge_fn_type(
  make_kcm_channel_bridge_fn_type fn)
{
 static make_kcm_channel_bridge_fn_type result = nullptr;
 if(fn)
 {
  result = fn;
 }
 return result;
}

void KCM_Lisp_Eval::run_source_function(KCM_Command_Runtime_Router& kcrr, quint64 qclo)
{
 cl_object clo = (cl_object) qclo;
 cl_object isf = cl_functionp(clo);
 if(isf != ECL_NIL)
 {
  KCM_Channel_Bridge* bridge = get_make_kcm_channel_bridge_fn_type()(kcrr);
  cl_object clo_ks = cl_cxx_backend::make_foreign_data(bridge);
  cl_funcall(2, clo, clo_ks);
 }
}


void KCM_Lisp_Eval::define_callback(cl_cxx_backend::callback_t cb,
 QString package_name, QString symbol_name, void* argument)
{
 package_name = package_name.toUpper();
 symbol_name = symbol_name.toUpper();
 cl_object obj = cl_cxx_backend::symbol(package_name.toLatin1().data(), symbol_name.toLatin1().data());
 cl_cxx_backend::define_function(obj, cb, argument);
}

void KCM_Lisp_Eval::test_callback(cl_cxx_backend::callback_t cb)
{
 cl_cxx_backend::eval_string("(COMMON-LISP-USER::TEST-CB)");
}

void KCM_Lisp_Eval::cl_arglist_to_strings(int size, int offset, cl_cxx_backend::cl_arglist arglist,
  QStringList& strings)
{
 for(int i = offset; i < size; ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  QString str = cl_object_to_qstring(clo);
  strings.push_back(str);
 }
}

void KCM_Lisp_Eval::cl_arglist_to_ms_tokens(int size, int offset, cl_cxx_backend::cl_arglist arglist,
  QList<MS_Token>& tokens)
{
 for(int i = offset; i < size; ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  QString str = cl_object_to_qstring(clo);
  if(SYMBOLP(clo))
  {
   MS_Token mst = MS_Token::decode(str);
   if(mst.kind != MS_Token_Kinds::Skip_Token)
   {
    tokens.push_back(mst);
   }
  }
  else if(str.startsWith('"'))
  {
   tokens.push_back({MS_Token_Kinds::String_Literal, str});
  }
  else
  {
   tokens.push_back({MS_Token_Kinds::Generic, str});
  }
 }
}

void KCM_Lisp_Eval::cl_arglist_to_tagged_strings(int size, int offset,
  cl_cxx_backend::cl_arglist arglist,
  QStringList& strings)
{
 for(int i = offset; i < size; ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  QString str = cl_object_to_qstring(clo);
  if(SYMBOLP(clo))
  {
   if(str.startsWith(':'))
   {
    strings.push_back(str.prepend('@'));
   }
   else
   {
    strings.push_back(str.prepend('&'));
   }
  }
  else if(str.startsWith('"'))
  {
   str[0] = '$';
   str.chop(1);
   strings.push_back(str);
  }
  else
  {
   strings.push_back(str.prepend('@'));
  }
 }
}


void KCM_Lisp_Eval::cl_arglist_to_flagged_strings(int size, int offset,
  cl_cxx_backend::cl_arglist arglist,
  QStringList& flags, QStringList& strings)
{
 for(int i = offset; i < size; ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  QString str = cl_object_to_qstring(clo);
  if(SYMBOLP(clo))
  {
   flags.push_back(str);
  }
  else
  {
   strings.push_back(str);
  }
 }
}

QString KCM_Lisp_Eval::cl_arglist_to_opaque_arguments(cl_cxx_backend::cl_arglist arglist,
  QVector<KCM_Lisp_Runtime_Argument>& klras)
{
 QString result;
 cl_object clo1 = cl_cxx_backend::nth_arg(arglist, 2);
 if(SYMBOLP(clo1))
 {
  result = cl_arglist_to_qstring(arglist, 2);
 }
 for(int i = 2; i < klras.size(); ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  KCM_Lisp_Runtime_Argument& klra = klras[i];
  klra.set_opaque_lisp_value( (quint64) clo);
 }
 return result;
}

quint64 KCM_Lisp_Eval::encode_encoded_value_to_cl_object(const KCM_Type_Object* kto, QString val)
{
 // // once again there are probably other options ...

 if(kto->is_string_like())
 {
  cl_object clo = qstring_to_cl_object(val);
  return (quint64) clo;
 }
 else
 {
  quint32 v = val.toInt();
  return (quint64) ecl_make_fixnum(v);
 }

}

quint64 KCM_Lisp_Eval::encode_value_to_cl_object(const KCM_Type_Object* kto, void* val)
{
 // // once again there are probably other options ...

 if(kto->is_string_like())
 {
  QString* qs = (QString*) val;
  cl_object clo = qstring_to_cl_object(*qs);
  return (quint64) clo;
 }
 else
 {
  quint32 v = *(quint32*)(val);
  return (quint64) ecl_make_fixnum(v);
 }
}

void* KCM_Lisp_Eval::opaque_lisp_value_to_pVoid(Opaque_Lisp_Value olv)
{
 cl_object clo = (cl_object) olv.value;
 return ecl_foreign_data_pointer_safe(clo);
}

void KCM_Lisp_Eval::run_held_lisp_list(quint64 lisp_val, quint64& mem)
{
 cl_object result = cl_eval( (cl_object) lisp_val);
 quint64 value = ecl_to_fixnum(result);
 mem = value;
}

void KCM_Lisp_Eval::eval_held_form(quint64 qclo)
{
 cl_eval( (cl_object) qclo);
}

void KCM_Lisp_Eval::eval_lisp_callable_deferred_value(quint64 qclo,
  quint64& result, QString convention)
{
 QPair<KCM_Scope_System*, QPair<int, quint64>>* pr = (QPair<KCM_Scope_System*, QPair<int, quint64>>*) qclo;
 KCM_Scope_System* scopes = pr->first;
 int hdcode = pr->second.first;
 cl_object clo = (cl_object) pr->second.second;
 cl_object clo_result = cl_eval(clo);
 quint64 h = scopes->find_held_value_by_hdcode(hdcode);
 if(h)
 {
  cl_object oldr = clo_result;
  clo_result = cl_eval( (cl_object) h );
 }
 if(convention == "fixnum")
 {
  result = ecl_to_fixnum(clo_result);
 }
 else if(convention == "bool")
 {
  result = ecl_to_bool(clo_result);
 }
 else
 {
  result = (quint64) clo_result;
 }
}


void KCM_Lisp_Eval::parse_opaque_lisp_value(Opaque_Lisp_Value olv,
  Opaque_Lisp_Value_Types& olvt, QString& encoded_value)
{
 cl_object clo = (cl_object) olv.value;
 cl_type clt = ecl_t_of(clo);
 if( (clt == t_base_string) || (clt == t_string) )
 {
  std::string str = cl_cxx::from_cl_object<std::string>(clo);
  olvt = Opaque_Lisp_Value_Types::Str;
  encoded_value = QString::fromStdString(str);
 }
 else if(clt == t_fixnum)
 {
  quint32 value = ecl_to_fixnum(clo);
  olvt = Opaque_Lisp_Value_Types::Fixnum_U32;
  encoded_value = QString::number(value);
 }
 else if(clt == t_list)
 {
  olvt = Opaque_Lisp_Value_Types::Held_List;
 }
 else if(clt == t_foreign)
 {

 }
 else
 {

 }
}

void KCM_Lisp_Eval::cl_arglist_to_arguments(cl_cxx_backend::cl_arglist arglist,
  QVector<KCM_Lisp_Runtime_Argument>& klras)
{
 for(int i = 1; i < klras.size(); ++i)
 {
  cl_object clo = cl_cxx_backend::nth_arg(arglist, i + 1);
  KCM_Lisp_Runtime_Argument& klra = klras[i];

  cl_type clt = ecl_t_of(clo);
  if(clt == t_base_string)
  {
   std::string str = cl_cxx::from_cl_object<std::string>(clo);
   klra.set_string(QString::fromStdString(str));
  }
  else if(clt == t_fixnum)
  {
   quint64 n = ecl_to_fixnum(clo);
   klra.set_cl_object(n);
  }
  else if(clt == t_string)
  {
   std::string str = cl_cxx::from_cl_object<std::string>(clo);
   klra.set_string(QString::fromStdString(str));
  }
  else if(clt == t_foreign)
  {
   klra.set_pVoid(ecl_foreign_data_pointer_safe(clo));
  }
  else
  {
   klra.set_cl_object( (quint64) clo);
  }
 }
}

void KCM_Lisp_Eval::prepare_dynamo_callbacks(void** pass_on)
{

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();
   if(rdg)
   {
    rdg->write_file_start();
   }
   return ECL_NIL;
  }, "KB", "WRITE-FILE-START", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();
   if(rdg)
   {
    rdg->write_file_end();
   }
   return ECL_NIL;
  }, "KB", "WRITE-FILE-END", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);
    QString sn = tokens.at(0).raw_text;
    QString tn = tokens.at(1).raw_text;
    if(rdg)
    {
     if(tn == ":fdef")
     {
      rdg->write_function_type_binding_statement(sn, tokens);
     }
     else
     {
      rdg->write_qreg_type_binding_statement(tn, sn);
     }
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-QREG-TYPE-BINDING-STATEMENT", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    MS_Token mst = cl_object_to_ms_token(sym);
    if(rdg)
    {
     rdg->write_promote_type_binding_expression(mst);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-PROMOTE-TYPE-BINDING-EXPRESSION", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   if(rdg)
   {
    rdg->write_cmd_eval();
   }
   return ECL_NIL;
  }, "KB", "WRITE-CMD-EVAL", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   if(rdg)
   {
    rdg->write_statement_clear();
   }
   return ECL_NIL;
  }, "KB", "WRITE-STATEMENT-CLEAR", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   if(rdg)
   {
    rdg->write_promote_expression();
   }
   return ECL_NIL;
  }, "KB", "WRITE-PROMOTE-EXPRESSION", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();
   int size = arglist->frame.size;
   cl_object clo = 0;
   int hdcode = 0;
   if(size > 1)
   {
    cl_object cclo = cl_cxx_backend::nth_arg(arglist, 1);
    hdcode = ecl_to_fixnum(cclo);
    clo = cl_cxx_backend::nth_arg(arglist, 2);
   }
   if(rdg)
   {
    quint64 qclo = 0;
    rdg->hold_deferred(hdcode, (quint64) clo, qclo);
    if(qclo)
    {
     reval->eval_held_form(qclo);
     rdg->finalize_hold_deferred();
    }
   }
   return ECL_NIL;
  }, "KB", "HOLD-DEFERRED", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);
    if(rdg)
    {
     rdg->write_s1_assignment_expression(tokens);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-S1-ASSIGNMENT-EXPRESSION", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);
    if(rdg)
    {
     rdg->write_s0_expression(tokens);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-S0-EXPRESSION", pass_on);

#define BASIC_DEFINE_CALLBACK(x, y) \
 define_callback( \
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object \
  { \
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]); \
   RZ_Dynamo_Generator* rdg = runtime->rdg(); \
   int size = arglist->frame.size; \
   if(size > 0) \
   { \
    QList<MS_Token> tokens; \
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens); \
    if(rdg) \
    { \
     rdg->y(tokens); \
    } \
   } \
   return ECL_NIL; \
  }, "KB", #x, pass_on); \


#define BASIC_DEFINE_NULLARY_CALLBACK(x, y) \
 define_callback( \
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object \
  { \
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]); \
   RZ_Dynamo_Generator* rdg = runtime->rdg(); \
   int size = arglist->frame.size; \
   if(rdg) \
   { \
    rdg->y(); \
   } \
   return ECL_NIL; \
  }, "KB", #x, pass_on); \


BASIC_DEFINE_CALLBACK(if-without-elsif, if_without_elsif)
BASIC_DEFINE_CALLBACK(if-with-else, if_with_else)
BASIC_DEFINE_CALLBACK(if-with-elsif, if_with_elsif)
BASIC_DEFINE_NULLARY_CALLBACK(push-nested-form-group, push_nested_form_group)
BASIC_DEFINE_NULLARY_CALLBACK(pull-nested-form-group, pull_nested_form_group)
BASIC_DEFINE_CALLBACK(enter-nested-form, enter_nested_form)
BASIC_DEFINE_CALLBACK(enter-secondary-nested-form, enter_secondary_nested_form)

BASIC_DEFINE_CALLBACK(nested-form-body, nested_form_body)

BASIC_DEFINE_CALLBACK(write-qpr, write_qpr)

BASIC_DEFINE_NULLARY_CALLBACK(write-enter-plene-block, write_enter_plene_block)
BASIC_DEFINE_NULLARY_CALLBACK(write-leave-plene-block, write_leave_plene_block)

BASIC_DEFINE_NULLARY_CALLBACK(write-enter-plebod, write_enter_plebod)

BASIC_DEFINE_NULLARY_CALLBACK(write-plene-block, write_plene_block)
BASIC_DEFINE_NULLARY_CALLBACK(write-enter-scope, write_enter_scope)
BASIC_DEFINE_NULLARY_CALLBACK(write-leave-scope, write_leave_scope)
BASIC_DEFINE_NULLARY_CALLBACK(leave-nested-form, leave_nested_form)
BASIC_DEFINE_NULLARY_CALLBACK(leave-secondary-nested-form, leave_secondary_nested_form)


BASIC_DEFINE_CALLBACK(write-plebod-symbol-declare-with-type ,write_plebod_symbol_declare_with_type)
BASIC_DEFINE_CALLBACK(write-plebod-symbol-init-with-type ,write_plebod_symbol_init_with_type)

BASIC_DEFINE_CALLBACK(write-anon-fdef, write_anon_fdef)

BASIC_DEFINE_CALLBACK(write-overloadable-fdef, write_overloadable_fdef)

BASIC_DEFINE_CALLBACK(prepare-expression, prepare_expression)
BASIC_DEFINE_CALLBACK(symbol-init-via-type, symbol_init_via_type)


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   RZ_Dynamo_Generator* rdg = runtime->rdg();
   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);
    if(rdg)
    {
     rdg->write_s0_expression(tokens);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-S0-EXPRESSION", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);
    if(rdg)
    {
     rdg->write_assignment_initialization_via_token(tokens);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-ASSIGNMENT-INITIALIZATION-VIA-TOKEN", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size > 0)
   {
    QList<MS_Token> tokens;
    cl_arglist_to_ms_tokens(size, 0, arglist, tokens);

    if(rdg)
    {
     rdg->write_s1_expression(tokens);
    }
   }
   return ECL_NIL;
  }, "KB", "WRITE-S1-EXPRESSION", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size > 0)
   {
   }
   return ECL_NIL;
  }, "KB", "_FC", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size > 0)
   {
    cl_object result = cl_cxx_backend::nth_arg(arglist, 1);
    if(SYMBOLP(result))
    {
     QString sn = cl_arglist_to_qstring(arglist, 1);

     switch(size)
     {
     case 1:
      break;
     case 2:
      {
       QString arg1 = cl_arglist_to_qstring(arglist, 2);
      }
      break;
     case 3:
      {
       QString arg1 = cl_arglist_to_qstring(arglist, 2);
       QString arg2 = cl_arglist_to_qstring(arglist, 3);
      }
      break;
     }
    }
   }
   return ECL_NIL;
  }, "KB", "tob", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size == 1)
   {
    QString sn = cl_arglist_to_qstring(arglist, 1);
   }
   return ECL_NIL;
  }, "KB", "KT", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QString followup_code;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    followup_code = cl_arglist_to_qstring(arglist, 1);
   }
  }, "KB", "tobc", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);
    cl_arglist_to_flagged_strings(size, 1, arglist, kw_flags, strings);
    QString result;
    if(rdg)
    {
     result = rdg->get_type_representation(sn, kw_flags, strings);
     return cl_cxx::to_cl_object<const std::string&>(result.toStdString());
    }
   }
   return ECL_NIL;
  }, "KB", "TR", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);
    cl_arglist_to_flagged_strings(size, 1, arglist, kw_flags, strings);
    if(rdg)
    {
     rdg->parse_sd(sn, kw_flags, strings);
    }
   }
   return ECL_NIL;
  }, "KB", "SD", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);

    cl_object sym1 = cl_cxx_backend::nth_arg(arglist, 2);
    QString sn1 = cl_object_to_qstring(sym1);

    if(rdg)
    {
     rdg->parse_si(sn, sn1);
    }
   }
   else if(size == 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);
    if(rdg)
    {
     rdg->hold_si(sn);
    }
   }
   return ECL_NIL;
  }, "KB", "SI", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);

    cl_object sym1 = cl_cxx_backend::nth_arg(arglist, 2);
    QString sn1 = cl_object_to_qstring(sym1);

    if(rdg)
    {
     rdg->parse_sa_entry(sn, sn1);
    }
   }
   return ECL_NIL;
  }, "KB", "SA_", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(rdg)
   {
    rdg->sa_leave();
   }
   return ECL_NIL;
  }, "KB", "_SA", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QStringList kw_flags;
   QStringList strings;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);
    cl_arglist_to_flagged_strings(size, 1, arglist, kw_flags, strings);
    if(rdg)
    {
     rdg->parse_sx(sn, kw_flags, strings);
    }
   }
   return ECL_NIL;
  }, "KB", "SX", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   RZ_Dynamo_Generator* rdg = runtime->rdg();
   int size = arglist->frame.size;
   QStringList kw_flags;
   QStringList strings;
   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);
    if(rdg)
    {
     rdg->write_fuxe_carrier(sn);
    }
   }
   return ECL_NIL;
  }, "KB", "FC", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   RZ_Dynamo_Generator* rdg = runtime->rdg();
   int size = arglist->frame.size;
   if(size > 0)
   {
    QStringList strs;
    cl_arglist_to_strings(size, 0, arglist, strs);
    if(rdg)
    {
     rdg->write_s1_call(strs);
    }
   }
   return ECL_NIL;
  }, "KB", "S1C", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   RZ_Dynamo_Generator* rdg = runtime->rdg();
   int size = arglist->frame.size;
   QStringList kw_flags;
   QStringList strings;
   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    QString sn = cl_object_to_qstring(sym);

    if(rdg)
    {
     rdg->write_lambda_literal_carrier(sn);
    }
   }
   return ECL_NIL;
  }, "KB", "LL", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   rdg->enter_fn_body();
   return ECL_NIL;
  }, "KB", "FB_", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   rdg->leave_fn_body();
   return ECL_NIL;
  }, "KB", "_FB", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   rdg->enter_statement();
   return ECL_NIL;
  }, "KB", "ST_", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   RZ_Dynamo_Generator* rdg = runtime->rdg();

   rdg->leave_statement();
   return ECL_NIL;
  }, "KB", "_ST", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QString code;

   if(size == 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    code = cl_arglist_to_qstring(arglist, 1);
   }
   return ECL_NIL;
  }, "KB", "HP", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    if(SYMBOLP(sym))
    {
     QString sn = cl_arglist_to_qstring(arglist, 1);
     if(size == 1)
     {
     }
    }
   }
   return ECL_NIL;
  }, "KB", "SR", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size > 0)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    if(SYMBOLP(sym))
    {
     QString type_name = cl_arglist_to_qstring(arglist, 1);
     QString type_expression = cl_arglist_to_qstring(arglist, 2);
    }
   }
   return ECL_NIL;
  }, "KB", "TD", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);

   if(runtime->rdg())
   {
    runtime->rdg()->enter_scope();
    return ECL_NIL;
   }

   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;
   if(size == 1)
   {
    cl_object cl_arg = cl_cxx_backend::nth_arg(arglist, 1);
    void* pv = ecl_foreign_data_pointer_safe(cl_arg);
   }
   else
   {
   }
   return ECL_NIL;
  }, "KB", "ES", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;

   if(size == 2)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    if(SYMBOLP(sym))
    {
     QString sn = cl_arglist_to_qstring(arglist, 1);
     cl_object sym1 = cl_cxx_backend::nth_arg(arglist, 2);
     if(SYMBOLP(sym1))
     {
      QString sn1 = cl_arglist_to_qstring(arglist, 2);
     }
    }
   }
   return ECL_NIL;
  }, "KB", "SC", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;

   if(size == 2)
   {
   }

   return ECL_NIL;
  }, "KB", "SV", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;

   if(size == 2)
   {

   }

   return ECL_NIL;
  }, "KB", "SVS", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   if(runtime->rdg())
   {
    runtime->rdg()->leave_scope();
    return ECL_NIL;
   }

   return ECL_NIL;
  }, "KB", "LS", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);
    quint64 fixnum = ecl_to_fixnum(lambda_pos);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }

    cl_object result = cl_cxx_backend::nth_arg(arglist, 3);
    return result;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KL", "STR", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }

    quint64 fixnum = ecl_to_fixnum(lambda_pos);

    cl_object quoted = cl_cxx_backend::nth_arg(arglist, 3);

    return quoted;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "CLQ", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size > 0)
   {
    QString symbol_name = cl_arglist_to_qstring(arglist, 1);
    quint64 result = runtime->bridge().get_value_of_symbol(symbol_name);
    return (cl_object) result;
   }
   return ECL_NIL;
  }, "KA", "VOF", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size > 0)
   {
    QString symbol_name = cl_arglist_to_qstring(arglist, 1);
    QString mode;
    quint64 result = runtime->bridge().get_interpreted_value_of_symbol(symbol_name, mode);
    if(mode == "fixnum")
    {
     return ecl_make_fixnum(result);
    }
    if(mode == "str")
    {
     QString* qs = (QString*) result;
     return make_base_string_copy(qs->toStdString().c_str());
    }
    return (cl_object) result;
   }
   return ECL_NIL;
  }, "KA", "IVOF", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   if(size > 0)
   {
    QString symbol_name = cl_arglist_to_qstring(arglist, 1);
    quint64 result = runtime->bridge().get_value_of_symbol(symbol_name);
    return (cl_object) result;
   }
   return ECL_NIL;
  }, "KA", "UNHOLD", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }
   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "CLF", pass_on);



 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size == 2)
   {
    cl_object lambda = cl_cxx_backend::nth_arg(arglist, 1);
    QString fname = cl_arglist_to_qstring(arglist, 2);
    runtime->bridge().kcm_finalize_fdef((quint64) lambda, fname);

   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "FINALIZE-FDEF", pass_on);
}


void KCM_Lisp_Eval::prepare_callbacks()
{
 void** pass_on = (void**) malloc(2 * sizeof(void*));

 pass_on[0] = kcm_lisp_runtime_;
 pass_on[1] = this;

 // //  TODO: delete unused ...
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KM\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KA\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KB\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KI\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KL\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KG\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"KC\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"CY\")");
 cl_cxx_backend::eval_string("(DEFPACKAGE \"CX\")");

 prepare_dynamo_callbacks(pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {

  }, "KA", "QDEBUG", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;

   bool result = false;
   if(size > 0)
   {
    cl_object arg = cl_cxx_backend::nth_arg(arglist, 1);
    cl_type clt = ecl_t_of(arg);
    switch(clt)
    {
    case t_fixnum:
    case t_bignum:
    case t_ratio:
    case t_singlefloat:
    case t_doublefloat:
     result = !ecl_zerop(arg); break;
    default:
     result = ecl_to_bool(arg); break;
    }
   }
   if(result)
   {
    return ECL_T;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "to_bool", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   int size = arglist->frame.size;

   bool result = false;
   if(size > 0)
   {
    cl_object arg = cl_cxx_backend::nth_arg(arglist, 1);
    cl_type clt = ecl_t_of(arg);
    switch(clt)
    {
    case t_fixnum:
    case t_bignum:
    case t_ratio:
    case t_singlefloat:
    case t_doublefloat:
     result = !ecl_zerop(arg); break;
    default:
     result = ecl_to_bool(arg); break;
    }
   }
   if(result)
   {
    return ECL_NIL;
   }
   else
   {
    return ECL_T;
   }
  }, "KA", "to_bool_not", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
 {
  KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
  KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

  int size = arglist->frame.size;

  if(size > 0)
  {
   cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);

   if(SYMBOLP(sym))
   {
    QString sn = cl_arglist_to_qstring(arglist, 1);

    QVector<KCM_Lisp_Runtime_Argument> klras;
    klras.resize(size);

    if(sn.startsWith('_'))
    {
     QString kw = reval->cl_arglist_to_opaque_arguments(arglist, klras);
     klras[1].set_string(kw);
    }
    else
    {
     reval->cl_arglist_to_arguments(arglist, klras);
    }
    runtime->kcm_call(sn, klras);
    const KCM_Lisp_Runtime_Argument& klra = klras[0];
    switch(klra.get_kind())
    {
    case KCM_Lisp_Runtime_Argument::Kinds::Cl_Object:
     return (cl_object) klra.cl_object();
    case KCM_Lisp_Runtime_Argument::Kinds::String:
     return make_base_string_copy(klra.string().toStdString().c_str());
    case KCM_Lisp_Runtime_Argument::Kinds::PVoid:
     return cl_cxx_backend::make_foreign_data(klra.pVoid());
    default:
     return ECL_NIL;
    }

   }
  }
 }, "KA", "KC", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);
   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);

   int size = arglist->frame.size;

   QString followup_code;

   if(size > 1)
   {
    cl_object sym = cl_cxx_backend::nth_arg(arglist, 1);
    followup_code = cl_arglist_to_qstring(arglist, 1);
   }
  }, "KA", "tobc", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;
   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);
    quint64 fixnum = ecl_to_fixnum(lambda_pos);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }

    cl_object result = cl_cxx_backend::nth_arg(arglist, 3);

    return result;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KL", "STR", pass_on);


 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }

    quint64 fixnum = ecl_to_fixnum(lambda_pos);

    cl_object quoted = cl_cxx_backend::nth_arg(arglist, 3);

    return quoted;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "CLQ", pass_on);

 define_callback(
  [](void* pass_on, cl_cxx_backend::cl_arglist arglist) -> cl_object
  {
   KCM_Lisp_Runtime* runtime = reinterpret_cast<KCM_Lisp_Runtime*>( ((void**) pass_on)[0]);
   KCM_Lisp_Eval* reval = reinterpret_cast<KCM_Lisp_Eval*>( ((void**) pass_on)[1]);

   cl_object result_size = cl_cxx_backend::nth_arg(arglist, 0);
   int size = arglist->frame.size;

   if(size == 3)
   {
    cl_object lambda_pos = cl_cxx_backend::nth_arg(arglist, 1);

    QString access;
    cl_object access_sym = cl_cxx_backend::nth_arg(arglist, 2);
    if(SYMBOLP(access_sym))
    {
     access = cl_arglist_to_qstring(arglist, 2);
    }

    // //  just a plain cl_object or ...?
    cl_object lisp_function = cl_cxx_backend::nth_arg(arglist, 3);

    cl_object* save_cl = new cl_object;
    *save_cl = lisp_function;
   }
   else
   {
    return ECL_NIL;
   }
  }, "KA", "CLF", pass_on);


}

QString KCM_Lisp_Eval::get_string_rep(cl_object clo)
{
 cl_object clp = cl_print(1, clo);
 QString result = cl_object_to_qstring(clp);
 return result;
}


void KCM_Lisp_Eval::eval_script_file(QString file_name, int load_depth, QString top_file)
{
 QFile file(file_name);

 if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  return;
 QString eval_text = file.readAll();

 eval_text.prepend("(progn\n");
 eval_text.append("\n\n);progn\n");

 QFileInfo fi(file_name);
 QDir default_dir = fi.absoluteDir();

 if(top_file.isEmpty())
  top_file = file_name;

 QString result = eval_string(eval_text);

}

void KCM_Lisp_Eval::eval_file(QString file_name, int load_depth, QString top_file)
{
 QFile file(file_name);

 if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  return;
 QString eval_text = file.readAll();

 QFileInfo fi(file_name);
 QDir default_dir = fi.absoluteDir();

 if(top_file.isEmpty())
  top_file = file_name;

 QString result = eval_string(eval_text);
}


QString KCM_Lisp_Eval::eval_string(QString eval_text)
{
 QString result;
 cl_object result_cl = cl_cxx_backend::eval_string(eval_text.toLatin1().data());
 result_cl = si_coerce_to_base_string(result_cl);
 unsigned char * cc = result_cl->base_string.self;

 for(unsigned char* c = cc; *c != 0; ++c)
 {
  QChar qc = QChar::fromLatin1(*c);
  result += qc;
 }
 return result;
}

QString KCM_Lisp_Eval::cl_arglist_to_qstring(cl_cxx_backend::cl_arglist arglist)
{
 QString result;
 cl_object result_cl = cl_cxx_backend::nth_arg(arglist, 1);
 result_cl = si_coerce_to_base_string(result_cl);
 unsigned char * cc = result_cl->base_string.self;

 for(unsigned char* c = cc; *c != 0; ++c)
 {
  QChar qc = QChar::fromLatin1(*c);
  result += qc;
 }
 return result;
}

MS_Token KCM_Lisp_Eval::cl_object_to_ms_token(cl_object clo)
{
 QString str = cl_object_to_qstring(clo);
 return MS_Token::decode(str);
}

cl_object KCM_Lisp_Eval::qstring_to_cl_object(QString qs)
{
 std::string sstr = qs.toStdString();
 return cl_cxx::to_cl_object<const std::string&>(sstr);
}

QString KCM_Lisp_Eval::cl_object_to_qstring(cl_object clo)
{
 QString result;
 clo = si_coerce_to_base_string(clo);
 unsigned char * cc = clo->base_string.self;

 for(unsigned char* c = cc; *c != 0; ++c)
 {
  QChar qc = QChar::fromLatin1(*c);
  result += qc;
 }
 return result;
}

QString KCM_Lisp_Eval::cl_arglist_to_qstring(cl_cxx_backend::cl_arglist arglist, int index)
{
 QString result;
 cl_object result_cl = cl_cxx_backend::nth_arg(arglist, index);
 result_cl = si_coerce_to_base_string(result_cl);
 unsigned char * cc = result_cl->base_string.self;

 for(unsigned char* c = cc; *c != 0; ++c)
 {
  QChar qc = QChar::fromLatin1(*c);
  result += qc;
 }
 return result;
}

#endif // USING_ECL

