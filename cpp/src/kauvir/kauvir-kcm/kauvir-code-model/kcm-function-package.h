
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_FUNCTION_PACKAGE__H
#define KCM_FUNCTION_PACKAGE__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)

class KCM_Channel_Group;
class KCM_Type_Object;

class KCM_Function_Package
{
 KCM_Channel_Group* kcg_;
 quint32 byte_code_;

public:

 KCM_Function_Package(KCM_Channel_Group* kcg);

 ACCESSORS(KCM_Channel_Group* ,kcg)
 ACCESSORS(quint32 ,byte_code)

 void init_byte_code_s1(bool sr = false);
 void init_byte_code_s0(bool sr = false);
 void init_byte_code_s10(bool sr = false);

 void init_byte_code(int head);

 int split_byte_code(int& xbc);

 const KCM_Type_Object* result_type_object();

};


_KANS(KCM)


#endif //KCM_FUNCTION_PACKAGE__H
