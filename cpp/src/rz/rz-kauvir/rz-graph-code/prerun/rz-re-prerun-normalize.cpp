
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-prerun-normalize.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"

#include "rz-graph-core/kernel/graph/rz-re-graph.h"

USING_RZNS(RECore)
USING_RZNS(GBuild)


RE_Prerun_Normalize::RE_Prerun_Normalize(RE_Graph& graph)
 : graph_(graph)
{

}

caon_ptr<RZ_Lisp_Graph_Visitor> RE_Prerun_Normalize::scan()
{
 caon_ptr<RZ_Lisp_Graph_Visitor> result = new RZ_Lisp_Graph_Visitor(&graph_);
 scan(*result);
 return result;
}

void RE_Prerun_Normalize::scan(RZ_Lisp_Graph_Visitor& v)
{
 v.set_graph(&graph_);
 v.normalize();
 v.hyper_normalize();
}

