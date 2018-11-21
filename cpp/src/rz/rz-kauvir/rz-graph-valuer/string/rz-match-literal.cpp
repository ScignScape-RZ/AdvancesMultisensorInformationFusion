
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-match-literal.h"

#include "token/rz-lisp-token.h"


USING_RZNS(GVal)

RZ_Match_Literal::operator tString() const
{
 return to_string();
}

tString RZ_Match_Literal::to_string() const
{
 return tString("/-" + raw_string_ + "->");
}

bool RZ_Match_Literal::operator>(const RZ_Match_Literal& rhs) const
{
 return to_string() > rhs.to_string();
}

bool RZ_Match_Literal::operator<(const RZ_Match_Literal& rhs) const
{
 return to_string() < rhs.to_string();
}
