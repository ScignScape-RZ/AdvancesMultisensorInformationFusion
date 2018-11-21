
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_EXPRESSION_REVIEW__H
#define RZ_EXPRESSION_REVIEW__H

#include <QDebug>
#include <QStringList>

#include "flags.h"
#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GVal)


class RZ_Expression_Review
{

private:

 QString text_;
 caon_ptr<RE_Node> node_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,node)
 ACCESSORS(QString ,text)

 RZ_Expression_Review();

 void add_text(QString str);

};

_RZNS(GVal)

#endif //RZ_EXPRESSION_REVIEW__H

