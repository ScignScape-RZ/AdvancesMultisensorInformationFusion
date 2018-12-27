
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-function-def-entry.h"

#include "rzns.h"


USING_RZNS(RECore)

RE_Function_Def_Entry::RE_Function_Def_Entry(caon_ptr<RE_Node> prior_node,
  RE_Function_Def_Kinds kind, caon_ptr<RE_Node> label_node)
 : prior_node_(prior_node), kind_(kind), label_node_(label_node)
{

}


