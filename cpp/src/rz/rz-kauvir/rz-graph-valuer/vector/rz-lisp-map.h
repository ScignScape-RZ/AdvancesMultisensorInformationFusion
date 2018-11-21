
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_MAP__H
#define RZ_LISP_MAP__H

#include "rz-typedefs.h"
#include "flags.h"
#include "accessors.h"

#include <QDebug>

#include "rzns.h"

RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)


RZNS_(GVal)

class RZ_String;


class RZ_Lisp_Map
{
public:
 RZ_Lisp_Map();


 template<typename T>
 friend T& operator<<(T& t, const RZ_Lisp_Map& rhs)
 {
//?  return t << rhs.to_string();
 }


 friend void operator<<(QDebug lhs, const RZ_Lisp_Map& rhs)
 {
//?  tString s = rhs.to_string();
//?  lhs << s;
 }

};

_RZNS(GVal)

#endif //RZ_LISP_MAP__H
