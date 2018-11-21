
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-runner.h"

#include "rz-graph-token/rz-lisp-graph-core-function.h"

#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"


#include "rz-lisp-graph-runner.run-from-node.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"

#include "rz-graph-build/rz-lisp-graph-result-holder.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-core/token/rz-re-token.h"

#include "rz-graph-core/tuple/rz-re-tuple-info.h"

#include "rzns.h"

USING_RZNS(GRun)

RZ_Lisp_Graph_Runner::RZ_Lisp_Graph_Runner(caon_ptr<RZ_Lisp_Graph_Valuer>  valuer)
 : valuer_(valuer), rq_(RE_Query::instance())
{
}


void RZ_Lisp_Graph_Runner::check_run_info(RZ_Lisp_Graph_Result_Holder& rh,
 RZ_Lisp_Graph_Core_Function& cf, tNode& start_node)
{
 check_core_function_info(cf);
 if(cf.flags.valuer)
 {
  valuer_redirect(rh, cf, start_node);
  return;
 }

 switch(cf.arity())
 {

 case 0: run_from_node<0>(rh, cf, start_node); break;

 case 1: run_from_node<1>(rh, cf, start_node); break;

 case 2: run_from_node<2>(rh, cf, start_node); break;
 default: break;
 }
}



void RZ_Lisp_Graph_Runner::valuer_redirect(RZ_Lisp_Graph_Result_Holder& rh,
 RZ_Lisp_Graph_Core_Function& cf, tNode& start_node)
{
 rh.hold(&start_node);
 valuer_->redirect_core_function(rh, cf.name(), start_node);
 check_continue(rh);
 rh.unhold();
}



void RZ_Lisp_Graph_Runner::check_core_function_info(RZ_Lisp_Graph_Core_Function& cf)
{
 QString name = cf.name();
 QString rz_name = cf.rz_name();

 if(cf.flags.preempt)
 {
  RZ_Lisp_Graph_Function_Info& info = cf.info();
//?
  auto a = RZ_Lisp_Graph_Function_Code_Map;
  if(info.Core_Function_Family == RZ_Function_Family_Not_Set)
  {
   if(RZ_Lisp_Graph_Function_Code_Map.contains(name))
   {
    info = RZ_Lisp_Graph_Function_Code_Map[name];
   }
  }
 }

}

template<int Arity>
void RZ_Lisp_Graph_Runner::run_from_node(RZ_Lisp_Graph_Result_Holder& rh,
 RZ_Lisp_Graph_Core_Function& cf, tNode& start_node)
{

}

void RZ_Lisp_Graph_Runner::check_continue(RZ_Lisp_Graph_Result_Holder& rh)
{
 if(rh.flags.continue_statement)
 {
  caon_ptr<tNode> continue_node = run_token_as_first_argument(rh);
  if(continue_node)
  {
   CAON_PTR_DEBUG(tNode ,continue_node)
   rh.continue_proceed(continue_node);
  }
  else
   rh.clear_continue_statement();
 }
}


void RZ_Lisp_Graph_Runner::init_run_sequence_pair(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& start_node,
 caon_ptr<tNode>& lhs_node,
 caon_ptr<tNode>& rhs_node,

 caon_ptr<tNode>& left_new_node,
 caon_ptr<tNode>& right_new_node )
{
 // //   The new nodes representing collections, if created

 //      lhs_node might be passed in if the current call is continuing from a prior one
 lhs_node = rh.pull_pass_node();
 rhs_node;

 caon_ptr<RE_Connectors> lhs_premise = nullptr;
 caon_ptr<RE_Connectors> rhs_premise = nullptr;

 if(lhs_node)
 {
  CAON_PTR_DEBUG(tNode ,lhs_node)
  caon_ptr<RZ_Lisp_Token> lhst = lhs_node->lisp_token();
  CAON_PTR_DEBUG(RZ_Lisp_Token ,lhst)

  rhs_node = check_run_sequence(rh, rhs_premise, start_node);

  CAON_PTR_DEBUG(tNode ,rhs_node)

  // //  lhs_node may have already been evaluated and proxied
  valuer_->check_node_value_proxy(lhs_node);
 }
 else
 {
  lhs_node = check_run_sequence(rh, lhs_premise, start_node);
  left_new_node = valuer_->check_node_type_with_entry_premise(*lhs_premise, lhs_node);
  rhs_node = check_run_sequence(rh, rhs_premise, *lhs_node);
 }

 CAON_PTR_DEBUG(tNode ,left_new_node)
 CAON_PTR_DEBUG(tNode ,lhs_node)

 CAON_PTR_DEBUG(tNode ,rhs_node)

 valuer_->check_node_type(lhs_node);

 right_new_node = valuer_->check_node_type_with_entry_premise(
  *rhs_premise, rhs_node);


}


caon_ptr<RZ_Lisp_Graph_Runner::tNode>
  RZ_Lisp_Graph_Runner::check_run_sequence(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<RE_Connectors>& premise, tNode& lhs_node)
{
 lhs_node.debug_connections();

 // //  The task for this method is to deal with a nested
 //    function call if rhs_node is not already defined
 //    from a Run_Call_Sequence.

 caon_ptr<tNode> result = nullptr;

 if(result = rq_.Run_Call_Sequence(&lhs_node))
 {
 }
 else if(result = rq_.Run_Call_Entry(&lhs_node))
 {
  if(caon_ptr<RE_Call_Entry> rce = result->re_call_entry())
  {
   premise = &rq_.Run_Call_Entry;
   caon_ptr<tNode> entry_node;
   if(entry_node = rq_.Run_Call_Entry(result))
   {
    if(caon_ptr<RZ_Lisp_Token> tok = entry_node->lisp_token())
    {
     tok->flags.is_nested_opaque_call = !tok->flags.is_core_function_symbol;
     if(tok->flags.is_nested_opaque_call)
     {
      valuer_->init_opaque_call(*result, *entry_node);
     }
    }
    result = entry_node;
   }
   else if(entry_node = rq_.Run_Data_Entry(result))
   {
    premise = &rq_.Run_Data_Entry;
    if(caon_ptr<RE_Tuple_Info> rti = entry_node->re_tuple_info())
    {
     CAON_PTR_DEBUG(RE_Tuple_Info ,rti)
     QString lo = rti->lisp_out();
     int len = lo.length();
     rti->set_call_entry_node(result);
    }
    result = entry_node;
   }

  }

 }
 if(!premise)
 {
  premise = &rq_.N_A;
 }
 return result;

}
caon_ptr<tNode> RZ_Lisp_Graph_Runner::run_token_as_first_argument(
 RZ_Lisp_Graph_Result_Holder& rh)
{
 caon_ptr<tNode> arity_node = rh.arity_node();
 CAON_PTR_DEBUG(tNode ,arity_node)
 arity_node->debug_connections();

 caon_ptr<tNode> new_start_node = rq_.Run_Call_Sequence(arity_node);
 if(new_start_node)
  return new_start_node;
 else if(new_start_node = rq_.Run_Cross_Sequence(arity_node))
 {
  return new_start_node;
 }
 else if(new_start_node = rq_.Run_Call_Entry(arity_node))
 {
  return new_start_node;
 }
 return nullptr;

}



