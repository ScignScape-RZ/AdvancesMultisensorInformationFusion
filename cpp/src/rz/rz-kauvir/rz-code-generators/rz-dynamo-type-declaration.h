
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_TYPE_DECLARATION__H
#define RZ_DYNAMO_TYPE_DECLARATION__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>

#include <QVector>

#include <QTextStream>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

RZNS_(RECore)
 class RE_Node;
 class RE_Block_Entry;
_RZNS(RECore)

USING_RZNS(RECore)

RZNS_(GBuild)
 class RZ_Lisp_Graph_Visitor;
 class RZ_Lisp_Graph_Visitor_Dynamo;
_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(GVal)

class RZ_Dynamo_Form;
class RZ_Lisp_Graph_Lexical_Scope;
class RZ_Function_Def_Syntax;
class RZ_Lisp_Graph_Block_Info;
class RZ_Dynamo_Block;


class RZ_Dynamo_Type_Declaration
{
 RZ_Dynamo_Form& form_;

 QString cmd_;

public:

 RZ_Dynamo_Type_Declaration(RZ_Dynamo_Form& form);

 ACCESSORS(QString ,cmd)

 void write(QTextStream& qts);

};

_RZNS(GVal)

#endif //RZ_DYNAMO_TYPE_DECLARATION__H
