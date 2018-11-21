
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_BLOCK_ENTRY_RUN_PLUGIN__H
#define RZ_BLOCK_ENTRY_RUN_PLUGIN__H

#include "accessors.h"

#include "flags.h"

#include "rz-lisp-graph-visitor.h"
#include "rz-lisp-graph-visitor-run-plugin.h"

#include "rzns.h"

RZNS_(GBuild)


class RZ_Lisp_Graph_Visitor;
class RZ_Lisp_Graph_Visitor_Run_State;

class RZ_Block_Entry_Run_Plugin : public RZ_Lisp_Graph_Visitor_Run_Plugin
{

 enum class RZ_Block_Entry_Branch_State
 {
  N_A, Pre_Block, Block_Pre_Entry, Block_Entry,
   Parameter_List_Pre_Entry, Parameter_Pre_Entry,
   Parameter_Entry, Parameter_Key, Parameter_Value,
   Parameter_Leave, Parameter_List_Leave

 };


 RZ_Lisp_Graph_Lexical_Scope::iterator_type lexical_scope_iterator_;

public:

 RZ_Block_Entry_Run_Plugin(RZ_Lisp_Graph_Visitor& main_visitor, RZ_Lisp_Graph_Lexical_Scope::iterator_type l);

 RZ_Block_Entry_Branch_State state_;

 bool advance();
 void get_current_token(RZ_Graph_Run_Token& rzt);
 void activate();
 void deactivate();
 bool find_next_token(RZ_Read_Table_State state_not_found,
  RZ_Read_Table_Post_Advance_State post_state_not_found);

};

_RZNS(GBuild)




#endif //RZ_BLOCK_ENTRY_RUN_PLUGIN__H
