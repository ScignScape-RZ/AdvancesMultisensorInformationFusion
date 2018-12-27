
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_TEMP_CASES__H
#define RZ_TEMP_CASES__H

#ifndef RZ_TEMP_CASES_
#define RZ_TEMP_CASES_(num) RZ_TEMP_CASES_##num
#endif

// //  How large?
#ifndef RZ_TEMP_CASES__FUNCTION_CODE
#define RZ_TEMP_CASES__FUNCTION_CODE RZ_TEMP_CASES_10
#endif

//#ifndef RZ_TEMP_CASES
//#define RZ_TEMP_CASES RZ_TEMP_CASES_16
//#endif


#ifndef RZ_TEMP_CASES_1
#define RZ_TEMP_CASES_1 RZ_TEMP_CASE(1)
#endif

#ifndef RZ_TEMP_CASES_2
#define RZ_TEMP_CASES_2 RZ_TEMP_CASE(2) RZ_TEMP_CASES_1
#endif

#ifndef RZ_TEMP_CASES_3
#define RZ_TEMP_CASES_3 RZ_TEMP_CASE(3) RZ_TEMP_CASES_2
#endif

#ifndef RZ_TEMP_CASES_4
#define RZ_TEMP_CASES_4 RZ_TEMP_CASE(4) RZ_TEMP_CASES_3
#endif

#ifndef RZ_TEMP_CASES_5
#define RZ_TEMP_CASES_5 RZ_TEMP_CASE(5) RZ_TEMP_CASES_4
#endif

#ifndef RZ_TEMP_CASES_6
#define RZ_TEMP_CASES_6 RZ_TEMP_CASE(6) RZ_TEMP_CASES_5
#endif

#ifndef RZ_TEMP_CASES_7
#define RZ_TEMP_CASES_7 RZ_TEMP_CASE(7) RZ_TEMP_CASES_6
#endif

#ifndef RZ_TEMP_CASES_8
#define RZ_TEMP_CASES_8 RZ_TEMP_CASE(8) RZ_TEMP_CASES_7
#endif

#ifndef RZ_TEMP_CASES_9
#define RZ_TEMP_CASES_9 RZ_TEMP_CASE(9) RZ_TEMP_CASES_8
#endif

#ifndef RZ_TEMP_CASES_10
#define RZ_TEMP_CASES_10 RZ_TEMP_CASE(10) RZ_TEMP_CASES_9
#endif

#ifndef RZ_TEMP_CASES_11
#define RZ_TEMP_CASES_11 RZ_TEMP_CASE(11) RZ_TEMP_CASES_10
#endif

#ifndef RZ_TEMP_CASES_12
#define RZ_TEMP_CASES_12 RZ_TEMP_CASE(12) RZ_TEMP_CASES_11
#endif

#ifndef RZ_TEMP_CASES_13
#define RZ_TEMP_CASES_13 RZ_TEMP_CASE(13) RZ_TEMP_CASES_12
#endif

#ifndef RZ_TEMP_CASES_14
#define RZ_TEMP_CASES_14 RZ_TEMP_CASE(14) RZ_TEMP_CASES_13
#endif

#ifndef RZ_TEMP_CASES_15
#define RZ_TEMP_CASES_15 RZ_TEMP_CASE(15) RZ_TEMP_CASES_14
#endif

#ifndef RZ_TEMP_CASES_16
#define RZ_TEMP_CASES_16 RZ_TEMP_CASE(16) RZ_TEMP_CASES_15
#endif

#ifndef RZ_TEMP_CASES_17
#define RZ_TEMP_CASES_17 RZ_TEMP_CASE(17) RZ_TEMP_CASES_16
#endif

#ifndef RZ_TEMP_CASES_18
#define RZ_TEMP_CASES_18 RZ_TEMP_CASE(18) RZ_TEMP_CASES_17
#endif

#ifndef RZ_TEMP_CASES_19
#define RZ_TEMP_CASES_19 RZ_TEMP_CASE(19) RZ_TEMP_CASES_18
#endif

#ifndef RZ_TEMP_CASES_20
#define RZ_TEMP_CASES_20 RZ_TEMP_CASE(20) RZ_TEMP_CASES_19
#endif


#endif //RZ_TEMP_CASES__H
