
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_RUN_ROUTER__H
#define RZ_LISP_GRAPH_RUN_ROUTER__H

#include "functions/rz-lisp-graph-function-families.h"


#include "rz-graph-build/types/core-types.h"

#include "rz-temp-cases.h"

#include "rz-graph-build/rz-lisp-graph-result-holder.h"


#include "rz-graph-token/rz-lisp-graph-value-holder.h"


RZNS_(GRun)


struct No_Cast_Needed
{
};

struct Cast_Needed
{
};

struct Cast_Copy
{
};

struct LHS_Cast_Marker
{
};

struct LHS_Value_Marker
{
};

struct RHS_Cast_Marker
{
};

struct RHS_Value_Marker
{
};

struct RET_Marker
{
};

struct Cast_Null_Marker
{
};

struct Raw_Token_Marker
{
};

template<typename T>
struct Is_Cast_Needed
{
 static const bool Value = false;
};

template<>
struct Is_Cast_Needed<Cast_Needed>
{
 static const bool Value = true;
};

template<bool, typename T1, typename T2>
struct If_Then_Else
{
};

template<typename T1, typename T2>
struct If_Then_Else<true, T1, T2>
{
 typedef T1 Type;
};

template<typename T1, typename T2>
struct If_Then_Else<false, T1, T2>
{
 typedef T2 Type;
};

template<typename LHS_Type, typename RHS_Type>
struct Get_Return_Type
{
 typedef RHS_Type Type;
};


template<
 RZ_Lisp_Graph_Function_Family CORE_FUNCTION_Family,
 RZ_Lisp_Graph_Function_Code CORE_FUNCTION_Code,
 RZ_Type_Families::Enum TYPE_FAMILY_Enum,
 typename LHS_Type = Cast_Needed, typename RHS_Type = Cast_Needed,
 typename RETURN_Type = Cast_Null_Marker>
struct Cast_Schedule
{
 static const RZ_Lisp_Graph_Function_Family Core_Function_Family = CORE_FUNCTION_Family;
 static const RZ_Lisp_Graph_Function_Code Core_Function_Code = CORE_FUNCTION_Code;
 static const RZ_Type_Families::Enum Type_Family = TYPE_FAMILY_Enum;

 typedef Cast_Schedule<Core_Function_Family,
  Core_Function_Code, Type_Family, LHS_Type, RHS_Type, RETURN_Type> This_Cast_Schedule_type;

 typedef RZ_Lisp_Graph_Function_Family_<Core_Function_Family> Core_Function_Family_Type;

 typedef LHS_Type LHS_type;
 typedef RHS_Type RHS_type;

 template<typename POSITION_MARKER_Type, typename NEW_RUN_Type, RZ_Type_Families::Enum Fam>
 struct Next_Schedule_Point
 {
 };

 template<typename NEW_RUN_Type, RZ_Type_Families::Enum Fam>
 struct Find_Next_Schedule_Point
 {
  typedef Next_Schedule_Point
  <
   // get the first position
   typename If_Then_Else
   <
    // either LHS
    Is_Cast_Needed<LHS_Type>::Value,
    LHS_Cast_Marker,
    // or maybe RHS
    typename If_Then_Else
    <
     Is_Cast_Needed<RHS_Type>::Value,
     RHS_Cast_Marker,
     // or else there is no more casting
     RET_Marker
    >::Type
   >::Type
   ,
   // get the return type for the second position
   // if no cast needed
   typename If_Then_Else
   <
    // cast needed here
    Is_Cast_Needed<LHS_Type>::Value,
    NEW_RUN_Type,
    typename If_Then_Else
    <
     // cast also needed here
     Is_Cast_Needed<RHS_Type>::Value,
     NEW_RUN_Type,
     // but here get return type instead
     typename Get_Return_Type<LHS_Type, RHS_Type>::Type
    >::Type
   >::Type, Fam
  > Type;
 };

 template<typename NEW_RUN_Type, RZ_Type_Families::Enum Fam>
 struct Next_Schedule_Point<LHS_Cast_Marker, NEW_RUN_Type, Fam>
 {
  typedef Cast_Schedule<Core_Function_Family,
   Core_Function_Code, Fam, NEW_RUN_Type, RHS_Type> Type;
 };

 template<typename NEW_RUN_Type, RZ_Type_Families::Enum Fam>
 struct Next_Schedule_Point<RHS_Cast_Marker, NEW_RUN_Type, Fam>
 {
  typedef Cast_Schedule<Core_Function_Family,
   Core_Function_Code, Fam, LHS_Type, NEW_RUN_Type> Type;
 };

 template<typename RET_Type, RZ_Type_Families::Enum Fam>
 struct Next_Schedule_Point<RET_Marker, RET_Type, Fam>
 {
  typedef Cast_Schedule<Core_Function_Family,
   Core_Function_Code, Fam, LHS_Type, RHS_Type, RET_Type> Type;
 };


 template<typename CAST_SCHED_Type, typename RUNNER_INFO_Type, RZ_Type_Families::Enum Fam,
  bool CTQ_FUNCTION_FAMILY_SET = RZ_Get_Family_Code<RUNNER_INFO_Type>::Value != RZ_Function_Family_Not_Set >
 struct Runner
 {
 };

#define RZ_TEMP_CASE(n) case n: \
 RZ_Lisp_Graph_Function_Run<Family_Code, n, Type_Family>::template run<T1, T2>(rh, *t1, *t2); break;

