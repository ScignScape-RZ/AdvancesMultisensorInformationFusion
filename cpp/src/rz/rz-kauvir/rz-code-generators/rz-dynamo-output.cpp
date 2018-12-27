
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-output.h"
#include "rzns.h"

#include "rz-dynamo-block.h"

USING_RZNS(GVal)

RZ_Dynamo_Output::RZ_Dynamo_Output(RZ_Lisp_Graph_Visitor_Dynamo& visitor_dynamo)
  :  visitor_dynamo_(visitor_dynamo), top_level_block_(nullptr)
{
}

void RZ_Dynamo_Output::init_function_def_syntax()
{
}

void RZ_Dynamo_Output::init_top_level_block()
{
 top_level_block_ = new RZ_Dynamo_Block();
}


void RZ_Dynamo_Output::write(QTextStream& qts)
{
 if(top_level_block_)
 {
  top_level_block_->scan_top_level(visitor_dynamo_);
  top_level_block_->write(qts);
 }
}
