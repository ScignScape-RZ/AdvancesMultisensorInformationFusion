
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_BLOCK__H
#define KCM_BLOCK__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)


class KCM_Channel_Group;
class KCM_Report_Syntax;

class Kauvir_Code_Model;

class KCM_Statement;

class KCM_Expression;
class KCM_Statement;
class KCM_Lexical_Scope;

class KCM_Block
{
 QVector<KCM_Statement*> statements_;

 KCM_Lexical_Scope* lexical_scope_;

public:

 KCM_Block(KCM_Lexical_Scope* lexical_scope);

 ACCESSORS(KCM_Lexical_Scope* ,lexical_scope)

 void add_statement(KCM_Statement* statement);


};


_KANS(KCM)


#endif //KCM_BLOCK__H
