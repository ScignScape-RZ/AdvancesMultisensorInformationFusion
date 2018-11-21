
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_OPAQUE_CALL__H
#define RZ_OPAQUE_CALL__H

#include "accessors.h"

#include <QString>
#include <QDebug>

#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GVal)

class RZ_Opaque_Call
{
private:

 typedef RE_Node tNode;

 caon_ptr<tNode> entry_node_;
 caon_ptr<tNode> pre_entry_node_;

public:

 ACCESSORS(caon_ptr<tNode> ,entry_node)
 ACCESSORS(caon_ptr<tNode> ,pre_entry_node)

 RZ_Opaque_Call(caon_ptr<tNode> pre_entry_node,
  caon_ptr<tNode> entry_node);

 caon_ptr<RZ_Lisp_Token> get_entry_token();

 template<typename T>
 void operator<<(T& t)
 {
 }

 template<typename T>
 friend void operator<<(T& t, RZ_Opaque_Call&)
 {
 }

 friend void operator<<(QDebug qd, RZ_Opaque_Call&)
 {
  qd << "<opaque>";
 }

};

_RZNS(GVal)

#endif //RZ_OPAQUE_CALL__H
