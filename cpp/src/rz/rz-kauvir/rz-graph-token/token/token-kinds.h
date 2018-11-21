
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TOKEN_KINDS__H
#define TOKEN_KINDS__H

#include "rzns.h"
RZNS_(GBuild)


enum class Basic_Token_Kinds {
 Symbol_Token, String_Token, Quote_Token, Backquote_Token, Escape_Quote_Token,
 Escape_Character_Token, NOOP_Token,
   // // C++ specific
   Function_Def_Redirect, Empty_Tuple_Indicator,
    Class_Def_Redirect
};


_RZNS(GBuild)

#endif //TOKEN_KINDS__H
