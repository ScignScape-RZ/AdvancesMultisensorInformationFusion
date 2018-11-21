
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-opaque-type-symbol.h"


#include "rz-graph-core/kernel/graph/rz-re-node.h"

#include "token/rz-lisp-token.h"

USING_RZNS(GVal)
USING_RZNS(GBuild)

caon_ptr<RZ_Opaque_Type_Symbol::tNode> RZ_Opaque_Type_Symbol::get_node()
{
 return reinterpret_cast<tNode*>(this);
}


caon_ptr<RZ_Lisp_Token> RZ_Opaque_Type_Symbol::get_token()
{
 return get_node()->lisp_token();
}

QString RZ_Opaque_Type_Symbol::get_name()
{
 return get_node()->lisp_token()->string_value();
}

