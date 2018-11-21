
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_QUERY__H
#define RZ_RE_QUERY__H

#include "kernel/rz-re-dominion.h"

#include "relae-graph/relae-node-ptr.h"

#include "rzns.h"

RZNS_(RECore)


class RE_Query : public node_query<RE_Dominion>
{
 RE_Query();

 public:
  #define DOMINION_CONNECTOR(name, label) \
   RE_Connectors name;
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR

 static const RE_Query& instance();
};

_RZNS(RECore)

#endif //RZ_RE_QUERY__H
