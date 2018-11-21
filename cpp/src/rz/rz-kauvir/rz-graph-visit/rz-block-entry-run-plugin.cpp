
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-block-entry-run-plugin.h"
#include "rz-lisp-graph-visitor.h"

#include "rz-graph-run/token/rz-graph-run-token.h"


#include "rzns.h"

USING_RZNS(GBuild)


RZ_Block_Entry_Run_Plugin::RZ_Block_Entry_Run_Plugin(RZ_Lisp_Graph_Visitor& main_visitor, RZ_Lisp_Graph_Lexical_Scope::iterator_type l)
 : RZ_Lisp_Graph_Visitor_Run_Plugin(main_visitor),
   lexical_scope_iterator_(l), state_(RZ_Block_Entry_Branch_State::N_A)
{

}


bool RZ_Block_Entry_Run_Plugin::advance()
{
 switch(state_)
 {
 case RZ_Block_Entry_Branch_State::Pre_Block:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Pre_Entry);
    // // Holds the "let" or "progn" token
       //? run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Reenter);
  state_ = RZ_Block_Entry_Branch_State::Block_Pre_Entry;

  break;

 case RZ_Block_Entry_Branch_State::Block_Pre_Entry:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Entry);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::No_Token);
  state_ = RZ_Block_Entry_Branch_State::Parameter_List_Pre_Entry;

  break;

 case RZ_Block_Entry_Branch_State::Parameter_List_Pre_Entry:
//?
  if(lexical_scope_iterator_.hasNext())
  {
   run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Pre_Entry);
   run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
   state_ = RZ_Block_Entry_Branch_State::Parameter_Pre_Entry;
  }
  else
  {
   run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Final);
   run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
   state_ = RZ_Block_Entry_Branch_State::N_A;
  }
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Pre_Entry:
   run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Pre_Entry);
   run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::No_Token);
   state_ = RZ_Block_Entry_Branch_State::Parameter_Entry;
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Entry:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Entry);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::No_Token);
  state_ = RZ_Block_Entry_Branch_State::Parameter_Key;
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Key:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Sequence);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
  state_ = RZ_Block_Entry_Branch_State::Parameter_Value;
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Value:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Final);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
  if(lexical_scope_iterator_.hasNext())
   state_ = RZ_Block_Entry_Branch_State::Parameter_Pre_Entry;
  else
   state_ = RZ_Block_Entry_Branch_State::Parameter_Leave;
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Leave:
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Final);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
  state_ = RZ_Block_Entry_Branch_State::Parameter_List_Leave;
  break;

 case RZ_Block_Entry_Branch_State::Parameter_List_Leave:
  deactivate();
  return false;
 }
 return true;
}


bool RZ_Block_Entry_Run_Plugin::find_next_token(RZ_Read_Table_State state_not_found,
 RZ_Read_Table_Post_Advance_State post_state_not_found)
{
 // //  Not reached...
 return false;

}

void RZ_Block_Entry_Run_Plugin::activate()
{
 state_ = RZ_Block_Entry_Branch_State::Pre_Block;
}


void RZ_Block_Entry_Run_Plugin::deactivate()
{
 state_ = RZ_Block_Entry_Branch_State::N_A;
}

void RZ_Block_Entry_Run_Plugin::get_current_token(RZ_Graph_Run_Token& rzt)
{
 switch(state_)
 {
 case RZ_Block_Entry_Branch_State::Parameter_List_Pre_Entry:
  if(lexical_scope_iterator_.hasNext())
   rzt.set_symbol_string_value("let");
  else
   rzt.set_symbol_string_value("progn");
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Key:
  lexical_scope_iterator_.next();
  rzt.set_symbol_string_value(lexical_scope_iterator_.key());
  break;

 case RZ_Block_Entry_Branch_State::Parameter_Value:
  rzt.init_from_scope_token(lexical_scope_iterator_.value());
  break;

 }


}


