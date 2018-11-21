
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_RUNTIME_ROUTER__H
#define KCM_COMMAND_RUNTIME_ROUTER__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include "kans.h"
#include "accessors.h"

#include "kcm-command-runtime-router-cast-schedule.h"


KANS_CLASS_DECLARE(KCM ,KCM_Carrier)
KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)
KANS_CLASS_DECLARE(KCM ,KCM_Expression)
KANS_CLASS_DECLARE(KCM ,KCM_Proxy_Scope)
KANS_CLASS_DECLARE(KCM ,KCM_Callable_Value)

KANS_CLASS_DECLARE(PhaonLib ,Phaon_Function_Vector)
USING_KANS(PhaonLib)


USING_KANS(KCM)

KANS_(CMD)

class KCM_Command_Runtime_Argument;
class KCM_Command_Package;
class KCM_Scope_System;

class KCM_Command_Runtime_Table;

class KCM_Command_Runtime_Router
{

 enum class UC_Argument_Conventions {
  N_A,
  Value_Direct,
 };

 enum class QOB_Argument_Conventions {
  N_A,
  QObject_Direct,
  Value_From_QString,
  QString_Direct,

 };

 enum class Return_Conventions {
  N_A, No_Return,
  Value_Direct,
 };

 enum class Reflection_Conventions {
  N_A, Qt_Meta_Object, Universal_Class, CL_Object
 };

 enum class Arg_Type_Codes {
   N_A, No_Return, QString_Return, Void_Pointer, Int, Float,
 };


 static Arg_Type_Codes parse_return_type_code(QString key)
 {
  if(key.endsWith("*"))
   return Arg_Type_Codes::Void_Pointer;
  static QMap<QString, Arg_Type_Codes> static_map {{
   {"u32", Arg_Type_Codes::Int},
   {"int", Arg_Type_Codes::Int},
   {"QString", Arg_Type_Codes::QString_Return},
  }};
  return static_map.value(key, Arg_Type_Codes::No_Return);
 }

 Arg_Type_Codes return_type_code_;

 struct Argument_Info
 {
  void* void_argument;
  void* void_argument_for_delete;

  QString type_name;
  const QMetaType* qmt;
  const QMetaObject* qmo;

  int q_meta_type_id;

  QOB_Argument_Conventions qob_convention;
  UC_Argument_Conventions uc_convention;



  Argument_Info(): q_meta_type_id(QMetaType::UnknownType),
    void_argument(nullptr), void_argument_for_delete(nullptr),
    qmt(nullptr),
    qob_convention(QOB_Argument_Conventions::N_A),
    uc_convention(UC_Argument_Conventions::N_A)
  {

  }

  // // this might really be better with a modifier object ...
  QString type_name_with_modifier(QString modifier, QString internal_type_string) const
  {
   QString tn;
   // hard code for now -- kludge...
   if(internal_type_string == "clv" && type_name == "void*")
   {
    tn = "Kauvir_Lisp_Callback*";
   }
   else if(type_name.isEmpty())
   {
    tn = internal_type_string;
   }
   else
   {
    tn = type_name;
   }
   if(modifier.isEmpty())
   {
    return tn;
   }
   else
   {
    QString post;
    if(modifier.endsWith('&'))
    {
     post += "&";
     modifier.chop(1);
    }
    QString m = modifier.replace('.', ' ') + ' ';
    return m.simplified() + ' ' + tn + post;
   }
  }
 };

 template<int Arg_Count>
 struct Do_Invoke_Method
 {
  static void run(KCM_Command_Runtime_Router* this_, QVector<KCM_Command_Runtime_Argument*>& args);
  static void run__no_uc(KCM_Command_Runtime_Router* this_, QVector<KCM_Command_Runtime_Argument*>& args);
 };

 template<int Arg_Count, bool ALLOW_UC>
 struct Do_Invoke_Method_;


 template<int Arg_Count>
 struct Do_Invoke_Method_<Arg_Count, true>
 {
  template<Return_Conventions RC>
  struct With_Return_Convention
  {
   static void run(KCM_Command_Runtime_Router* this_,
     QVector<KCM_Command_Runtime_Argument*>& args)
   {
    Do_Invoke_Method<Arg_Count>::run(this_, args);
   }
  };

  static void run(KCM_Command_Runtime_Router* this_, QVector<KCM_Command_Runtime_Argument*>& args)
  {
    Do_Invoke_Method<Arg_Count>::run(this_, args);
  }
 };

 template<int Arg_Count>
 struct Do_Invoke_Method_<Arg_Count, false>
 {
  template<Return_Conventions RC>
  struct With_Return_Convention
  {
   static void run(KCM_Command_Runtime_Router* this_,
     QVector<KCM_Command_Runtime_Argument>& args)
   {
    Do_Invoke_Method<Arg_Count>::run__no_uc(this_, args);
   }
  };

  static void run(KCM_Command_Runtime_Router* this_, QVector<KCM_Command_Runtime_Argument>& args)
  {
    Do_Invoke_Method<Arg_Count>::run__no_uc(this_, args);
  }
 };

 void do_invoke_method(QVector<KCM_Command_Runtime_Argument*>& args);

