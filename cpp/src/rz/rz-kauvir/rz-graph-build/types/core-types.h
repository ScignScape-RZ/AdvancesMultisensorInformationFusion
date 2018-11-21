
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef CORE_TYPES__H
#define CORE_TYPES__H


#include "rz-graph-valuer/string/rz-string.h"

#include "rz-graph-valuer/valuer/rz-lisp-symbol.h"

#include "types/run-types.h"

#include "rz-graph-valuer/valuer/rz-opaque-call.h"
#include "rz-graph-valuer/valuer/rz-opaque-type-symbol.h"
#include "rz-graph-token/valuer/rz-null-value.h"


#include "rzns.h"


#define RZ_RUN_TYPE_NS(ns_name, enum_name, name, cpp_name, embed_name, fam) \
 RZNS_(ns_name) \
 class cpp_name; \
 _RZNS(ns_name)
#include "types/type-codes.namespaced.h"
#undef RZ_RUN_TYPE_NS

#include "types/run-type-codes.h"

#endif //CORE_TYPES__H
