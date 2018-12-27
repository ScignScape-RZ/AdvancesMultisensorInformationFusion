
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-graph-embed-token.h"
#include "rz-graph-embed-package.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-run/token/rz-graph-run-token.h"

#include <QStringList>


USING_RZNS(GEmbed)

RZ_Graph_Embed_Token::RZ_Graph_Embed_Token(QString raw_text,
 caon_ptr<RZ_Graph_Embed_Package> embed_package)
 : kind_(Basic_Token_Kinds::Symbol_Token), raw_text_(raw_text),
   embed_package_(embed_package), args_(nullptr),
   entry_node_(nullptr), function_def_info_(nullptr)
{

}


RZ_Graph_Embed_Token::RZ_Graph_Embed_Token(QString raw_text,
 Basic_Token_Kinds kind,
 caon_ptr<RZ_Graph_Embed_Package> embed_package)
  : kind_(kind), raw_text_(raw_text),
   embed_package_(embed_package), args_(nullptr),
   entry_node_(nullptr), function_def_info_(nullptr)
{

}


RZ_Graph_Embed_Token::RZ_Graph_Embed_Token(QString raw_text, QString arg,
 caon_ptr<RZ_Graph_Embed_Package> embed_package)
 : kind_(Basic_Token_Kinds::Symbol_Token), raw_text_(raw_text), embed_package_(embed_package),
   args_(new QStringList(arg)), entry_node_(nullptr)
{

}


RZ_Graph_Embed_Token::RZ_Graph_Embed_Token(RZ_Lisp_Token& rz_lisp_token,
 caon_ptr<RZ_Graph_Embed_Package> embed_package)
 : embed_package_(embed_package), args_(nullptr), entry_node_(nullptr)
{
 init_from_lisp_token(rz_lisp_token);
}

void RZ_Graph_Embed_Token::init_from_lisp_token(const RZ_Lisp_Token &rlt)
{
 kind_ = rlt.kind_and_string_value(raw_text_);
}

Basic_Token_Kinds RZ_Graph_Embed_Token::kind_and_string_value(QString& sv) const
{
 sv = raw_text_;
 return kind_;
}


void RZ_Graph_Embed_Token::convey(int position, RZ_Graph_Run_Token& rzt)
{
 //?   This is currently the only point of needing rz-graph-run
 //    (and provides functionality mostly for rz-graph-run so
 //     could plausibly moved there...)

 rzt.set_symbol_string_value(string_value(position));
}


QString RZ_Graph_Embed_Token::string_value(int position)
{
 if(position == 0)
  return string_value();
 if(args_)
 {
  return args_->at(position - 1);
 }
 return QString();
}


QString RZ_Graph_Embed_Token::padded_string_value(int position)
{
 if(position == 0)
  return string_value();
 if(args_)
 {
  return QString(" %1 ").arg(args_->at(position - 1));
 }
 return QString();
}

QString RZ_Graph_Embed_Token::string_value()
{
 if(embed_package_)
 {
  return embed_package_->name() + ":" + raw_text();
 }
 return raw_text();
}


void RZ_Graph_Embed_Token::set_args(QStringList& qsl)
{
 args_ = new QStringList(qsl);
}

void RZ_Graph_Embed_Token::advance_arg(int& position)
{
 if(args_)
 {
  if(position < args_->size())
   ++position;
  else position = 0;
 }
 else
  position = 0;

}

