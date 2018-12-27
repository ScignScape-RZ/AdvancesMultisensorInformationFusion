
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_NULL_VALUE__H
#define RZ_NULL_VALUE__H

#include "accessors.h"

#include <QString>
#include <QDebug>

#include "flags.h"

#include "rzns.h"

RZNS_(GBuild)

class RZ_Null_Value
{
 QString description_;

public:

 ACCESSORS(QString ,description)

 RZ_Null_Value(QString description);

 template<typename T>
 friend void operator<<(T& t, RZ_Null_Value&)
 {
 }

 friend void operator<<(QDebug qd, RZ_Null_Value&)
 {
  qd << "<opaque>";
 }


};

_RZNS(GBuild)

#endif //RZ_NULL_VALUE__H
