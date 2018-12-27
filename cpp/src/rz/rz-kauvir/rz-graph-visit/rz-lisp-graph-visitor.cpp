
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-visitor.h"


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

#include "rz-code-generators/rz-dynamo-output.h"

#include "rz-graph-core/kernel/graph/rz-re-connection.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "rz-code-elements/rz-expression-review.h"
#include "rzns.h"

USING_RZNS(GBuild)

USING_RZNS(GEmbed)

RZ_Lisp_Graph_Visitor::RZ_Lisp_Graph_Visitor(caon_ptr<RE_Graph> graph)
 : graph_(graph),
   rq_(RE_Query::instance()),
   fr_(RE_Frame::instance()), lisp_graph_runner_(nullptr),
   current_block_node_(nullptr),
   valuer_(new RZ_Lisp_Graph_Valuer(*this)),
   current_lexical_scope_(*valuer_->root_lexical_scope()),
   current_run_plugin_(nullptr),
   data_continue_node_(nullptr),
   current_lex_iterator_(nullptr),
   dynamo_output_(nullptr)
{
 init_core_functions();

 valuer_->rz_lisp_core_function_finder = [this](QString name)
 {
  return this->find_core_function(name);
 };

 run_valuer_ = new RZ_Graph_Embed_Run_Valuer(*valuer_);
}

void RZ_Lisp_Graph_Visitor::prepare_rz_path_handlers_output(QString handlers)
{
 if(!handlers.isEmpty())
 {
  handlers.replace(QRegularExpression("\\n"), "\n;");
  handlers.prepend(";;;; R/Z Handlers");
  handlers.append(";;;;\n");
  add_initial_output_text(handlers);
 }
}

void RZ_Lisp_Graph_Visitor::add_initial_output_text(QString text)
{

}


void RZ_Lisp_Graph_Visitor::insert_core_function(QString name,
 caon_ptr<RZ_Lisp_Graph_Core_Function> cf)
{
 core_function_map_.insert({name, cf});
}

