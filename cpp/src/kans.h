
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KANS__H
#define KANS__H



// // this is defined by default;
 //   for most cases it should stay so...
 //   Should be defined via compiler flag by qmake.
 //   If that is edited from the project files
 //   uncomment this as needed ...
 //   #define USE_KANS

#ifdef USE_KANS

#define KANS_(X) \
 namespace KA { namespace X {

#define _KANS(X) \
 } }


#define KANS_CLASS_DECLARE(X ,C) \
 namespace KA { namespace X { class C; } }


#ifndef INNER_NS_
#define INNER_NS_(X) \
 namespace X{
#endif

#ifndef _INNER_NS
#define _INNER_NS(X) \
 }
#endif


#define USING_KANS(x) \
 using namespace KA::x;


#else

#define KANS_(X) \

#define _KANS(X) \

#define INNER_NS_(X) \

#define END_INNER_NS(X) \

#define USING_KANS(x) \

#define KANS_CLASS_DECLARE(X ,C) \
  class C;

#endif


#endif //KANS__H
