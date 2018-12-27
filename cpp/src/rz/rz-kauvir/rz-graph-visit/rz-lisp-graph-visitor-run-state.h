
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_VISITOR_RUN_STATE__H
#define RZ_LISP_GRAPH_VISITOR_RUN_STATE__H

#include "accessors.h"

#include "flags.h"

#include "rz-graph-sre/rz-read-table-state.h"

#include "rzns.h"

RZNS_(GBuild)


class RZ_Lisp_Graph_Visitor;

class RZ_Lisp_Graph_Visitor_Run_State
{
public:

 flags_(1)
  bool on_embed_redirect_branch:1;
  bool on_embed_redirect_entry:1;
  bool on_embed_redirect_leave:1;
  bool has_run_plugin:1;

  bool cpp_mode:1;
  bool current_noop:1;
  bool override_quasi_statements:1;

 _flags

private:

 RZ_Read_Table_State read_table_state_;
 RZ_Read_Table_Post_Advance_State post_advance_state_;
 RZ_Read_Table_Advance_Token_State advance_token_state_;

public:

 ACCESSORS(RZ_Read_Table_State ,read_table_state)
 ACCESSORS(RZ_Read_Table_Post_Advance_State ,post_advance_state)
 ACCESSORS(RZ_Read_Table_Advance_Token_State ,advance_token_state)

 RZ_Lisp_Graph_Visitor_Run_State();

 bool check_node_advance_state()
 {
  return advance_token_state_ == RZ_Read_Table_Advance_Token_State::Node_Loaded
     || advance_token_state_ == RZ_Read_Table_Advance_Token_State::Token_Read;
 }


};

_RZNS(GBuild)




#endif //RZ_LISP_GRAPH_VISITOR_RUN_STATE__H
