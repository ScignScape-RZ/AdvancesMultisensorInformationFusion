
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_EXPRESSION__H
#define KCM_EXPRESSION__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)

class KCM_Channel_Group;
class Kauvir_Code_Model;
class KCM_Report_Syntax;
class KCM_Statement;
class KCM_Callable_Value;

class KCM_Expression
{
 const Kauvir_Type_Object* kauvir_type_object_;
 KCM_Channel_Group* channel_group_;

 QString kcm_code_;

 KCM_Statement* implied_statement_;

 // // temporary? ...
 KCM_Callable_Value* ref_anon_;


public:

 KCM_Expression(QString kcm_code, KCM_Channel_Group* channel_group);
 KCM_Expression(KCM_Channel_Group* channel_group);
 KCM_Expression(KCM_Statement* implied_statement);

 ACCESSORS(KCM_Channel_Group* ,channel_group)
 ACCESSORS(QString ,kcm_code)
 ACCESSORS(KCM_Statement* ,implied_statement)
 ACCESSORS(KCM_Callable_Value* ,ref_anon)

 void report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs);

};


_KANS(KCM)


#endif //KCM_EXPRESSION__H
