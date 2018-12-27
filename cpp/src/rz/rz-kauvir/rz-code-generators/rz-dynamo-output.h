
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_OUTPUT__H
#define RZ_DYNAMO_OUTPUT__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>

#include <QTextStream>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-function-def/rz-function-def-syntax.h"



RZNS_(GBuild)
 class RZ_Lisp_Graph_Visitor;
 class RZ_Lisp_Graph_Visitor_Dynamo;
_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(GVal)

class RZ_Dynamo_Block;



class RZ_Dynamo_Output
{

 RZ_Lisp_Graph_Visitor_Dynamo& visitor_dynamo_;
 RZ_Lisp_Graph_Visitor& visitor();

 caon_ptr<RZ_Dynamo_Block> top_level_block_;

 void init_function_def_syntax();

public:

 RZ_Dynamo_Output(RZ_Lisp_Graph_Visitor_Dynamo& visitor_dynamo);

 void write(QTextStream& qts);

 void init_top_level_block();

};

_RZNS(GVal)

#endif //RZ_DYNAMO_OUTPUT__H
