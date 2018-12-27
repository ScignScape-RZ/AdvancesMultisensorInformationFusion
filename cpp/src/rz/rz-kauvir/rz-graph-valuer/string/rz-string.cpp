
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "token/rz-lisp-token.h"

#include "rz-string.h"

USING_RZNS(GVal)

RZ_String::operator tString() const
{
 return to_string();
}

tString RZ_String::to_string() const
{
 if(flags.has_raw_string)
  return tString('"' + raw_string_ + '"');
 return token_->string_value();
}

bool RZ_String::operator>(const RZ_String& rhs) const
{
 return to_string() > rhs.to_string();
}

bool RZ_String::operator<(const RZ_String& rhs) const
{
 return to_string() < rhs.to_string();
}
