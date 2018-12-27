
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-generator.h"


#include <QTextStream>
#include <QDebug>

#include "rz-dynamo-nested-acc.h"

USING_KANS(Dynamo)


KCM_Direct_Eval_Info::KCM_Direct_Eval_Info()
{

}


RZ_Dynamo_Generator::RZ_Dynamo_Generator(QTextStream& overall_qts)
  :  overall_qts_(overall_qts), qts_(&overall_qts),
     scope_depth_(-1), current_nested_target_(0),
     direct_eval_info_(new KCM_Direct_Eval_Info),
     current_expression_acc_index_(0), current_nesting_level_(0),
     current_nested_form_index_(0), current_nested_form_level_(0),
     pending_expression_state_(Pending_Expression_State::N_A)
{

}

void RZ_Dynamo_Generator::check_nested_target(int val)
{
 if(current_nested_target_ < val)
 {
  current_nested_target_= val;
 }
}


void RZ_Dynamo_Generator::leave_scope()
{
 if(scope_depth_ > 0)
 {

 }
 else
 {
  // end of file
  (*qts_) << "\n\n)\n";
 }
 --scope_depth_;

}

void RZ_Dynamo_Generator::write_file_start()
{
 (*qts_) << "\n;;- file_ ...\n\n";
 enter_scope();
}

void RZ_Dynamo_Generator::write_file_end()
{
 (*qts_) << "\n\n;;- _file ...\n";
 leave_scope();
}

void RZ_Dynamo_Generator::write_overloadable_fdef(QList<MS_Token>& tokens)
{
 QString sn = tokens.at(0).raw_text;
 write_function_type_binding_statement(sn, tokens);
}


