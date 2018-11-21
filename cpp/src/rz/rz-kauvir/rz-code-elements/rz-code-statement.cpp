
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-code-statement.h"

#include "rzns.h"


USING_RZNS(GVal)

RZ_Code_Statement::RZ_Code_Statement(Statement_Kinds statement_kind,
                                     caon_ptr<RE_Node> node)
  :  statement_kind_(statement_kind), node_(node)
{
}

QString RZ_Code_Statement::kind_to_string()
{
 switch(statement_kind_)
 {
 case Statement_Kinds::Type_Declaration:
  return "Type Declaration";
 case Statement_Kinds::Assignment:
  return "Assignment";
 case Statement_Kinds::Expression:
  return "Expression";
 case Statement_Kinds::Partial:
  return "Partial";
 default:
  return "??";
 }

}
