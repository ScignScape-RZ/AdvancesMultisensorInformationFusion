
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-node.h"

#include "token/rz-re-token.h"

#include "rzns.h"

USING_RZNS(RECore)

void RE_Node::each_connection(std::function<void(const RE_Connectors& connector,
 const RE_Node&, const RE_Connection* connection)> fn) const
{
 targets_iterator_type it(targets_);
 while(it.hasNext())
 {
  it.next();
  const RE_Connectors& connector = *it.key();
  const RE_Node& target = *it.value();
  fn(connector, target, nullptr);
 }

 annotated_targets_iterator_type ait(annotated_targets_);
 while(ait.hasNext())
 {
  ait.next();
  const RE_Connectors& connector = *ait.key();
  const RE_Connection* connection = ait.value().first.raw_pointer();
  const RE_Node& target = *ait.value().second;
  fn(connector, target, connection);

 }

}


caon_ptr<RZ_Lisp_Token> RE_Node::lisp_token()
{
 if(re_token())
 {
  return re_token()->lisp_token();
 }
 return nullptr;
}

void RE_Node::debug_connections()
{
 targets_iterator_type it(targets_);
 while(it.hasNext())
 {
  it.next();
  CAON_EVALUATE_DEBUG(RE_Connectors ,key ,it.key())
  CAON_EVALUATE_DEBUG(RE_Node ,value ,it.value())

 }
}

void RE_Node::add_hyponode(caon_ptr<RE_Node> n)
{
 hyponodes_.push_back(n);
}


void RE_Node::swap_relation(const RE_Connectors& connector,
 caon_ptr<RE_Node> n1, caon_ptr<RE_Node> n2)
{
 CAON_PTR_DEBUG(RE_Node ,n1)
 CAON_PTR_DEBUG(RE_Node ,n2)


 #ifdef NO_CAON
   RE_Connectors* pc = const_cast<RE_Connectors*>( &connector );
   targets_.remove(pc, n1);
   targets_.insert(pc, n2);
 #else
  targets_.remove(&connector, n1);
  targets_.insert(&connector, n2);
 #endif //NO_CAON

}


void RE_Node::delete_relation(const RE_Connectors& connector,
 caon_ptr<RE_Node> n1)
{
 CAON_PTR_DEBUG(RE_Node ,n1)
  #ifdef NO_CAON
    RE_Connectors* pc = const_cast<RE_Connectors*>( &connector );
    targets_.remove(pc, n1);
  #else
   targets_.remove(&connector, n1);
  #endif //NO_CAON
}

