
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_FRAME__H
#define RZ_RE_FRAME__H

#include "rz-re-frame.h"

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include "rzns.h"

RZNS_(RECore)


class RE_Frame : public node_frame<RE_Dominion>
{
 RE_Frame();

 public:

 static RE_Frame& instance();

};

_RZNS(RECore)

#endif //RZ_RE_FRAME__H
