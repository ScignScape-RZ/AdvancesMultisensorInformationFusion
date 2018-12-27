
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_GRAPH__H
#define RZ_RE_GRAPH__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include <QTextStream>

#include "rzns.h"

RZNS_(RECore)


class RE_Graph : public node_graph<RE_Dominion>
{
 public:
  RE_Graph(caon_ptr<RE_Node> root_node = nullptr);

 void report(QTextStream& qts);
 void report_from_node(QTextStream& qts,
  const RE_Node& node, int indent = 0);

};

_RZNS(RECore)


#endif //RZ_RE_GRAPH__H
