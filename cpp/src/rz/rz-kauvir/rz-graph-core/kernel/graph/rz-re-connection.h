
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_CONNECTION__H
#define RZ_RE_CONNECTION__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include <QTextStream>

#include "rzns.h"
#include "accessors.h"

RZNS_(RECore)

class Run_Call_Entry;
class RE_Node;

class RE_Connection
{
 caon_ptr<RE_Node> re_node_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,re_node)

 RE_Connection(caon_ptr<RE_Node> re_node);



};


_RZNS(RECore)

#endif //RZ_RE_CONNECTION__H

