
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_SRE_TOKEN__H
#define RZ_SRE_TOKEN__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-node-ptr.h"

#include "rz-graph-token/token/token-kinds.h"

#include <QString>
#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"


RZNS_(GRun)

 class RZ_Graph_Run_Token;

_RZNS(GRun)
USING_RZNS(GRun)



RZNS_(RECore)

class RE_Document;
class RE_Node;
class RE_Graph;

class RZ_SRE_Token
{
 caon_ptr<RZ_Graph_Run_Token> run_token_;
 caon_ptr<RE_Node> node_;

public:

 RZ_SRE_Token(caon_ptr<RZ_Graph_Run_Token> run_token, caon_ptr<RE_Node> node);

 ACCESSORS(caon_ptr<RZ_Graph_Run_Token> ,run_token)
 ACCESSORS(caon_ptr<RE_Node> ,node)

 QString text_value();
 QString node_label();

};

_RZNS(RECore)

#endif //RZ_SRE_TOKEN__H
