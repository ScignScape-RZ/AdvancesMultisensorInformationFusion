
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_SOURCE_FUNCTION__H
#define KCM_SOURCE_FUNCTION__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)


class KCM_Channel_Group;

class KCM_Statement;

class KCM_Expression;
class KCM_Statement;
class KCM_Lexical_Scope;
class Kauvir_Code_Model;
class KCM_Report_Syntax;

class KCM_Channel_Group;

class KCM_Source_Function
{
 QString full_name_;
 QString local_name_;
 quint64 cl_object_;
 KCM_Channel_Group* kcg_;

public:

 KCM_Source_Function(KCM_Channel_Group* kcg);

 ACCESSORS(QString ,full_name)
 ACCESSORS(QString ,local_name)
 ACCESSORS(quint64 ,cl_object)
 ACCESSORS(KCM_Channel_Group* ,kcg)


};


_KANS(KCM)


#endif //KCM_SOURCE_FUNCTION__H
