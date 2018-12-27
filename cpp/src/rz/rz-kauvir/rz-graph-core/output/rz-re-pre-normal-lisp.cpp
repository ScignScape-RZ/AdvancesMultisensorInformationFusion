
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-pre-normal-lisp.h"

#include "kernel/graph/rz-re-graph.h"
#include "kernel/graph/rz-re-node.h"

#include "kernel/rz-re-root.h"

#include "token/rz-re-token.h"

#include "tuple/rz-re-tuple-info.h"
#include "code/rz-re-call-entry.h"

#include "rzns.h"

USING_RZNS(RECore)


#ifdef NO_CAON
 RE_Pre_Normal_Lisp::RE_Pre_Normal_Lisp(RE_Document* document)
#else
 RE_Pre_Normal_Lisp::RE_Pre_Normal_Lisp(caon_ptr<RE_Document> document)
#endif
 : RE_Lisp_Output(document)
{

}


void RE_Pre_Normal_Lisp::report_token(QTextStream& qts,
 const RE_Token& token)
{
 if(token.flags.is_symbol_declaration)
 {
  qts << "(rz-decl " << token.raw_text() << ")";
 }
 else
  qts << token.get_lisp_out();
}

void RE_Pre_Normal_Lisp::report_tuple_info_entry(QTextStream& qts,
 const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr)
{
 qts << '(';
 if(rce_ptr)
  qts << QString("<%1>").arg(rce_ptr->call_id());
 qts << rti.lisp_out_with_id() << ' ';
}

void RE_Pre_Normal_Lisp::report_call_entry(QTextStream& qts,
 const RE_Call_Entry& rce)
{
 qts << QString("<%1>").arg(rce.call_id());
}

void RE_Pre_Normal_Lisp::report_call_leave(QTextStream& qts,
 const RE_Call_Entry& rce)
{
 qts << QString("</%1>").arg(rce.call_id());
}

void RE_Pre_Normal_Lisp::report_tuple_info_leave(QTextStream& qts,
 const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr)
{
 qts << ')';
}

