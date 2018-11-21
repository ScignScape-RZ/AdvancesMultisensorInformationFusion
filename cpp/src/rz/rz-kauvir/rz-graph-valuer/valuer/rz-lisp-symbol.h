
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_SYMBOL__H
#define RZ_LISP_SYMBOL__H

#include "accessors.h"
#include "flags.h"


#include "relae-graph/relae-caon-ptr.h"

#include <QString>

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GVal)

class RZ_Lisp_Symbol
{
private:

 caon_ptr<RE_Node> node_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,node)

 RZ_Lisp_Symbol(caon_ptr<RE_Node> n);

 template<typename T>
 friend void operator<<(T& t, RZ_Lisp_Symbol& sym)
 {}

};

_RZNS(GVal)

#endif //RZ_LISP_SYMBOL__H
