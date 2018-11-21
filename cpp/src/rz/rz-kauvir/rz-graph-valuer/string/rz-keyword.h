
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_KEYWORD__H
#define RZ_KEYWORD__H

#include "rz-typedefs.h"
#include "flags.h"

#include "rz-string.h"


#include <QDebug>


#include "flags.h"
#include "accessors.h"


#include "rzns.h"


RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)

RZNS_(GVal)

class RZ_String;

class RZ_Keyword
{
public:

 flags_(1)
  bool is_function_overload_marker:1;
  bool is_file_marker:1;
  bool is_numeric_marker:1;
  bool is_arrow_marker:1;
 _flags

private:

 RZ_String rz_string_;

public:

 ACCESSORS__RGET(RZ_String ,rz_string)

 RZ_Keyword(RZ_Lisp_Token* t = nullptr):Flags(0), rz_string_(t){}

 RZ_Keyword(tString s):Flags(0),rz_string_(s){}

 void set_token(RZ_Lisp_Token* t)
 {
  rz_string_.set_token(t);
 }


 tString cut()
 {
  return str().mid(1);
 }

 tString str()
 {
  return rz_string_.to_string();
 }

 tString to_string() const
 {
  return rz_string_.to_string();
 }

 template<typename T>
 friend T& operator<<(T& t, const RZ_Keyword& rhs)
 {
  return t << rhs.to_string();
 }


 friend void operator<<(QDebug lhs, const RZ_Keyword& rhs)
 {
  tString s = rhs.to_string();
  lhs << s;
 }

};

_RZNS(GVal)

#endif //RZ_KEYWORD__H
