
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-prerun-tokens.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-core/token/rz-re-token.h"

USING_RZNS(RECore)
USING_RZNS(GBuild)


RE_Prerun_Tokens::RE_Prerun_Tokens(caon_ptr<RE_Document> document)
 : RE_Lisp_Output(document)
{

}


void RE_Prerun_Tokens::init_token(RE_Token& token)
{
 RZ_Lisp_Token::init_lisp_token(token);
}

void RE_Prerun_Tokens::report_token(QTextStream& qts,
 const RE_Token& token)
{
 qts << QString("<<%1>>").arg(token.raw_text());
}


void RE_Prerun_Tokens::report_tuple_info_entry(QTextStream& qts,
 const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr)
{

}

void RE_Prerun_Tokens::report_tuple_info_leave(QTextStream& qts,
 const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr)
{

}

void RE_Prerun_Tokens::report_call_entry(QTextStream& qts,
 const RE_Call_Entry& rce)
{

}

void RE_Prerun_Tokens::report_call_leave(QTextStream& qts,
 const RE_Call_Entry& rce)
{

}

