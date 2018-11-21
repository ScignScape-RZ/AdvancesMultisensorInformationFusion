
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_TOKEN__H
#define RZ_RE_TOKEN__H

#include "accessors.h"
#include "flags.h"


#include "code/rz-re-code-representation.h"

#include <QString>

#include <functional>

#include "rz-graph-token/token/rz-lisp-token.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rzns.h"

USING_RZNS(GBuild)

RZNS_(RECore)


class RE_Token
{
public:
 flags_(5)
  bool is_keyword:1;
  bool is_symbol_declaration:1;
  bool is_up_scope_declaration:1;
  bool is_quoted:1;
  bool is_back_quoted:1;
  bool is_mapkey:1;
  bool is_string_literal:1;
  bool is_text_map_value_literal:1;
  bool is_numeric_literal:1;
  bool is_equalizer:1;
  bool is_arrow:1;
  bool has_mapkey:1;
  bool is_match_literal:1;
  bool is_empty_tuple_indicator:1;
  bool is_do:1;
  bool is_do_mapkey:1;
  bool is_cpp_scoped:1;
  bool precedes_ghost_scope:1;
  bool not_entry:1;
  bool strong_ghost_scope:1;
  bool follows_if_token:1;
  bool is_xq_literal:1;
  bool is_raw_lisp:1;
  bool has_type_indicator:1;
  bool follows_call_arrow:1;
  bool follows_elsif_token:1;
  bool precedes_call_arrow:1;
 _flags


public:

 enum class Prefix_Kinds {
  N_A, Keyword, Symbol_Declaration, Up_Scope_Declaration,
  Quoted, Back_Quoted
 };

 static Prefix_Kinds parse_prefix_kind(QString prefix)
 {
  static QMap<QString, Prefix_Kinds> static_map {{
   {":", Prefix_Kinds::Keyword},  {"'", Prefix_Kinds::Quoted},
   {",", Prefix_Kinds::Symbol_Declaration},
   {"`", Prefix_Kinds::Back_Quoted} }};
  return static_map.value(prefix, Prefix_Kinds::N_A);
 }

 enum class Suffix_Kinds {
  N_A, Mapkey, Type_Var
 };

 static Suffix_Kinds parse_suffix_kind(QString suffix)
 {
  static QMap<QString, Suffix_Kinds> static_map {{
   {":", Suffix_Kinds::Mapkey}, {"'", Suffix_Kinds::Type_Var},
  }};
  return static_map.value(suffix, Suffix_Kinds::N_A);
 }




private:

 int syntactic_depth_;
 QString raw_text_;
 int line_number_;

 caon_ptr<RZ_Lisp_Token> lisp_token_;

 RE_Code_Representation::Special_Token special_token_;

 void inital_check_numeric();

 void resolve_arrow_prefix(QString prefix, QString raw_text);

public:

 ACCESSORS(QString ,raw_text)
 ACCESSORS(int ,syntactic_depth)
 ACCESSORS(int ,line_number)
 ACCESSORS(caon_ptr<RZ_Lisp_Token> ,lisp_token)

 RE_Token(QString raw_text, QString prefix = QString(),
   QString suffix = QString(), int line_number = 0);

 static bool matches_text_map_key_pattern(QString prefix,
  QString suffix)
 {
  return (parse_prefix_kind(prefix) == Prefix_Kinds::Keyword)
   && (parse_suffix_kind(suffix) == Suffix_Kinds::Mapkey);
 }

 QString string_summary(int length = 8);

 QString string_value() const
 {
  return raw_text();
 }

 QString clasp_string_value() const;

 QString get_lisp_out() const;

 QString special_token_kind_string() const;

 RE_Code_Representation::Special_Token_Kind special_token_kind() const
 {
  return special_token_.kind;
 }

 // //   This is inline to reduce compilation dependencies
 bool is_declaration_arrow() const
 {
  if(flags.is_arrow)
  {
   // //   Check different arrow kinds ...
    //(but for now...)
   return true;
  }
  return false;
 }

 RE_Code_Representation::Special_Tokens special_token()
 {
  return special_token_.token;
 }

 bool matches_text_map_key()
 {
  return flags.is_keyword && flags.is_mapkey;
 }
};

_RZNS(RECore)

#endif //RZ_RE_TOKEN__H
