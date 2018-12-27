
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_ROOT__H
#define RZ_RE_ROOT__H


#include "relae-graph/relae-node-ptr.h"

#include "rz-re-dominion.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Document;

class RE_Root
{
 RE_Document* document_;

public:

 RE_Root(RE_Document* document);

 QString document_path();
};

_RZNS(RECore)


#endif //RZ_RE_ROOT__H
