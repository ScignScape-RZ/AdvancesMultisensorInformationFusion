
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-token.h"

#include "rz-graph-core/token/rz-re-token.h"

#include "rz-graph-valuer/string/rz-string.h"


#include "valuer/rz-lisp-core-function.h"


#include "rzns.h"

USING_RZNS(GBuild)

RZ_Lisp_Token::RZ_Lisp_Token(QString raw_text, Special_Constructor_Mode scm, int line_number)
 : Flags(0), raw_text_(raw_text), line_number_(line_number), out_(nullptr)
{

}


RZ_Lisp_Token::RZ_Lisp_Token(QString raw_text, int line_number)
 : Flags(0), raw_text_(raw_text), line_number_(line_number), out_(nullptr)
{
 if(raw_text_.endsWith('?'))
 {
  if(raw_text.size() == 1)
  {
   return;
  }
  if(raw_text.startsWith('='))
  {
   return;
  }
  if(raw_text.startsWith('-'))
  {
   return;
  }
  flags.final_question_mark = true;
  raw_text_.chop(1);
 }
 else if(raw_text[0] == '?')
 {
  raw_text_ = raw_text_.mid(1);
  flags.initial_question_mark = true;
 }

}

caon_ptr<RZ_Lisp_Token> RZ_Lisp_Token::check_init_lisp_token(RE_Token& re_token)
{
 caon_ptr<RZ_Lisp_Token> result = re_token.lisp_token();
 if(!result)
 {
  init_lisp_token(re_token);
  result = re_token.lisp_token();
 }
 return result;
}


void RZ_Lisp_Token::init_lisp_token(RE_Token& re_token)
{
 caon_ptr<RZ_Lisp_Token> rlt;
 if(re_token.flags.is_string_literal)
 {
  rlt = new RZ_Lisp_Token(re_token.string_value(), RZ_Lisp_Token::Special_Constructor_Mode::Raw_Text);
  rlt->flags.is_string_literal = true;
  re_token.set_lisp_token(rlt);
  return;
 }
 rlt = new RZ_Lisp_Token(re_token.string_value());

 re_token.set_lisp_token(rlt);

 rlt->flags.is_keyword = re_token.flags.is_keyword;
 rlt->flags.is_symbol_declaration = re_token.flags.is_symbol_declaration;
 rlt->flags.is_string_literal = re_token.flags.is_string_literal;
 rlt->flags.is_numeric_literal = re_token.flags.is_numeric_literal;
 rlt->flags.is_xq_literal = re_token.flags.is_xq_literal;
 rlt->flags.is_raw_lisp = re_token.flags.is_raw_lisp;

 rlt->flags.is_quoted = re_token.flags.is_quoted;

 rlt->flags.is_declaration_arrow = re_token.is_declaration_arrow();
 rlt->flags.is_mapkey = re_token.flags.is_mapkey;
 rlt->flags.is_do_mapkey = re_token.flags.is_do_mapkey;
 rlt->flags.has_mapkey = re_token.flags.has_mapkey;
 rlt->flags.is_match_literal = re_token.flags.is_match_literal;
 rlt->flags.is_empty_tuple_indicator = re_token.flags.is_empty_tuple_indicator;

 rlt->flags.is_cpp_scoped = re_token.flags.is_cpp_scoped;
 rlt->flags.not_entry = re_token.flags.not_entry;
 rlt->flags.has_type_indicator = re_token.flags.has_type_indicator;

 rlt->flags.follows_call_arrow = re_token.flags.follows_call_arrow;

 rlt->flags.precedes_call_arrow = re_token.flags.precedes_call_arrow;

}


void RZ_Lisp_Token::skip_lisp_out()
{
 flags.skip_lisp_out = true;
}

void RZ_Lisp_Token::comment_lisp(QString str)
{
 check_out();
}

void RZ_Lisp_Token::redirect_lisp(QString str)
{
 check_out();
}

void RZ_Lisp_Token::redirect_paste(QString str)
{
 check_out();
}


void RZ_Lisp_Token::redirect_lisp(QString str,
 std::function<void(QString&)>* callback)
{
 flags.out_redirect = true;
 check_out();
}

void RZ_Lisp_Token::redirect_lisp(QString str,
 RZ_Lisp_Node& node)
{
 flags.out_redirect = true;
 check_out();
}

void RZ_Lisp_Token::redirect_lisp_in_form(QString str,
 RZ_Lisp_Node& node)
{
 flags.out_redirect = true;
 check_out();
}


void RZ_Lisp_Token::check_out()
{
//? if(!out_)
//  out_ = new RZ_Lisp_Token_Out_Info;
}


caon_ptr<RZ_Type_Object> RZ_Lisp_Token::type_object()
{
 return vh_.type_object();
}

void RZ_Lisp_Token::set_type_object(RZ_Type_Object& cto)
{
 vh_.set_type_object(&cto);
}

void RZ_Lisp_Token::mark_as_string_literal()
{
 set_new_cast_value<RZ_String, QString>(raw_text_);
}

caon_ptr<RZ_Lisp_Token_Out_Info> RZ_Lisp_Token::get_lisp_out
 (RZ_Type_Variety& tv, QString& result)
{
 if(out_)
 {
  return out_;
 }
 if(flags.is_empty_tuple)
 {
  result += "(rz-empty-tuple)";
  return nullptr;
 }
 if(caon_ptr<RZ_Lisp_Core_Function> cf = pRestore<RZ_Lisp_Core_Function>(tv))
 {
  if(cf->flags.paste)
  {

  }
  result = cf->get_out_name();
 }
 else if(flags.is_core_function_symbol)
 {
  caon_ptr<RZ_Lisp_Core_Function> cf = pRestore<RZ_Lisp_Core_Function>();
  result = cf->get_out_name_or_string();
 }
 else
  result = lisp_string_value();
 return nullptr;
}

QString RZ_Lisp_Token::lisp_string_value()
{
 QString result;
 if(flags.is_keyword)
 {
  result = string_value();
  result.prepend(':');
 }
 else if(flags.follows_call_arrow)
 {
  result = string_value();
  result.prepend(":|.");
  result.append('|');
 }
 else if(flags.is_string_literal)
 {
  if(flags.is_double_back_quoted)
   result = QString("``") + string_value();
  else
   result = QString('"') + string_value() + '"';
 }
 else if(flags.is_double_quoted)
 {
  result = QString("''") + string_value();
 }
 else if(flags.is_quoted)
 {
  result = QString("'") + string_value();
 }
 else
  result = string_value();
 return result;
}


Basic_Token_Kinds RZ_Lisp_Token::kind_and_string_value(QString& result) const
{
 result = raw_text_;
 // //  Put this here for now because not every
  //    follows_call_arrow scenario will necessarily
  //    demand the :|.| construction ...
 if(flags.follows_call_arrow)
 {
  result.prepend(":|.");
  result.append('|');
  return Basic_Token_Kinds::Symbol_Token;
 }
 else if(flags.is_string_literal)
  return Basic_Token_Kinds::String_Token;
 else
  return Basic_Token_Kinds::Symbol_Token;
}


QString RZ_Lisp_Token::cpp_string_value()
{
 QString result = lisp_string_value();
 result.replace('-', '_');
 return result;
}


