
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_CODE_REPRESENTATION__H
#define RZ_RE_CODE_REPRESENTATION__H

#include "accessors.h"
#include "flags.h"


#include <QString>
#include <QMap>


#include "rzns.h"
RZNS_(RECore)


class RE_Code_Representation
{

public:

 enum class Special_Token_Kind
 {
  N_A, Normal, Text_Map_Enter, Text_Map_Leave, Text_Map_Leave_In_Statement,
  Auto_Statement_End, Auto_Statement_End_If_EOL, Arrow
 };

 enum class Special_Tokens
 {
  N_A
  #define RE_SPECIAL_TOKEN(token, cpp_enum, kind) \
   ,cpp_enum
  #define RE_SPECIAL_TOKEN_RENAME(token, cpp_enum, kind) \
   ,cpp_enum
  # include "rz-re-code-representation.special-tokens.h"
  #undef RE_SPECIAL_TOKEN_RENAME
  #undef RE_SPECIAL_TOKEN
 };

 struct Special_Token {
  Special_Tokens token;
  QString lisp_name;
  Special_Token_Kind kind;
  operator bool()
  {
   return token != Special_Tokens::N_A;
  }
 };

 static Special_Token check_special_token(QString token_string,
  bool do_parse = true)
 {
  static Special_Token special_token_na
   {Special_Tokens::N_A, QString(), Special_Token_Kind::N_A};
  static QMap<QString, Special_Token> static_map {{
   #define RE_SPECIAL_TOKEN(token, cpp_enum, kind) \
    { token, {Special_Tokens::cpp_enum, \
     token, Special_Token_Kind::kind} },
   #define RE_SPECIAL_TOKEN_RENAME(token, cpp_enum, kind) \
    { token, {Special_Tokens::cpp_enum, \
     #cpp_enum, Special_Token_Kind::kind} },
    #include "rz-re-code-representation.special-tokens.h"
   #undef RE_SPECIAL_TOKEN_RENAME
   #undef RE_SPECIAL_TOKEN
   }};

  if(do_parse)
  {
   return static_map.value(token_string, special_token_na);
  }
  else
  {
   return special_token_na;
  }
 }

private:

public:


};

_RZNS(RECore)

#endif //RZ_RE_CODE_REPRESENTATION__H
