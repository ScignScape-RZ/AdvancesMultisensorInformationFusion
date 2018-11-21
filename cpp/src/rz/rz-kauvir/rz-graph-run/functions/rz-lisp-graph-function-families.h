
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_FUNCTION_FAMILIES__H
#define RZ_LISP_GRAPH_FUNCTION_FAMILIES__H


#include "rz-graph-token/valuer/rz-lisp-graph-function-family-enum.h"

#include "rz-graph-build/rz-lisp-graph-result-holder.h"

#include "rz-graph-token/types/type-families.h"

#include "rzns.h"

RZNS_(GBuild)
class RZ_Lisp_Graph_Value_Holder;
class RZ_Lisp_Graph_Result_Holder;
_RZNS(GBuild)


USING_RZNS(GBuild)


RZNS_(GRun)

typedef int RZ_Lisp_Graph_Function_Code;

#define RZ_GCALL_S(name, fam) RZ_Graph_Call_S, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_S>::name, RZ_Type_Families::fam

#define RZ_GCALL_T(name, fam) RZ_Graph_Call_T, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_T>::name, RZ_Type_Families::fam

#define RZ_GCALL_TC(name, fam) RZ_Graph_Call_TC, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TC>::name, RZ_Type_Families::fam

#define RZ_GCALL_Tc(name, fam) RZ_Graph_Call_Tc, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tc>::name, RZ_Type_Families::fam

#define RZ_GCALL_Tv(name, fam) RZ_Graph_Call_Tv, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tv>::name, RZ_Type_Families::fam

#define RZ_GCALL_TV(name, fam) RZ_Graph_Call_TV, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TV>::name, RZ_Type_Families::fam

#define RZ_GCALL_VT(name, fam) RZ_Graph_Call_VT, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VT>::name, RZ_Type_Families::fam

#define RZ_GCALL_C(name, fam) RZ_Graph_Call_C, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_C>::name, RZ_Type_Families::fam

#define RZ_GCALL_CT(name, fam) RZ_Graph_Call_CT, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CT>::name, RZ_Type_Families::fam

#define RZ_GCALL_CC(name, fam) RZ_Graph_Call_CC, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CC>::name, RZ_Type_Families::fam

#define RZ_GCALL_VV(name, fam) RZ_Graph_Call_VV, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VV>::name, RZ_Type_Families::fam


#define RZ_GCALL_S_(name) RZ_Graph_Call_S, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_S>::name

#define RZ_GCALL_T_(name) RZ_Graph_Call_T, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_T>::name

#define RZ_GCALL_TC_(name) RZ_Graph_Call_TC, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TC>::name

#define RZ_GCALL_Tc_(name) RZ_Graph_Call_Tc, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tc>::name

#define RZ_GCALL_Tv_(name) RZ_Graph_Call_Tv, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tv>::name

#define RZ_GCALL_TV_(name) RZ_Graph_Call_TV, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TV>::name

#define RZ_GCALL_VT_(name) RZ_Graph_Call_VT, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VT>::name

#define RZ_GCALL_C_(name) RZ_Graph_Call_C, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_C>::name

#define RZ_GCALL_CT_(name) RZ_Graph_Call_CT, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CT>::name

#define RZ_GCALL_CC_(name) RZ_Graph_Call_CC, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CC>::name

#define RZ_GCALL_VV_(name) RZ_Graph_Call_VV, \
 RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VV>::name




#define RZ_LISP_GRAPH_FUNCTION_CODES_( Family_Name ) \
template<> \
struct RZ_Lisp_Graph_Function_Family_<Family_Name> \
{ enum Code {

#define _RZ_LISP_GRAPH_FUNCTION_CODES };};

typedef int RZ_Graph_Function_Code;

template<typename T>
struct RZ_Get_Family_Code
{
 static const RZ_Lisp_Graph_Function_Family Value =  RZ_Function_Family_Not_Set;
};

template<RZ_Lisp_Graph_Function_Family F>
struct RZ_Lisp_Graph_Function_Family_
{
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_S> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_S;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_T> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_T;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tc> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_Tc;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TC> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_TC;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TV> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_TV;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VV> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_VV;
};


template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VT> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_VT;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_C> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_C;
};

template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CT> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_CT;
};


template<>
struct RZ_Get_Family_Code< RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CC> >
{
 static const RZ_Lisp_Graph_Function_Family Value = RZ_Graph_Call_CC;
};

typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_S> RZ_Graph_Call_S_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_T> RZ_Graph_Call_T_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TC> RZ_Graph_Call_TC_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_Tc> RZ_Graph_Call_Tc_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_TV> RZ_Graph_Call_TV_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VT> RZ_Graph_Call_VT_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_VV> RZ_Graph_Call_VV_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_C> RZ_Graph_Call_C_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CT> RZ_Graph_Call_CT_Family;
typedef RZ_Lisp_Graph_Function_Family_<RZ_Graph_Call_CC> RZ_Graph_Call_CC_Family;

template<RZ_Lisp_Graph_Function_Family cff, int i, RZ_Type_Families::Enum Fam>
struct RZ_Lisp_Graph_Function_Run
{
  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, T1& t1, T2& t2)
  {
   qDebug() << "cff " << cff;
   qDebug() << "i " << i;
   qDebug() << "Fam " << Fam;
  }
  template<typename T>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& token, T& t)
  {
   qDebug() << "cff " << cff;
   qDebug() << "i " << i;
   RZ_Type_Families::Enum F = Fam;
   qDebug() << F;
   qDebug() << "cff " << cff;
  }
  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, T1& t, RZ_Lisp_Token& token)
  {
  }

  template<typename T1, typename T2>
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Call& opc, RZ_Lisp_Token& token)
  {
   RZ_Type_Families::Enum F = Fam;
   qDebug() << F;
  }

  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& t1, RZ_Lisp_Graph_Value_Holder& t2)
  {
   RZ_Type_Families::Enum F = Fam;
   qDebug() << F;
  }


  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Value_Holder& t1, RZ_Lisp_Token& t2)
  {
  }
  static void run(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& start_token)
  {
   qDebug() << "cff " << cff;
   qDebug() << "i " << i;
   RZ_Type_Families::Enum F = Fam;
   qDebug() << F;
   qDebug() << "cff " << cff;
  }
};

_RZNS(GRun)


#endif //RZ_LISP_GRAPH_FUNCTION_FAMILIES__H
