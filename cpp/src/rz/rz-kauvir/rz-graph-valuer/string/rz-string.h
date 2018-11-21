
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_STRING__H
#define RZ_STRING__H

#include "rz-typedefs.h"
#include "flags.h"


#include <QDebug>
#include <QString>

#include "accessors.h"

#include "rzns.h"


RZNS_(GBuild)

class RZ_Lisp_Token;
class RZ_Lisp_Graph_Result_Holder;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GVal)


class RZ_String
{
public:

 flags_(1)
  bool has_arguments:1;
  bool has_raw_string:1;
 _flags

private:
 RZ_Lisp_Token* token_;
 tString raw_string_;


public:

 ACCESSORS(RZ_Lisp_Token* ,token)
 ACCESSORS(tString ,raw_string)


 operator tString() const;

 tString to_string() const;


 friend void operator<<(QDebug lhs, const RZ_String& rhs)
 {
  tString s = rhs.to_string();
  lhs << s;
 }

 RZ_String(RZ_Lisp_Token* t = nullptr):Flags(0),token_(t){}
 RZ_String(tString s):Flags(0),token_(nullptr),raw_string_(s)
 {
  flags.has_raw_string = true;
 }

 friend bool operator==(const RZ_String& lhs, const RZ_String& rhs)
 {
  return lhs.to_string() == rhs.to_string();
 }

 operator bool()
 {
  tString s = to_string();
  return s.isEmpty() || s.isNull();
 }

 bool operator>(const RZ_String& rhs) const;
 bool operator<(const RZ_String& rhs) const;

  template<typename T>
  friend T& operator<<(T& t, const RZ_String& s)
  {
   return t << s.to_string();
  }

  friend RZ_Lisp_Graph_Result_Holder& operator<<(RZ_Lisp_Graph_Result_Holder& rh, const RZ_String& s)
  {
   rh << s;
   return rh;
  }


  RZ_String operator+(const RZ_String& rhs )
  {
   return RZ_String( to_string() + rhs.to_string() );
  }

  template<typename T>
  bool operator>(const T& rhs) const
  {
   return false;
  }

  template<typename T>
  bool operator<(const T& rhs) const
  {
   return false;
  }

  template<typename T>
  friend bool operator>(const T& lhs, const RZ_String& rhs)
  {
   return false;
  }

  template<typename T>
  friend bool operator<(const T& lhs, const RZ_String& rhs)
  {
   return false;
  }
};


_RZNS(GVal)

#endif //RZ_STRING__H
