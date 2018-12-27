
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-parse-context.h"

USING_RZNS(RECore)


RE_Parse_Context::RE_Parse_Context(): Flags(0),
  current_open_print_node_(nullptr)
{

}