 template<typename CAST_SCHED_Type, typename ARITY_FAMILY_Type, RZ_Type_Families::Enum Fam>
 struct Runner<CAST_SCHED_Type, ARITY_FAMILY_Type, Fam, true>
 {
  static const RZ_Lisp_Graph_Function_Family Family_Code =
   RZ_Get_Family_Code<ARITY_FAMILY_Type>::Value ;
  static const RZ_Type_Families::Enum Type_Family = Fam;
  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, caon_ptr<T1> t1, caon_ptr<T2> t2)
  {
   switch(CAST_SCHED_Type::Core_Function_Code)
   {
    RZ_TEMP_CASES__FUNCTION_CODE
   }
  }
 };
#undef RZ_TEMP_CASE


#define RZ_TEMP_CASE(n) case n: \
 RZ_Lisp_Graph_Function_Run<Family_Code, n, Type_Family>::run(rh, token, vh); break;

 template<typename CAST_SCHED_Type, RZ_Type_Families::Enum Fam>
 struct Runner<CAST_SCHED_Type, RHS_Value_Marker, Fam>
 {
  static const RZ_Lisp_Graph_Function_Family Family_Code = CORE_FUNCTION_Family;
  static const RZ_Type_Families::Enum Type_Family = Fam;
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token, RZ_Lisp_Graph_Value_Holder& vh)
  {
   switch(CORE_FUNCTION_Code)
   {
    RZ_TEMP_CASES__FUNCTION_CODE
   }
  }
#undef RZ_TEMP_CASE

#define RZ_TEMP_CASE(n) case n: \
 RZ_Lisp_Graph_Function_Run<Family_Code, n, Type_Family>::run(rh, v1, v2); break;

  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& v1, RZ_Lisp_Graph_Value_Holder& v2)
  {
   switch(CORE_FUNCTION_Code)
   {
    RZ_TEMP_CASES__FUNCTION_CODE
   }
  }
#undef RZ_TEMP_CASE

 };


 template<typename CAST_SCHED_Type, RZ_Type_Families::Enum Fam>
 struct Runner<CAST_SCHED_Type, Raw_Token_Marker, Fam>
 {
  static const RZ_Lisp_Graph_Function_Family Family_Code = CORE_FUNCTION_Family;
  static const RZ_Type_Families::Enum Type_Family = Fam;

#define RZ_TEMP_CASE(n) case n: \
     RZ_Lisp_Graph_Function_Run<Family_Code, n, Type_Family> \
      ::run(rh, start_token, pass_node); break;

  static void run(RZ_Lisp_Graph_Result_Holder& rh,
   RZ_Lisp_Token& start_token, caon_ptr<tNode> pass_node)
  {
   switch(CORE_FUNCTION_Code)
   {
    RZ_TEMP_CASES__FUNCTION_CODE
   }
  }
#undef RZ_TEMP_CASE

#define RZ_TEMP_CASE(n) case n: \
     RZ_Lisp_Graph_Function_Run<Family_Code, n, Type_Family> \
      ::run(rh, start_token); break;

  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& start_token)
  {
   switch(CORE_FUNCTION_Code)
   {
    // //?    RZ_TEMP_CASES__FUNCTION_CODE
   }
  }
#undef RZ_TEMP_CASE
 };


#define RZ_TEMP_CASE(n) case n: \
 Next_Runner<n, RZ_Run_Type<n>::Type_Family>::Type::run(rh, v1->template pRetrieve<RZ_Run_Type<n>::Type>(), v2 ); break;

 template<typename CAST_SCHED_Type, RZ_Type_Families::Enum Fam>
 struct Runner<CAST_SCHED_Type, LHS_Cast_Marker, Fam>
 {
  template<int Code, RZ_Type_Families::Enum Fam1>
  struct Next_Runner
  {
   typedef typename Next_Schedule_Point<LHS_Cast_Marker, typename RZ_Run_Type<Code>::Type, Fam1>::Type::
    template Runner
    <
     This_Cast_Schedule_type,
     typename If_Then_Else
     <
      Is_Cast_Needed<RHS_Type>::Value, RHS_Cast_Marker,
      Core_Function_Family_Type
     >::Type, Fam1
    > Type;
  };

  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, caon_ptr<T1> v1, caon_ptr<T2> v2)
  {
   switch(v1->typecode())
   {
   case RZ_Run_Types::Not_Set:break;
    RZ_TEMP_CASES_(TYPECODE)
   }
  }
 };
#undef RZ_TEMP_CASE


#define RZ_TEMP_CASE(n) case n: \
  Next_Runner<n, RZ_Run_Type<n>::Type_Family>::Type::run(rh, v1, \
   v2->template pRetrieve<RZ_Run_Type<n>::Type>() ); break;
 template<typename CAST_SCHED_Type, RZ_Type_Families::Enum Fam>
 struct Runner<CAST_SCHED_Type, RHS_Cast_Marker, Fam>
 {
  template<int Code, RZ_Type_Families::Enum Fam1>
  struct Next_Runner
  {
   typedef typename Next_Schedule_Point<RHS_Cast_Marker, typename RZ_Run_Type<Code>::Type,
    RZ_Type_Families::merge(Fam, Fam1) >::Type::
    template Runner<This_Cast_Schedule_type, Core_Function_Family_Type,
     RZ_Type_Families::merge(Fam, Fam1)

     > Type;
  };

  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, caon_ptr<T1> v1, caon_ptr<T2> v2)
  {
   switch(v2->typecode())
   {
    case RZ_Run_Types::Not_Set: break;
    RZ_TEMP_CASES_(TYPECODE)
   }
  }
 };
#undef RZ_TEMP_CASE
};

_RZNS(GRun)


#endif //RZ_LISP_GRAPH_RUN_ROUTER__H
