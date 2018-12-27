
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-embed-branch-run-plugin.h"
#include "rz-lisp-graph-visitor.h"

#include "rz-graph-run/token/rz-graph-run-token.h"

#include "rz-graph-embed/rz-graph-embed-token.h"

#include "rzns.h"

USING_RZNS(GBuild)


RZ_Embed_Branch_Run_Plugin::RZ_Embed_Branch_Run_Plugin(RZ_Lisp_Graph_Visitor& main_visitor)
 : RZ_Lisp_Graph_Visitor_Run_Plugin(main_visitor), current_embed_arg_position_(0)
{

}


bool RZ_Embed_Branch_Run_Plugin::advance()
{
 switch(run_state_.read_table_state())
 {
 case RZ_Read_Table_State::Expression_Entry:
 case RZ_Read_Table_State::Expression_Sequence:
  return find_next_token(RZ_Read_Table_State::Expression_Final, RZ_Read_Table_Post_Advance_State::Holds_Token);
 case RZ_Read_Table_State::Expression_Final:
  if(run_state_.flags.on_embed_redirect_leave)
  {
   run_state_.flags.on_embed_redirect_leave = false;
   return false;
  }
  break;

 case RZ_Read_Table_State::Expression_Pre_Entry:
  {
   run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Entry);
   run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::No_Token);
  }
  break;

 case RZ_Read_Table_State::Expression_Embed_Sequence:
  {
   caon_ptr<RZ_Graph_Embed_Token> rget;
   if(rget)
   {
    rget->advance_arg(current_embed_arg_position_);
    if(current_embed_arg_position_ == 0)
    {
     return check_embed_call_entry(*rget);
    }
   }
  }
 }
 return true;
}

bool RZ_Embed_Branch_Run_Plugin::check_embed_call_entry(RZ_Graph_Embed_Token& rget)
{
 if(rget.entry_node())
 {
  CAON_EVALUATE_DEBUG(RE_Node ,en ,rget.entry_node())
  run_state_.flags.on_embed_redirect_branch = false;
  run_state_.flags.on_embed_redirect_entry = true;
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Pre_Entry);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
  return true;
 }
 else
 {
  run_state_.flags.on_embed_redirect_branch = false;
  return false;
 }
}

void RZ_Embed_Branch_Run_Plugin::activate()
{
}


void RZ_Embed_Branch_Run_Plugin::deactivate()
{
}

void RZ_Embed_Branch_Run_Plugin::get_current_token(RZ_Graph_Run_Token& rzt)
{

}


bool RZ_Embed_Branch_Run_Plugin::find_next_token(RZ_Read_Table_State state_not_found,
 RZ_Read_Table_Post_Advance_State post_state_not_found)
{
 if(run_state_.flags.on_embed_redirect_branch)
 {
  // // what about nested embed redirect...?
  caon_ptr<RZ_Graph_Embed_Token> rget;
  if(rget)
    rget->advance_arg(current_embed_arg_position_);
  {
   if(current_embed_arg_position_ == 0)
   {
    run_state_.flags.on_embed_redirect_branch = false;
    run_state_.set_read_table_state(state_not_found);
    run_state_.set_post_advance_state(post_state_not_found);
    return false;
   }
   else
   {
    run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Embed_Sequence);
    run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
   }
  }
 }

 else if(run_state_.flags.on_embed_redirect_entry)
 {
  run_state_.flags.on_embed_redirect_entry = false;
  run_state_.flags.on_embed_redirect_leave = true;
  run_state_.set_read_table_state(RZ_Read_Table_State::Expression_Final);
  run_state_.set_post_advance_state(RZ_Read_Table_Post_Advance_State::Holds_Token);
 }
 return true;
}
