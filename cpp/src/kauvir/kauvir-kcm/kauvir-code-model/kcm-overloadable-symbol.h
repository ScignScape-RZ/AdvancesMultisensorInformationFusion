
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_OVERLOADALE_SYMBOL__H
#define KCM_OVERLOADALE_SYMBOL__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QString>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)


class KCM_Channel_Group;
class Kauvir_Code_Model;
class KCM_Report_Syntax;

class KCM_Overloadable_Symbol
{
 QString symbol_name_;
 int overload_index_;

public:


 KCM_Overloadable_Symbol(QString symbol_name, int overload_index);
 KCM_Overloadable_Symbol();


 ACCESSORS(QString ,symbol_name)
 ACCESSORS(int ,overload_index)

 void report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs);

 QString encode_to_symbol_name() const;

};


_KANS(KCM)


#endif //KCM_OVERLOADABLE_SYMBOL__H
