
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-graph-scope-token.h"

#include "token/rz-lisp-token.h"

USING_RZNS(GVal)
USING_RZNS(GBuild)

RZ_Lisp_Graph_Scope_Token::RZ_Lisp_Graph_Scope_Token(QString channel_code)
 : channel_code_(channel_code), function_token_(nullptr),
   declaration_token_(nullptr), value_node_(nullptr)
{

}



RZ_Lisp_Graph_Scope_Token::RZ_Lisp_Graph_Scope_Token(caon_ptr<RZ_Lisp_Token> f,
  caon_ptr<RZ_Lisp_Token> d, caon_ptr<RE_Node> n)
 : function_token_(f), declaration_token_(d), value_node_(n)
{

}

RZ_Lisp_Graph_Scope_Token::RZ_Lisp_Graph_Scope_Token(RZ_Lisp_Token& f, RZ_Lisp_Token& d)
 :  function_token_(&f), declaration_token_(&d), value_node_(nullptr)
{

}


RZ_Lisp_Graph_Scope_Token::RZ_Lisp_Graph_Scope_Token(RZ_Lisp_Token& f, RZ_Lisp_Token& d,
  QString dtn, caon_ptr<RE_Node> n)
 : function_token_(&f), declaration_token_(&d), declared_type_name_(dtn), value_node_(n)
{

}


QString RZ_Lisp_Graph_Scope_Token::value_to_string() const
{
 return vh_.to_string();
}

QString RZ_Lisp_Graph_Scope_Token::type_to_string() const
{
 if(declared_type_name_.isEmpty())
  return vh_.type_to_string();
 else
 {
  return declared_type_name_;
 }
}


bool RZ_Lisp_Graph_Scope_Token::type_matches(caon_ptr<RZ_Type_Object> rto) const
{
 return vh_.type_object() == rto;
}

QString RZ_Lisp_Graph_Scope_Token::value_to_string(QString& type, RZ_Type_Variety&) const
{
 return value_to_string(type);
}


QString RZ_Lisp_Graph_Scope_Token::value_to_string(QString& type) const
{
 if(declared_type_name_.isEmpty())
  return vh_.to_string_with_type(type);
 else
 {
  type = declared_type_name_;
  return vh_.to_string();
 }
}

QString RZ_Lisp_Graph_Scope_Token::value_to_lisp_string() const
{
 const RZ_Type_Object& rto = *vh_.type_object();
 if(rto.id() == RZ_Run_Types::Opc)
 {
  return "nil";
 }
 else if(rto.name() == "Vec")
 {
  return "nil";
 }
 else if(rto.id() == RZ_Run_Types::FnDefInfo)
 {
  return "nil";
 }
 return vh_.to_lisp_string();
}

Basic_Token_Kinds RZ_Lisp_Graph_Scope_Token::initial_kind_and_string_value(QString& result) const
{
 CAON_PTR_DEBUG(RZ_Lisp_Token ,function_token_)
 CAON_PTR_DEBUG(RZ_Lisp_Token ,declaration_token_)

 result = value_to_lisp_string();
 return Basic_Token_Kinds::Symbol_Token;
}

