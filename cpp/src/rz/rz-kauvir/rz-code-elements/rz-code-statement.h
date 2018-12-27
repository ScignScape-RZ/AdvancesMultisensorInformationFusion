
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_CODE_STATEMENT__H
#define RZ_CODE_STATEMENT__H

#include <QDebug>
#include <QStringList>

#include "flags.h"
#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GVal)


class RZ_Code_Statement
{
public:

 enum class Statement_Kinds {
  N_A, Type_Declaration, Assignment, Expression, Partial

 };

private:

 Statement_Kinds statement_kind_;

 caon_ptr<RE_Node> node_;

 QString annotation_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,node)
 ACCESSORS(QString ,annotation)

 RZ_Code_Statement(Statement_Kinds statement_kind, caon_ptr<RE_Node> node);

 QString kind_to_string();

};

_RZNS(GVal)

#endif //RZ_CODE_STATEMENT__H

