
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_PARSE_CONTEXT__H
#define RZ_RE_PARSE_CONTEXT__H

#include "relae-graph/relae-parser.h"

#include "flags.h"

#include "rzns.h"
RZNS_(RECore)

class RE_Graph;
class RE_Node;

class RE_Parse_Context
{
 typedef RE_Node tNode;

public:
 flags_(2)
  flag_(1, pre_markup);
  flag_(2, inside_run_acc);
  flag_(3, inside_text_map_acc);
  flag_(4, inside_run_comment);
  flag_(5, inside_string_literal);
  flag_(6, inside_match_literal);
  flag_(7, inside_string_plex);
  flag_(8, inside_path_handlers);
  flag_(9, inside_xq_literal);
  flag_(10, inside_raw_lisp);
  flag_(11, inside_extended_string_literal);
  flag_(12, arrow_pending_symbol_modify_to_method);
  flag_(13, take_a_space);

 _flags_

private:
 caon_ptr<RE_Node> current_open_print_node_;

public:

 RE_Parse_Context();

};

_RZNS(RECore)

#endif //RZ_RE_PARSE_CONTEXT__H
