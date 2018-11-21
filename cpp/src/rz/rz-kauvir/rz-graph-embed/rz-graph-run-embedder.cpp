
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-graph-run-embedder.h"


#include "rz-graph-embed-token.h"
#include "rz-graph-embed-package.h"

#include "rz-graph-build/rz-lisp-graph-result-holder.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"

#include "relae-graph/relae-node-ptr.h"


#include <QStringList>

USING_RZNS(GEmbed)

RZ_Graph_Run_Embedder::RZ_Graph_Run_Embedder(caon_ptr<RZ_Lisp_Graph_Valuer> valuer)
 : valuer_(valuer), fr_(RE_Frame::instance()), rq_(RE_Query::instance()), cpp_project_(nullptr)
{
 init_noop_node();
}

void RZ_Graph_Run_Embedder::init_noop_node()
{
 rz_cpp_embed_package_ = new RZ_Graph_Embed_Package("RZCPP");

 caon_ptr<RZ_Graph_Embed_Token> rget = new RZ_Graph_Embed_Token("RZ-NO-OP",
  rz_cpp_embed_package_);
 noop_node_ = new tNode(rget);
 noop_node_->set_label(QString("<embed:%1>").arg("RZ-NO-OP"));
}


void RZ_Graph_Run_Embedder::check_redirect(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& current_start_node)
{
 // //  Leave it for the proceed call to decide
 //     how to redirect at runtime
 if(rh.flags.continue_proceed)
  return;

 if(rh.flags.skip_redirect)
  rh.flags.skip_redirect = false;
 else
 {
  redirect_to_noop(rh, current_start_node);
 }
}



void RZ_Graph_Run_Embedder::redirect_to_noop(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& current_start_node)
{
 caon_ptr<tNode> arg = &current_start_node;
 if(caon_ptr<tNode> n = rh.get_lead_function_node(arg))
 {
  redirect_to_noop(*n);
 }
}


void RZ_Graph_Run_Embedder::redirect_to_noop(tNode& n)
{
 caon_ptr<tNode> pn(&n);
 pn <<fr_/rq_.Run_Embed_Redirect>> noop_node_;
}

void RZ_Graph_Run_Embedder::redirect(RZ_Lisp_Graph_Result_Holder& rh,
 QString function_name, tNode& function_node)
{
 rh.skip_redirect();

 if(caon_ptr<tNode> n = rh.get_lead_function_node(&function_node))
 {
  redirect(*n, function_name);
 }
}

void RZ_Graph_Run_Embedder::embed_rename(RZ_Lisp_Graph_Result_Holder& rh,
 QString function_name, tNode& function_node)
{
 rh.skip_redirect();

 if(caon_ptr<tNode> n = rh.get_lead_function_node(&function_node))
 {
  embed_rename(*n, function_name);
 }
}

void RZ_Graph_Run_Embedder::embed_deferred_callback(RZ_Lisp_Graph_Result_Holder& rh,
 QString function_name, tNode& function_node)
{
 rh.skip_redirect();

 embed_deferred_callback(function_node, function_name);
}


void RZ_Graph_Run_Embedder::redirect(RZ_Lisp_Graph_Result_Holder& rh, std::initializer_list<QString> args,
 caon_ptr<tNode> function_node)
{
 rh.skip_redirect();
 if(caon_ptr<tNode> n = rh.get_lead_function_node(function_node))
 {
  QStringList qsl;
  for(auto a : args)
   qsl << a;
  redirect(*n, qsl);
 }
}


void RZ_Graph_Run_Embedder::redirect_no_package(RZ_Lisp_Graph_Result_Holder& rh, std::initializer_list<QString> args,
 caon_ptr<tNode> function_node)
{
 rh.skip_redirect();
 if(caon_ptr<tNode> n = rh.get_lead_function_node(function_node))
 {
  QStringList qsl;
  for(auto a : args)
   qsl << a;
  redirect(*n, qsl, true);
 }
}



void RZ_Graph_Run_Embedder::redirect_with_call_no_package(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& redirect_entry_node, std::initializer_list<QString> args, caon_ptr<tNode> function_node)
{
 rh.skip_redirect();
 if(caon_ptr<tNode> n = rh.get_lead_function_node(function_node))
 {
  QStringList qsl;
  for(auto a : args)
   qsl << a;
  RZ_Graph_Embed_Token& rget = *redirect(*n, qsl, true);
  rget.set_entry_node(&redirect_entry_node);
 }
}


void RZ_Graph_Run_Embedder::redirect(RZ_Lisp_Graph_Result_Holder& rh, QStringList& qsl,
 tNode& function_node)
{
 rh.skip_redirect();

 if(caon_ptr<tNode> n = rh.get_lead_function_node(&function_node))
 {
  redirect(*n, qsl);
 }
}



caon_ptr<RZ_Graph_Embed_Token> RZ_Graph_Run_Embedder::redirect(tNode& n, QStringList& qsl, bool no_package)
{
 //?
 if(qsl.isEmpty())
  return nullptr;

 QString front = qsl.front();
 qsl.removeFirst();


 caon_ptr<RZ_Graph_Embed_Token> rget;

 if(no_package)
  rget = new RZ_Graph_Embed_Token(front);
 else
  rget = new RZ_Graph_Embed_Token(front, rz_cpp_embed_package_);


 caon_ptr<tNode> new_node = new tNode(rget);

 new_node->set_label(QString("<embed:%1>").arg(front));

 if(!qsl.empty())
 {
  rget->set_args(qsl);
 }

 &n <<fr_/rq_.Run_Embed_Redirect>> new_node;

 return rget;
}


void RZ_Graph_Run_Embedder::redirect(tNode& n, QString function_name)
{
 caon_ptr<RZ_Graph_Embed_Token> rget = new RZ_Graph_Embed_Token(function_name, rz_cpp_embed_package_);
 caon_ptr<tNode> new_node = new tNode(rget);

 new_node->set_label(QString("<embed:%1>").arg(function_name));

 &n <<fr_/rq_.Run_Embed_Redirect>> new_node;
}

void RZ_Graph_Run_Embedder::embed_deferred_callback(tNode& n, QString function_name)
{
 QString package_name = "rz";

 if(function_name.contains(':'))
 {
  QStringList qsl = function_name.split(':');
  package_name = qsl[0];
 }
 function_name.replace(':', "__");


 // //  TODO: deal with package other than rz: ...

 function_name.prepend(':');
 QString embed_name = "rz-vdc";
 caon_ptr<RZ_Graph_Embed_Token> rget = new RZ_Graph_Embed_Token(embed_name, function_name, rz_cpp_embed_package_);

 caon_ptr<tNode> new_node = new tNode(rget);

 new_node->set_label(QString("<vdc:%1>").arg(function_name));

 &n <<fr_/rq_.Run_Embed_Redirect>> new_node;
}


void RZ_Graph_Run_Embedder::embed_rename(tNode& n, QString function_name)
{
 caon_ptr<RZ_Graph_Embed_Token> rget = new RZ_Graph_Embed_Token(function_name, rz_cpp_embed_package_);
 caon_ptr<tNode> new_node = new tNode(rget);

 new_node->set_label(QString("<rename:%1>").arg(function_name));

 &n <<fr_/rq_.Run_Embed_Rename>> new_node;
}

