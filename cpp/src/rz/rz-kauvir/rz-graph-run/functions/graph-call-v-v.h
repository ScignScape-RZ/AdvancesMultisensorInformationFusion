
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef GRAPH_CALL_V_V__H
#define GRAPH_CALL_V_V__H

#include "token/rz-lisp-token.h"


#include "rz-graph-valuer/valuer/rz-lisp-graph-valuer.h"

#include "relae-graph/relae-caon-ptr.h"

#include "functions/rz-lisp-graph-function-families.h"

#include "rzns.h"

RZNS_(GRun)

#define RZ_LISP_GRAPH_FUNCTION_DECLARE(str, name, arity, status) name,

RZ_LISP_GRAPH_FUNCTION_CODES_(RZ_Graph_Call_VV)
 null = 0,
 #include "core-functions-v-v.h"
_RZ_LISP_GRAPH_FUNCTION_CODES

#undef RZ_LISP_GRAPH_FUNCTION_DECLARE

RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Set_Equal, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().set_equal(rh, *ft, v1, v2);
  }
 }
};


RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Set_Equal_Via_Type, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().set_equal_via_type(rh, *ft, v1, v2);
  }
 }
};


RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Assign_To_Type, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().assign_to_type(rh, *ft, v1, v2);
  }
 }
};

// //  currently this is identical to Assign_To_Type;
 //    any difference enforced by code generators ...
RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Assign_To_Type_Overloadable, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().assign_to_type(rh, *ft, v1, v2);
  }
 }
};


RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Preinit_Assign_To_Type_Overloadable, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().preinit_assign_to_type_overloadable(rh, *ft, v1, v2);
  }
 }
};



RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Set_Preinit_Equal, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().set_preinit_equal(rh, *ft, v1, v2);
  }
 }
};


RZ_GCALL_IMPLEMENT
<RZ_GCALL_VV(Set_Preinit_Equal_To_Type, Internal)>
{
 static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1,
                 RZ_Lisp_Graph_Value_Holder& v2)
 {
  caon_ptr<RZ_Lisp_Token> ft = rh.get_lead_function_token();
  if(ft)
  {
   rh.valuer().set_preinit_equal_to_type(rh, *ft, v1, v2);
  }
 }
};

_RZNS(GRun)

#endif //GRAPH_CALL_V_V__H
