
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RZ_RE_GRAMMAR__H
#define RZ_RE_GRAMMAR__H

#include "relae-graph/relae-grammar.h"

#include "kernel/rz-re-dominion.h"

#include "rzns.h"


RZNS_(RECore)

class RE_Graph;
class RE_Graph_Build;
class RE_Parser;

class RE_Grammar : public Relae_Grammar<RE_Graph, RE_Parser>
{
public:

 RE_Grammar();



 void init(RE_Parser& p, RE_Graph& g,
           RE_Graph_Build& graph_build);


};

_RZNS(RECore)

#endif //RZ_RE_GRAMMAR__H
