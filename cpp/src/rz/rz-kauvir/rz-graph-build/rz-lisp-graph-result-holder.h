
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_RESULT_HOLDER__H
#define RZ_LISP_GRAPH_RESULT_HOLDER__H

#include "accessors.h"

#include <stack>

#include <map>

#include <QTextStream>

#include "rzns.h"

#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-token/rz-lisp-graph-value-holder.h"

#include <stack>


RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;

_RZNS(GVal)


USING_RZNS(GVal)

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GBuild)

class RZ_Lisp_Token;

class RZ_Lisp_Graph_Result_Holder
{
public:
 flags_(2)
  bool is_writing:1;
  bool has_external:1;
  bool has_boolean:1;
  bool last_boolean:1;
  bool recur:1;
  bool is_transient_symbol:1;
  bool is_empty:1;
  bool break_loop:1;
  bool continue_statement:1;
  bool continue_proceed:1;
  bool proceed_anticipate_nested_run_call:1;
  bool has_held_value:1;
  bool skip_redirect:1;

  //?
  bool skip_init_do_block:1;
 _flags

private:

 typedef RE_Node tNode;
 typedef QTextStream tStringStream;

 RZ_Lisp_Graph_Valuer& valuer_;

 caon_ptr<tNode> arity_node_;
 caon_ptr<tNode> pass_node_;

 std::stack<caon_ptr<tNode>> current_start_nodes_;

 RZ_Lisp_Graph_Value_Holder value_holder_;

 caon_ptr<tNode> lead_function_node_;


public:

 ACCESSORS(caon_ptr<tNode> ,arity_node)
 ACCESSORS(caon_ptr<tNode> ,pass_node)
 ACCESSORS__RGET(RZ_Lisp_Graph_Value_Holder ,value_holder)
 ACCESSORS__GET(RZ_Lisp_Graph_Valuer& ,valuer)

 RZ_Lisp_Graph_Result_Holder(RZ_Lisp_Graph_Valuer& valuer);

 void clear_continue_proceed()
 {
  flags.continue_proceed = false;
 }


 void hold(caon_ptr<tNode> n);
 void unhold();

 caon_ptr<tNode> pull_pass_node();
 void continue_proceed(caon_ptr<tNode> n);

 caon_ptr<RZ_Lisp_Token> function_token();

 caon_ptr<tNode> function_node();
 caon_ptr<tNode> get_lead_function_node(caon_ptr<tNode> current_start_node = nullptr);

 void clear_continue_statement()
 {
  flags.continue_statement = false;
 }

 void mark_continue_statement(caon_ptr<tNode> n);


 caon_ptr<RZ_Lisp_Token> get_lead_function_token();

 void skip_redirect();

};

_RZNS(GBuild)


#endif //RZ_LISP_GRAPH_RESULT_HOLDER__H
