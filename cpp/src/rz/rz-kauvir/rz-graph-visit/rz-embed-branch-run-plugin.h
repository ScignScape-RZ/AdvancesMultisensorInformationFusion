
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_EMBED_BRANCH_RUN_PLUGIN__H
#define RZ_EMBED_BRANCH_RUN_PLUGIN__H

#include "accessors.h"

#include "flags.h"

#include "rz-lisp-graph-visitor.h"
#include "rz-lisp-graph-visitor-run-plugin.h"

#include "rzns.h"

RZNS_(GBuild)


class RZ_Lisp_Graph_Visitor;
class RZ_Lisp_Graph_Visitor_Run_State;

class RZ_Embed_Branch_Run_Plugin : public RZ_Lisp_Graph_Visitor_Run_Plugin
{

 int current_embed_arg_position_;

public:

 RZ_Embed_Branch_Run_Plugin(RZ_Lisp_Graph_Visitor& main_visitor);

 bool advance();
 void get_current_token(RZ_Graph_Run_Token& rzt);
 void activate();
 void deactivate();
 bool find_next_token(RZ_Read_Table_State state_not_found,
  RZ_Read_Table_Post_Advance_State post_state_not_found);

 bool check_embed_call_entry(RZ_Graph_Embed_Token& rget);


};

_RZNS(GBuild)




#endif //RZ_EMBED_BRANCH_RUN_PLUGIN__H
