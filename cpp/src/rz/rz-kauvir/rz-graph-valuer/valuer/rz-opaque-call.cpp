
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-opaque-call.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"


USING_RZNS(GVal)

RZ_Opaque_Call::RZ_Opaque_Call(caon_ptr<tNode> pre_entry_node,
  caon_ptr<tNode> entry_node)
 : pre_entry_node_(pre_entry_node), entry_node_(entry_node)
{

}

caon_ptr<RZ_Lisp_Token> RZ_Opaque_Call::get_entry_token()
{
 caon_ptr<RZ_Lisp_Token> result = nullptr;
 CAON_PTR_DEBUG(RE_Node ,entry_node_)
 result = entry_node_->lisp_token();
 return result;
}
