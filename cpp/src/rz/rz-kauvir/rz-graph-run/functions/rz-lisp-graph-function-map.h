
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_FUNCTION_MAP__H
#define RZ_LISP_GRAPH_FUNCTION_MAP__H


#include <QMap>

#include "rz-graph-token/valuer/rz-lisp-graph-function-info.h"

#include "functions/rz-lisp-graph-function-families.h"

#include "rz-lisp-graph-core-function-declarations.h"


#include "rzns.h"

USING_RZNS(GRun)



#ifdef RZ_LISP_GRAPH_FUNCTION_DECLARE
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE
#endif


RZNS_(GRun)


static QMap<QString, RZ_Lisp_Graph_Function_Info> RZ_Lisp_Graph_Function_Code_Map
{{
#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_S_(name)}},
#include "functions/core-functions-s.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_T_(name)}},
#include "functions/core-functions-t.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_TC_(name)}},
 #include "functions/core-functions-t-c.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_CC_(name)}},
#include "functions/core-functions-c-c.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_VV_(name)}},
#include "functions/core-functions-v-v.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_C_(name)}},
#include "functions/core-functions-c.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_CT_(name)}},
#include "functions/core-functions-c-t.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_Tc_(name)}},
#include "functions/core-functions-tc.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_Tv_(name)}},
 #include "functions/core-functions-tv.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) {#name, {RZ_GCALL_TV_(name)}},
#include "functions/core-functions-t-v.h"
#undef RZ_LISP_GRAPH_FUNCTION_DECLARE
}};

_RZNS(GRun)

#endif //RZ_LISP_GRAPH_FUNCTION_MAP__H
