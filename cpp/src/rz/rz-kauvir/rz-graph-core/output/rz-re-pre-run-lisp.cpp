
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-pre-run-lisp.h"

#include "rzns.h"

USING_RZNS(RECore)

RE_Pre_Run_Lisp::RE_Pre_Run_Lisp(caon_ptr<RE_Document> document)
 : RE_Lisp_Output(document)
{

}


void RE_Pre_Run_Lisp::output_from_node(QTextStream& qts,
 const RE_Node& node, int indent)
{
 qts << "OK";
}


void RE_Pre_Run_Lisp::report_call_entry(QTextStream& qts,
 const RE_Call_Entry& rce)
{
}

void RE_Pre_Run_Lisp::report_call_leave(QTextStream& qts,
 const RE_Call_Entry& rce)
{
}
