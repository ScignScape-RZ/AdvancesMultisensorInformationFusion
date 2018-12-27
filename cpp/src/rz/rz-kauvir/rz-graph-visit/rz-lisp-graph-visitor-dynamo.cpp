
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-visitor.h"

#include "rz-lisp-graph-visitor-dynamo.h"

#include "rz-graph-run/token/rz-graph-run-token.h"
#include "rz-graph-token/token/rz-lisp-token.h"
#include "rz-graph-core/kernel/graph/rz-re-node.h"
#include "rz-function-def/rz-function-def-info.h"
#include "rz-graph-token/rz-lisp-graph-core-function.h"
#include "rz-graph-core/token/rz-re-token.h"
#include "rz-graph-embed/rz-graph-embed-token.h"

#include "rz-block-entry-run-plugin.h"
#include "rz-graph-core/code/rz-re-function-def-entry.h"
#include "rz-graph-valuer/scope/rz-lisp-graph-lexical-scope.h"
#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"
#include "rz-graph-run/rz-lisp-graph-runner.h"
#include "rz-graph-build/rz-lisp-graph-result-holder.h"
#include "rz-graph-build/types/run-type-codes.h"
#include "rz-graph-embed/rz-graph-run-embedder.h"
#include "rz-graph-embed-run/rz-graph-embed-run-valuer.h"
#include "rz-graph-embed/rz-graph-embed-check.h"
#include "rz-graph-core/code/rz-re-call-entry.h"
#include "rz-graph-core/code/rz-re-block-entry.h"
#include "rz-embed-branch-run-plugin.h"
#include "rz-graph-core/tuple/rz-re-tuple-info.h"
#include "rz-graph-sre/rz-sre-token.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-block-info.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "rzns.h"

USING_RZNS(GBuild)

USING_RZNS(GEmbed)

RZ_Lisp_Graph_Visitor_Dynamo::RZ_Lisp_Graph_Visitor_Dynamo(RZ_Lisp_Graph_Visitor& visitor)
 : visitor_(visitor), pending_block_info_(nullptr)
{

}

