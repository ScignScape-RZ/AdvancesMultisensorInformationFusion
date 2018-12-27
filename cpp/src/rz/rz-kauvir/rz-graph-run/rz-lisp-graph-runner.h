
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_RUNNER__H
#define RZ_LISP_GRAPH_RUNNER__H

#include "accessors.h"


#include "rz-graph-token/types/run-types.h"

#include "rz-graph-core/kernel/query/rz-re-query.h"

#include "rz-graph-core/kernel/rz-re-dominion.h"

#include "functions/rz-lisp-graph-function-map.h"

#include <stack>

#include <map>

#include "rzns.h"

RZNS_(RECore)

class RE_Node;
class RE_Graph;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GRun)

class RZ_Graph_Run_Token;

_RZNS(GRun)


RZNS_(GBuild)

class RZ_Lisp_Core_Runner;
class RZ_Lisp_Graph_Visitor;
class RZ_Lisp_Graph_Result_Holder;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;

_RZNS(GVal)

USING_RZNS(GVal)

RZNS_(GRun)

class RZ_Lisp_Graph_Runner
{

 caon_ptr<RZ_Lisp_Graph_Valuer> valuer_;

 const RE_Query& rq_;


 typedef RE_Node tNode;

public:

 RZ_Lisp_Graph_Runner(caon_ptr<RZ_Lisp_Graph_Valuer> valuer);

 void check_run_info(RZ_Lisp_Graph_Result_Holder& rh,
  RZ_Lisp_Graph_Core_Function& cf, tNode& start_node);

 void check_core_function_info(RZ_Lisp_Graph_Core_Function& cf);

 void valuer_redirect(RZ_Lisp_Graph_Result_Holder& rh,
  RZ_Lisp_Graph_Core_Function& cf, tNode& start_node);

 template<int Arity>
 void run_from_node(RZ_Lisp_Graph_Result_Holder& rh,
  RZ_Lisp_Graph_Core_Function& cf, tNode& start_node);

 void check_continue(RZ_Lisp_Graph_Result_Holder& rh);

 caon_ptr<tNode> check_run_sequence(RZ_Lisp_Graph_Result_Holder& rh,
  caon_ptr<RE_Connectors>& premise, tNode& lhs_node);

 caon_ptr<tNode> run_token_as_first_argument(RZ_Lisp_Graph_Result_Holder& rh);

 void init_run_sequence_pair(RZ_Lisp_Graph_Result_Holder& rh,
  tNode& start_node, caon_ptr<tNode>& first_node,
  caon_ptr<tNode>& second_node,  caon_ptr<tNode>& left_new_node,
                        caon_ptr<tNode>& right_new_node);


};

_RZNS(GRun)


#endif //RZ_LISP_GRAPH_RUNNER__H
