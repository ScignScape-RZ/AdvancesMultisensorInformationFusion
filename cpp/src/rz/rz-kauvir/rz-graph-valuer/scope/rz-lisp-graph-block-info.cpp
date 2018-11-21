
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QString>
#include <QMap>

#include <QStringList>

#include "rz-lisp-graph-block-info.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"
#include "rz-graph-core/code/rz-re-block-entry.h"


USING_RZNS(GVal)

RZ_Lisp_Graph_Block_Info::RZ_Lisp_Graph_Block_Info(caon_ptr<RE_Node> block_entry_node, caon_ptr<RZ_Lisp_Graph_Block_Info> parent_block_info)
 : block_entry_node_(block_entry_node), continue_node_(nullptr), iterator_count_(0),
   allocation_count_(increment_allocation_count()),
   child_block_info_(nullptr), parent_block_info_(parent_block_info)
{

}



void RZ_Lisp_Graph_Block_Info::add_assignment_count(QString sym)
{
 ++assignment_counts_[sym];
}


QString RZ_Lisp_Graph_Block_Info::symbol_string(QString sym)
{
 int c = assignment_counts_.value(sym, 0);
 if(c > 0)
 {
  sym += QString("'%1").arg(c);
 }
 return sym;
}

void RZ_Lisp_Graph_Block_Info::reset_iterator()
{
 iterator_count_ = 0;
}

caon_ptr<RZ_Lisp_Graph_Block_Info> RZ_Lisp_Graph_Block_Info::has_returns_assignments()
{
 if(returns_assignments_.isEmpty())
 {
  if(child_block_info_)
  {
   return child_block_info_->has_returns_assignments();
  }
  return nullptr;
 }
 return this;
}

bool RZ_Lisp_Graph_Block_Info::needs_else()
{
 if(block_entry_node_)
 {
  if(caon_ptr<RE_Block_Entry> rbe = block_entry_node_->re_block_entry())
  {
   return (rbe->flags.if_block) && !(rbe->flags.has_else_block);
  }
 }
 return false;
}


bool RZ_Lisp_Graph_Block_Info::check_final_iterator()
{
 ++iterator_count_;
 int total = assignments_.size() + returns_assignments_.size();
 return iterator_count_ == total;
}

void RZ_Lisp_Graph_Block_Info::add_assignment(caon_ptr<RE_Node> key, const RZ_Lisp_Graph_Value_Holder& vh)
{
 assignments_[key] = vh;
 assignment_order_.push_back(key);
}

void RZ_Lisp_Graph_Block_Info::add_returns_assignment(const RZ_Lisp_Graph_Value_Holder& vh)
{
 returns_assignments_.push_back(vh);
}
