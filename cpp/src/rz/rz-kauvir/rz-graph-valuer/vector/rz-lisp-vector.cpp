
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-vector.h"

#include "valuer/rz-lisp-graph-valuer.h"

#include "rz-graph-core/tuple/rz-re-tuple-info.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rzns.h"


USING_RZNS(GVal)

RZ_Lisp_Vector::RZ_Lisp_Vector(caon_ptr<RE_Tuple_Info> tuple_info, RZ_Type_Object& rto)
 : Flags(0), tuple_info_(tuple_info)
{
 token_representation_ = new RZ_Lisp_Token(tuple_info_->token_representation());
 token_representation_->flags.is_token_representation = true;
 token_representation_->set_value(caon_ptr<RZ_Lisp_Vector>(this));
 token_representation_->set_type_object(rto);
}

caon_ptr<RZ_Lisp_Vector::tNode> RZ_Lisp_Vector::get_call_entry_node()
{
 if(tuple_info_)
  return tuple_info_->call_entry_node();
 return nullptr;
}


void RZ_Lisp_Vector::to_string_list(QStringList& qsl, RZ_Lisp_Graph_Valuer& valuer)
{
 QVectorIterator<caon_ptr<tNode>> it(nodes_);
 while(it.hasNext())
 {
  caon_ptr<tNode> n = it.next();
  qsl.push_back(valuer.node_to_string(*n));
 }
}



void RZ_Lisp_Vector::add_node(caon_ptr<tNode> n)
{
 nodes_.push_back(n);

}