 void init_argument_info(QVector<KCM_Command_Runtime_Argument*>& args,
   QVector<quint64>& store);
 void init_argument_info_qob(QVector<KCM_Command_Runtime_Argument*>& args,
   QVector<quint64>& store);
 void init_argument_info_uc(QVector<KCM_Command_Runtime_Argument*>& args,
   QVector<quint64>& store);



 KCM_Command_Runtime_Argument* sigma_argument_;
 QVector<KCM_Command_Runtime_Argument*> lambda_arguments_;
 QVector<Argument_Info> argument_info_;
 Reflection_Conventions reflection_convention_;

 QString fuxe_name_;

 const KCM_Type_Object* result_type_object_;

 KCM_Command_Runtime_Table* table_;
 KCM_Scope_System* scopes_;

 quint64 call_result_;

 QString& string_result_;

 KCM_Expression* kcm_expression_;

 KCM_Proxy_Scope* proxy_scope_;

 quint64 string_result_code_;

 QString cpkg_output_symbol_name_;

 typedef void*(*envv_fn_type)(void*);
 envv_fn_type envv_fn_;

 QOB_Argument_Conventions qob_argument_convention_from_type_name(QString tn);

 enum class FN_Codes
 {
  N_A,
  NOR_CC, RET_CC,
  NOR_C, RET_C,
  NOR_P, RET_P,
  NOR_R, RET_R,
  NOR_S, RET_S,
  NOR_PC, NOR_RC, NOR_SC,
  NOR_PP, NOR_RP, NOR_SP,
  NOR_PR, NOR_RR, NOR_SR,
  NOR_PS, NOR_RS, NOR_SS,
  RET_PC, RET_RC, RET_SC,
  RET_PP, RET_RP, RET_SP,
  RET_PR, RET_RR, RET_SR,
  RET_PS, RET_RS, RET_SS,
 };

 QString output_type_string();

public:

 KCM_Command_Runtime_Router(KCM_Command_Runtime_Table* table,
   KCM_Scope_System* scopes, KCM_Proxy_Scope* proxy_scope, QString& string_result);

 ACCESSORS(quint64 ,call_result)
 ACCESSORS(quint64 ,string_result_code)
 ACCESSORS(const KCM_Type_Object* ,result_type_object)

 ACCESSORS(Arg_Type_Codes ,return_type_code)
 ACCESSORS(KCM_Proxy_Scope* ,proxy_scope)

 ACCESSORS(QString ,fuxe_name)
 ACCESSORS__RGET(QVector<Argument_Info> ,argument_info)
 ACCESSORS(envv_fn_type ,envv_fn)

 QString return_type_name();

 quint64& raw_result_ref()
 {
  return call_result_;
 }

 ACCESSORS__RGET(QString ,string_result)

 QString return_type_name_strip_namespace();

 QObject* this_object();

 KCM_Channel_Group* get_channel_group();

 void parse_command_package(KCM_Command_Package* cpkg);
 KCM_Command_Runtime_Argument* parse_carrier_to_argument(KCM_Carrier& kcc, int pos);

 void proceed();
 void proceed_s0(Phaon_Function_Vector* pfv);
 void proceed_s1(Phaon_Function_Vector* pfv);

 void proceed_s0_argvec(s0_fn1_p_type fn, void** pResult, int byte_code,
   bool sr, int s10_size = 0);

 void proceed_s0_0(Phaon_Function_Vector* pfv, void** pResult);

 void proceed_s0_1(Phaon_Function_Vector* pfv, void** pResult);

 void proceed_s0_2(Phaon_Function_Vector* pfv, void** pResult);

 template<int c, typename fn_type>
 void proceed_s0(void** pResult, fn_type fn, int byte_code, bool sr, bool s10 = false);

 template<int c, typename fn_type>
 void proceed_s0(QVector<quint64>& args, void** pResult,
   fn_type fn, int byte_code, bool sr);


 template<int c, typename fn_type>
 void proceed_s0_r(QVector<quint64>& args, void*& result,
   fn_type fn, int byte_code);

 template<int c, typename fn_type>
 void proceed_s0_sr(QVector<quint64>& args,
   fn_type fn, int byte_code);

 template<int c, typename fn_type>
 void proceed_s0_nor(QVector<quint64>& args,
   fn_type fn, int byte_code);

 Phaon_Function_Vector* get_phaon_function_vector(QString fn);

 void proceed_s1_0(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);
 void proceed_s1_1(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);
 void proceed_s1_2(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);

 void proceed_s1_0_uc(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);
 void proceed_s1_1_uc(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);
 void proceed_s1_2_uc(Phaon_Function_Vector* pfv, void** pResult, void* raw_value);

 FN_Codes check_init_raw_value(KCM_Command_Runtime_Argument* kcra,
   FN_Codes fnc, quint64& mem, QPair<KCM_Scope_System*, QPair<int, quint64>>& qclo_value,
   QString* const& qs_mem, void*& result, int& ptr_depth);

 FN_Codes add_string_cast_to_fn_code(FN_Codes fnc);
 FN_Codes add_ptr_cast_to_fn_code(FN_Codes fnc);

 void run_callable_value(KCM_Callable_Value* kcv);

 void hold_string_result(QString str)
 {
  string_result_ = str;
  string_result_code_ = (quint64) &string_result_;
 }


};

_KANS(CMD)

#endif //KCM_COMMAND_RUNTIME_ROUTER__H
