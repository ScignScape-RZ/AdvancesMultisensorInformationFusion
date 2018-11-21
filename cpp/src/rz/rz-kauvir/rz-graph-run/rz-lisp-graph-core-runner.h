
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_CORE_RUNNER__H
#define RZ_GRAPH_CORE_RUNNER__H


#include <QMap>

#include "rz-graph-token/rz-lisp-graph-value-holder.h"

#include "rz-graph-build/rz-lisp-graph-result-holder.h"


#include "functions/rz-lisp-graph-function-map.h"

#include "rz-lisp-graph-core-runner.h"

#include "rzns.h"


USING_RZNS(GBuild)


RZNS_(GRun)

struct RZ_Lisp_Graph_Core_Runner
{
 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Graph_Value_Holder& v1, RZ_Lisp_Graph_Value_Holder& v2);

 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Graph_Value_Holder& vh, RZ_Lisp_Token& token);

 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Token& token, RZ_Lisp_Graph_Value_Holder& vh);


 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Token& start_token, caon_ptr<tNode> pass_node);

 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Token& start_token);

 template<RZ_Lisp_Graph_Function_Family>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Function_Code function_code,
  RZ_Lisp_Token& lhs_token, RZ_Lisp_Token& rhs_token);

};

_RZNS(GRun)


#endif //RZ_GRAPH_CORE_RUNNER__H
