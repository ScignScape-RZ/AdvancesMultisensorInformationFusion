
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-result-holder.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"

#include "rz-graph-core/token/rz-re-token.h"


#include <QStringList>

#include "rzns.h"

USING_RZNS(GBuild)

RZ_Lisp_Graph_Result_Holder::RZ_Lisp_Graph_Result_Holder(RZ_Lisp_Graph_Valuer& valuer)
 : Flags(0), valuer_(valuer), arity_node_(nullptr),
   pass_node_(nullptr), lead_function_node_(nullptr)
{
}

void RZ_Lisp_Graph_Result_Holder::hold(caon_ptr<tNode> n)
{
 current_start_nodes_.push(n);
}

void RZ_Lisp_Graph_Result_Holder::unhold()
{
 current_start_nodes_.pop();
}

caon_ptr<RZ_Lisp_Graph_Result_Holder::tNode>
RZ_Lisp_Graph_Result_Holder::pull_pass_node()
{
 caon_ptr<tNode> result = pass_node_;
 pass_node_ = nullptr;
 return result;
}

void RZ_Lisp_Graph_Result_Holder::continue_proceed(caon_ptr<tNode> n)
{
 flags.continue_proceed = true;
 flags.continue_statement = false;
 pass_node_ = arity_node_;
 arity_node_ = n;
 if(lead_function_node_)
  return;
 lead_function_node_ = function_node();
}

caon_ptr<RZ_Lisp_Token> RZ_Lisp_Graph_Result_Holder::function_token()
{
 // //  Usually this will only be called from
 //    a context where a function node will
 //    have been pushed on, but ...
 if(caon_ptr<tNode> n = function_node())
  return n->re_token()->lisp_token();
 return nullptr;
}

caon_ptr<RZ_Lisp_Graph_Result_Holder::tNode>
 RZ_Lisp_Graph_Result_Holder::function_node()
{
 if(current_start_nodes_.empty())
  return nullptr;
 return current_start_nodes_.top();
}


void RZ_Lisp_Graph_Result_Holder::mark_continue_statement(caon_ptr<tNode> n)
{
 CAON_PTR_DEBUG(tNode ,n)
 flags.continue_statement = true;
 arity_node_ = n;
}

caon_ptr<RZ_Lisp_Graph_Result_Holder::tNode>
 RZ_Lisp_Graph_Result_Holder::get_lead_function_node(caon_ptr<tNode> current_start_node)
{
 if(lead_function_node_)
  return lead_function_node_;

 if(caon_ptr<tNode> result = function_node())
  return result;

 return current_start_node;
}

caon_ptr<RZ_Lisp_Token> RZ_Lisp_Graph_Result_Holder::get_lead_function_token()
{
 if(caon_ptr<tNode> n = get_lead_function_node())
  return n->re_token()->lisp_token();
 return nullptr;
}

void RZ_Lisp_Graph_Result_Holder::skip_redirect()
{
 flags.skip_redirect = true;
}


