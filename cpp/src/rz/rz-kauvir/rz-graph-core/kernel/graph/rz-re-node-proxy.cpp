
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-node-proxy.h"

#include "token/rz-re-token.h"

#include "rzns.h"

USING_RZNS(RECore)

RE_Node_Proxy::RE_Node_Proxy(caon_ptr<RE_Node> node)
  : node_(node)
{

}
