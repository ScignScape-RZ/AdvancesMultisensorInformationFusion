
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_RUN_TOKEN__H
#define RZ_GRAPH_RUN_TOKEN__H


#include "flags.h"

#include "accessors.h"

#include "rz-graph-token/token/token-kinds.h"

#include <QString>

#include <QDebug>

#include "rzns.h"

RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)
USING_RZNS(GBuild)


RZNS_(GVal)

class RZ_Lisp_Graph_Scope_Token;

_RZNS(GVal)
USING_RZNS(GVal)


RZNS_(GEmbed)

class RZ_Graph_Embed_Token;
class RZ_Graph_Cpp_Token;


_RZNS(GEmbed)
USING_RZNS(GEmbed)


RZNS_(GRun)


class RZ_Graph_Run_Token
{
public:

 flags_(4)
  bool has_string_value:1;
  bool is_list_entry:1;
  bool nothing:1;
  bool has_cpp_redirect:1;
  bool is_core_function_symbol:1;
  bool is_function_expression_entry:1;
  bool is_infix_operator_entry:1;
  bool is_prefix_operator_entry:1;
  bool is_inserted_tuple_info:1;
  bool is_assignment_block_entry:1;
  bool is_mapkey:1;
  bool is_do_mapkey:1;
  bool is_caserun_argument:1;
  bool has_mapkey:1;
  bool has_match_literal_value:1;
  bool is_empty_tuple_indicator:1;
  bool is_if_with_elsif:1;
  bool is_lex_assignment_entry:1;
  bool is_quoted:1;
  bool is_keyword:1;
  bool is_their:1;
  bool is_cpp_scoped:1;
  bool is_via_type_assignment:1;
  bool is_type_symbol_in_declaration:1;
  bool is_symbol_declaration:1;
  bool is_untyped_symbol_declaration:1;
  bool follows_call_arrow:1;
  bool is_elsif_with_elsif:1;
  bool is_if_with_else:1;
 _flags

private:

 QString string_value_;
 Basic_Token_Kinds kind_;

public:

 ACCESSORS__GET(QString ,string_value)

 ACCESSORS__SET__IMPL(QString ,string_value)
 {
  string_value_ = string_value;
  flags.has_string_value = true;
 }

 ACCESSORS(Basic_Token_Kinds ,kind)

 RZ_Graph_Run_Token();
 RZ_Graph_Run_Token(QString string_value, Basic_Token_Kinds kind);


 void init_from_scope_token(const RZ_Lisp_Graph_Scope_Token& scope_token);
 void init_from_embed_token(const RZ_Graph_Embed_Token& embed_token);


 QString text_value() const;

 // this is needed by rz-clasp-code
 QString lisp_value() const;

  // //  The difference lisp_string_value and
   //    lisp_value is lisp_value adds the , on
   //    symbol declarations ...
 QString lisp_string_value() const;


 QString cpp_string_value() const;

 void set_symbol_string_value(QString string_value)
 {
  set_string_value(string_value);
  kind_ = Basic_Token_Kinds::Symbol_Token;
 }


 void init_from(RZ_Lisp_Token& rzlt);

};

_RZNS(GRun)


#endif //RZ_GRAPH_RUN_TOKEN__H
