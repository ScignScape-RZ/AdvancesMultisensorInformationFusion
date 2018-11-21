
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "distractor.h"

USING_KANS(DSM)

Distractor::Distractor(QString name, Enum en)
  :  name_(name), en_(en)
{

}


Distractor* Distractor::get_by_name(QString name)
{
 static QMap<QString, Distractor*> static_map {{

#define TEMP_MACRO(x)  {#x, new Distractor(#x, Enum::x)},
 TEMP_MACRO(N_A)
 TEMP_MACRO(Cafeteria)
 TEMP_MACRO(Car)
 TEMP_MACRO(Mensa)
 TEMP_MACRO(Office)
 TEMP_MACRO(Pub)
 TEMP_MACRO(Road)
   }};
#undef TEMP_MACRO

 return static_map.value(name, static_map.value("N_A"));
}

