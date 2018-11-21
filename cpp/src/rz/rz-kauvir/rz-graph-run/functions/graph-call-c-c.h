
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH_CALL_C_C__H
#define GRAPH_CALL_C_C__H

#include "types/type-families.h"

struct RZ_Core_Symbol;

#include "rzns.h"

RZNS_(GRun)

RZ_LISP_GRAPH_FUNCTION_CODES_(RZ_Graph_Call_CC)
 null = 0,
 #include "core-functions-c-c.h"
_RZ_LISP_GRAPH_FUNCTION_CODES

_RZNS(GRun)

#endif //GRAPH_CALL_C_C__H