//? needed any more?
caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Visitor_Dynamo::block_info_from_block_entry_node(caon_ptr<RE_Node> ben)
{
 caon_ptr<RZ_Lisp_Graph_Block_Info> result = nullptr;
 if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
 {
  CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
  CAON_DEBUG_NOOP
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Visitor_Dynamo::check_pending_block_info(caon_ptr<RE_Node> node)
{
 return visitor_.get_block_info_from_function_node(node);
}


MS_Token RZ_Lisp_Graph_Visitor_Dynamo::lisp_token_from_token_text(QString text,
  QString& bridge_code)
{
 static QMap<QString, MS_Token> static_map {{
   {"<|", {MS_Token_Kinds::Skip_Token, ":TYPE-DECL"}},
   {":::", {MS_Token_Kinds::Skip_Token, ":TYPE-DECL"}},
   {"=>>", {MS_Token_Kinds::Skip_Token, ":TYPE-DECL"}},
   {"->", {MS_Token_Kinds::Instruction_Symbol, QString()}},
   {"\\->", {MS_Token_Kinds::Instruction_Symbol, QString()}},
   {"@->", {MS_Token_Kinds::Instruction_Symbol, QString()}},
  }};

 if(text == "$->")
 {
  return {MS_Token_Kinds::Skipped_Flag_Symbol, "FN-NO-BLOCK"};
 }
 if(text.startsWith("$-"))
 {
  bridge_code = "$-";
  return {MS_Token_Kinds::Bridge_Symbol, text.mid(2)};
 }
 else if(text.startsWith("#-"))
 {
  bridge_code = "#-";
  return {MS_Token_Kinds::Bridge_Symbol, text.mid(2)};
 }
 else if(text.startsWith("%-"))
 {
  bridge_code = "%";
  return {MS_Token_Kinds::Bridge_Symbol, text.mid(2)};
 }
 else
 {
  return static_map.value(text, {MS_Token_Kinds::N_A, text});
 }
}

RZ_Lisp_Graph_Visitor_Dynamo::Special_Form_Flags RZ_Lisp_Graph_Visitor_Dynamo::parse_special_form_flag(QString text)
{
 static QMap<QString, Special_Form_Flags> static_map {{
   {"my", Special_Form_Flags::Type_Declare},
   {"our", Special_Form_Flags::Type_Declare},
   {"let", Special_Form_Flags::Type_Declare},
   {".my", Special_Form_Flags::Type_Declare},
   {".our", Special_Form_Flags::Type_Declare},
   {".let", Special_Form_Flags::Type_Declare},
   {"\\=", Special_Form_Flags::Assignment},
   {"=", Special_Form_Flags::Assignment},
   {"<<|", Special_Form_Flags::Formula},

  }};

 return static_map.value(text, Special_Form_Flags::N_A);
}


QString RZ_Lisp_Graph_Visitor_Dynamo::function_name_from_token_text(QString text)
{
 static QMap<QString, QString> static_map {{
   {"my", "kb::write-qreg-type-binding-statement"},
   {"our", "kb::write-qreg-type-binding-statement"},
   {".my", "kb::write-qreg-type-binding-statement"},
   {".our", "kb::write-qreg-type-binding-statement"},
   {".let", "kb::write-qreg-type-binding-statement"},
   {"let", "kb::write-qreg-type-binding-statement"},
   {"\\=", "kb::si"},
   {"\\==", "kb::symbol-init-via-type"},
   {"/->", "kb::write-s1-expression"},
   {"do", "kb::write-anon-fdef"},
   {"elsif", ""},
   {"if", "kb::if-without-elsif"},
   {"KAUVIR_DECLARE_INTERACTIVE", "kb::sr"},

   //? {"qpr", "kb::write-qpr"},

   {"\\=>>", "kb::write-overloadable-fdef"},
   {"=?", "equal"},
   {"&if", "&if-t-e"},
   {"??", "ka::to_bool"},
   {"!!", "ka::to_bool_not"},
  }};

 return static_map.value(text, text);

}

QString RZ_Lisp_Graph_Visitor_Dynamo::wrap_token_with_bridge_code(QString token, QString bridge_code, QString es_argument)
{
 char c = bridge_code.at(0).toLatin1();
 switch(c)
 {
 case '$':
  return QString("(ka::svs %1 %2)").arg(es_argument).arg(token);
 default:
  return QString("(ka::sv %1 %2)").arg(es_argument).arg(token);
 }
}

//?
caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Visitor_Dynamo::clear_pending_block_info()
{
 caon_ptr<RZ_Lisp_Graph_Block_Info> result = pending_block_info_;
 pending_block_info_ = nullptr;
 return result;
}

void RZ_Lisp_Graph_Visitor_Dynamo::check_assignment_annotation(caon_ptr<RE_Node> statement_entry_node,
  caon_ptr<RZ_Code_Statement> st)
{
 if(caon_ptr<RE_Node> aa_node = visitor_.get_assignment_annotation_node_from_statement_entry_node(statement_entry_node))
 {
  if(caon_ptr<RE_Token> tok = aa_node->re_token())
    st->set_annotation(tok->raw_text());
 }
}

caon_ptr<RZ_Code_Statement> RZ_Lisp_Graph_Visitor_Dynamo::get_code_statement_from_statement_entry_node(
  caon_ptr<RE_Node> statement_entry_node)
{
 caon_ptr<RE_Node> st_node = visitor_.get_code_statement_node_from_statement_entry_node(statement_entry_node);
 if(st_node)
 {
  return st_node->rz_code_statement();
 }
 return nullptr;
}


caon_ptr<RZ_Expression_Review> RZ_Lisp_Graph_Visitor_Dynamo::get_expression_review_from_entry_node(
  caon_ptr<RE_Node> entry_node)
{
 caon_ptr<RE_Node> er_node = visitor_.get_expression_review_node_from_entry_node(entry_node);
 if(er_node)
 {
  return er_node->rz_expression_review();
 }
 return nullptr;
}



caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::get_next_node(caon_ptr<RE_Node> start_node,
  RZ_Lisp_Graph_Visitor::Next_Node_Premise& next_node_premise)
{
 CAON_PTR_DEBUG(RE_Node, start_node)

 // next_node_premise is read-write
 caon_ptr<RE_Node> result = nullptr;

 if(pending_block_info_)
 {
  next_node_premise = RZ_Lisp_Graph_Visitor::Next_Node_Premise::Block_Entry;
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,pending_block_info_)
  result = pending_block_info_->block_entry_node();
  return result;
 }

 switch(next_node_premise)
 {
 case RZ_Lisp_Graph_Visitor::Next_Node_Premise::Expression:
  next_node_premise = visitor_.get_cross_node(start_node, result);
  break;
 default:
  next_node_premise = visitor_.get_next_node(start_node, result);
  break;
 }
 return result;
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::get_next_statement_node(caon_ptr<RE_Node> sen)
{
 CAON_PTR_DEBUG(RE_Node ,sen)
 caon_ptr<RE_Node> result = visitor_.get_cross_sequence_node(sen);
 CAON_PTR_DEBUG(RE_Node ,result)
 return result;
}


caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::leave_nested_block(caon_ptr<RZ_Lisp_Graph_Block_Info> rbi, caon_ptr<RZ_Lisp_Graph_Block_Info>& nn_bi)
{
 if(rbi)
 {
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,rbi)
  caon_ptr<RE_Node> result = rbi->continue_node();
  CAON_PTR_DEBUG(RE_Node ,result)

  // for debug ...
  {
   if(caon_ptr<RE_Node> ben = rbi->block_entry_node())
   {
    if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
    {
     CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
     CAON_DEBUG_NOOP
    }
   }
  }

  if(result)
  {
   nn_bi = visitor_.get_block_info_from_function_node(result);
  }
  else
  {
   nn_bi = nullptr;
  }
  return result;
 }
 nn_bi = nullptr;
 return nullptr;
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::block_entry_node_from_function_def_entry_node(caon_ptr<RE_Node> start_node)
{
 CAON_PTR_DEBUG(RE_Node ,start_node)
 if(caon_ptr<RZ_Lisp_Token> rzlt = start_node->lisp_token())
 {
  if(rzlt->raw_text() == "\\=>>")
  {
   start_node = visitor_.get_call_sequence_node(start_node);
  }
 }
 return visitor_.nested_block_entry_from_prior_node(start_node);
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::call_entry_node_from_block_entry_node(caon_ptr<RE_Node> start_node)
{
 CAON_PTR_DEBUG(RE_Node ,start_node)
 return visitor_.call_entry_from_node(start_node);
}

caon_ptr<RZ_Function_Def_Info> RZ_Lisp_Graph_Visitor_Dynamo::get_function_def_info_from_entry(caon_ptr<RE_Function_Def_Entry> fde)
{
 caon_ptr<RE_Node> prior_node = fde->prior_node();
 CAON_PTR_DEBUG(RE_Node ,prior_node)

 if(caon_ptr<RZ_Lisp_Token> ptok = prior_node->lisp_token())
 {
  if(ptok->raw_text() == "\\=>>")
  {
   prior_node = visitor_.get_call_sequence_node(prior_node);
   if(!prior_node)
   {
    return nullptr;
   }
  }
 }

 if(caon_ptr<RE_Node> fdi_node = visitor_.get_call_sequence_node(prior_node))
 {
  CAON_PTR_DEBUG(RE_Node ,fdi_node)
  if(caon_ptr<RZ_Lisp_Token> tok = fdi_node->lisp_token())
  {
   return tok->pRestore<RZ_Function_Def_Info>();
   //return fdi_node->rz_function_def_info();
  }
 }
 return nullptr;
}


caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::start_node_from_call_entry_node(caon_ptr<RE_Node> entry_node)
{
 return visitor_.entry_from_call_entry(entry_node);
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor_Dynamo::find_statement_cross_sequence_node(caon_ptr<RE_Node> start_node)
{
 CAON_PTR_DEBUG(RE_Node ,start_node)
 caon_ptr<RE_Node> result = visitor_.get_cross_sequence_node(start_node);
 CAON_PTR_DEBUG(RE_Node ,result)
 return result;
}

