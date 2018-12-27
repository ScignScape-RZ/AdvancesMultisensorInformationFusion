
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


// // List run types.  The RZ_RUN_TYPE macro is redefined in different places
 //   and expands to different code using the two values written on each line
//   here, depending on the context in which this file is included.


RZ_RUN_TYPE(Dbl, dbl, double, Double, Core_Operative)
RZ_RUN_TYPE(Int, int, int, Integer, Core_Operative)
RZ_RUN_TYPE(I8, i8, char, Integer8, Core_Operative)

#include "type-codes.namespaced.h"

#define RZ_TEMP_CASES_TYPECODE_NON_NAMESPACED 3

#define RZ_TEMP_CASES_TYPECODE RZ_TEMP_CASES_16
