
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_VISITOR_RUN_PLUGIN__H
#define RZ_LISP_GRAPH_VISITOR_RUN_PLUGIN__H

#include "accessors.h"

#include "flags.h"

#include "rz-graph-sre/rz-read-table-state.h"

#include "rzns.h"



RZNS_(GRun)

class RZ_Graph_Run_Token;

_RZNS(GRun)

USING_RZNS(GRun)
USING_RZNS(RECore)


RZNS_(GBuild)


class RZ_Lisp_Graph_Visitor;
class RZ_Lisp_Graph_Visitor_Run_State;

class RZ_Lisp_Graph_Visitor_Run_Plugin
{

protected:

 RZ_Lisp_Graph_Visitor& main_visitor_;
 RZ_Lisp_Graph_Visitor_Run_State& run_state_;


public:

 RZ_Lisp_Graph_Visitor_Run_Plugin(RZ_Lisp_Graph_Visitor& main_visitor);

 virtual bool advance() = 0;
 virtual void get_current_token(RZ_Graph_Run_Token& rzt) = 0;
 virtual void activate() = 0;
 virtual void deactivate() = 0;
 virtual bool find_next_token(RZ_Read_Table_State state_not_found,
  RZ_Read_Table_Post_Advance_State post_state_not_found) = 0;

};

_RZNS(GBuild)




#endif //RZ_LISP_GRAPH_VISITOR_RUN_PLUGIN__H
