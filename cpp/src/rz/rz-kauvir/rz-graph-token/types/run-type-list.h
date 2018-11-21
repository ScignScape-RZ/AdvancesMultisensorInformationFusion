
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


// //  Writes a list of run types to be placed directly into an enumeration
 //    The first (Not_Set) is a null default, while others are drawn from
//    the list of codes used in several places via a temporary macro.

Not_Set

#define RZ_RUN_TYPE_NS(ns_name, enum_name, name, cpp_name, embed_name, fam) \
 RZ_RUN_TYPE(enum_name, name, cpp_name, embed_name, fam)
#define RZ_RUN_TYPE(enum_name, name, cpp_name, embed_name, fam) ,enum_name
#include "type-codes.h"
#undef RZ_RUN_TYPE
#undef RZ_RUN_TYPE_NS

