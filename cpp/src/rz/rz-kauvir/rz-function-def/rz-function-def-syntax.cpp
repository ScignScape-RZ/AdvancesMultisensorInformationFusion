
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-function-def-syntax.h"
#include "rzns.h"

USING_RZNS(GVal)

RZ_Function_Def_Syntax::RZ_Function_Def_Syntax()
 : Flags(0)
{
 // //  For now default lisp renames
 symbol_renames_["?"] = "&optional";
}


void RZ_Function_Def_Syntax::check_symbol_rename(QString& sym) const
{
 if(symbol_renames_.contains(sym))
 {
  sym = symbol_renames_[sym];
 }
}

