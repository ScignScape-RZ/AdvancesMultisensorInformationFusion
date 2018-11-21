
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH_CALL_T__H
#define GRAPH_CALL_T__H

#include "token/rz-lisp-token.h"
#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"

#include "functions/rz-lisp-graph-function-families.h"

#include "rzns.h"

RZNS_(GRun)

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) name,

RZ_LISP_GRAPH_FUNCTION_CODES_(RZ_Graph_Call_T)
 null = 0,
 #include "core-functions-t.h"
_RZ_LISP_GRAPH_FUNCTION_CODES

#undef RZ_LISP_GRAPH_FUNCTION_DECLARE


_RZNS(GRun)


#endif //GRAPH_CALL_T__H
