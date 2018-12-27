
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QString>
#include <QMap>

#include <QStringList>

#include "rz-lisp-graph-lexical-scope.h"

#include "rz-graph-token/token/rz-lisp-token.h"

USING_RZNS(GVal)

void RZ_Lisp_Graph_Lexical_Scope::add_symbol(RZ_Lisp_Token& tok)
{
 symbols_.insert(tok.raw_text(), RZ_Lisp_Graph_Scope_Token(&tok));
}

void RZ_Lisp_Graph_Lexical_Scope::add_channel_symbol_from_symbol_name(QString name, QString channel_code)
{
 symbols_.insert(name, RZ_Lisp_Graph_Scope_Token(channel_code));
}

QString RZ_Lisp_Graph_Lexical_Scope::channel_code_for_symbol_name(QString name)
{
 const RZ_Lisp_Graph_Scope_Token& tok = symbols_[name];
 return tok.channel_code();
}

void RZ_Lisp_Graph_Lexical_Scope::add_symbol(RZ_Lisp_Token& function_token,
 RZ_Lisp_Token& tok)
{
 symbols_.insert(tok.raw_text(), RZ_Lisp_Graph_Scope_Token(function_token, tok));
 symbol_order_.push_back(tok.raw_text());
}


void RZ_Lisp_Graph_Lexical_Scope::add_type_named_symbol(RZ_Lisp_Token& function_token,
 RZ_Lisp_Token& tok, QString type_name)
{
 symbols_.insert(tok.raw_text(), RZ_Lisp_Graph_Scope_Token(function_token, tok, type_name));
 symbol_order_.push_back(tok.raw_text());
}



void RZ_Lisp_Graph_Lexical_Scope::add_function_symbol(RZ_Lisp_Token& tok)
{
 RZ_Lisp_Graph_Scope_Token st(&tok);
 function_symbols_.insert(tok.raw_text(), st);
 symbol_order_.push_back(tok.raw_text());
}


void RZ_Lisp_Graph_Lexical_Scope::add_annotations(RZ_Lisp_Token& tok, QStringList& sl)
{
 for(QString qs : sl)
  annotations_.insert(tok.raw_text(), qs);
}

QStringList RZ_Lisp_Graph_Lexical_Scope::get_annotations(RZ_Lisp_Token& tok)
{
 return annotations_.values(tok.raw_text());
}

QStringList RZ_Lisp_Graph_Lexical_Scope::get_annotations(QString key)
{
 return annotations_.values(key);
}


void RZ_Lisp_Graph_Lexical_Scope::mark_value_node(const RZ_Lisp_Token& tok,
 RE_Node& value_node)
{
 if(symbols_.contains(tok.raw_text()))
 {
  symbols_[tok.raw_text()].set_value_node(&value_node);
 }
}

void RZ_Lisp_Graph_Lexical_Scope::relocate_function_symbol(const RZ_Lisp_Token& tok,
 RE_Node& value_node)
{
 QString s = tok.raw_text();
 if(symbols_.contains(s))
 {
  RZ_Lisp_Graph_Scope_Token& st = symbols_[s];
  function_symbols_[s] = st;
  st.set_value_node(&value_node);
 }
}


void RZ_Lisp_Graph_Lexical_Scope::mark_value(const RZ_Lisp_Token& tok,
 RZ_Lisp_Graph_Value_Holder& vh)
{
 if(symbols_.contains(tok.raw_text()))
 {
  symbols_[tok.raw_text()].set_vh(vh);
 }
}

RZ_Lisp_Graph_Scope_Token* RZ_Lisp_Graph_Lexical_Scope::contains_function_symbol_without_parent(QString symbol_name)
{
 if(function_symbols_.contains(symbol_name))
 {
  return &function_symbols_[symbol_name];
 }
 return nullptr;
}

RZ_Lisp_Graph_Scope_Token* RZ_Lisp_Graph_Lexical_Scope::contains_symbol_without_parent(QString symbol_name)
{
 if(symbols_.contains(symbol_name))
 {
  return &symbols_[symbol_name];
 }
 return nullptr;
}

RZ_Lisp_Graph_Scope_Token* RZ_Lisp_Graph_Lexical_Scope::contains_function_symbol(QString symbol_name)
{
 RZ_Lisp_Graph_Scope_Token* result = contains_function_symbol_without_parent(symbol_name);
 if(result)
  return result;
 if(parent_)
 {
  return parent_->contains_function_symbol(symbol_name);
 }
 return nullptr;
}


RZ_Lisp_Graph_Scope_Token* RZ_Lisp_Graph_Lexical_Scope::contains_symbol(QString symbol_name)
{
 RZ_Lisp_Graph_Scope_Token* result = contains_symbol_without_parent(symbol_name);
 if(result)
  return result;
 if(parent_)
 {
  return parent_->contains_symbol(symbol_name);
 }
 return nullptr;
}


void RZ_Lisp_Graph_Lexical_Scope::mark_type_assertion(const RZ_Lisp_Token& tok,
 QString ta)
{
 if(symbols_.contains(tok.raw_text()))
 {
  symbols_[tok.raw_text()].set_declared_type_name(ta);
 }
}


RZ_Lisp_Graph_Lexical_Scope::RZ_Lisp_Graph_Lexical_Scope(caon_ptr<RZ_Lisp_Graph_Lexical_Scope> p)
 : parent_(p)
{}

