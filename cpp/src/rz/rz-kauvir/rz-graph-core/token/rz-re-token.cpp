
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-token.h"

#include <QRegularExpression>

#include <QDebug>

#include "rzns.h"

USING_RZNS(RECore)

RE_Token::RE_Token(QString raw_text, QString prefix,
 QString suffix, int line_number)
 : Flags(0), lisp_token_(nullptr),
   raw_text_(raw_text), line_number_(line_number)
{
 if(raw_text_ == "do")
 {
  if( (prefix.size() == 0) && (suffix.size() == 0) )
  {
   flags.is_do = true;
   special_token_ =
    RE_Code_Representation::check_special_token(raw_text_, false);
   return;
  }
 }

 Prefix_Kinds prefix_kind = parse_prefix_kind(prefix);
 Suffix_Kinds suffix_kind = parse_suffix_kind(suffix);

 bool parse_special_token = false;

 switch(prefix_kind)
 {
 case Prefix_Kinds::Keyword:
  flags.is_keyword = true;
  break;

 case Prefix_Kinds::Symbol_Declaration:
  flags.is_symbol_declaration = true;
  break;

 case Prefix_Kinds::Up_Scope_Declaration:
  flags.is_up_scope_declaration = true;
  break;

 case Prefix_Kinds::Quoted:
  flags.is_quoted = true;
  break;

 case Prefix_Kinds::Back_Quoted:
  flags.is_back_quoted = true;
  break;

 default:
  inital_check_numeric();
  parse_special_token = !flags.is_numeric_literal;
  break;
 }

 switch(suffix_kind)
 {
 case Suffix_Kinds::Mapkey:
  flags.is_mapkey = true;
  if(raw_text.startsWith('-'))
  {
   flags.is_do_mapkey = true;
  }
  parse_special_token = false;
  break;

 default:
  if(raw_text.endsWith('='))
    flags.is_equalizer = true;

  else if(raw_text.startsWith('-') && raw_text.endsWith('>'))
  {
   resolve_arrow_prefix(prefix, raw_text);
   flags.is_arrow = true;
   parse_special_token = true;
  }

  else if(raw_text == "->def")
  {
   flags.is_arrow = true;
   parse_special_token = true;
  }

  else if(raw_text == "@->")
  {
   flags.is_arrow = true;
   parse_special_token = true;
  }

  else if(raw_text == "/->")
  {
   flags.is_arrow = true;
   parse_special_token = true;
  }

  else if(raw_text == "\\->")
  {
   flags.is_arrow = true;
   parse_special_token = true;
  }

  else if(raw_text == "$->")
  {
   flags.is_arrow = true;
   parse_special_token = true;
  }

  break;
 }

 special_token_ =
  RE_Code_Representation::check_special_token(raw_text_, parse_special_token);

}

QString RE_Token::special_token_kind_string() const
{
 switch(special_token_kind())
 {
 case RE_Code_Representation::Special_Token_Kind::Arrow:
  return "Arrow";

 case RE_Code_Representation::Special_Token_Kind::Auto_Statement_End_If_EOL:
  return "Auto_Statement_End_If_EOL";

 case RE_Code_Representation::Special_Token_Kind::Auto_Statement_End:
  return "Auto_Statement_End";

 case RE_Code_Representation::Special_Token_Kind::Text_Map_Leave_In_Statement:
  return "Text_Map_Leave_In_Statement";

 case RE_Code_Representation::Special_Token_Kind::Text_Map_Leave:
  return "Text_Map_Leave";

 case RE_Code_Representation::Special_Token_Kind::Text_Map_Enter:
  return "Text_Map_Enter";

 case RE_Code_Representation::Special_Token_Kind::Normal:
  return "Normal";

 case RE_Code_Representation::Special_Token_Kind::N_A:
  return "N_A";

 default:
   return "??";

 }
}

QString RE_Token::clasp_string_value() const
{
 QString result = string_value();
 if(flags.is_keyword)
 {
  result.prepend(':');
 }
 return result;
}


void RE_Token::resolve_arrow_prefix(QString prefix, QString raw_text)
{
 Flags = 0;
 raw_text_ = prefix + raw_text;
 flags.is_arrow = true;

}

// //   This does not consider keywords etc.
//      It is assumed this will only be called
//      after checking that the token is not a
//      keyword, etc.
void RE_Token::inital_check_numeric()
{
 QRegularExpression re("\\A\\d");
 QRegularExpressionMatch match = re.match(raw_text_);

 flags.is_numeric_literal = match.hasMatch();
}

QString RE_Token::get_lisp_out() const
{
 QString result = special_token_.lisp_name;
 if(result.isEmpty())
 {
  result = raw_text_;
 }
 if(flags.is_keyword)
 {
  result.prepend(':');
 }
 if(flags.is_quoted)
 {
  result.prepend('\'');
 }
 if(flags.is_string_literal)
 {
  result.prepend('"');
  result.append('"');
 }
 return result;
}

QString RE_Token::string_summary(int length)
{
 QString result = raw_text_;
 int end_length = 0;
 if(flags.is_keyword)
 {
  result.prepend(':');
 }
 if(flags.is_quoted)
 {
  result.prepend('\'');
 }
 if(flags.is_back_quoted)
 {
  result.prepend('`');
 }
 if(flags.is_symbol_declaration)
 {
  result.prepend(',');
 }
 if(flags.is_up_scope_declaration)
 {
  result.prepend(';');
 }
 if(flags.is_string_literal)
 {
  result.prepend('"');
  end_length += 2;
 }
 if(flags.is_mapkey)
 {
  ++end_length;
 }
 bool overflow = (result.length() + end_length) > length;
 if(overflow)
 {
  result.truncate(length - end_length - 3);
  result += "...";
 }
 if(flags.is_string_literal)
 {
  result += '"';
 }
 if(flags.is_mapkey)
 {
  result += ':';
 }
 return result;
}



