
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_NODE_PROXY__H
#define RZ_RE_NODE_PROXY__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include "accessors.h"

#include <functional>

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

class RE_Node_Proxy
{
 caon_ptr<RE_Node> node_;

public:

 RE_Node_Proxy(caon_ptr<RE_Node> node);
 ACCESSORS(caon_ptr<RE_Node> ,node)

};

_RZNS(RECore)


#endif //RZ_RE_NODE_PROXY__H
