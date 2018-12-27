
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-graph-run-token.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-scope-token.h"

#include "rz-graph-embed/rz-graph-embed-token.h"


#include "rzns.h"
USING_RZNS(GRun)


RZ_Graph_Run_Token::RZ_Graph_Run_Token(QString string_value, Basic_Token_Kinds kind)
 : Flags(0), string_value_(string_value), kind_(kind)
{
 flags.has_string_value = true;
}


RZ_Graph_Run_Token::RZ_Graph_Run_Token()
 : Flags(0), kind_(Basic_Token_Kinds::Symbol_Token)
{}

QString RZ_Graph_Run_Token::text_value() const
{
 QString result =  string_value_;
 if(flags.is_quoted)
  result = result.prepend('\'');
 return result;
}

void RZ_Graph_Run_Token::init_from(RZ_Lisp_Token& rzlt)
{
 Flags = 0;
 if(rzlt.flags.is_empty_tuple_indicator)
 {
  flags.is_empty_tuple_indicator = true;
  kind_ = Basic_Token_Kinds::Empty_Tuple_Indicator;
  return;
 }
 flags.has_string_value = true;
 kind_ = rzlt.kind_and_string_value(string_value_);
 flags.is_function_expression_entry = rzlt.flags.is_function_expression_entry;
 flags.is_core_function_symbol = rzlt.flags.is_core_function_symbol;
 flags.is_infix_operator_entry = rzlt.flags.is_infix_operator_entry;
 flags.is_prefix_operator_entry = rzlt.flags.is_prefix_operator_entry;
 flags.is_assignment_block_entry = rzlt.flags.is_assignment_block_entry;
 flags.is_mapkey = rzlt.flags.is_mapkey;
 flags.is_do_mapkey = rzlt.flags.is_do_mapkey;
 flags.is_caserun_argument = rzlt.flags.is_block_entry_caserun;
 flags.has_mapkey = rzlt.flags.has_mapkey;
 flags.has_match_literal_value = rzlt.flags.is_match_literal;
 flags.is_if_with_elsif = rzlt.flags.is_if_with_elsif;
 flags.is_if_with_else = rzlt.flags.is_if_with_else;
 flags.is_elsif_with_elsif = rzlt.flags.is_elsif_with_elsif;
 flags.is_lex_assignment_entry = rzlt.flags.is_lex_assignment_entry;
 flags.is_via_type_assignment = rzlt.flags.is_via_type_assignment;
 flags.is_type_symbol_in_declaration = rzlt.flags.is_type_symbol_in_declaration;
 flags.is_symbol_declaration = rzlt.flags.is_symbol_declaration;
 flags.is_untyped_symbol_declaration = rzlt.flags.is_untyped_symbol_declaration;


 flags.is_quoted = rzlt.flags.is_quoted;
 flags.is_keyword = rzlt.flags.is_keyword;

 flags.is_their = rzlt.flags.is_their;
 flags.is_cpp_scoped = rzlt.flags.is_cpp_scoped;
 flags.follows_call_arrow = rzlt.flags.follows_call_arrow;

}


void RZ_Graph_Run_Token::init_from_embed_token(const RZ_Graph_Embed_Token& embed_token)
{
 flags.has_string_value = true;
 kind_ = embed_token.kind_and_string_value(string_value_);

}


void RZ_Graph_Run_Token::init_from_scope_token(const RZ_Lisp_Graph_Scope_Token& scope_token)
{
 flags.has_string_value = true;
 kind_ = scope_token.initial_kind_and_string_value(string_value_);
}

//QString RZ_Graph_Run_Token::lisp_string_value() const
//{
// if(flags.is_via_type_assignment)
// {
//  return QString("q-create :|%1|").arg(string_value_);
// }
// else
// {
//  return string_value_;
// }
//}

QString RZ_Graph_Run_Token::cpp_string_value() const
{
 QString result = string_value_;
 result.replace('-', '_');
 return result;
}

QString RZ_Graph_Run_Token::lisp_string_value() const
{
 QString result =  string_value_;
 if(flags.is_quoted)
  result.prepend('\'');
 if(flags.is_keyword)
  result.prepend(':');

 if(flags.is_via_type_assignment)
 {
  result.prepend("(q-create :|");
  result.append("|)");
 }
 return result;

}


QString RZ_Graph_Run_Token::lisp_value() const
{
 QString result =  string_value_;
 if(flags.is_quoted)
  result.prepend('\'');
 if(flags.is_keyword)
  result.prepend(':');

 if(flags.is_symbol_declaration)
  result.prepend(',');

 if(flags.is_via_type_assignment)
 {
  result.prepend("(q-create :|");
  result.append("|)");
 }
 return result;

}






