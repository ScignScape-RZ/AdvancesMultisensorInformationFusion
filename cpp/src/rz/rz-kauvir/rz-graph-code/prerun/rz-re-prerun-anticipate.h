
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_PRERUN_ANTICIPATE__H
#define RZ_RE_PRERUN_ANTICIPATE__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-node-ptr.h"

#include "output/rz-re-lisp-output.h"

#include "rz-graph-core/kernel/graph/rz-re-graph.h"

#include <QString>
#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"

RZNS_(GBuild)
class RZ_Lisp_Graph_Visitor;
_RZNS(GBuild)
USING_RZNS(GBuild)


RZNS_(GVal)
class RZ_Dynamo_Output;
_RZNS(GVal)
USING_RZNS(GVal)



RZNS_(RECore)


class RE_Document;
class RE_Node;
class RE_Graph;


class RE_Prerun_Anticipate
{
 RZ_Lisp_Graph_Visitor& visitor_;

public:

 RE_Prerun_Anticipate(RZ_Lisp_Graph_Visitor& visitor);

 void scan(std::function<void(RZ_Dynamo_Output&)> fn);

};

_RZNS(RECore)

#endif //RZ_RE_PRERUN_ANTICIPATE__H
