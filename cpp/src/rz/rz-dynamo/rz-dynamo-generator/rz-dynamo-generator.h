
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_GENERATOR__H
#define RZ_DYNAMO_GENERATOR__H


#include "accessors.h"

#include "multistep-token.h"

#include "kans.h"

#include <QString>
#include <QStringList>
#include <QStack>
#include <QPair>

class QTextStream;

KANS_(Dynamo)

class KCM_Direct_Eval_Info
{
 QString temp_;

public:

 KCM_Direct_Eval_Info();

};

class RZ_Dynamo_Nested_Acc;


class RZ_Dynamo_Generator
{
 QTextStream& overall_qts_;

 QTextStream* qts_;

 QStack<QTextStream*> qts_stack_;

 signed int scope_depth_;

 QString held_init_symbol_;

 KCM_Direct_Eval_Info* direct_eval_info_;

 void write_set_kto(const MS_Token& mst);

 enum Pending_Expression_State
 {
  N_A,  If_Without_Elsif,
  If_With_Elsif,  If_With_Else,
  Elsif_With_Elsif
 };

 Pending_Expression_State pending_expression_state_;

 QMap<QPair<int, int>, QString> expression_accs_;

 int current_expression_acc_index_;
 int current_nesting_level_;

 QStack<QPair<QString, QPair<int, int>>> write_triggers_;

 QMap<QPair<int, int>, QString> pending_fdef_blocks_;

 QMap<QPair<int, int>, QString> pending_anon_fdef_blocks_;

 int current_nested_target_;
 int current_nested_form_index_;
 int current_nested_form_level_;

 QString pending_fdef_name_;

 QMap<QString, QList<RZ_Dynamo_Nested_Acc*>> nested_acc_triggers_;

 void check_nested_target(int val);

 void write_recurring_symbols();

 QString* get_current_acc();
 void init_write_trigger(QString str, QPair<int, int> trigger);
 void check_push_qts();
 void check_pop_qts();

 int write_expression_template_list(QString& templt, QList<MS_Token>& tokens);
 int write_cond_expression_template_list(QString& templt, QList<MS_Token>& tokens);


 void check_subtract_triggers(QStringList& readies);


public:


 RZ_Dynamo_Generator(QTextStream& overall_qts);

 void write_plebod_symbol_declare_with_type(QList<MS_Token>& tokens);
 void write_plebod_symbol_init_with_type(QList<MS_Token>& tokens);

 void write_enter_plebod();

 void prepare_expression(QList<MS_Token>& tokens);
 void if_without_elsif(QList<MS_Token>& tokens);
 void if_with_elsif(QList<MS_Token>& tokens);
 void if_with_else(QList<MS_Token>& tokens);
 void elsif_with_elsif(QList<MS_Token>& tokens);
 void nested_form_body(QList<MS_Token>& tokens);
 void enter_nested_form(QList<MS_Token>& tokens);
 void enter_secondary_nested_form(QList<MS_Token>& tokens);
 void write_overloadable_fdef(QList<MS_Token>& tokens);

 QString get_lisp_call_mode_insertion(QString raw_text);

 void write_anon_fdef(QList<MS_Token>& tokens);

 void leave_nested_form();
 void leave_secondary_nested_form();
 void push_nested_form_group();
 void pull_nested_form_group();

 void write_qpr(QList<MS_Token>& tokens);

 void hold_deferred(int hdcode, quint64 clo, quint64& eval_clo);
 void finalize_hold_deferred();

 void write_enter_plene_block();
 void write_leave_plene_block();

 void write_plene_block();
 void write_enter_scope();
 void write_leave_scope();

 void add_acc_token(QString& acc, const MS_Token& token, QStringList& nested_incompletes);


 void enter_scope();
 void leave_scope();

 void enter_fn_body();
 void leave_fn_body();

 void write_qreg_type_binding_statement(QString type, QString symbol_name);

 void write_s0_expression(QList<MS_Token>& tokens);
 void write_s1_expression(QList<MS_Token>& tokens);
 void write_s1_assignment_expression(QList<MS_Token>& tokens);

 void write_function_type_binding_statement(QString sn, QList<MS_Token>& tokens);

 void write_assignment_initialization_via_token(QList<MS_Token>& tokens);

 void symbol_init_via_type(QList<MS_Token>& tokens);
 void write_symbol_init_via_type_default_value(QString symbol_name, QString memtype);

 void write_lambdas(QList<MS_Token>& tokens);
 int write_nested_lambdas(QList<MS_Token>& tokens, int start, int depth);

 void write_promote_type_binding_expression(MS_Token& mst);
 void write_promote_expression();

 void write_cmd_eval();
 void write_statement_clear();

 void enter_statement();
 void leave_statement();
 void minimal_leave_statement();

 void write_file_start();
 void write_file_end();

 void write_fuxe_carrier(QString sn);
 void write_lambda_literal_carrier(QString sn);

 void parse_sx(QString sn, QStringList& kw_flags, QStringList& strings);

 void parse_sd(QString sn, QStringList& kw_flags, QStringList& strings);

 void parse_si(QString sn, QString arg);

 void parse_sa_entry(QString assignment_kind, QString sn);
 void sa_leave();

 void hold_si(QString sn);

 QString get_type_representation(QString sn, QStringList& kw_flags, QStringList& strings);

 void write_s1_call(QStringList& qsl);
};


_KANS(Dynamo)

#endif //RZ_DYNAMO_GENERATOR__H
