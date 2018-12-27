
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-connection.h"


#include "rzns.h"
USING_RZNS(RECore)

RE_Connection::RE_Connection(caon_ptr<RE_Node> re_node)
 : re_node_(re_node)
{

}
