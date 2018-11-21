
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#define DOMINION_NODE_TYPE RE_Node

#ifndef DOMINION_HIDE_NO_NAMESPACE
// // No namespace
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(dbl, double, Double)
DOMINION_TYPE(integer, int, Int)
DOMINION_TYPE(i8, char, I8)
DOMINION_TYPE(qstring, QString, QStr)
#endif

#include "relae-graph/dominion-macros.h"

#define DOMINION_OUTER_NAMESPACE RZ


#define DOMINION_INNER_NAMESPACE RECore
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(re_root, RE_Root, RE_Root)
DOMINION_TYPE(re_token, RE_Token, RE_Token)
DOMINION_TYPE(proxy, RE_Node_Proxy, Proxy)
DOMINION_TYPE(re_tuple_info, RE_Tuple_Info, RE_Tuple_Info)
DOMINION_TYPE(re_call_entry, RE_Call_Entry, RE_Call_Entry)
DOMINION_TYPE(re_block_entry, RE_Block_Entry, RE_Block_Entry)
DOMINION_TYPE(re_function_def_entry, RE_Function_Def_Entry, RE_Function_Def_Entry)
DOMINION_TYPE(string_plex_builder, RZ_String_Plex_Builder, StrPlexBuilder)
#undef DOMINION_INNER_NAMESPACE



#define DOMINION_INNER_NAMESPACE Text
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(text_punctuation, RZ_Text_Punctuation, RZ_Text_Punctuation)
#undef DOMINION_INNER_NAMESPACE

#define DOMINION_INNER_NAMESPACE GEmbed
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(embed_token, RZ_Graph_Embed_Token, RZ_Graph_Embed_Token)
DOMINION_TYPE(cpp_token, RZ_Graph_Cpp_Token, RZ_Graph_Cpp_Token)
DOMINION_TYPE(kauvir_token, RZ_Graph_Kauvir_Token, RZ_Graph_Kauvir_Token)
DOMINION_TYPE(dynamo_token, RZ_Graph_Dynamo_Token, RZ_Graph_Dynamo_Token)
DOMINION_TYPE(ecl_token, RZ_Graph_ECL_Token, RZ_Graph_ECL_Token)
#undef DOMINION_INNER_NAMESPACE


#define DOMINION_INNER_NAMESPACE GBuild
#include "relae-graph/dominion-macros.h"
//?
DOMINION_TYPE(core_function, RZ_Lisp_Graph_Core_Function, Graph_CoreFun)
DOMINION_TYPE(cfn, RZ_Lisp_Core_Function, Token_CoreFun)
DOMINION_TYPE(fair_annotation, RZ_FAIR_Annotation, Fair_Annotation)
DOMINION_TYPE(null_value, RZ_Null_Value, Null_Value)
DOMINION_TYPE(empty_tuple, RZ_Lisp_Empty_Tuple, EmptyTuple)
#undef DOMINION_INNER_NAMESPACE


#define DOMINION_INNER_NAMESPACE GVal
#include "relae-graph/dominion-macros.h"
DOMINION_TYPE(fair_codepoint, RZ_FAIR_Codepoint, FAIR_Codepoint)
DOMINION_TYPE(fair_archpoint, RZ_FAIR_Archpoint, FAIR_Archpoint)
DOMINION_TYPE(fair_textpoint, RZ_FAIR_Textpoint, FAIR_Textpoint)
DOMINION_TYPE(fair_filepoint, RZ_FAIR_Filepoint, FAIR_Filepoint)
DOMINION_TYPE(vec, RZ_Lisp_Vector, Lisp_Vector)
DOMINION_TYPE(map, RZ_Lisp_Map, Lisp_Map)
DOMINION_TYPE(str, RZ_String, Str)
DOMINION_TYPE(str_plex, RZ_String_Plex, StrPlex)
DOMINION_TYPE(mlt, RZ_Match_Literal, Mlt)
DOMINION_TYPE(opc, RZ_Opaque_Call, Opc)
DOMINION_TYPE(sym, RZ_Lisp_Symbol, Sym)
DOMINION_TYPE(ots, RZ_Opaque_Type_Symbol, Ots)
DOMINION_TYPE(lexs, RZ_Lisp_Graph_Lexical_Scope, Lexs)
DOMINION_TYPE(block_info, RZ_Lisp_Graph_Block_Info, Block_Info)
DOMINION_TYPE(rz_function_def_info, RZ_Function_Def_Info, RZ_Function_Def_Info)
DOMINION_TYPE(rz_code_statement, RZ_Code_Statement, RZ_Code_Statement)
DOMINION_TYPE(rz_expression_review, RZ_Expression_Review, RZ_Expression_Review)
#undef DOMINION_INNER_NAMESPACE

#undef DOMINION_OUTER_NAMESPACE
#undef DOMINION_NODE_TYPE

