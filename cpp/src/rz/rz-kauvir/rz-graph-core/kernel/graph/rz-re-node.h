
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_NODE__H
#define RZ_RE_NODE__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include "kernel/frame/rz-re-frame.h"

#include "accessors.h"

#include <functional>

#include <QVector>

#include "rzns.h"


RZNS_(GBuild)

 class RZ_Lisp_Token;

_RZNS(GBuild)


RZNS_(RECore)

USING_RZNS(GBuild)

class RE_Node : public node_ptr<RE_Dominion>
{

 QVector<caon_ptr<RE_Node>> hyponodes_;
 caon_ptr<RE_Node> parent_;

public:

 #define DOMINION_TYPE DOMINION_NODE_CONSTRUCTOR
 #include "kernel/dominion/types.h"
 #undef DOMINION_TYPE

 ACCESSORS__RGET(QVector<caon_ptr<RE_Node>> ,hyponodes)
 ACCESSORS(caon_ptr<RE_Node> ,parent)

 caon_ptr<RZ_Lisp_Token> lisp_token();

 void debug_connections();

 void each_connection(std::function<void(const RE_Connectors& connector,
  const RE_Node&, const RE_Connection* connection)> fn)  const;

 void swap_relation(const RE_Connectors& connector,
  caon_ptr<RE_Node> n1, caon_ptr<RE_Node> n2);

 void delete_relation(const RE_Connectors& connector,
  caon_ptr<RE_Node> n1);

 void add_hyponode(caon_ptr<RE_Node> n);


};

_RZNS(RECore)


#endif //RZ_RE_NODE__H
