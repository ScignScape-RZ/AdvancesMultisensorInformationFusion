
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-basic-functions.h"


#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kcm-command-runtime/kcm-command-runtime-table.h"

#include "kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "fn-doc/fn-doc.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)

KANS_(Dynamo)


void test_call(KCM_Callable_Value* kcv)
{
 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}

void test_void()
{
 qDebug() << "OK";
}

void test_dfr_call(quint64 qclo, KCM_Callable_Value* kcv)
{
 quint64 result;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
 qDebug() << result;

 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}


void lr(quint64 qclo)
{
 quint64 result = 0;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "nil");
 qDebug() << result;
}



void test_int_call(int num, KCM_Callable_Value* kcv)
{
 qDebug() << num;

 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}



void test_dfr(quint64 qclo, quint64 qclo1)
{
 quint64 x = (quint64) qclo;
 quint64 y = (quint64) qclo1;

 void* vx = (void*) x;
 void* vy = (void*) y;

 QPair<KCM_Scope_System*, QPair<int, quint64>>* pr2 =
   (QPair<KCM_Scope_System*, QPair<int, quint64>>*) qclo;

 QPair<KCM_Scope_System*, QPair<int, quint64>>* pr3 =
   (QPair<KCM_Scope_System*, QPair<int, quint64>>*) qclo1;

 quint64 result;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
 qDebug() << result;

 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo1, result, "fixnum");
 qDebug() << result;
}



void test_calls(KCM_Callable_Value* kcv, KCM_Callable_Value* kcv1)
{
 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);

 KCM_Command_Runtime_Router* kcrr1 = kcv1->kcrr();
 kcrr1->run_callable_value(kcv1);
}


void test_arg_vec_calls(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
  KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
  kcrr->run_callable_value(*kcv);
 }
}

void test_arg_vec_dfr_call(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 for(quint64 qui: args)
 {
  if(i % 2)
  {
   KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
   KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
   kcrr->run_callable_value(*kcv);
  }
  else
  {
   quint64 qclo = *((quint64*)qui);

   quint64 result;
   KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
   qDebug() << result;
  }
  ++i;
 }
}

int test_find(QString outstr, QString instr)
{
 return outstr.indexOf(instr);
}

void test_arg_vec_str(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  QString** qs = (QString**) qui;
  qDebug() << **qs;
 }
}


void test_if_then_else(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 bool test = false;
 for(quint64 qui: args)
 {
  if(i % 2)
  {
   if(test)
   {
    KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
    KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
    kcrr->run_callable_value(*kcv);
    return;
   }
  }
  else
  {
   quint64 qclo = *((quint64*)qui);

   quint64 result;
   KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "bool");
   qDebug() << result;
   test = (bool) result;
  }
  ++i;
 }
}

void if_t_e(quint64 args_ptr)
{
 test_if_then_else(args_ptr);
}

void fndoc_read(Fn_Doc* fnd, QString fn)
{
 qDebug() << "Reading " << fn << " ...";
 fnd->read(fn);
}

QString fndoc_test_summary(Fn_Doc* fnd)
{
 QString summ = fnd->test_summary();
 return summ;
}


void* envv(void* kind)
{
 if(kind)
 {
  qDebug() << "Kind: " << *(QString*)kind;
  return insert_envv(kind, nullptr);
 }
 else
 {
  qDebug() << "In envv: Return kind could not be determined.";
  return nullptr;
 }
}

void* insert_envv(void* kind, void* test)
{
 static QMap<QString, void*> hold;
 QString* k = reinterpret_cast<QString*>(kind);
 if(test)
 {
  hold[*k] = test;
 }
 return hold.value(*k);
}

void prs(QString str)
{
 qDebug() << str;
}

void test_prss(QString str1, QString str2)
{
 qDebug() << str1;
 qDebug() << str2;
}


void prn(int num)
{
 qDebug() << num;
}


void pr_two_n(int num, int n1)
{
 qDebug() << num << ", " << n1;
}

void prdn(quint64 num, quint64 n1)
{
 qDebug() << num << ", " << n1;
}

int let_num(int num)
{
 return num;
}

QString let_str(QString str)
{
 return str;
}

void init_basic_functions_kci(Kauvir_Code_Model& kcm)
{
 init_test_functions_kci(kcm);

 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table& table = *kcm.table();

 KCM_Channel_Group g1(kcm.channel_names());
 {
  g1.add_sigma_carrier(
    {kcm.get_kcm_type_by_type_name( "Fn_Doc*" ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  // // use read-f since read also applies to multi ...
  table.init_phaon_function(g1, "read-f", 710, &fndoc_read);

  g1.clear_all();
 }

 {
  g1.add_sigma_carrier(
    {kcm.get_kcm_type_by_type_name( "Fn_Doc*" ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-summary", 610, &fndoc_test_summary);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "prs", 700, &prs);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test_prss", 700, &test_prss);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-arg-vec-calls", 700, &test_arg_vec_calls);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-find", 700, &test_find);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-arg-vec-str", 700, &test_arg_vec_str);

  g1.clear_all();
 }

 {
  table.init_phaon_function(g1, "test-void", 700, &test_void);
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-arg-vec-dfr-call", 700, &test_arg_vec_dfr_call);

  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-if-then-else", 700, &test_if_then_else);

  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "if-t-e", 700, &if_t_e);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "prn", 700, &prn);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "pr-two-n", 700, &pr_two_n);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "prdn", 700, &prdn);

  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-call", 700, &test_call);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-dfr", 700, &test_dfr);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-calls", 700, &test_calls);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "lr", 700, &lr);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-dfr-call", 700, &test_dfr_call);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  table.init_phaon_function(g1, "test-int-call", 700, &test_int_call);

  g1.clear_all();
 }

 {
  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "let_num", 700, &let_num);

  g1.clear_all();
 }

 {
  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "let_str", 700, &let_str);

  g1.clear_all();

 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "envv", 700, &envv);

  g1.clear_all();
 }


}

_KANS(Dynamo)

