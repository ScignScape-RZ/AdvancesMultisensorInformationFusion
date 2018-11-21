
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_RUNTIME_ROUTER_QOB__H
#define KCM_COMMAND_RUNTIME_ROUTER_QOB__H

#include "kcm-command-runtime-router.h"

#include "kcm-command-runtime-argument.h"


USING_KANS(CMD)


#define ARGS_TEMP_MACRO(INDEX) \
 typename Type_List_Type::Type##INDEX& arg##INDEX \
   = *reinterpret_cast<typename Type_List_Type::Type##INDEX*> \
    ( argument_info[INDEX].void_argument );

#define QARG_TEMP_MACRO(INDEX) QArgument<ARG##INDEX##_Type> \
  ( argument_info[INDEX].type_name_with_modifier(args[INDEX - 1]->qob_reflection_modifier(), args[INDEX - 1]->qob_reflection_type_name()).toLatin1(), arg##INDEX) \



#define CASE_TEMP_MACRO_(INDEX, READY, INTERCHANGE_TYPE) \
 case INDEX: \
  Cast_##READY::run<OBJECT_Type, \
    typename Interchange<Type_List_Type, INDEX, READY>:: \
    template With_Type<INTERCHANGE_TYPE>::Result_Type>  \
    (method_name, obj, next_cast_index, kcrr,  \
    argument_info, args);  \
  break;  \


#define ARGS_TEMP_MACRO(INDEX) \
 typename Type_List_Type::Type##INDEX& arg##INDEX \
   = *reinterpret_cast<typename Type_List_Type::Type##INDEX*> \
    ( argument_info[INDEX].void_argument );

#define CAST_INDEX_SWITCH(TYPE) \
   switch(cast_index) \
   { \
    CASE_TEMP_MACRO(0, TYPE) \
    CASE_TEMP_MACRO(1, TYPE) \
   } \



struct Do_Invoke_Method__Cast_Schedule__QOB
{

 struct Cast_2_Readyx
 {
  template<typename OBJECT_Type, typename ARG1_Type, typename ARG2_Type>
  static void run(QString method_name, OBJECT_Type obj, QVector<KCM_Command_Runtime_Argument*>& args,
                  ARG1_Type& arg1, ARG2_Type& arg2,
                  const QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info)
  {
   QMetaObject::invokeMethod(obj, method_name.toLatin1(),
     QArgument<ARG1_Type>(argument_info[1].type_name_with_modifier(args[0]->qob_reflection_modifier(), args[0]->qob_reflection_type_name()).toLatin1(), arg1),
     QArgument<ARG2_Type>(argument_info[2].type_name_with_modifier(args[1]->qob_reflection_modifier(), args[1]->qob_reflection_type_name()).toLatin1(), arg2));
  }

  template<typename OBJECT_Type, typename RET_Type, typename ARG1_Type, typename ARG2_Type>
  static void run(QString method_name, OBJECT_Type obj,
                  QString return_type, RET_Type& ret,
                  QVector<KCM_Command_Runtime_Argument*>& args,
                  ARG1_Type& arg1, ARG2_Type& arg2,
                  const QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info)
  {
   QMetaObject::invokeMethod(obj, method_name.toLatin1(),
                             QReturnArgument<RET_Type>(return_type.toLatin1(), ret),
                             QArgument<ARG1_Type>(argument_info[1].type_name_with_modifier(args[0]->qob_reflection_modifier(), args[0]->qob_reflection_type_name()).toLatin1(), arg1),
     QArgument<ARG2_Type>(argument_info[2].type_name_with_modifier(args[1]->qob_reflection_modifier(), args[1]->qob_reflection_type_name()).toLatin1(), arg2));

   qDebug() << "RET: " << ret;
  }
 };

#define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
   CASE_TEMP_MACRO_(INDEX, 2, INTERCHANGE_TYPE)

#define CAST_INDEX_SWITCH(TYPE) \
   switch(cast_index) \
   { \
    CASE_TEMP_MACRO(0, TYPE) \
    CASE_TEMP_MACRO(1, TYPE) \
   } \

#ifdef EXPAND_2_MACROS
 struct Cast_2
 {
  static constexpr int ready_at_cast_index = 2;
  template<typename OBJECT_Type, typename Type_List_Type>
  static void run(QString method_name, OBJECT_Type obj,
                  int cast_index, KCM_Command_Runtime_Router& kcrr,
                  QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info,
                  QVector<KCM_Command_Runtime_Argument*>& args)
  {
   if(cast_index == ready_at_cast_index)
   {
    switch(kcrr.return_type_code())
    {
    case KCM_Command_Runtime_Router::Arg_Type_Codes::No_Return:
     {
      ARGS_TEMP_MACRO(1)
      ARGS_TEMP_MACRO(2)
      Cast_2_Ready::run(method_name, obj,
                        args, arg1, arg2, argument_info);
     }
     break;
    case KCM_Command_Runtime_Router::Arg_Type_Codes::Int:
     {
      int& rrr = (int&) kcrr.raw_result_ref();
      ARGS_TEMP_MACRO(1)
      ARGS_TEMP_MACRO(2)
      Cast_2_Ready::run(method_name, obj,
        "int",
        rrr,
        args, arg1, arg2, argument_info);
     }
     break;
    }
   }
   else
   {
    int next_cast_index = cast_index + 1;
    KCM_Command_Runtime_Router::QOB_Argument_Conventions ac =
      argument_info[next_cast_index].qob_convention;
    switch(ac)
    {
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct:
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString:
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QObject_Direct:
     {
      CAST_INDEX_SWITCH(quint64)
     }
     break;
    }
   }
  }
 };
#endif // EXPAND_2_MACROS

#ifdef EXPAND_1_MACROS
 struct Cast_1
 {
  static constexpr int ready_at_cast_index = 1;
  template<typename OBJECT_Type, typename Type_List_Type>
  static void run(QString method_name, OBJECT_Type obj,
                  int cast_index, KCM_Command_Runtime_Router& kcrr,
                  QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info,
                  QVector<KCM_Command_Runtime_Argument*>& args)
  {
   if(cast_index == ready_at_cast_index)
   {
    switch(kcrr.return_type_code())
    {
    case KCM_Command_Runtime_Router::Arg_Type_Codes::No_Return:
     {
      ARGS_TEMP_MACRO(1)
      Cast_1_Ready::run(method_name, obj,
                        args, arg1, argument_info);
     }
     break;
    case KCM_Command_Runtime_Router::Arg_Type_Codes::Int:
     {
      int& rrr = (int&) kcrr.raw_result_ref();
      ARGS_TEMP_MACRO(1)
      Cast_1_Ready::run(method_name, obj,
        "int",
        rrr,
        args, arg1, argument_info);
     }
     break;
    }
   }
   else
   {
    int next_cast_index = cast_index + 1;
    KCM_Command_Runtime_Router::QOB_Argument_Conventions ac =
      argument_info[next_cast_index].qob_convention;
    switch(ac)
    {
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct:
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString:
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QObject_Direct:
     {
      CAST_INDEX_SWITCH(quint64)
     }
     break;
    }
   }
  }
 };
#endif // EXPAND_1_MACROS

#define CAST_READY_MACRO(ARG_COUNT) \
 struct Cast_##ARG_COUNT##_Ready \
 { \
  template<typename OBJECT_Type  TYPENAMES_typename> \
  static void run(QString method_name, OBJECT_Type obj, QVector<KCM_Command_Runtime_Argument*>& args \
   TYPENAMES_arg,  const QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info) \
  { \
   QMetaObject::invokeMethod(obj, method_name.toLatin1() \
    QARGUMENTS ); \
  } \
  template<typename OBJECT_Type, typename RET_Type  TYPENAMES_typename> \
  static void run(QString method_name, OBJECT_Type obj, QString return_type, \
   RET_Type& ret, QVector<KCM_Command_Runtime_Argument*>& args \
   TYPENAMES_arg,  const QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info) \
  { \
   QMetaObject::invokeMethod(obj, method_name.toLatin1(), \
    QReturnArgument<RET_Type>(return_type.toLatin1(), ret) \
    QARGUMENTS  ); \
  } \
 }; \

#define CAST_STRUCT_START_MACRO(ARG_COUNT) \
 struct Cast_##ARG_COUNT \
 { \

#define CAST_STRUCT_RUN_MACRO(ARG_COUNT) \
  static constexpr int ready_at_cast_index = ARG_COUNT; \
  template<typename OBJECT_Type, typename Type_List_Type> \
  static void run(QString method_name, OBJECT_Type obj, \
    int cast_index, KCM_Command_Runtime_Router& kcrr, \
    QVector<KCM_Command_Runtime_Router::Argument_Info>& argument_info, \
    QVector<KCM_Command_Runtime_Argument*>& args) \
  { \

#define CAST_READY_SWITCH_MACRO(ARG_COUNT) \
   switch(kcrr.return_type_code()) \
   { \
   case KCM_Command_Runtime_Router::Arg_Type_Codes::No_Return: \
    { \
     ARGS_TEMP_MACROS \
     Cast_##ARG_COUNT##_Ready::run(method_name, obj, args  ARGUMENTS, argument_info); \
    } \
    break; \
   case KCM_Command_Runtime_Router::Arg_Type_Codes::Void_Pointer: \
    { \
     ARGS_TEMP_MACROS \
     Cast_##ARG_COUNT##_Ready::run(method_name, obj, \
       kcrr.return_type_name_strip_namespace(), \
       kcrr.raw_result_ref(), \
       args  ARGUMENTS, argument_info); \
     } \
    break; \
   case KCM_Command_Runtime_Router::Arg_Type_Codes::Int: \
    { \
     int& x = *reinterpret_cast<int*>(kcrr.raw_result_ref()); \
     ARGS_TEMP_MACROS \
     Cast_##ARG_COUNT##_Ready::run(method_name, obj, \
      "int", x, args  ARGUMENTS, argument_info); \
    } \
    break; \
   case KCM_Command_Runtime_Router::Arg_Type_Codes::QString_Return: \
    { \
     QString& qs = kcrr.string_result(); \
     ARGS_TEMP_MACROS \
     Cast_##ARG_COUNT##_Ready::run(method_name, obj, \
      "QString", qs, args  ARGUMENTS, argument_info); \
    } \
    break; \
   } \


#define CAST_SWITCH_MACRO(ARG_COUNT) \
   else \
   { \
    int next_cast_index = cast_index + 1; \
    KCM_Command_Runtime_Router::QOB_Argument_Conventions ac = \
      argument_info[next_cast_index].qob_convention; \
    switch(ac) \
    { \
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct: \
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString: \
    case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QObject_Direct: \
     { \
      CAST_INDEX_SWITCH(quint64) \
     } \
     break; \
    } \
   } \

#define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
   CASE_TEMP_MACRO_(INDEX, 2, INTERCHANGE_TYPE)



#define CAST_STRUCT_END_MACRO } };



#define TEMP_MACRO(ARG_COUNT) \
 CAST_READY_MACRO(ARG_COUNT) \
 CAST_STRUCT_START_MACRO(ARG_COUNT) \
 CAST_STRUCT_RUN_MACRO(ARG_COUNT) \
 if(cast_index == ready_at_cast_index) \
 { \
  CAST_READY_SWITCH_MACRO(ARG_COUNT) \
 } \
 CAST_SWITCH_MACRO(ARG_COUNT) \
 CAST_STRUCT_END_MACRO



//#define TEMP__TEMP_MACRO(ARG_COUNT) \
// CAST_READY_MACRO(ARG_COUNT) \
// CAST_STRUCT_START_MACRO(ARG_COUNT) \
// CAST_STRUCT_RUN_MACRO(ARG_COUNT) \
// if(cast_index == ready_at_cast_index) \
// { \
//  CAST_READY_SWITCH_MACRO(ARG_COUNT) \
// } \
// else \
// { \
//  int next_cast_index = cast_index + 1; \
//  KCM_Command_Runtime_Router::QOB_Argument_Conventions ac = \
//    argument_info[next_cast_index].qob_convention; \
//  switch(ac) \
//  { \
//  case KCM_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct: \
//  case KCM_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString: \
//   { \
//    CAST_INDEX_SWITCH(quint32) \
//   } \
//   break; \
//  } \
// } \
// CAST_STRUCT_END_MACRO


// special case for ARG_COUNT = 0

#define TEMP_MACRO_0 \
 CAST_READY_MACRO(0) \
 CAST_STRUCT_START_MACRO(0) \
 CAST_STRUCT_RUN_MACRO(0) \
 \
  CAST_READY_SWITCH_MACRO(0) \
 \
 \
 CAST_STRUCT_END_MACRO

 // for arg count 0
 #define TYPENAMES_typename
 #define TYPENAMES_arg
 #define QARGUMENTS
 #define ARGUMENTS
 #define ARGS_TEMP_MACROS

TEMP_MACRO_0

  #undef TYPENAMES_typename
  #undef TYPENAMES_arg
  #undef ARGS_TEMP_MACROS
  #undef CASE_TEMP_MACROS
  #undef ARGUMENTS
  #undef QARGUMENTS

 // end arg count 0

 // for arg count 1


#ifdef EXPAND_1_MACROS

  #define TYPENAMES_typename ,typename ARG1_Type
  #define TYPENAMES_arg ,ARG1_Type arg1
  #define QARGUMENTS  \
   ,QARG_TEMP_MACRO(1) \

  #define ARGUMENTS   ,arg1

  #define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
     CASE_TEMP_MACRO_(INDEX, 1, INTERCHANGE_TYPE)

  #define CAST_INDEX_SWITCH(TYPE) \
     switch(cast_index) \
     { \
      CASE_TEMP_MACRO(0, TYPE) \
     } \


  #define ARGS_TEMP_MACROS \
   ARGS_TEMP_MACRO(1) \


//?
//  TEMP_MACRO(2)
  #define ARG_COUNT 1

  CAST_READY_MACRO(1)
  CAST_STRUCT_START_MACRO(1)
  CAST_STRUCT_RUN_MACRO(1)
  if(cast_index == ready_at_cast_index)
  {
   CAST_READY_SWITCH_MACRO(1)
  }
  CAST_SWITCH_MACRO(1)
  CAST_STRUCT_END_MACRO

#else

 #define TYPENAMES_typename ,typename ARG1_Type
 #define TYPENAMES_arg ,ARG1_Type arg1
 #define QARGUMENTS  \
  ,QARG_TEMP_MACRO(1) \

 #define ARGUMENTS   ,arg1

 #define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
    CASE_TEMP_MACRO_(INDEX, 1, INTERCHANGE_TYPE)

 #define CAST_INDEX_SWITCH(TYPE) \
    switch(cast_index) \
    { \
     CASE_TEMP_MACRO(0, TYPE) \
    } \


 #define ARGS_TEMP_MACROS \
  ARGS_TEMP_MACRO(1) \

  TEMP_MACRO(1)

  #undef TYPENAMES_typename
  #undef TYPENAMES_arg
  #undef ARGS_TEMP_MACROS
  #undef CASE_TEMP_MACROS
  #undef ARGUMENTS
  #undef QARGUMENTS

#endif

 // end arg count 1


  // for arg count 2

#ifdef EXPAND_2_MACROS

  #define TYPENAMES_typename ,typename ARG1_Type ,typename ARG2_Type
  #define TYPENAMES_arg ,ARG1_Type arg1 ,ARG2_Type arg2
  #define QARGUMENTS  \
   ,QARG_TEMP_MACRO(1) \
   ,QARG_TEMP_MACRO(2) \

  #define ARGUMENTS   ,arg1 ,arg2

  #define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
     CASE_TEMP_MACRO_(INDEX, 2, INTERCHANGE_TYPE)

  #define CAST_INDEX_SWITCH(TYPE) \
     switch(cast_index) \
     { \
      CASE_TEMP_MACRO(0, TYPE) \
      CASE_TEMP_MACRO(1, TYPE) \
     } \


  #define ARGS_TEMP_MACROS \
   ARGS_TEMP_MACRO(1) \
   ARGS_TEMP_MACRO(2) \

//?
//  TEMP_MACRO(2)
  #define ARG_COUNT 2

  CAST_READY_MACRO(2)
  CAST_STRUCT_START_MACRO(2)
  CAST_STRUCT_RUN_MACRO(2)
  if(cast_index == ready_at_cast_index)
  {
   CAST_READY_SWITCH_MACRO(2)
  }
  CAST_SWITCH_MACRO(2)
  CAST_STRUCT_END_MACRO


   #undef TYPENAMES_typename
   #undef TYPENAMES_arg
   #undef ARGS_TEMP_MACROS
   #undef CASE_TEMP_MACROS
   #undef ARGUMENTS
   #undef QARGUMENTS

  // end arg count 2

#else

  #define TYPENAMES_typename ,typename ARG1_Type ,typename ARG2_Type
  #define TYPENAMES_arg ,ARG1_Type arg1 ,ARG2_Type arg2
  #define QARGUMENTS  \
   ,QARG_TEMP_MACRO(1) \
   ,QARG_TEMP_MACRO(2) \

  #define ARGUMENTS   ,arg1 ,arg2

  #define CASE_TEMP_MACRO(INDEX, INTERCHANGE_TYPE) \
     CASE_TEMP_MACRO_(INDEX, 2, INTERCHANGE_TYPE)

  #define CAST_INDEX_SWITCH(TYPE) \
     switch(cast_index) \
     { \
      CASE_TEMP_MACRO(0, TYPE) \
      CASE_TEMP_MACRO(1, TYPE) \
     } \

  #define ARGS_TEMP_MACROS \
   ARGS_TEMP_MACRO(1) \
   ARGS_TEMP_MACRO(2) \

   TEMP_MACRO(2)

   #undef TYPENAMES_typename
   #undef TYPENAMES_arg
   #undef ARGS_TEMP_MACROS
   #undef CASE_TEMP_MACROS
   #undef ARGUMENTS
   #undef QARGUMENTS

#endif
};

template<int i>
struct Do_Invoke_Method__Cast_Schedule__QOB__Cast_
{
 //typedef Argument_
};

#define TEMP_MACRO(i) \
template<> \
struct Do_Invoke_Method__Cast_Schedule__QOB__Cast_<i> \
{ \
 typedef typename Do_Invoke_Method__Cast_Schedule__QOB::Cast_##i Type; \
}; \


TEMP_MACRO(0)
TEMP_MACRO(1)
TEMP_MACRO(2)

#endif //KCM_COMMAND_RUNTIME_ROUTER_QOB__H

