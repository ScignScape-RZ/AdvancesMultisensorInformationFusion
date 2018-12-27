
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-frame.h"

#include "kernel/graph/rz-re-node.h"

#include "rzns.h"

#include <QDebug>


USING_RZNS(RECore)

RE_Frame::RE_Frame()
 : node_frame<RE_Dominion>()
{


}

RE_Frame& RE_Frame::instance()
{
 static RE_Frame* the_instance = nullptr;
 if(!the_instance)
  the_instance = new RE_Frame;
 return *the_instance;
}
