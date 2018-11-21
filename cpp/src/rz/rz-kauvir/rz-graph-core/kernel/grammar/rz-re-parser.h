
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_PARSER__H
#define RZ_RE_PARSER__H

#include "relae-graph/relae-parser.h"

#include "kernel/rz-re-dominion.h"

#include "rzns.h"
RZNS_(RECore)

class RE_Graph;

class RE_Parser : public Relae_Parser<RE_Galaxy>
{
 QString raw_text_;

public:

 ACCESSORS(QString ,raw_text)

 RE_Parser(caon_ptr<RE_Graph> g);

};

_RZNS(RECore)

#endif //RZ_RE_PARSER__H
