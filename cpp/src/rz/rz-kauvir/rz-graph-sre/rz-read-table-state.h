
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_READ_TABLE_STATE__H
#define RZ_READ_TABLE_STATE__H

#include "rzns.h"

RZNS_(RECore)

enum class RZ_Read_Table_State
{
 Inactive, Root, Pre_Root,
  File_Block_Pre_Entry,
  Block_Pre_Entry, Block_Entry,
  Statement_Pre_Entry, Statement_Entry,
  Expression_Pre_Entry, Expression_Entry,
  Expression_Sequence, Cross_Pre_Continue, Cross_Continue,
  Expression_Final, Expression_End, Expression_Leave,
  Statement_Final, Statement_End, Statement_Leave,
  Block_Final, Block_End, Block_Leave,
  Block_Pre_Continue, Block_Continue, Nested_Block_Rewind_Pre_Continue,
  Block_Continue_Call_Pre_Entry, Block_Continue_Call_Entry,
  Nested_Block_Leave_No_Continue, Block_Leave_No_Continue,
  Nested_Block_Leave_Statement_Final,
  Do_Map_Block_Continue, Do_Map_Block_Leave,
   Do_Map_Block_Statement_Leave,

  Next_Node_Loaded__Block_Pre_Entry,

  Expression_Rewind,
  Rewind,

  Graph_End,

  UnUSED_1,
  Expression_Embed_Sequence,
  Expression_Embed_Leave,


};


enum class RZ_Read_Table_Post_Advance_State
{
 N_A, Holds_Token, No_Token, Reenter, Deactivate
};

enum class RZ_Read_Table_Advance_Token_State
{
 N_A, Next_Node_Holds_Token, Token_Loaded, Token_Read, Node_Loaded
};

enum class RZ_Read_Table_Advance_Graph_State
{
 N_A, Block_Entry, Call_Entry, Call_Sequence, Cross_Entry,
  Cross_Continue, Cross_Block,
};


struct RZ_SRE_State
{
 typedef RZ_Read_Table_State Read_Table_State;
 typedef RZ_Read_Table_Post_Advance_State Post_Advance_State;
 typedef RZ_Read_Table_Advance_Token_State Advance_Token_State;
 typedef RZ_Read_Table_Advance_Graph_State Advance_Graph_State;
};

struct RZ_SRE_Result_State
{
 RZ_SRE_State::Read_Table_State read_table_state;
 RZ_SRE_State::Post_Advance_State post_advance_state;
 RZ_SRE_State::Advance_Token_State advance_token_state;
 RZ_SRE_State::Advance_Graph_State advance_graph_state;

 RZ_SRE_Result_State():
   read_table_state(RZ_SRE_State::Read_Table_State::Inactive),
   post_advance_state(RZ_SRE_State::Post_Advance_State::N_A),
   advance_token_state(RZ_SRE_State::Advance_Token_State::N_A),
   advance_graph_state(RZ_SRE_State::Advance_Graph_State::N_A)
 {}
};



_RZNS(RECore)


#endif //RZ_READ_TABLE_STATE__H