void RZ_Lisp_Graph_Visitor::init_core_functions()
{
 #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, cpp_fname, arity, status) \
  insert_core_function(QString(#rz_name), \
   new RZ_Lisp_Graph_Core_Function(#rz_name, #cpp_fname, arity, \
    RZ_Lisp_Graph_Core_Function::status));
 #include "rz-lisp-graph-visitor.core-function-list.h"
 #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
}


void RZ_Lisp_Graph_Visitor::valuer_redirect(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<RZ_Lisp_Graph_Core_Function> cf, caon_ptr<tNode> start_node)
{
 valuer_->redirect_core_function(rh, cf->name(), *start_node);
}


void RZ_Lisp_Graph_Visitor::activate()
{
 run_state_.set_read_table_state(RZ_Read_Table_State::Pre_Root);
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::graph_root_node()
{
 if(graph_)
  return graph_->root_node();
 else
  return nullptr;
}


void RZ_Lisp_Graph_Visitor::deactivate()
{
 run_state_.set_read_table_state(RZ_Read_Table_State::Inactive);
 run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::N_A);
}

QString RZ_Lisp_Graph_Visitor::get_mapkey_string(caon_ptr<RE_Node> node)
{
 CAON_PTR_DEBUG(RE_Node ,node)
 if(caon_ptr<tNode> mapkey_node = rq_.Run_Map_Key_Value(node))
 {
  CAON_PTR_DEBUG(RE_Node ,mapkey_node)
  if(caon_ptr<RZ_Lisp_Token> token = mapkey_node->lisp_token())
  {
   return token->lisp_string_value();
  }
  else if(caon_ptr<RE_Token> re_token = mapkey_node->re_token())
  {
   return re_token->raw_text();
  }
 }
 return QString();
}

caon_ptr<RZ_Graph_Embed_Token> RZ_Lisp_Graph_Visitor::current_embed_rename_token(caon_ptr<tNode> node)
{
 if(node)
 {
  CAON_PTR_DEBUG(tNode ,node)
  if(caon_ptr<tNode> n = rq_.Run_Embed_Rename(node))
  {
   return n->embed_token();
  }
 }
 return nullptr;
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::nested_block_entry_from_prior_node(caon_ptr<tNode> node)
{
 // // explain this...
 caon_ptr<tNode> en = rq_.Run_Call_Sequence(node);
 CAON_PTR_DEBUG(tNode ,en)
 return rq_.Run_Block_Entry(en);
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::nested_block_entry_from_node(caon_ptr<tNode> node)
{
 return rq_.Run_Block_Entry(node);
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::call_entry_from_node(caon_ptr<tNode> node)
{
 return rq_.Run_Call_Entry(node);
}



caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::entry_from_call_entry(caon_ptr<tNode> node)
{
 if(node)
 {
  CAON_PTR_DEBUG(tNode ,node)
  node->debug_connections();
  return rq_.Run_Call_Entry(node);
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::data_entry_from_call_entry(caon_ptr<tNode> node)
{
 if(node)
 {
  CAON_PTR_DEBUG(tNode ,node)
  node->debug_connections();
  return rq_.Run_Data_Entry(node);
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::find_block_entry_node(caon_ptr<tNode> node, caon_ptr<RZ_Lisp_Graph_Block_Info>& rbi)
{
 if(node)
 {
  node->debug_connections();
  if(caon_ptr<RE_Node> binode = rq_.Block_Info(node))
  {
   rbi = binode->block_info();
  }
  return rq_.Run_Block_Entry(node);
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::embed_redirect_node(caon_ptr<tNode> node)
{
 if(node)
 {
  return rq_.Run_Embed_Redirect(node);
 }
 return nullptr;
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
  RZ_Lisp_Graph_Visitor::find_run_call_entry(caon_ptr<tNode> node)
{
 caon_ptr<tNode> result = nullptr;
 if(node)
 {
  result = rq_.Run_Call_Entry(node);
 }
 return result;
}



caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::find_run_block_entry(caon_ptr<tNode> node, caon_ptr<tNode>* call_entry_node)
{
 caon_ptr<tNode> result = nullptr;
 if(node)
 {
  result = rq_.Run_Block_Entry(node);
 }
 if(call_entry_node)
 {
  if(result)
  {
   *call_entry_node = rq_.Run_Call_Entry(result);
  }
  else
   *call_entry_node = nullptr;
 }
 return result;
}


bool RZ_Lisp_Graph_Visitor::check_embed_noop(caon_ptr<tNode> n)
{
 return valuer_->check_embed_noop(n);
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::find_call_entry(const tNode& node, caon_ptr<RE_Call_Entry>& rce)
{
#ifdef NO_CAON
 caon_ptr<RE_Node> pnode = const_cast<caon_ptr<RE_Node> >( &node );
#else
 caon_ptr<RE_Node> pnode = &node;
#endif
 if(rce = node.re_call_entry())
 {
  return rq_.Run_Call_Entry(pnode);
 }
 else if(caon_ptr<tNode> next_node = rq_.Run_Call_Entry(pnode))
 {
  return find_call_entry(*next_node, rce);
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::find_data_entry(const tNode& node, caon_ptr<RE_Call_Entry>& rce)
{
 CAON_PTR_DEBUG(RE_Call_Entry ,rce)

  #ifdef NO_CAON
   caon_ptr<RE_Node> pnode = const_cast<caon_ptr<RE_Node> >( &node );
  #else
   caon_ptr<RE_Node> pnode = &node;
  #endif

 if(rce = node.re_call_entry())
 {
  caon_ptr<tNode> ref = rce->ref_node();
  caon_ptr<tNode> par = rce->parent_entry_node();
  caon_ptr<tNode> sn = rce->self_node();

  CAON_PTR_DEBUG(tNode ,ref)
  CAON_PTR_DEBUG(tNode ,par)
  CAON_PTR_DEBUG(tNode ,sn)

  return rq_.Run_Data_Entry(pnode);
 }
 else if(caon_ptr<tNode> next_node = rq_.Run_Call_Entry(pnode))
 {
  return find_data_entry(*next_node, rce);
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::find_next_token(caon_ptr<tNode> start_node,
 RZ_SRE_Result_State& result_state, bool expression_flag, bool non_sequence)
{
 caon_ptr<tNode> result = nullptr;
 CAON_PTR_DEBUG(tNode ,start_node)
 start_node->debug_connections();
 if(!non_sequence)
 {
  if(result = rq_.Run_Call_Sequence(start_node))
  {
   result_state.read_table_state = RZ_Read_Table_State::Expression_Sequence;
   result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Token_Loaded;
   result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Call_Sequence;
   return result;
  }
  else if(result = rq_.Run_Call_Entry(start_node))
  {
   if(caon_ptr<RE_Call_Entry> rce = result->re_call_entry())
   {
    CAON_PTR_DEBUG(RE_Call_Entry ,rce)
    result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Node_Loaded;
    result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Call_Entry;
    if(rce->flags.is_statement_entry)
     result_state.read_table_state = RZ_Read_Table_State::Statement_Pre_Entry;
    else
     result_state.read_table_state = RZ_Read_Table_State::Expression_Pre_Entry;
   }
   return result;
  }
  else if(result = rq_.Run_Data_Entry(start_node))
  {
   result_state.read_table_state = RZ_Read_Table_State::Expression_Sequence;
   result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Token_Loaded;
   result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Call_Sequence;
   return result;
  }

  else if(result = rq_.Run_Data_Leave(start_node))
  {
   CAON_PTR_DEBUG(RE_Node ,result)
   if(caon_ptr<RE_Tuple_Info> rti = result->re_tuple_info())
   {
    CAON_PTR_DEBUG(RE_Tuple_Info ,rti)
    CAON_DEBUG_NOOP
   }
   return result;
  }
 }

 if(result = rq_.Run_Block_Entry(start_node))
 {
  if(caon_ptr<RE_Block_Entry> rbe = result->re_block_entry())
  {
   CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
   result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Node_Loaded;
    // //? should this be Cross_Block on non_sequence?
   result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Block_Entry;
   result_state.read_table_state = RZ_Read_Table_State::Block_Pre_Entry;
  }
  return result;
 }
 if(result = rq_.Run_Cross_Sequence(start_node))
 {
  if(caon_ptr<RE_Call_Entry> rce = result->re_call_entry())
  {
   // //  This means cross-entry
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)
   result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Node_Loaded;
   result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Cross_Entry;
   if(rce->flags.is_statement_entry)
    result_state.read_table_state = RZ_Read_Table_State::Statement_Pre_Entry;
   else
    result_state.read_table_state = RZ_Read_Table_State::Expression_Pre_Entry;
  }
  else
  {
   // //  This means cross-continue
   result_state.advance_token_state = RZ_Read_Table_Advance_Token_State::Token_Loaded;
   result_state.advance_graph_state = RZ_Read_Table_Advance_Graph_State::Cross_Continue;
   result_state.read_table_state = RZ_Read_Table_State::Cross_Pre_Continue;
  }
 }
 else
 {
  start_node->debug_connections();
 }
 return result;
}


caon_ptr<tNode> RZ_Lisp_Graph_Visitor::find_data_leave(tNode& n)
{
 if(caon_ptr<tNode> dl_node = rq_.Run_Data_Leave(&n) )
 {
  CAON_PTR_DEBUG(tNode ,dl_node)
  CAON_DEBUG_NOOP
  if(caon_ptr<RE_Tuple_Info> rti = dl_node->re_tuple_info())
  {
   CAON_PTR_DEBUG(RE_Tuple_Info ,rti)
   if(caon_ptr<tNode> ce_node = rti->call_entry_node())
   {
    CAON_PTR_DEBUG(tNode ,ce_node)
    if(caon_ptr<RE_Tuple_Info> ce_rti = ce_node->re_tuple_info())
    {
     if(caon_ptr<tNode> entry_node = ce_rti->call_entry_node())
     {
      CAON_PTR_DEBUG(tNode ,entry_node)
      return entry_node;
     }
    }
   }
  }
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
  RZ_Lisp_Graph_Visitor::find_do_map_block_continue_node(caon_ptr<tNode> node, caon_ptr<tNode>& call_entry_node_or_parent_node,
  QString& explanation)
{
 CAON_PTR_DEBUG(tNode ,node)
 if(!node)
   return nullptr;
 node->debug_connections();

 caon_ptr<tNode> result = rq_.Run_Nested_Do_Map_Block_Entry_Rewind(node);

 caon_ptr<RE_Call_Entry> rce = node->re_call_entry();
 CAON_PTR_DEBUG(RE_Call_Entry ,rce)


 if(result)
 {
  CAON_PTR_DEBUG(tNode ,result)
  caon_ptr<tNode> block_entry_node = rq_.Run_Block_Entry(result);
  CAON_PTR_DEBUG(tNode ,block_entry_node)
  if(caon_ptr<tNode> cen = rq_.Run_Call_Entry(result))
  {
   explanation = "Run_Call_Entry";
   call_entry_node_or_parent_node = cen;
  }
 }
 else if(rce)
 {
  if(caon_ptr<tNode> ben = rce->block_entry_node())
  {
   CAON_PTR_DEBUG(tNode ,ben)
   if(caon_ptr<tNode> parent_node = rq_.Parent_Do_Map_Block(ben))
   {
    // // in this case set call_entry_node_or_parent_node
    call_entry_node_or_parent_node = parent_node;
    explanation = "Parent_Do_Map_Block";
   }
   else if(parent_node = rq_.Parent_Block_Map(ben))
   {
    caon_ptr<tNode> cross_node = nullptr;
    CAON_PTR_DEBUG(tNode ,parent_node)
    if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
    {
     CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
     CAON_DEBUG_NOOP
     if(caon_ptr<tNode> sen = rbe->statement_entry_node())
     {
      CAON_PTR_DEBUG(tNode ,sen)
      CAON_DEBUG_NOOP
      cross_node = rq_.Run_Cross_Sequence(sen);
     }
    }


    if(caon_ptr<RE_Block_Entry> parent_rbe = parent_node->re_block_entry())
    {
     CAON_PTR_DEBUG(RE_Block_Entry ,parent_rbe)
     // //  Definitely rbe->flags.function_definition does not
      //    need to go through the rewind rigamarole.
      //    Definitely rbe->flags.if_block does.
      //    Any other block variants needing this?
     if(parent_rbe->flags.if_block)
     {
      if(cross_node)
      {
       explanation = "Parent_Block_Map__With_Cross";
      }
      else
      {
       explanation = "Parent_Block_Map";
      }
      call_entry_node_or_parent_node = parent_node;
     }
    }
   }
  }
 }
 return result;
}



caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
  RZ_Lisp_Graph_Visitor::find_block_continue_node(caon_ptr<tNode> node, caon_ptr<tNode>& block_entry_node)
{
 CAON_PTR_DEBUG(tNode ,node)
 if(!node)
   return nullptr;
 node->debug_connections();
 caon_ptr<tNode> result = rq_.Run_Nested_Block_Continue(node);
 if(result)
 {
  block_entry_node = rq_.Run_Block_Entry(result);
 }
 return result;
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode> RZ_Lisp_Graph_Visitor::find_block_continue(caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 if(!node)
   return nullptr;
 if(caon_ptr<RE_Call_Entry> rce = node->re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  caon_ptr<tNode> ref = rce->ref_node();
  caon_ptr<tNode> par = rce->parent_entry_node();
  caon_ptr<tNode> bl_node = rce->block_entry_node();

  CAON_PTR_DEBUG(tNode ,ref)
  CAON_PTR_DEBUG(tNode ,par)

  if(bl_node)
  {
   CAON_PTR_DEBUG(tNode ,bl_node)
   if(caon_ptr<RE_Block_Entry> rbe = bl_node->re_block_entry())
   {
    CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
    if(caon_ptr<tNode> sen = rbe->statement_entry_node())
    {
     CAON_PTR_DEBUG(tNode ,sen)
     if(caon_ptr<tNode> result = rq_.Run_Cross_Sequence(sen))
     {
      CAON_PTR_DEBUG(tNode ,result)
      return result;
     }
    }
   }
  }
  else if(par)
  {
   if(par != ref)
   {
    if(caon_ptr<RE_Node> next_node = rq_.Run_Cross_Sequence(par))
    {
     CAON_PTR_DEBUG(RE_Node ,next_node)
     return next_node;
    }
   }
  }
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Visitor::current_block_info(caon_ptr<tNode> node)
{
 if(node)
 {
  CAON_PTR_DEBUG(RE_Node ,node)
  node->debug_connections();
  if(caon_ptr<tNode> n = rq_.Block_Info(node))
  {
   return n->block_info();
  }
 }
 return nullptr;
}

caon_ptr<tNode> find_block_continue();


QString RZ_Lisp_Graph_Visitor::identify_function(QString name,
 caon_ptr<RZ_Lisp_Graph_Core_Function>& cf)
{
 cf = find_core_function(name);
 if(cf)
 {
  return cf->name();
 }
 // //  If a symbol has only these characters assume it's a function
  //  Escape the dash?
 QRegularExpression rx("[^*<>&+#$@/%=?\\-^]");
 QRegularExpressionMatch rxm = rx.match(name);
 if(rxm.hasMatch())
  return QString();
 else
  return name;
}

RZ_Lisp_Graph_Visitor::Next_Node_Premise RZ_Lisp_Graph_Visitor::get_next_node(caon_ptr<RE_Node> start_node, caon_ptr<RE_Node>& result)
{

 if(result = rq_.Run_Call_Sequence(start_node))
 {
  return Next_Node_Premise::Normal;
 }
 if(result = rq_.Run_Call_Entry(start_node))
 {
  return Next_Node_Premise::Expression;
 }
 if(result = rq_.Run_Function_Def_Entry(start_node))
 {
  return Next_Node_Premise::Function_Def_Entry;
 }
 if(result = rq_.Run_Block_Entry(start_node))
 {
  return Next_Node_Premise::Token_To_Block_Entry;
 }
 return Next_Node_Premise::N_A;
}

caon_ptr<tNode> RZ_Lisp_Graph_Visitor::get_call_sequence_node(caon_ptr<tNode> node)
{
 return rq_.Run_Call_Sequence(node);
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor::get_expression_review_node_from_entry_node(caon_ptr<RE_Node> entry_node)
{
 CAON_PTR_DEBUG(RE_Node ,entry_node)
 return rq_.Element_Review(entry_node);
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor::get_assignment_annotation_node_from_statement_entry_node(
  caon_ptr<RE_Node> statement_entry_node)
{
 CAON_PTR_DEBUG(RE_Node ,statement_entry_node)
 return rq_.Assignment_Annotation(statement_entry_node);
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor::get_code_statement_node_from_statement_entry_node(
  caon_ptr<RE_Node> statement_entry_node)
{
 CAON_PTR_DEBUG(RE_Node ,statement_entry_node)
 return rq_.Element_Association(statement_entry_node);
}

RZ_Lisp_Graph_Visitor::Next_Node_Premise RZ_Lisp_Graph_Visitor::get_cross_node(caon_ptr<RE_Node> start_node, caon_ptr<RE_Node>& result)
{
 if(result = rq_.Run_Cross_Sequence(start_node))
 {
  CAON_PTR_DEBUG(RE_Node ,result)
  if(caon_ptr<RE_Call_Entry> rce = result->re_call_entry())
  {
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)
   return Next_Node_Premise::Expression;
  }
  else if(caon_ptr<RZ_Lisp_Token> tok = result->lisp_token())
  {
   CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
   return Next_Node_Premise::Normal;
  }
  else
  {
   return Next_Node_Premise::N_A;
  }
 }
 return Next_Node_Premise::N_A;
}



caon_ptr<tNode> RZ_Lisp_Graph_Visitor::check_raw_lisp(caon_ptr<tNode> node)
{
 if(caon_ptr<tNode> result = rq_.Raw_Lisp_Paste(node))
 {
  CAON_PTR_DEBUG(tNode ,result)
  return result;
 }
 return nullptr;
}


caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Visitor::get_block_info_from_function_node(caon_ptr<RE_Node> node)
{
 if(caon_ptr<RE_Node> bin = rq_.Block_Info(node))
 {
  return bin->block_info();
 }
 return nullptr;
}

caon_ptr<tNode> RZ_Lisp_Graph_Visitor::find_effective_call_entry(caon_ptr<tNode> sn)
{
 caon_ptr<tNode> result = rq_.Run_Call_Entry(sn);
 if(result)
 {
  CAON_PTR_DEBUG(tNode ,result)
  if(caon_ptr<RE_Call_Entry> rce = result->re_call_entry())
  {
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)
   return find_effective_call_entry(result);
  }
  return result;
 }
 return nullptr;
}

caon_ptr<tNode> RZ_Lisp_Graph_Visitor::hyper_normalize_run_call(caon_ptr<RE_Call_Entry> rce, tNode& start_node,
 const RE_Connectors& qtok)
{
 caon_ptr<RE_Call_Entry> srce = start_node.re_call_entry();
 CAON_PTR_DEBUG(RE_Call_Entry ,srce)
 CAON_PTR_DEBUG(RE_Call_Entry ,rce)
 if(srce)
 {
  if(caon_ptr<RE_Node> n = find_effective_call_entry(&start_node))
  {
   CAON_PTR_DEBUG(RE_Node ,n)
   caon_ptr<RZ_Expression_Review> rer = new RZ_Expression_Review;
   caon_ptr<RE_Node> rern = new RE_Node(rer);
   rer->set_node(rern);
   rern->add_hyponode(n);
   rer->add_text(QString("E1:")+n->label());
   &start_node << fr_/rq_.Element_Review >> rern;

  }

 }

}





caon_ptr<tNode> RZ_Lisp_Graph_Visitor::normalize_run_call(int depth, int pos, tNode& pre_entry_node,
  tNode& start_node, const RE_Connectors& qtok,
  caon_ptr<RE_Call_Entry> current_call_entry,
  caon_ptr<RE_Call_Entry> carried_call_entry,
  caon_ptr<tNode>* node_to_change)
{
 bool cross_flag = (qtok == rq_.Run_Cross_Sequence);

 caon_ptr<RE_Call_Entry> srce = start_node.re_call_entry();
 CAON_PTR_DEBUG(RE_Call_Entry ,srce)

 if(node_to_change)
 {
  caon_ptr<RE_Node> ntc = *node_to_change;
  CAON_PTR_DEBUG(RE_Node ,ntc)
  CAON_DEBUG_NOOP
 }


 caon_ptr<RE_Call_Entry> effective_rce = carried_call_entry;

 // //  This allows multiple Call_Entry guards to be strung together
 if(srce)
 {
    // //?
  if(caon_ptr<RE_Node> nn = rq_.Run_Nested_Do_Map_Block_Entry(&start_node))
  {
   normalize_nested_block(&start_node, nn, rq_.Run_Nested_Do_Map_Block_Entry);
  }

  if(srce->flags.no_normalize)
  {
   return nullptr;
  }

  caon_ptr<RE_Connection> cion; // this "skips" rces...

  caon_ptr<tNode> n1 = rq_.Run_Call_Entry_Direct[cion](&pre_entry_node);
  caon_ptr<tNode> n2 = rq_.Run_Call_Entry(&start_node);

  caon_ptr<tNode> n = nullptr;

  CAON_PTR_DEBUG(RE_Node ,n1)
  CAON_PTR_DEBUG(RE_Node ,n2)

  if(n1)
  {
   if(cross_flag)
   {

   }
   else
   {
    n = n1;
    if(n2)
    {
     if(cross_flag)
     {
      if(n2 != n1)
      {
       qDebug() << "Problem at: " << __LINE__;
      }
     }
    }
    else
    {
     qDebug() << "Problem at: " << __LINE__;
    }
    if(effective_rce)
    {
     qDebug() << "Check effective RCE: " << __LINE__;
    }
    else
    {
     effective_rce = srce;
    }
   }
  }

  if(!n)
  {
   // //  can we always do this?
   n = n2;
   if(effective_rce)
   {
    qDebug() << "Check effective RCE: " << __LINE__;
   }
   else
   {
    effective_rce = srce;
   }
  }

  if(n)
  {
   CAON_PTR_DEBUG(RE_Node ,n)
   n = normalize_run_call(depth, pos, start_node, *n, rq_.Run_Call_Entry, srce, effective_rce);

   check_cross_do(&start_node);

   if(n)
    return n;
   else
    return &start_node;
  }
  else if(n = rq_.Run_Data_Entry(&start_node))
  {
   // //  return &start_node because the holds the
    //     effective "rce" object
   normalize_nested_data(start_node, *n, rq_.Run_Data_Entry);
   return &start_node;
  }
  if(!cross_flag)
  {
   return nullptr;
  }
 }
 caon_ptr<tNode> function_node = &start_node;
 if(caon_ptr<RZ_Lisp_Token> tok = start_node.lisp_token())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
  CAON_PTR_DEBUG(RE_Call_Entry ,current_call_entry)
  caon_ptr<RZ_Lisp_Graph_Core_Function> cf;

  QString function_name;

  if(!tok->flags.not_entry)
   function_name = identify_function(tok->literal_string_value(), cf);

  if(tok->flags.is_string_literal)
  {
   // //  Any significance to a string literal which matches
    //     a function name?
   function_node = check_normalize_infix_run_call(current_call_entry, carried_call_entry, depth, pre_entry_node, start_node, qtok);
   if(function_node && node_to_change)
    *node_to_change = function_node;
  }

  else if(function_name.isEmpty())
  {
   function_node = check_normalize_infix_run_call(current_call_entry, carried_call_entry, depth, pre_entry_node, start_node, qtok);
   if(function_node && node_to_change)
    *node_to_change = function_node;
   if(function_node)
   {
    CAON_PTR_DEBUG(tNode ,function_node)
    if(caon_ptr<RE_Token> re_t = function_node->re_token())
    {
     CAON_PTR_DEBUG(RE_Token ,re_t)
     CAON_DEBUG_NOOP
    }
    if(current_call_entry)
    {
     current_call_entry->flags.is_function_expression_entry = true;
     // //    This is for debug only ...
     current_call_entry->set_debug_text_hint(tok->string_value());
    }
   }
  }

  else if(cf)
  {
   CAON_PTR_DEBUG(tNode ,function_node)
   if(caon_ptr<RE_Token> re_t = function_node->re_token())
   {
    CAON_PTR_DEBUG(RE_Token ,re_t)
    CAON_DEBUG_NOOP
   }

   if(tok->flags.is_call_arrow)
   {
    tok->flags.is_nested_opaque_call = true;
   }
   else
   {
    if(current_call_entry)
    {
     current_call_entry->flags.is_function_expression_entry = true;
     // //    This is for debug only ...
     current_call_entry->set_debug_text_hint(function_name);
    }
    tok->flags.is_function_expression_entry = true;
    tok->flags.is_core_function_symbol = true;
    tok->set_value(cf);
    tok->set_type_object(*valuer_->type_variety().get_type_object(RZ_Run_Types::GraphCoreFun));
   }
  }
  else
  {
   tok->flags.is_function_expression_entry = true;
   tok->flags.is_likely_function_symbol = true;
  }
 }
 CAON_PTR_DEBUG(RE_Node ,function_node)

 // //  this is not only for 'nested' except vis-a-vis RCE chains...
  //     well not sure?
 normalize_nested_run_call(srce, depth, *function_node);
 return nullptr;
}



void RZ_Lisp_Graph_Visitor::pre_interpret(caon_ptr<tNode> start_node)
{
 normalize(*start_node);
 hyper_normalize(*start_node);
 anticipate(*start_node);
}

void RZ_Lisp_Graph_Visitor::hyper_normalize()
{
 if(graph_)
 {
  hyper_normalize(*graph_->root_node());
 }
}

void RZ_Lisp_Graph_Visitor::normalize()
{
 if(graph_)
 {
  normalize(*graph_->root_node());
 }
}

void RZ_Lisp_Graph_Visitor::anticipate(std::function<void(RZ_Dynamo_Output&)> fn)
{
 if(graph_)
 {
  if(dynamo_output_)
  {
   // //  circular?
   //dynamo_output_->init_top_level_block();
   fn(*dynamo_output_);
  }

  anticipate(*graph_->root_node());
 }
}


void RZ_Lisp_Graph_Visitor::hyper_normalize(tNode& start_node)
{
 if(caon_ptr<tNode> n = rq_.Run_Call_Entry(&start_node))
 {
  CAON_PTR_DEBUG(tNode ,n)
  hyper_normalize_run_call(nullptr, *n, rq_.Run_Call_Entry);
 }
 else if(n = rq_.Run_Block_Entry(&start_node))
 {
  hyper_normalize_block(*n, rq_.Run_Block_Entry);
 }
}

void RZ_Lisp_Graph_Visitor::normalize(tNode& start_node)
{
 if(caon_ptr<tNode> n = rq_.Run_Call_Entry(&start_node))
 {
  normalize_run_call(0, 0, start_node, *n, rq_.Run_Call_Entry);
 }
 else if(n = rq_.Run_Block_Entry(&start_node))
 {
  normalize_block(start_node, *n, rq_.Run_Block_Entry);
 }
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::check_normalize_infix_run_call
 (caon_ptr<RE_Call_Entry> rce, caon_ptr<RE_Call_Entry> crce, int depth, tNode& pre_entry_node, tNode& start_node,
  const RE_Connectors& qtok)
{
 // //   Checks to see if the current expression uses
 //     infix syntax.
 caon_ptr<tNode> current_node;
 if(current_node = rq_.Run_Call_Sequence(&start_node))
 {
  // is there a duplicated check here because of swap?
  CAON_PTR_DEBUG(tNode ,current_node)
  return check_normalize_infix_run_call(rce, crce, depth, pre_entry_node,
   start_node, *current_node, qtok);
 }
 else
 {
  // //  If not, assume the start node is a function symbol
  if(  (crce && crce->flags.is_statement_entry) )
  {
   caon_ptr<RZ_Code_Statement> st = new RZ_Code_Statement(
     RZ_Code_Statement::Statement_Kinds::Expression, &start_node);
   caon_ptr<tNode> stn = new tNode(st);
   &start_node << fr_/rq_.Element_Association >> stn;
  }

  caon_ptr<RZ_Lisp_Token> tok = start_node.lisp_token();
  CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
  tok->flags.is_likely_function_symbol = true;
  tok->flags.is_function_expression_entry = true;
  return &start_node;
 }
}



caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::check_normalize_infix_run_call(caon_ptr<RE_Call_Entry> rce,
  caon_ptr<RE_Call_Entry> crce, int depth, tNode& pre_entry_node, tNode& start_node, tNode& current_node,
  const RE_Connectors& qtok)
{
 // //  Arguably this function could be called recursively rather than with a loop.
  //    In its current form the loop could potentially just be written in the
 //     two-argument form of normalize_infix_run_call.  However, it seems
 //     clearer to separate the two functions to clarify that current_node
 //     is assumed different from start_node here and also to leave open
 //     the possibility of recursion.

 caon_ptr<tNode> previous_node = &start_node;
 // //  This loop does not allow for a Run_Call_Entry preceding
 //     the function token.
 for(caon_ptr<tNode> n = &current_node; n; n = rq_.Run_Call_Sequence(n))
 {
  if(caon_ptr<RZ_Lisp_Token> tok = n->lisp_token())
  {
   if(tok->flags.is_call_arrow)
   {
    return &start_node;
   }

   caon_ptr<RZ_Lisp_Graph_Core_Function> cf;

//   if(tok->raw_text().startsWith(">-"))
//   {
//    tok->flags.is_function_expression_entry = true;
//    tok->flags.is_likely_function_symbol = true;
//    swap_function_nodes(pre_entry_node, start_node, *previous_node, *n, qtok);
//    return &current_node;
//   }

   QString function_name;

   if(!tok->flags.not_entry)
    function_name = identify_function(tok->literal_string_value(), cf);

   if(!function_name.isEmpty())
   {
    if(cf)
    {
     tok->flags.is_infix_operator_entry = true;
     // ok?
     tok->flags.is_function_expression_entry = true;

     tok->flags.is_core_function_symbol = true;
     tok->set_value(cf);
     tok->set_type_object(*valuer_->type_variety().get_type_object(RZ_Run_Types::GraphCoreFun));
    }
    else
    {
     tok->flags.is_infix_operator_entry = true;
     tok->flags.is_function_expression_entry = true;
     tok->flags.is_likely_function_symbol = true;
    }
    CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)

    swap_function_nodes(pre_entry_node, start_node, *previous_node, *n, qtok);
    return &current_node;
   }
   else
   {
    previous_node = n;
   }
  }
 }
 // //   If we're here, it means the start_node is (assumed to be)
  //      a function symbol after all

 // //  we can assume statement kind is expression ...

 //if(depth == 0)
 if(crce && crce->flags.is_statement_entry)
 {
  caon_ptr<RZ_Code_Statement> st = new RZ_Code_Statement(
    RZ_Code_Statement::Statement_Kinds::Expression, &start_node);
  caon_ptr<tNode> stn = new tNode(st);
  &start_node << fr_/rq_.Element_Association >> stn;
 }

 caon_ptr<RZ_Lisp_Token> stok = start_node.lisp_token();
 stok->flags.is_function_expression_entry = true;
 stok->flags.is_likely_function_symbol = true;
 return &start_node;
}

void RZ_Lisp_Graph_Visitor::hyper_normalize_block(tNode& start_node,
 const RE_Connectors& qtok)
{
 if(caon_ptr<RE_Block_Entry> rbe = start_node.re_block_entry())
 {
  if(caon_ptr<tNode> call_start_node = rq_.Run_Call_Entry(&start_node))
  {
   caon_ptr<tNode> node = hyper_normalize_run_call(nullptr,
    *call_start_node, qtok);
  }
 }
}

void RZ_Lisp_Graph_Visitor::normalize_block(tNode& pre_entry_node,
 tNode& start_node, const RE_Connectors& qtok, caon_ptr<tNode>* node_to_change)
{
 if(caon_ptr<RE_Block_Entry> rbe = start_node.re_block_entry())
 {
  if(caon_ptr<tNode> call_start_node = rq_.Run_Call_Entry(&start_node))
  {
   caon_ptr<tNode> node = normalize_run_call(0, 0, start_node,
    *call_start_node, qtok, nullptr, nullptr, node_to_change);

   if(node)
   {
    CAON_PTR_DEBUG(tNode ,node)
    while(caon_ptr<tNode> next_node = rq_.Run_Cross_Sequence(node))
    {
     CAON_PTR_DEBUG(tNode ,next_node)
     normalize_run_call(0, 0, *node, *next_node, rq_.Run_Cross_Sequence,
                        nullptr, nullptr, &next_node);
     node = next_node;
    }
   }
  }
 }
}

caon_ptr<RZ_Lisp_Graph_Core_Function> RZ_Lisp_Graph_Visitor::find_core_function(QString name)
{
 if(core_function_map_.find(name) != core_function_map_.end())
  return core_function_map_[name];
 return nullptr;
}

void RZ_Lisp_Graph_Visitor::swap_function_nodes(tNode& pre_entry_node,
 tNode&  head_node, tNode&  previous_node,
 tNode&  function_node, const RE_Connectors& qtok)
{
 pre_entry_node.swap_relation(qtok, &head_node, &function_node);

 if(caon_ptr<RE_Node> retval_node = rq_.Retval_Follow(&head_node) )
 {
  head_node.delete_relation(rq_.Retval_Follow, retval_node);
  if(retval_node == &function_node)
  {
   &function_node << fr_/rq_.Retval_Follow >> &head_node;
  }
  else
  {
   &function_node << fr_/rq_.Retval_Follow >> retval_node;
  }
 }

 previous_node.delete_relation(rq_.Run_Call_Sequence, &function_node);
 caon_ptr<tNode> next_node;
 if(next_node = rq_.Run_Call_Sequence(&function_node))
 {
  function_node.delete_relation(rq_.Run_Call_Sequence, next_node);
  &previous_node << fr_/rq_.Run_Call_Sequence >> next_node;
 }
 else if(next_node = rq_.Run_Call_Entry(&function_node))
 {
  function_node.delete_relation(rq_.Run_Call_Entry, next_node);
  &previous_node << fr_/rq_.Run_Call_Entry >> next_node;
 }

 if(caon_ptr<tNode> cross_node = rq_.Run_Cross_Sequence(&head_node))
 {
  head_node.delete_relation(rq_.Run_Cross_Sequence, cross_node);
  &function_node << fr_/rq_.Run_Cross_Sequence >> cross_node;
 }
 else if(cross_node = rq_.Run_Block_Entry(&head_node))
 {
  head_node.delete_relation(rq_.Run_Block_Entry, cross_node);
  &function_node << fr_/rq_.Run_Block_Entry >> cross_node;
 }

 &function_node << fr_/rq_.Run_Call_Sequence >> &head_node;

}

void RZ_Lisp_Graph_Visitor::normalize_nested_run_call(
  caon_ptr<RE_Call_Entry> carried_rce, int depth, tNode& function_node)
{
 CAON_PTR_DEBUG(RE_Call_Entry ,carried_rce)
 // //  Check normalize nested calls
 caon_ptr<tNode> previous_node = &function_node;
 int count = 0;
 while(previous_node)
 {
  CAON_PTR_DEBUG(tNode ,previous_node)
  caon_ptr<tNode> next_node;
  if(next_node = rq_.Run_Call_Sequence(previous_node))
  {
   ++count;
   previous_node = next_node;
  }
  else if(next_node = rq_.Run_Block_Entry(previous_node))
  {
   previous_node = normalize_nested_block(previous_node, next_node, rq_.Run_Block_Entry);
   ++count;
  }
  else if(next_node = rq_.Run_Call_Entry(previous_node))
  {
   CAON_PTR_DEBUG(RE_Node ,next_node)
   next_node->debug_connections();
   normalize_run_call(depth + 1, count, *previous_node, *next_node, rq_.Run_Call_Entry,
                      nullptr, carried_rce, &next_node);

   // // is this the right place for this?
   check_cross_do(next_node);


   // //  don't do the continuation on count == 0 because those are not nested ...
   if(count == 0)
   {
    previous_node = next_node;
   }
   else
   {
    previous_node = normalize_nested_run_call_continuation(depth, count, previous_node, next_node);
   }
   ++count;
  }
  else
   break;
 }
}

void RZ_Lisp_Graph_Visitor::check_cross_do(caon_ptr<RE_Node> n)
{
 if(caon_ptr<RE_Node> don = rq_.Run_Cross_Do(n))
 {
  CAON_PTR_DEBUG(RE_Node ,don)
  don->debug_connections();
  if(caon_ptr<RE_Node> arn = rq_.Run_Call_Sequence(don))
  {
   CAON_PTR_DEBUG(RE_Node ,arn)
   if(caon_ptr<RZ_Lisp_Token> rzlt = arn->lisp_token())
   {
    CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
    if(caon_ptr<RE_Node> fdef_node = rq_.Run_Function_Def_Entry(arn))
    {
     if(caon_ptr<RE_Function_Def_Entry> fdef = fdef_node->re_function_def_entry())
     {
      caon_ptr<RE_Node> pn = fdef->prior_node();
      CAON_PTR_DEBUG(RE_Node ,pn)
      CAON_PTR_DEBUG(RE_Function_Def_Entry ,fdef)
      caon_ptr<RZ_Function_Def_Info> new_fdi = valuer_->new_function_def_info(fdef);
      rzlt->set_value(new_fdi);

     }
    }
   }
  }
 }
}

caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::normalize_nested_run_call_continuation(int depth, int pos,
  caon_ptr<tNode> previous_node, caon_ptr<tNode> function_node)
{
 CAON_PTR_DEBUG(tNode ,previous_node)
 CAON_PTR_DEBUG(tNode ,function_node)

 caon_ptr<RE_Node> pnnode = rq_.Run_Cross_Sequence(previous_node);
 caon_ptr<RE_Node> fnnode = rq_.Run_Cross_Sequence(function_node);

 caon_ptr<tNode> fnext_node = nullptr;
 caon_ptr<tNode> next_node = nullptr;

 if(fnnode)
 {
  // //  only for do?
  if(caon_ptr<RE_Call_Entry> rce = function_node->re_call_entry() )
  {
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)
   if(rce->flags.is_do_lambda)
   {
    fnext_node = fnnode;
   }
  }
 }

 if(pnnode)
 {
  if(fnext_node)
  {
   qDebug() << "Warning: " << __LINE__;
  }
  next_node = pnnode;
 }

 if(fnext_node)
 {
  normalize_run_call(depth, pos + 1, *function_node, *fnext_node, rq_.Run_Cross_Sequence,
                     nullptr, nullptr, &fnext_node);

  //normalize_nested_run_call(function_node->re_call_entry(), depth, *fnext_node);
  CAON_PTR_DEBUG(RE_Node ,next_node)
  return nullptr; //normalize_nested_run_call_continuation(depth, pos, function_node, fnext_node);
 }

 else if(next_node)
 {
  CAON_PTR_DEBUG(RE_Node ,next_node)
  // //  Because of how Run_Cross_Sequence is used
   //     for both continuations in Lambda4 -- maybe separate them out?
  if(caon_ptr<RE_Call_Entry> rce = next_node->re_call_entry())
  {
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)

   normalize_run_call(depth, pos, *function_node, *next_node, rq_.Run_Cross_Sequence,
                      nullptr, nullptr, &next_node);
   CAON_PTR_DEBUG(RE_Node ,next_node)
   return normalize_nested_run_call_continuation(depth, pos, function_node, next_node);
  }
  else
  {
   return next_node;
  }
 }

 else if(next_node = rq_.Run_Block_Entry(function_node))
 {
  return normalize_nested_block(function_node, next_node, rq_.Run_Block_Entry);
 }
 else
  return nullptr;
}


QString RZ_Lisp_Graph_Visitor::call_entry_label(caon_ptr<RE_Call_Entry> rce)
{
 if(caon_ptr<RE_Node> n = rce->get_node())
  return call_entry_label(n);
 return QString();
}

QString RZ_Lisp_Graph_Visitor::call_entry_label(caon_ptr<RE_Node> n)
{
 QString result;
 CAON_PTR_DEBUG(RE_Node ,n)
 if(caon_ptr<RE_Node> ln = rq_.Run_Map_Key_Label(n))
 {
  if(caon_ptr<RE_Token> token = ln->re_token())
  {
   result = token->clasp_string_value();
  }
 }
 return result;
}

void
 RZ_Lisp_Graph_Visitor::normalize_nested_data(tNode& previous_node,
  tNode&  data_node, const RE_Connectors& qtok)
{
 // //  The task here is to walk through a data structure
 //     normalizing nested calls if there are any.

 if(caon_ptr<RE_Tuple_Info> tinfo = data_node.re_tuple_info())
 {
  CAON_PTR_DEBUG(RE_Tuple_Info ,tinfo)

  data_node.debug_connections();
  if(caon_ptr<tNode> start_node = rq_.Run_Data_Entry(&data_node))
  {
   CAON_PTR_DEBUG(RE_Node ,start_node)
   if(caon_ptr<RZ_Lisp_Token> tok = start_node->lisp_token())
   {
    QString str = tok->string_value();
    start_node->debug_connections();
   }
  }
 }
}


caon_ptr<RZ_Lisp_Graph_Visitor::tNode>
 RZ_Lisp_Graph_Visitor::normalize_nested_block(caon_ptr<tNode> previous_node,
  caon_ptr<tNode> function_node, const RE_Connectors& qtok)
{
 normalize_block(*previous_node, *function_node, qtok, &function_node);
 note_block_entry(function_node);

 CAON_PTR_DEBUG(tNode ,function_node)

 //  function_node->debug_connections();

 // alternative to Run_Cross_Block?
 if(caon_ptr<tNode> en_node = rq_.Run_Cross_Sequence(function_node))
 {
  CAON_PTR_DEBUG(tNode ,en_node)

  if(caon_ptr<RE_Call_Entry> rce = en_node->re_call_entry())
  {
   normalize_run_call(0, 0, *function_node, *en_node, rq_.Run_Cross_Sequence);
  }
 }

 return nullptr;
}

void RZ_Lisp_Graph_Visitor::check_function_symbol(caon_ptr<tNode> function_node)
{
 if(caon_ptr<RZ_Lisp_Token> tok = function_node->lisp_token())
 {
  caon_ptr<RZ_Lisp_Graph_Core_Function> cf;
  identify_function(tok->string_value(), cf);
  if(cf)
  {
   if(tok->flags.is_call_arrow)
   {
    tok->flags.is_nested_opaque_call = true;
   }
   else
   {
    tok->flags.is_core_function_symbol = true;
    tok->set_value(cf);
    set_token_type_object(tok, RZ_Run_Types::GraphCoreFun);
   }
  }
 }
}

void RZ_Lisp_Graph_Visitor::note_block_entry(caon_ptr<tNode> function_node)
{
 CAON_PTR_DEBUG(tNode ,function_node)
 caon_ptr<RZ_Lisp_Graph_Lexical_Scope> s = new RZ_Lisp_Graph_Lexical_Scope;
 caon_ptr<tNode> n = new tNode(s);
 function_node << fr_/rq_.Run_Lexical_Scope >> n;
}

void RZ_Lisp_Graph_Visitor::set_token_type_object(
  caon_ptr<RZ_Lisp_Token> token, RZ_Run_Types::Enum E)
{
 token->set_type_object(*valuer_->type_variety().get_type_object(E));
}

void RZ_Lisp_Graph_Visitor::anticipate(tNode& start_node)
{
 caon_ptr<tNode> n;
 if(n = rq_.Run_Call_Entry(&start_node))
 {
  anticipate_run_call(*n);
 }
 else if(n = rq_.Run_Block_Entry(&start_node))
 {
  anticipate_block(*n);
 }
}



void RZ_Lisp_Graph_Visitor::check_lisp_graph_runner()
{
 if(!lisp_graph_runner_)
 {
  if(valuer_)
  {
   if(!valuer_->embedder())
   {
    valuer_->set_embedder(new RZ_Graph_Run_Embedder(valuer_));
   }
   lisp_graph_runner_ = new RZ_Lisp_Graph_Runner(valuer_);
  }
 }
}

void RZ_Lisp_Graph_Visitor::check_redirect(RZ_Lisp_Graph_Result_Holder& rh, caon_ptr<tNode> n)
{
 if(valuer_->embedder())
 {
  valuer_->embedder()->check_redirect(rh, *n);
 }
}

caon_ptr<tNode> RZ_Lisp_Graph_Visitor::check_type_indicator(caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 return rq_.Type_Indicator(node);
}


void RZ_Lisp_Graph_Visitor::anticipate_block(tNode& start_node)
{
 if(caon_ptr<RE_Block_Entry> rbe = start_node.re_block_entry())
 {
  if(rbe->flags.file_default)
  {
   valuer_->enter_new_lexical_scope();
   CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
   rbe->set_lexical_scope(valuer_->current_lexical_scope());
  }
  caon_ptr<tNode> call_entry_node;
  if(call_entry_node = rq_.Run_Call_Entry(&start_node))
  {
   CAON_PTR_DEBUG(tNode ,call_entry_node)

   anticipate_run_call(*call_entry_node);

   while(call_entry_node = rq_.Run_Cross_Sequence(call_entry_node))
   {
    anticipate_run_call(*call_entry_node);
   }
  }
  if(call_entry_node = rq_.Run_Cross_Sequence(&start_node))
  {
   anticipate_run_call(*call_entry_node);
  }
 }
}

QString RZ_Lisp_Graph_Visitor::type_expression_from_node(caon_ptr<tNode> node)
{
 QString result;

 CAON_PTR_DEBUG(RE_Node ,node)
 node->debug_connections();
 if(caon_ptr<RE_Node> ce_node = rq_.Run_Call_Entry(node))
 {
  CAON_PTR_DEBUG(RE_Node ,ce_node)
  ce_node->debug_connections();
  node = rq_.Run_Cross_Sequence(ce_node);
  CAON_PTR_DEBUG(RE_Node ,node)
  while(node)
  {
   if(caon_ptr<RZ_Lisp_Token> token = node->lisp_token() )
   {
    result += token->raw_text() + " ";
   }
   node = rq_.Run_Call_Sequence(node);
  }
 }
 if(result.endsWith(' '))
  result.chop(1);
 return result;
}


void RZ_Lisp_Graph_Visitor::check_token_node_type(caon_ptr<RZ_Lisp_Token> tok,
 caon_ptr<tNode> token_node)
{
 CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
 if(tok)
 {
  if(tok->type_object())
   return;
  valuer_->check_node_type(token_node);

 }

}

caon_ptr<tNode> RZ_Lisp_Graph_Visitor::get_data_entry(caon_ptr<tNode> node)
{
 CAON_PTR_DEBUG(tNode ,node)
 caon_ptr<tNode> result = rq_.Run_Data_Entry(node);
 return result;
}


caon_ptr<tNode> RZ_Lisp_Graph_Visitor::anticipate_run_call(tNode& start_node)
{
 if(caon_ptr<RE_Call_Entry> rce = start_node.re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  if(caon_ptr<tNode> node = rq_.Run_Call_Entry(&start_node))
  {
   if(!rce->flags.no_anticipate)
   {
    anticipate_run_call(*node);
   }

   if(caon_ptr<tNode> block_entry_node = rq_.Run_Nested_Block_Entry(&start_node))
   {
    valuer_->enter_new_lexical_scope();
    if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
    {
     CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
     rbe->set_lexical_scope(valuer_->current_lexical_scope());
     {
      CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
      CAON_DEBUG_NOOP
     }
    }

    anticipate_block(*block_entry_node);
    valuer_->leave_lexical_scope();
   }

   return &start_node;

  }
  else
   return nullptr;
 }
 check_lisp_graph_runner();

 RZ_Lisp_Graph_Result_Holder rh(*valuer_);
 caon_ptr<tNode> function_node = &start_node;
 do
 {
  rh.clear_continue_proceed();
  if(rh.arity_node())
   function_node = rh.arity_node();
  if(caon_ptr<RZ_Lisp_Token> tok = function_node->lisp_token())
  {
   CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
   check_token_node_type(tok, function_node);

   caon_ptr<RZ_Type_Object> rto = tok->vh().type_object();
   CAON_PTR_DEBUG(RZ_Type_Object ,rto)

   RZ_Run_Types::Enum rtc = RZ_Run_Type_Code<RZ::GBuild::RZ_Lisp_Graph_Core_Function>::Value;

   caon_ptr<RZ_Type_Object> vto =  valuer_->type_variety().get_type_object(RZ_Run_Type_Code<RZ_Lisp_Graph_Core_Function>::Value);
   CAON_PTR_DEBUG(RZ_Type_Object ,vto)

   if(tok->type_object() ==
    valuer_->type_variety().get_type_object(RZ_Run_Type_Code<RZ_Lisp_Graph_Core_Function>::Value))
   {
    caon_ptr<RZ_Lisp_Graph_Core_Function> cf =
     tok->pRestore<RZ_Lisp_Graph_Core_Function>();
    CAON_PTR_DEBUG(RZ_Lisp_Graph_Core_Function ,cf)
   }


   caon_ptr<RZ_Lisp_Graph_Core_Function> cf =
     tok->pRestore<RZ_Lisp_Graph_Core_Function>(valuer_->type_variety());

   if(cf)
   {
    lisp_graph_runner_->check_run_info(rh, *cf, *function_node);
    check_redirect(rh, function_node);
    if(rh.flags.proceed_anticipate_nested_run_call)
    {
     anticipate_nested_run_calls(start_node, rh);
     rh.flags.proceed_anticipate_nested_run_call = false;
    }
    else if(cf->flags.defer)
      anticipate_nested_run_calls(start_node, rh);
   }
   else if(rh.flags.continue_proceed)
   {
    // // This means that a series of tokens
    //   is revealed to be a continuation function call.
    cf = normalize_continue_run_call(rh.pass_node(), tok, function_node);
    if(cf)
    {
     rh.flags.continue_proceed = false;
     lisp_graph_runner_->check_run_info(rh, *cf, *function_node);
    }
   }
   else
   {
    anticipate_nested_run_calls(start_node, rh);
    rh.flags.continue_proceed = false;
   }
  }
 }
 while(rh.flags.continue_proceed);
 return nullptr;
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Visitor::get_cross_sequence_node(caon_ptr<RE_Node> node)
{
 caon_ptr<tNode> result = rq_.Run_Cross_Sequence(node);
 return result;
}

void RZ_Lisp_Graph_Visitor::anticipate_nested_run_calls(tNode& start_node,
  RZ_Lisp_Graph_Result_Holder& rh)
{
 caon_ptr<tNode> n;
 if(n = rq_.Run_Call_Entry(&start_node))
 {
  CAON_PTR_DEBUG(tNode ,n)
  anticipate_run_call(*n);
 }
 if(n = rq_.Run_Call_Sequence(&start_node))
 {
  CAON_PTR_DEBUG(tNode ,n)
  anticipate_nested_run_calls(*n, rh);
 }
 if(n = rq_.Run_Cross_Sequence(&start_node))
 {
  anticipate_nested_run_calls(*n, rh);
 }

 if(n = rq_.Run_Block_Entry(&start_node))
 {
  anticipate_run_call(*n);
 }
 else if(n = rq_.Run_Cross_Block(&start_node))
 {
  anticipate_run_call(*n);
 }
}

caon_ptr<RZ_Lisp_Graph_Core_Function> RZ_Lisp_Graph_Visitor::normalize_continue_run_call
 (caon_ptr<tNode> pass_node, caon_ptr<RZ_Lisp_Token> tok, caon_ptr<tNode> function_node)
{
 caon_ptr<RZ_Lisp_Graph_Core_Function> cf;
 identify_function(tok->string_value(), cf);
 if(cf)
 {
  tok->flags.is_core_function_symbol = true;
  tok->set_value(cf);
 }
 return cf;
}

