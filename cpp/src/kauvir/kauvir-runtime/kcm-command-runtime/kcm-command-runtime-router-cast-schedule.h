
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_RUNTIME_ROUTER_CAST_SCHEDULE__H
#define KCM_COMMAND_RUNTIME_ROUTER_CAST_SCHEDULE__H

#include <QtGlobal>

#include <QDebug>

#include <functional>


#include "kans.h"
#include "accessors.h"


#include "kauvir-type-system/kauvir-universal-class.h"


KANS_(CMD)

class Kauvir_Request_Runtime;
class Kauvir_Runtime_Router_Invokable;


typedef void(Kauvir_Universal_Class::*ft)(void*, void*);


struct Cast_Needed
{
 quint64 dummy;
 operator quint64&()
 {
  return dummy;
 }
 operator void*()
 {
  return (void*)dummy;
 }
};

struct No_Cast_Needed
{
};

template<typename T1>
struct Type_List__1
{
 typedef T1 Type1;
};

template<typename T1, typename T2>
struct Type_List__2
{
 typedef T1 Type1;
 typedef T2 Type2;
};

template<typename T1, typename T2, typename T3>
struct Type_List__3
{
 typedef T1 Type1;
 typedef T2 Type2;
 typedef T3 Type3;
};

template<typename T1, typename T2, typename T3, typename T4>
struct Type_List__4
{
 typedef T1 Type1;
 typedef T2 Type2;
 typedef T3 Type3;
 typedef T4 Type4;
};

template<typename Type_List_Type, int INTERCHANGE_Index, int TOTAL>
struct Interchange
{
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 0, 1>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__1<INTERCHANGE_Type> Result_Type;
 };
};


template<typename Type_List_Type>
struct Interchange<Type_List_Type, 0, 2>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__2<INTERCHANGE_Type, typename Type_List_Type::Type2> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 1, 2>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__2<typename Type_List_Type::Type1, INTERCHANGE_Type> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 0, 3>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__3<INTERCHANGE_Type, typename Type_List_Type::Type2, typename Type_List_Type::Type3> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 1, 3>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__3<typename Type_List_Type::Type1, INTERCHANGE_Type, typename Type_List_Type::Type3> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 2, 3>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__3<typename Type_List_Type::Type1, typename Type_List_Type::Type2, INTERCHANGE_Type> Result_Type;
 };
};


template<typename Type_List_Type>
struct Interchange<Type_List_Type, 0, 4>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__4<INTERCHANGE_Type, typename Type_List_Type::Type2,
    typename Type_List_Type::Type3, typename Type_List_Type::Type4> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 1, 4>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__4<typename Type_List_Type::Type1, INTERCHANGE_Type,
    typename Type_List_Type::Type3, typename Type_List_Type::Type4> Result_Type;
 };
};



template<typename Type_List_Type>
struct Interchange<Type_List_Type, 2, 4>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__4<typename Type_List_Type::Type1, typename Type_List_Type::Type2,
    INTERCHANGE_Type, typename Type_List_Type::Type3> Result_Type;
 };
};

template<typename Type_List_Type>
struct Interchange<Type_List_Type, 3, 4>
{
 template<typename INTERCHANGE_Type>
 struct With_Type
 {
  typedef Type_List__4<typename Type_List_Type::Type1, typename Type_List_Type::Type2,
    typename Type_List_Type::Type3, INTERCHANGE_Type> Result_Type;
 };
};




typedef Type_List__1<Cast_Needed> Type_List__1__All_Cast_Needed_Type;
typedef Type_List__2<Cast_Needed, Cast_Needed> Type_List__2__All_Cast_Needed_Type;
typedef Type_List__3<Cast_Needed, Cast_Needed, Cast_Needed> Type_List__3__All_Cast_Needed_Type;
typedef Type_List__4<Cast_Needed, Cast_Needed, Cast_Needed, Cast_Needed> Type_List__4__All_Cast_Needed_Type;

template<int i>
struct Type_List__All_Cast_Needed
{

};

template<>
struct Type_List__All_Cast_Needed<0>
{
 typedef No_Cast_Needed Type;
};

template<>
struct Type_List__All_Cast_Needed<1>
{
 typedef Type_List__1__All_Cast_Needed_Type Type;
};

template<>
struct Type_List__All_Cast_Needed<2>
{
 typedef Type_List__2__All_Cast_Needed_Type Type;
};

template<>
struct Type_List__All_Cast_Needed<3>
{
 typedef Type_List__3__All_Cast_Needed_Type Type;
};

template<>
struct Type_List__All_Cast_Needed<4>
{
 typedef Type_List__4__All_Cast_Needed_Type Type;
};



_KANS(CMD)

#endif //KCM_COMMAND_RUNTIME_ROUTER_CAST_SCHEDULE__H

