
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-lisp-output.h"

#include "kernel/document/rz-re-document.h"

#include "kernel/graph/rz-re-graph.h"
#include "kernel/graph/rz-re-node.h"

#include "kernel/rz-re-root.h"

#include "token/rz-re-token.h"

#include "tuple/rz-re-tuple-info.h"


#include "token/rz-re-token.h"

#include "rzns.h"


USING_RZNS(RECore)


RE_Lisp_Output::RE_Lisp_Output(caon_ptr<RE_Document> document)
 : document_(document), fr_(RE_Frame::instance()),
    rq_(RE_Query::instance())
{

}


QString RE_Lisp_Output::get_lisp_out(const RE_Token& token)
{
 return token.get_lisp_out();
}


void RE_Lisp_Output::output(QString path)
{
 document_->write_report(path, *this);
}

void RE_Lisp_Output::write_report(QTextStream& qts)
{
 caon_ptr<RE_Node> node = document_->graph()->root_node();
 output_from_node(qts, *node);
}


void RE_Lisp_Output::output_from_node(QTextStream& qts,
 const RE_Node& node, int indent, caon_ptr<RE_Call_Entry> rce_ptr)
{
 CAON_PTR_DEBUG(RE_Call_Entry ,rce_ptr)

 QString padding(indent, ' ');

 caon_ptr<RE_Call_Entry> rce = nullptr;
 caon_ptr<RE_Block_Entry> rbe = nullptr;
 caon_ptr<RE_Tuple_Info> rde = nullptr;

 if(caon_ptr<RE_Token> token = node.re_token())
 {
  init_token(*token);
  report_token(qts, *token);
 }

 else if(rce = node.re_call_entry())
 {
 }
 else if(rbe = node.re_block_entry())
 {

 }
 else if(rde = node.re_tuple_info())
 {

 }

#ifdef NO_CAON
  caon_ptr<RE_Node> pnode = caon_ptr<RE_Node>( &node );
#else
 caon_ptr<RE_Node> pnode = &node;
#endif

 if(caon_ptr<RE_Node> next_node = rq_.Run_Call_Sequence(pnode))
 {
  qts << ' ';
  output_from_node(qts, *next_node, indent + 1);
 }

 if(caon_ptr<RE_Node> next_node = rq_.Run_Call_Entry(pnode))
 {
  CAON_PTR_DEBUG(RE_Node ,next_node)
  if(rce)
  {
   qts << "\n" << padding;
   qts << '(';
   report_call_entry(qts, *rce);
   output_from_node(qts, *next_node, indent, rce);
   report_call_leave(qts, *rce);
   qts << ')';

   if(caon_ptr<RE_Node> cross_node = rq_.Run_Cross_Sequence(pnode))
   {
    qts << ' ';
    output_from_node(qts, *cross_node, indent);
   }
  }
  else
  {
   output_from_node(qts, *next_node, indent + 1);
  }

  // //?  for do map ...
  caon_ptr<RE_Node> do_map_continue_node = nullptr;
  caon_ptr<RE_Node> temp_next_node = next_node;
  while(true)
  {
   // //  check if these nodes are being visited multiple times?
   do_map_continue_node = rq_.Run_Nested_Do_Map_Block_Entry(temp_next_node);
   if(do_map_continue_node)
   {
    CAON_PTR_DEBUG(RE_Node ,do_map_continue_node)
    qts << ' ';
    output_from_node(qts, *do_map_continue_node, indent);
    temp_next_node = do_map_continue_node;
   }
   else
   {
    break;
   }
  }


 }

 if(caon_ptr<RE_Node> next_node = rq_.Run_Block_Entry(pnode))
 {
  qts << "\n" << padding;
  qts << "(block ";
  output_from_node(qts, *next_node, indent + 1);
  if(caon_ptr<RE_Node> cross_node = rq_.Run_Cross_Sequence(next_node))
  {
   output_from_node(qts, *cross_node, indent + 1);
  }
  qts << ')';
 }

 if(caon_ptr<RE_Node> next_node = rq_.Run_Data_Entry(pnode))
 {
  CAON_PTR_DEBUG(RE_Node ,next_node)
  next_node->debug_connections();
  if(caon_ptr<RE_Tuple_Info> rti = next_node->re_tuple_info())
  {
   qts << "\n" << padding << ' ';
   report_tuple_info_entry(qts, *rti, rce);
   if(next_node = rq_.Run_Data_Entry(next_node))
    output_from_node(qts, *next_node, indent + 1);
   report_tuple_info_leave(qts, *rti, rce);
  }
  if(caon_ptr<RE_Node> cross_node = rq_.Run_Cross_Sequence(pnode))
  {
   qts << ' ';
   output_from_node(qts, *cross_node, indent);
  }
 }

 if(caon_ptr<RE_Node> next_node = rq_.Run_Function_Def_Entry(pnode))
 {
  CAON_PTR_DEBUG(RE_Node ,next_node)
  next_node->debug_connections();

  // Function Def Entry followed by Call Entry then
  //  Cross Sequence (not Block Entry)
  // probably implies type expression

  if(caon_ptr<RE_Node> call_entry_node = rq_.Run_Call_Entry(next_node))
  {
   if(caon_ptr<RE_Node> entry_node = rq_.Run_Cross_Sequence(call_entry_node))
   {
    CAON_PTR_DEBUG(RE_Node ,entry_node)
    output_from_node(qts, *entry_node);
   }
  }
 }
}


