
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH_CALL_S__H
#define GRAPH_CALL_S__H

#include "token/rz-lisp-token.h"

#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"

#include "functions/rz-lisp-graph-function-families.h"

RZNS_(GRun)


typedef RZ::RECore::RE_Node tNode;

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) name,

#define RZ_TEMP_MACRO_(X) \
 template<> \
 struct RZ_Lisp_Graph_Function_Family_<X> \
 { enum Code { \
  null = 0, \


#define _RZ_TEMP_MACRO }; };


RZ_LISP_GRAPH_FUNCTION_CODES_(RZ_Graph_Call_S)
 null = 0,
 #include "core-functions-s.h"
_RZ_LISP_GRAPH_FUNCTION_CODES

#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

#define RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION(count) \
 RZ_GCALL_IMPLEMENT <RZ_GCALL_S(Leave_Logical_Scope_##count, Internal)> \
 { \
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& start_token, caon_ptr<tNode> pass_node) \
  { \
   start_token.redirect_paste("#_rz-class"); \
  } \
 }; \


#undef RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION

#define RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION(fun_name, v_method) \
 RZ_GCALL_IMPLEMENT <RZ_GCALL_S(fun_name, Internal)> \
 { \
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& start_token, caon_ptr<tNode> pass_node) \
  { \
   rh.valuer->v_method(rh, start_token, pass_node); \
  } \
 }; \


#undef RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION

#define RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION(fun_name, v_method) \
 RZ_GCALL_IMPLEMENT <RZ_GCALL_S(fun_name, Internal)> \
 { \
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& start_token, caon_ptr<tNode> pass_node) \
  { \
   rh.valuer->v_method(start_token, pass_node); \
  } \
 }; \

#undef RZ_GCALL_TEMP_DEFAULT_IMPLEMENTATION

_RZNS(GRun)

#endif //GRAPH_CALL_S__H
