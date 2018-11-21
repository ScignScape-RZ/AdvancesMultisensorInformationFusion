
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH_CALL_TC__H
#define GRAPH_CALL_TC__H

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"


#include "functions/rz-lisp-graph-function-families.h"

#include "rzns.h"

RZNS_(GVal)

class RZ_Lisp_Symbol;

_RZNS(GVal)


USING_RZNS(GVal)
USING_RZNS(GBuild)

RZNS_(GRun)

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) name,

RZ_LISP_GRAPH_FUNCTION_CODES_(RZ_Graph_Call_Tc)
 null = 0,
 #include "core-functions-tc.h"
_RZ_LISP_GRAPH_FUNCTION_CODES

#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

RZ_GCALL_IMPLEMENT <RZ_GCALL_Tc(My, Core_Class)>
{
 template<typename T1, typename T2>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token, T2& t2)
 {

 }
 template<typename T1, typename T2>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token, RZ_Opaque_Call& opc)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.function_token();

  if(ft)
  {
   caon_ptr<tNode> n = rh.valuer().register_lexical_symbol(*ft, token, opc);
   rh.mark_continue_statement(n);
  }

 }

 template<typename T1, typename T2>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token, RZ_Opaque_Type_Symbol& ots)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.function_token();

  if(ft)
  {
   caon_ptr<tNode> n = rh.valuer().register_lexical_symbol(*ft, token, ots);
   rh.mark_continue_statement(n);
  }
 }

 template<typename T1, typename T2>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token,
  RZ_Lisp_Symbol& sym)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.function_token();
  if(ft)
  {
   caon_ptr<tNode> n = rh.valuer().register_lexical_symbol(rh, *ft, token, sym);
   rh.mark_continue_statement(n);
  }
 }

 template<typename T1, typename T2>
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token,
  RZ_Lisp_Vector& symvec)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.function_token();
  if(ft)
  {
   caon_ptr<tNode> n = rh.valuer().register_lexical_symbols(rh, *ft, token, symvec);
   rh.mark_continue_statement(n);
  }
 }
};


_RZNS(GRun)



#endif //GRAPH_CALL_TC__H
