
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_FUNCTION_FAMILY_ENUM__H
#define RZ_LISP_GRAPH_FUNCTION_FAMILY_ENUM__H

#include "rzns.h"

RZNS_(GRun)

enum RZ_Lisp_Graph_Function_Family
{
 RZ_Function_Family_Not_Set, RZ_Graph_Call_S, RZ_Graph_Call_T, RZ_Graph_Call_TC, RZ_Graph_Call_Tc, RZ_Graph_Call_TV,
 RZ_Graph_Call_VT, RZ_Graph_Call_VV, RZ_Graph_Call_C, RZ_Graph_Call_CT, RZ_Graph_Call_CC, RZ_Left_Macro, RZ_Right_Macro
};

_RZNS(GRun)

#endif //RZ_LISP_GRAPH_FUNCTION_FAMILY_ENUM__H
