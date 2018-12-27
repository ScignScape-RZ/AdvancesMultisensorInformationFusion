
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-query.h"

#include "rzns.h"


USING_RZNS(RECore)


RE_Query::RE_Query()
 : node_query<RE_Dominion>()
  #define DOMINION_CONNECTOR(name, label) \
    ,name(RE_Connectors(RE_Connectors_Case_Labels::name, label))
  #include "kernel/dominion/connectors.h"
  #undef DOMINION_CONNECTOR
{
 int order = 0;
 #define DOMINION_CONNECTOR(name, label) \
  name.order = order; \
  ++order;
 #include "kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
}

const RE_Query& RE_Query::instance()
{
 static RE_Query* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RE_Query;
 return *the_instance;
}
