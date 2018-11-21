
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-sre-token.h"

#include "rz-graph-run/token/rz-graph-run-token.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"


USING_RZNS(RECore)

RZ_SRE_Token::RZ_SRE_Token(caon_ptr<RZ_Graph_Run_Token> run_token,
  caon_ptr<RE_Node> node)
 : run_token_(run_token), node_(node)
{

}

QString RZ_SRE_Token::text_value()
{
 if(run_token_)
  return run_token_->text_value();
 return QString();
}

QString RZ_SRE_Token::node_label()
{
 if(node_)
  return node_->label();
 return QString();
}

