
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


RE_SPECIAL_TOKEN("doc-info_", DocInfo_, Text_Map_Enter)
RE_SPECIAL_TOKEN("_doc-info", _DocInfo, Text_Map_Leave)

RE_SPECIAL_TOKEN_RENAME("----", Logical_Scope_Enter_4, Auto_Statement_End)
RE_SPECIAL_TOKEN_RENAME(";;;;", Logical_Scope_Leave_4, Auto_Statement_End)

RE_SPECIAL_TOKEN("->", Call_Arrow, Arrow)
RE_SPECIAL_TOKEN("\\->", Call_Arrow_Fdef, Arrow)
RE_SPECIAL_TOKEN("%->", Call_Arrow_To_Block, Arrow)
RE_SPECIAL_TOKEN("->def", Call_Arrow_No_Def, Arrow)
RE_SPECIAL_TOKEN("$->", Call_Arrow_Note, Arrow)
RE_SPECIAL_TOKEN("@->", Call_Arrow_Async, Arrow)
RE_SPECIAL_TOKEN("->>", Call_Arrow_No_Cast, Arrow)

//RE_SPECIAL_TOKEN("-->", Call_Arrow_Future, Arrow)
//RE_SPECIAL_TOKEN("'->", Call_Arrow_Type_Expression, Arrow)
//RE_SPECIAL_TOKEN("`->", Call_Arrow_Monad, Arrow)
//RE_SPECIAL_TOKEN("-/>", Call_Arrow_With_Matching, Arrow)
//RE_SPECIAL_TOKEN(">-->", Call_Arrow_Via_Lisp_Callback, Normal)
//RE_SPECIAL_TOKEN(">-", Pending_Call_Arrow_Via_Lisp_Callback, Normal)
//RE_SPECIAL_TOKEN("/-->", Default_With_Matching, Auto_Statement_End)
//RE_SPECIAL_TOKEN("$$", Matching_Default, Normal)

RE_SPECIAL_TOKEN("-!", Auto_Expand_To_Null_Test, Normal)
RE_SPECIAL_TOKEN("-?", Auto_Expand_To_Not_Null_Test, Normal)

RE_SPECIAL_TOKEN("retval", Return_Value_Blank_Or_Identity, Normal)