void RZ_Dynamo_Generator::write_function_type_binding_statement(QString sn, QList<MS_Token>& tokens)
{
 // //  is this not needed?
 //?sn.replace('-', '_');

 int sz = tokens.size();

 QString prin1 = tokens.at(2).raw_text;
 (*qts_) << "\n\n; fn_sig_ ...\n";
 (*qts_) << prin1;

 if(sz > 3)
 {
  (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_nested_block| \""
          << sn << "\" kto))";
 }
 else
 {
  (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_overloadable_function_type_binding_to_statement| \""
          << sn << "\" kto))";
 }
 write_cmd_eval();

 if(sz > 3)
 {
  (*qts_) << "\n\n; _fn_sig ...\n";
  int index = tokens.at(3).second_number();
  pending_fdef_blocks_[{current_nesting_level_, index}] = sn;
 }
 else
 {
  (*qts_) << "\n; _fn_sig (no def) ...\n";
  (*qts_) << "\n(ka::kc :|kcg_clear_all| kcg)";
 }
}

void RZ_Dynamo_Generator::write_qreg_type_binding_statement(QString type, QString symbol_name)
{
 (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object_by_qregistered_type_name| \""
      << type << "\") )";
 (*qts_) << "\n(ka::kc :|kcm_add_type_binding| \"" << symbol_name << "\" kto)";
}

void RZ_Dynamo_Generator::write_promote_expression()
{
 (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_expression_to_statement| kcx))";
}

void RZ_Dynamo_Generator::symbol_init_via_type(QList<MS_Token>& tokens)
{
 if(tokens.size() == 2)
 {
  write_symbol_init_via_type_default_value(tokens.first().raw_text, tokens.at(1).raw_text);
  return;
 }
 else
 {
  write_symbol_init_via_type_default_value(tokens.first().raw_text, "let");
 }
 // todo ...
}

void RZ_Dynamo_Generator::write_symbol_init_via_type_default_value(QString symbol_name, QString memtype)
{
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_promote_type_binding_to_statement_via_type_default_literal__"
   << memtype << "| kcg \"" << symbol_name << "\"))";
}

void RZ_Dynamo_Generator::write_assignment_initialization_via_token(QList<MS_Token>& tokens)
{
 const MS_Token& askind = tokens.at(0);

 const MS_Token& sym = tokens.at(1);

 const MS_Token& typ = tokens.at(2);
 write_set_kto(typ);
 const MS_Token& tok = tokens.at(3);

 switch(tok.kind)
 {
 case MS_Token_Kinds::Literal:
  (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_token| \""
       << sym.raw_text << "\" kto \"" << tok.raw_text << "\"))";
  break;

 default:
  (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_token| \""
       << sym.raw_text << "\" kto " << tok.raw_text << "))";
  break;

 }
}

void RZ_Dynamo_Generator::write_s0_expression(QList<MS_Token>& tokens)
{
 MS_Token askind = tokens.takeAt(0);

 MS_Token tfuxe = tokens.takeAt(0);
 QString fuxe = tfuxe.raw_text.replace('-', '_');


 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \"" << fuxe << "\")";

 write_lambdas(tokens);
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
}


void RZ_Dynamo_Generator::write_s1_assignment_expression(QList<MS_Token>& tokens)
{
 MS_Token askind = tokens.takeAt(0);
 MS_Token sigma_check_symbol = tokens.takeAt(0);

 // // right order?
 MS_Token t1 = tokens.takeAt(0);
 MS_Token t2 = tokens.takeAt(0);

 MS_Token tfuxe;
 MS_Token tsigma;
 if(t1.kind == MS_Token_Kinds::Scoped_Symbol)
 {
  tfuxe = t2;
  tsigma = t1;
 }
 else
 {
  tfuxe = t1;
  tsigma = t2;
 }

 QString sigma = tsigma.raw_text;
 QString fuxe = tfuxe.raw_text.replace('-', '_');;

 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \"" << fuxe << "\")";
 (*qts_) << "\n(ka::kc :|kcg_add_sigma_carrier_via_symbol| kcg \"" << sigma << "\")";
 write_lambdas(tokens);
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
}


void RZ_Dynamo_Generator::write_s1_expression(QList<MS_Token>& tokens)
{
 // // right order?
 MS_Token tfuxe = tokens.takeAt(0);
 MS_Token tsigma = tokens.takeAt(0);


 QString sigma = tsigma.raw_text;
 QString fuxe = tfuxe.raw_text.replace('-', '_');;

 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \"" << fuxe << "\")";
 (*qts_) << "\n(ka::kc :|kcg_add_sigma_carrier_via_symbol| kcg \"" << sigma << "\")";
 write_lambdas(tokens);
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
}

void RZ_Dynamo_Generator::hold_deferred(int hdcode, quint64 clo, quint64& eval_clo)
{
 (*qts_) << "\n(ka::kc :|kcm_hold_deferred| "
         << hdcode << " '(progn \n;; held ...\n";
 eval_clo = clo;
}

void RZ_Dynamo_Generator::finalize_hold_deferred()
{
 (*qts_) << "\n));; ... held \n\n";
}

void RZ_Dynamo_Generator::write_set_kto(const MS_Token& mst)
{
 switch(mst.kind)
 {
 case MS_Token_Kinds::Type_Symbol:
  // // this needs to distinguish qobj, qreg etc. ...
  (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object_by_name| \"" << mst.raw_text << "\"))";
  break;
 case MS_Token_Kinds::Kernel_Type_Symbol:
  (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object__" << mst.raw_text << "|))";
  break;
 default:
  break;
 }
}


int RZ_Dynamo_Generator::write_nested_lambdas(QList<MS_Token>& tokens, int start, int depth)
{
 qDebug() << "Obsolete...";
 return 0;
}


void RZ_Dynamo_Generator::write_lambdas(QList<MS_Token>& tokens)
{
 QString type_name;
 for(int i = 0; i < tokens.length(); ++i)
 {
  MS_Token mst = tokens.at(i);
  switch(mst.kind)
  {
  case MS_Token_Kinds::Type_Symbol:
   type_name = mst.raw_text;
   // // this needs to distinguish qobj, qreg etc. ...
   (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object_by_name| \"" << type_name << "\"))";
   break;
  case MS_Token_Kinds::Kernel_Type_Symbol:
   type_name = mst.raw_text;
   (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object__" << type_name << "|))";
   break;
  case MS_Token_Kinds::Literal:
   if(type_name.isEmpty())
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_literal| kcg \""
      << mst.raw_text << "\")";
   }
   else
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_typed_literal| kcg kto \""
      << mst.raw_text << "\")";
    type_name.clear();
   }
   break;
  case MS_Token_Kinds::String_Literal:
   if(type_name.isEmpty())
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_literal| kcg kto "
      << mst.raw_text << ")";
   }
   else
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_typed_literal| kcg kto "
      << mst.raw_text << ")";
    type_name.clear();
   }
   break;

    // // do we need both coords? ...
  case MS_Token_Kinds::Nested_Forward:
   (*qts_) << " \n(ka::kc :|kcg_lambda_carrier_from_result_channel| kcg "
     << mst.to_number_pair_split_string() << ")\n";

   check_nested_target(mst.second_number());
   break;

  case MS_Token_Kinds::Scoped_Symbol:
   // // do we always need vof?
   if(type_name.isEmpty())
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_scoped_symbol| kcg \""
      << mst.raw_text << "\")";
   }
   else
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_scoped_symbol_and_type_name| kcg kto \""
      << mst.raw_text << "\")";
    type_name.clear();
   }
   break;
  case MS_Token_Kinds::Raw_Symbol:
   if(type_name.isEmpty())
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_symbol| kcg \""
      << mst.raw_text << "\")";
   }
   else
   {
    (*qts_) <<
      "\n(ka::kc :|kcg_add_lambda_carrier_via_typed_symbol| kcg kto \""
      << mst.raw_text << "\")";
    type_name.clear();
   }
   break;
  }
 }

}


