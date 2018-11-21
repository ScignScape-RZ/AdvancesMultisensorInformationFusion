
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_OPAQUE_TYPE_SYMBOL__H
#define RZ_OPAQUE_TYPE_SYMBOL__H

#include "accessors.h"

#include <QString>
#include <QDebug>


#include "relae-graph/relae-caon-ptr.h"
#include "flags.h"

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

class RZ_Opaque_Type_Symbol
{
private:

 typedef RE_Node tNode;


public:

 QString get_name();
 caon_ptr<tNode> get_node();

 caon_ptr<RZ_Lisp_Token> get_token();

 template<typename T>
 void operator<<(T& t)
 {
 }

 template<typename T>
 friend void operator<<(T& t, RZ_Opaque_Type_Symbol&)
 {
 }

 friend void operator<<(QDebug qd, RZ_Opaque_Type_Symbol& ots)
 {
  qd << "<opaque type symbol>" << ots.get_name();
 }

};

_RZNS(GVal)

#endif //RZ_OPAQUE_TYPE_SYMBOL__H
