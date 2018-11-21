
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-graph.h"
#include "rz-re-node.h"

#include "kernel/rz-re-root.h"

#include "token/rz-re-token.h"

#include "tuple/rz-re-tuple-info.h"
#include "code/rz-re-call-entry.h"

#include "code/rz-re-block-entry.h"
#include "kernel/graph/rz-re-connection.h"

#include "rzns.h"

USING_RZNS(RECore)

RE_Graph::RE_Graph(caon_ptr<RE_Node> root_node)
 : node_graph<RE_Dominion>(root_node)
{

}

void RE_Graph::report(QTextStream& qts)
{
 if(caon_ptr<RE_Root> root = root_node_->re_root())
 {
  qts << "Root node: " << root->document_path();
 }
 report_from_node(qts, *root_node_);
}

void RE_Graph::report_from_node(QTextStream& qts,
 const RE_Node& node, int indent)
{
 QString padding(indent, ' ');
 qts << "\n" << padding;
 if(caon_ptr<RE_Token> token = node.re_token())
 {
  qts << "[token= " << token->string_summary() << "]";
 }
 else if(caon_ptr<RE_Call_Entry> rce = node.re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  QString extra;
  if(!rce->prefix().isEmpty())
  {
   extra = QString(" (%1) ").arg(rce->prefix());
  }
  if(rce->flags.no_normalize)
  {
   extra += "nn";
  }
  if(rce->flags.no_anticipate)
  {
   extra += "na";
  }
  qts << QString("<call %1%2>").arg(rce->call_id()).arg(extra);
 }
 else if(caon_ptr<RE_Block_Entry> rbe = node.re_block_entry())
 {
  qts << QString("<block %1:%2>").arg(rbe->call_id()).arg(rbe->nested_depth());
 }
 else if(caon_ptr<RE_Tuple_Info> rti = node.re_tuple_info())
 {
  if(rti->is_entry())
   qts << QString("<data %1 ...>").arg(rti->data_id());
  else
   qts << "<... data>";
 }
 else
 {
  qts << "<<node/" << node.label() << ">>";
 }
  //Run_Data_Entry
 node.each_connection([this, node, &qts, &padding, &indent]
  (const RE_Connectors& connector, const RE_Node& target, const RE_Connection* connection)
 {
  // //   For debugging...
  QString label = node.label();

  // //  Somehow, this connector is causing trouble
  if(connector.case_label == RE_Connectors_Case_Labels::Run_Fundef_Map_Key_Sequence)
  {
   //?return;
  }


  // //  This connector loops ...
  if(connector.case_label == RE_Connectors_Case_Labels::Parent_Block_Map)
  {
   qts << "\n\n" << padding << "Has connection: " << connector.label() << "\n";
   return;
  }

  qts << "\n\n" << padding << "For connection: " << connector.label() << "\n"
      << padding << "==== ";

  if(connection)
  {
   qts << "\n\n" << padding << "Annotated: \n";

   if(caon_ptr<RE_Node> cn = connection->re_node())
   {
    qts << " [[" << cn->label() << "]]\n";
   }

   qts << padding << "---- ";

  }

  report_from_node(qts, target, indent + 1);
  qts << "\n" << padding << "....";
 });
 //report_from_node(root_node_);
}