void RZ_Dynamo_Generator::write_statement_clear()
{
 (*qts_) << "\n(ka::kc :|kcg_clear_all| kcg)";
}

void RZ_Dynamo_Generator::write_cmd_eval()
{
 (*qts_) << "\n(setq cmd-pkg (ka::kc :|kcm_statement_to_command_package| kcs))";
 (*qts_) << "\n(ka::kc :|kcm_direct_eval| cmd-pkg)";
}

void RZ_Dynamo_Generator::write_promote_type_binding_expression(MS_Token& mst)
{
 // any need to check mst.kind?
 (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_expression| \"" << mst.raw_text << "\" kcx))";
}


void RZ_Dynamo_Generator::write_recurring_symbols()
{
 (*qts_) << "(let ("
         "\n (kcg)"
         "\n (kcf)"
         "\n (ksf)"
         "\n (kcs)"
         "\n (kto)"
         "\n (ckto)"
         "\n (kcb)"
         "\n (kcx)"
         "\n (oli)"
         "\n (kcm-code)"
         "\n (cmd-pkg)"
         "\n )"
         "\n(setq kcg (ka::kc :|new_KCM_Channel_Group|) )"
         "\n(setq kto (ka::kc :|kcm_type_object__u64|) )"
            ;
}

void RZ_Dynamo_Generator::enter_scope()
{
 ++scope_depth_;
 if(scope_depth_ > 0)
 {
  (*qts_) << "\n(ka::kc :|kcg_clear_all| kcg)"
         "\n(ka::kc :|kcm_push_kcm_code_floor|)";
 }
 else
 {
  // beginning of file
  write_recurring_symbols();
  (*qts_) << "\n(setq kcf (ka::kc :|kcm_create_and_enter_file| \"<dynamic>\"))\n";
 }
}


void RZ_Dynamo_Generator::parse_sd(QString sn, QStringList& kw_flags, QStringList& strings)
{
 if(kw_flags.contains("TYPE-DECL"))
 {
  (*qts_) << "\n(setq kto " << strings.first() << " )";
  (*qts_) << "\n(ka::kc :|kcm_add_type_binding| \"" << sn << "\" kto)";

 }
}

QString RZ_Dynamo_Generator::get_type_representation(QString sn, QStringList& kw_flags, QStringList& strings)
{
 QString result;
 if(strings.isEmpty())
 {
  if(sn.endsWith("*@"))
  {
   sn.chop(2);
   result = QString("(ka::kc :|kcm_type_object_by_qobject_type_name| \"%1\")").arg(sn);
  }
  else
  {
   result = sn;
   result.prepend("(ka::kc :|kcm_type_object__");
   result.append("|)");
  }
 }
 return result;
}

void RZ_Dynamo_Generator::parse_sx(QString sn, QStringList& kw_flags, QStringList& strings)
{
 if(kw_flags.contains("TYPE-DECL"))
 {
  (*qts_) << "\n\n;;function signature";
  // strip parens from begin and end ...
  QString preformed = strings.first().mid(1);
  preformed.chop(1);
  (*qts_) << "\n" << preformed;
  (*qts_) << "\n(setq oli (ka::kc :|kcm_add_overloadable_type_binding| \"" << sn << "\" kto))"
    "\n(setq kcs (ka::kc :|kcm_promote_overloadable_type_binding_to_statement| \"" << sn << "\" oli))";

  if(direct_eval_info_)
  {
   (*qts_) << "\n(setq cmd-pkg (ka::kc :|kcm_statement_to_command_package| kcs))";
   (*qts_) << "\n(ka::kc :|kcm_direct_eval| cmd-pkg)";
  }
  else if(scope_depth_ == 0)
  {
   (*qts_) << "\n(ka::kc :|kcm_add_statement_to_file| kcs kcf)";
  }
  else
  {
   (*qts_) << "\n(ka::kc :|kcm_add_statement_to_block| kcs kcb)";
  }
 }
}

void RZ_Dynamo_Generator::parse_si(QString sn, QString arg)
{
 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \"" << arg << "\")";
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
 (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_expression| \"" << sn << "\" kcx))";
}

void RZ_Dynamo_Generator::parse_sa_entry(QString assignment_kind, QString sn)
{
 if(sn.startsWith(','))
 {
  hold_si(sn.mid(1));
 }
 else
 {
  // //?
  hold_si(sn);
 }
}

void RZ_Dynamo_Generator::sa_leave()
{
 (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
 (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_type_binding_to_statement_with_expression| \"" << held_init_symbol_ << "\" kcx))";
 minimal_leave_statement();
 held_init_symbol_.clear();
}

void RZ_Dynamo_Generator::hold_si(QString sn)
{
 held_init_symbol_ = sn;
}


void RZ_Dynamo_Generator::write_fuxe_carrier(QString sn)
{
 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \""
     << sn.replace('-', '_') << "\")";
}

void RZ_Dynamo_Generator::write_s1_call(QStringList& qsl)
{
 (*qts_) << "\n(ka::kc :|kcg_add_sigma_carrier_via_symbol| kcg \""
     << qsl.at(0).mid(1) << "\")";

 QString fuxe = qsl.at(1);

 (*qts_) << "\n(ka::kc :|kcm_kcg_add_fuxe_carrier| kcg kto  \""
     << fuxe.replace('-', '_') << "\")";

 for(int i = 2; i < qsl.size(); ++i)
 {
  write_lambda_literal_carrier(qsl.at(i));
 }

 // //  i.e. a call with no return ...
 if(held_init_symbol_.isEmpty())
 {
  (*qts_) << "\n(setq kcx (ka::kc :|kcm_dissolve_to_nested_expression| kcg))";
  (*qts_) << "\n(setq kcs (ka::kc :|kcm_promote_expression_to_statement| kcx))";
 }
 // //  give result type based on held ...
 else
 {
  (*qts_) << "\n(ka::kc :|kcg_add_result_carrier_via_type_from_bind_symbol| kcg \""
       << held_init_symbol_ << "\")";
 }

}

void RZ_Dynamo_Generator::write_lambda_literal_carrier(QString sn)
{
 if(sn.startsWith("$\""))
 {
  (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object__str|))";

  (*qts_) << "\n(ka::kc :|kcg_add_lambda_carrier_via_typed_literal| kcg kto "
      << sn.mid(1) << ")";
 }
 else if(sn.startsWith(','))
 {
  (*qts_) << "\n(ka::kc :|kcg_add_lambda_carrier_via_bind_symbol| kcg \""
      << sn.mid(1) << "\")";
 }
 else
 {
  (*qts_) << "\n(setq kto (ka::kc :|kcm_type_object__u32|))";

  (*qts_) << "\n(ka::kc :|kcg_add_lambda_carrier_via_typed_literal| kcg kto \""
      << sn << "\")";
 }
}



void RZ_Dynamo_Generator::enter_fn_body()
{
 (*qts_) << "\n\n;; fn body"
   "\n(setq kcb (ka::kc :|kcm_create_and_enter_block|))"
   "\n(ka::kc :|kcm_join_statement_to_block| kcs kcb)";
}

void RZ_Dynamo_Generator::leave_fn_body()
{
 (*qts_) << "\n\n;leave fn body\n(ka::kc :|kcm_leave_block| kcb)";
}

void RZ_Dynamo_Generator::enter_statement()
{
 (*qts_) << "\n\n;statement_\n(ka::kc :|kcg_clear_all| kcg)";
}

void RZ_Dynamo_Generator::minimal_leave_statement()
{
 if(direct_eval_info_)
 {
  (*qts_) << "\n(setq cmd-pkg (ka::kc :|kcm_statement_to_command_package| kcs))";
  (*qts_) << "\n(ka::kc :|kcm_direct_eval| cmd-pkg)";
 }
 else if(scope_depth_ > 0)
 {
  (*qts_) << "\n(ka::kc :|kcm_add_statement_to_block| kcs kcb)";
 }
 else
 {
  (*qts_) << "\n(ka::kc :|kcm_add_statement_to_file| kcs kcf)";
 }
 (*qts_) << "\n;statement_\n(ka::kc :|kcg_clear_all| kcg)\n\n";
}

void RZ_Dynamo_Generator::leave_statement()
{
 (*qts_) << "\n;_statement";

 if(direct_eval_info_)
 {
  (*qts_) << "\n(setq cmd-pkg (ka::kc :|kcm_statement_to_command_package| kcs))";
  (*qts_) << "\n(ka::kc :|kcm_direct_eval| cmd-pkg)";
 }
 else if(scope_depth_ > 0)
 {
  (*qts_) << "\n(ka::kc :|kcm_add_statement_to_block| kcs kcb)";
 }
 else
 {
  (*qts_) << "\n(ka::kc :|kcm_add_statement_to_file| kcs kcf)";
 }
}

QString* RZ_Dynamo_Generator::get_current_acc()
{
 if(current_expression_acc_index_ > 0)
 {
  if(expression_accs_.contains({current_nesting_level_, current_expression_acc_index_}))
  {
   return &expression_accs_[{current_nesting_level_, current_expression_acc_index_}];
  }
 }
 return nullptr;
}

void RZ_Dynamo_Generator::check_subtract_triggers(QStringList& readies)
{
 QString key = QString(":|#hold<%1-%2>|").arg(current_nested_form_level_).arg(current_nested_form_index_);

 if(nested_acc_triggers_.contains(key))
 {
  QStringList carried_readies;
  QList<RZ_Dynamo_Nested_Acc*> naccs = nested_acc_triggers_.value(key);
  // //  will this list ever have more than one?
  for(RZ_Dynamo_Nested_Acc* nacc : naccs)
  {
   nacc->subtract_trigger(key);
   QString ready = nacc->check_finalize(carried_readies);
   if(!ready.isEmpty())
   {
    readies.push_back(ready);
   }
  }
  if(!carried_readies.isEmpty())
  {
   readies.append(carried_readies);
  }
 }
}


QString RZ_Dynamo_Generator::get_lisp_call_mode_insertion(QString raw_text)
{
 static QMap<QString, QString> static_map {{
  {":lc-n", ""},
  {":lc-f", "'"},
 }};

 return static_map.value(raw_text);
}


void RZ_Dynamo_Generator::prepare_expression(QList<MS_Token>& tokens)
{
 MS_Token lisp_call_mode_token = tokens.takeAt(0);

 QString lisp_call_mode_insertion = get_lisp_call_mode_insertion(lisp_call_mode_token.raw_text);

 QStringList nested_incompletes;
 QString* acc = get_current_acc();
 QString temp;
 if(!acc)
 {
  temp = QString("\n(ka::kc :|_kcm_hold_opaque_lisp_value| :|#hold<%1-%2>| ").arg(current_nested_form_level_).arg(current_nested_form_index_);
  acc = &temp;
 }
 lisp_call_mode_insertion.prepend("\n");
 lisp_call_mode_insertion.append("(");
 acc->append(lisp_call_mode_insertion);
 for(MS_Token& mst : tokens)
 {
  add_acc_token(*acc, mst, nested_incompletes);
 }
 acc->append(")\n");
 if(acc == &temp)
 {
  acc->append(") ;_hold \n");
 }

 QStringList readies;
 check_subtract_triggers(readies);

 if(nested_incompletes.isEmpty())
 {
  // //  temp may or may not be empty;
   //    the acc may also have caused
   //    a different qts to have text
  (*qts_) << temp;
  if(!readies.isEmpty())
  {
   (*qts_) << "\n ; readies:";
   for(QString qs : readies)
   {
    (*qts_) << " \n ; ready ... ";
    (*qts_) << qs;
   }
  }
 }
 else
 {
  // //  what if readies is not empty here too?

  RZ_Dynamo_Nested_Acc* nacc = new RZ_Dynamo_Nested_Acc(*acc);
  nacc->add_triggers(nested_incompletes, nested_acc_triggers_);

  if(!readies.isEmpty())
  {
   nacc->absorb_readies(readies);
  }

  // // ok? ...
//  if(!readies.isEmpty())
//  {
//   (*qts_) << "\n ; readies:";
//   for(QString qs : readies)
//   {
//    (*qts_) << " \n ; ready ... ";
//    (*qts_) << qs;
//   }
//  }

 }
}

void RZ_Dynamo_Generator::add_acc_token(QString& acc, const MS_Token& mst, QStringList& nested_incompletes)
{
 switch(mst.kind)
 {
 case MS_Token_Kinds::Type_Symbol:
 case MS_Token_Kinds::Kernel_Type_Symbol:
  break;

 case MS_Token_Kinds::Scoped_Symbol:
  acc.append(QString(" (ka::ivof \"%1\") ").arg(mst.raw_text));
  break;


 case MS_Token_Kinds::Nested_Forward:
  {
   QString ni = QString(":|#hold<%1>|").arg(mst.raw_text);
   nested_incompletes.push_back(ni);
   acc.append(QString(" (ka::unhold %1) ").arg(ni));
  }
  break;

 default:
  acc.append(QString(" %1 ").arg(mst.raw_text));
 }
}

void RZ_Dynamo_Generator::init_write_trigger(QString str, QPair<int, int> trigger)
{
 write_triggers_.push({str, trigger});
}

void RZ_Dynamo_Generator::write_plene_block()
{
 // actually gets the return from write_leave_plene_block ...

 // is this the right place for this?
 if(pending_fdef_name_.isEmpty())
 {
  (*qts_) << " ; ... plene\n";
 }
 else
 {
  QString fn = pending_fdef_name_;
  fn.replace('-', '_');
  // // extra close parens for the lambda and setq ...
  (*qts_) << " )) (ka::kc :|kcm_finalize_fdef| ksf \"" << pending_fdef_name_ << "\") ; ... plene\n";
 }

}

void RZ_Dynamo_Generator::write_plebod_symbol_declare_with_type(QList<MS_Token>& tokens)
{
 (*qts_) << "\n(ka::kc :|kcm_prepare_proxy_symbol| \""
         << tokens.first().raw_text << "\" \""
         << tokens.at(1).raw_text << "\")";
}

void RZ_Dynamo_Generator::write_plebod_symbol_init_with_type(QList<MS_Token>& tokens)
{
 (*qts_) << "\n(ka::kc :|kcm_init_proxy_symbol| \""
         << tokens.first().raw_text << "\" \""
         << tokens.at(1).raw_text << "\")";

}

int RZ_Dynamo_Generator::write_cond_expression_template_list(QString& templt, QList<MS_Token>& tokens)
{
 int result = 0;
 for(MS_Token& mst : tokens)
 {
  if(mst.kind == MS_Token_Kinds::Nested_Forward)
  {
   result = mst.second_number();
   if(result % 2)
   {
    if(result == tokens.size())
    {
     // i.e. we need to insert a "t" for fallback ...
     templt += QString(" (t :.%1) ").arg(result);
    }
    else
    {
     templt += QString(" (:.%1 ").arg(result);
    }
   }
   else
   {
    templt += QString(" :.%1) ").arg(result);
   }
  }
 }
 return result;

}

int RZ_Dynamo_Generator::write_expression_template_list(QString& templt, QList<MS_Token>& tokens)
{
 int result = 0;
 for(MS_Token& mst : tokens)
 {
  if(mst.kind == MS_Token_Kinds::Nested_Forward)
  {
   result = mst.second_number();
   templt += QString(" :.%1 ").arg(result);
  }
 }
 return result;
}

void RZ_Dynamo_Generator::if_without_elsif(QList<MS_Token>& tokens)
{
 pending_expression_state_ = Pending_Expression_State::If_Without_Elsif;

 QString templt = "(if ";

 int max = write_expression_template_list(templt, tokens);
 templt += "\n)\n";
 init_write_trigger(templt, {current_nesting_level_ + 1, max});
 //current_expression_acc_index_
}

void RZ_Dynamo_Generator::write_enter_plebod()
{
 (*qts_) << "\n(ka::kc :|kcm_enter_plebod|) ";
}

void RZ_Dynamo_Generator::write_enter_scope()
{
 (*qts_) << "\n(ka::kc :|kcm_enter_runtime_scope|) ";
}

void RZ_Dynamo_Generator::write_leave_scope()
{
 (*qts_) << "\n(ka::kc :|kcm_leave_runtime_scope|) ";
}


void RZ_Dynamo_Generator::if_with_else(QList<MS_Token>& tokens)
{
 pending_expression_state_ = Pending_Expression_State::If_Without_Elsif;

 QString templt = "(if ";

 int max = write_expression_template_list(templt, tokens);
 templt += "\n)\n";
 init_write_trigger(templt, {current_nesting_level_ + 1, max});
}

void RZ_Dynamo_Generator::if_with_elsif(QList<MS_Token>& tokens)
{
 pending_expression_state_ = Pending_Expression_State::If_Without_Elsif;

 QString templt = "(cond ";

 int max = write_cond_expression_template_list(templt, tokens);


 templt += "\n)\n";
 init_write_trigger(templt, {current_nesting_level_ + 1, max});
}

void RZ_Dynamo_Generator::elsif_with_elsif(QList<MS_Token>& tokens)
{

}

void RZ_Dynamo_Generator::enter_nested_form(QList<MS_Token>& tokens)
{
 int ts = tokens.size();
 QString note;
 int hdcode = 0;
 if(ts == 3)
 {
  MS_Token nmst = tokens.at(0);
  if(nmst.kind == MS_Token_Kinds::Note_Symbol)
  {
   note = nmst.raw_text;
  }
  MS_Token cmst = tokens.at(1);
  if(cmst.kind == MS_Token_Kinds::Literal)
  {
   hdcode = cmst.first_number();
  }
 }


 MS_Token mst = tokens.at(ts - 1);

 if(mst.kind == MS_Token_Kinds::Nested_Back)
 {
  QPair<int, int> pr = mst.to_number_pair();
  if(pending_anon_fdef_blocks_.contains(pr))
  {
   pending_fdef_name_ = QString("<anon>%1-%2").arg(pr.first).arg(pr.second);
   (*qts_) << "\n(ka::kc :|kcm_kcg_add_lambda_carrier_of_anon_fdef| kcg \""
           << pending_fdef_name_ << "\")";
  }
  else
  {
   int level = pr.first;
   int index = pr.second;
   // // is current_nesting_level_ always equal to level?
   QString fname = pending_fdef_blocks_.take({current_nesting_level_, index});
   if(fname.isEmpty())
   {
    // need a stack?
    current_nested_form_index_ = index;
    current_nested_form_level_ = level;
    if(note.isEmpty())
    {
     (*qts_) << "\n(ka::kc :|kcm_prepare_nested_expression| kcx "
       << level << ' ' << index << ')';
    }
    else
    {
     (*qts_) << "\n(ka::kc :|kcm_prepare_nested_" << note
                << "_expression| kcx "
       << hdcode << ' ' << level << ' ' << index << ')';
    }
   }
   else
   {
    // // can't I just write << index << ...?
    (*qts_) << "\n(ka::kc :|kcm_prepare_fdef_clo| kcs " <<
             index  // QString::number(index)
            << ")";
    pending_fdef_name_ = fname;
   }
  }
 }
}

void RZ_Dynamo_Generator::write_anon_fdef(QList<MS_Token>& tokens)
{
 QString prin1 = tokens.at(1).raw_text;
 (*qts_) << "\n\n; fn_sig_ ...\n";
 (*qts_) << prin1;

 (*qts_) << "\n\n; _fn_sig ...\n";

 if(tokens.size() > 1)
 {
  QPair<int, int> anon_coords = tokens.at(2).to_number_pair();

  (*qts_) << QString("\n(ka::kc :|kcm_prepare_anon_fdef_expression| kto \"<anon>%1-%2\")\n")
     .arg(anon_coords.first).arg(anon_coords.second);

  pending_anon_fdef_blocks_[anon_coords] = QString();
 }
}

void RZ_Dynamo_Generator::enter_secondary_nested_form(QList<MS_Token>& tokens)
{
 MS_Token mst = tokens.at(0);
 if(mst.kind == MS_Token_Kinds::Nested_Back)
 {

  current_expression_acc_index_ = mst.second_number();
  expression_accs_[{current_nesting_level_, current_expression_acc_index_}] = QString();

  check_push_qts();

  qts_ = new QTextStream(&expression_accs_[{current_nesting_level_, current_expression_acc_index_}]);
 }
}


void RZ_Dynamo_Generator::check_push_qts()
{
 if(qts_ != &overall_qts_)
 {
  qts_stack_.push(qts_);
 }
}

void RZ_Dynamo_Generator::write_enter_plene_block()
{
 // // here?
 ++current_nesting_level_;

 // // check if we have to complete an fdef
 if(pending_fdef_name_.isEmpty())
 {
  (*qts_) << "\n(progn ; plene_block_\n";
 }
 else
 {
  (*qts_) << "\n(setq ksf (lambda (|_@:bridge|) ; lambda plene_block_\n";
  write_recurring_symbols();

  // // currently the first keyword is not used by Eval needs it to be there ...

  (*qts_) << "\n(ka::kc :|_kcm_load_bridge| :|#bridge<"
    << current_nesting_level_ << ">| |_@:bridge|)";
 }
}

void RZ_Dynamo_Generator::write_leave_plene_block()
{
 // // here?
 --current_nesting_level_;

 (*qts_) << "\n) ; _plene_block\n";
}

void RZ_Dynamo_Generator::check_pop_qts()
{
 if(qts_stack_.isEmpty())
 {
  qts_ = &overall_qts_;
 }
 else
 {
  qts_ = qts_stack_.pop();
 }
}

void RZ_Dynamo_Generator::nested_form_body(QList<MS_Token>& tokens)
{

}

void RZ_Dynamo_Generator::leave_nested_form()
{
 if(current_nested_form_index_ == current_nested_target_)
 {
  // // finalize the form group ...
  (*qts_) << "\n(ka::kc :|kcm_finalize_nested_form_group| kcx)\n";

  // // always needed?
  (*qts_) << "\n(ka::kc :|kcg_clear_all| kcg)\n";
 }
}

void RZ_Dynamo_Generator::leave_secondary_nested_form()
{
 delete qts_;
 check_pop_qts();
}

void RZ_Dynamo_Generator::push_nested_form_group()
{

}

void RZ_Dynamo_Generator::write_qpr(QList<MS_Token>& tokens)
{
 MS_Token mst{MS_Token_Kinds::Fuxe_Symbol, "qpr"};
 tokens.prepend(mst);
 write_s0_expression(tokens);
}

void RZ_Dynamo_Generator::pull_nested_form_group()
{
 QPair<QString, QPair<int, int> > pr = write_triggers_.pop();
 QString templt = pr.first;
 int max = pr.second.second;
 for(int i = 1; i <= max; ++i)
 {
  QString repl = expression_accs_.take({current_nesting_level_, i});
  QString key = QString(":.%1").arg(i);
  templt.replace(key, repl);
 }
 (*qts_) << "\n ; pulling nested form group ... \n" << templt;
}


