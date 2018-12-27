
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_MATCH_LITERAL__H
#define RZ_MATCH_LITERAL__H

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


class RZ_Match_Literal
{

private:
 tString raw_string_;


public:

 ACCESSORS(tString ,raw_string)


 operator tString() const;

 tString to_string() const;

 friend void operator<<(QDebug lhs, const RZ_Match_Literal& rhs)
 {
  tString s = rhs.to_string();
  lhs << s;
 }

 RZ_Match_Literal(tString s):
   raw_string_(s)
 {
 }

 friend bool operator==(const RZ_Match_Literal& lhs, const RZ_Match_Literal& rhs)
 {
  return lhs.to_string() == rhs.to_string();
 }

 operator bool()
 {
  tString s = to_string();
  return s.isEmpty() || s.isNull();
 }

 bool operator>(const RZ_Match_Literal& rhs) const;
 bool operator<(const RZ_Match_Literal& rhs) const;

  template<typename T>
  friend T& operator<<(T& t, const RZ_Match_Literal& s)
  {
   return t << s.to_string();
  }

  friend RZ_Lisp_Graph_Result_Holder& operator<<(RZ_Lisp_Graph_Result_Holder& rh, const RZ_Match_Literal& s)
  {
   rh << s;
   return rh;
  }


  RZ_Match_Literal operator+(const RZ_Match_Literal& rhs )
  {
   return RZ_Match_Literal( to_string() + rhs.to_string() );
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
  friend bool operator>(const T& lhs, const RZ_Match_Literal& rhs)
  {
   return false;
  }

  template<typename T>
  friend bool operator<(const T& lhs, const RZ_Match_Literal& rhs)
  {
   return false;
  }


};


_RZNS(GVal)

#endif //RZ_MATCH_LITERAL__H
