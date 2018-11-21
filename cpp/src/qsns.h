

//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef QSNS__H
#define QSNS__H

#ifdef USE_QSNS

#define QSNS_(X) \
 namespace QScign { namespace X {

#define _QSNS(X) \
 } }


#define QSNS_CLASS_DECLARE(X ,C) \
 namespace QScign { namespace X { class C; } }

#ifndef INNER_NS_
#define INNER_NS_(X) \
 namespace X{
#endif

#ifndef _INNER_NS
#define _INNER_NS(X) \
 }
#endif


#define USING_QSNS(x) \
 using namespace QScign::x;


#else

#define QSNS_(X) \

#define _QSNS(X) \

#define INNER_NS_(X) \

#define END_INNER_NS(X) \

#define USING_QSNS(x) \

#define QSNS_CLASS_DECLARE(X ,C) \
  class C;

#endif


#endif // NS__H
