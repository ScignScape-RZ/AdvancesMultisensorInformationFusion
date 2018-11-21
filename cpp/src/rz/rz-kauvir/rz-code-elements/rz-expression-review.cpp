
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-expression-review.h"

#include "rzns.h"


USING_RZNS(GVal)

RZ_Expression_Review::RZ_Expression_Review()
  :  node_(nullptr)
{
}

void RZ_Expression_Review::add_text(QString str)
{
 text_ += str + " ";
}
