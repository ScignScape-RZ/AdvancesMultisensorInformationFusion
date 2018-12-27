
#include "rz-re-prerun-anticipate.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"

#include "rz-graph-core/kernel/graph/rz-re-graph.h"

USING_RZNS(RECore)
USING_RZNS(GBuild)


//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

RE_Prerun_Anticipate::RE_Prerun_Anticipate(RZ_Lisp_Graph_Visitor& visitor)
 : visitor_(visitor)
{

}

void RE_Prerun_Anticipate::scan(std::function<void(RZ_Dynamo_Output&)> fn)
{
 visitor_.anticipate(fn);
}
