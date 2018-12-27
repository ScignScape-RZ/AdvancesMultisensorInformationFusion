
#include "rz-lisp-graph-valuer.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-token/token/rz-lisp-token.h"


#include "scope/rz-lisp-graph-lexical-scope.h"

#include "rz-graph-token/valuer/rz-null-value.h"
#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-core/kernel/graph/rz-re-node.h"

#include "rz-graph-core/code/rz-re-function-def-entry.h"


#include "rz-graph-core/token/rz-re-token.h"

#include "rz-graph-core/tuple/rz-re-tuple-info.h"
#include "rz-graph-core/code/rz-re-call-entry.h"


#include "rz-graph-build/rz-lisp-graph-result-holder.h"

#include "string/rz-string.h"
#include "string/rz-match-literal.h"

#include "valuer/rz-lisp-symbol.h"
#include "valuer/rz-opaque-call.h"
#include "rz-graph-build/types/rz-lisp-empty-tuple.h"

#include "valuer/rz-opaque-type-symbol.h"

#include "rz-graph-build/types/run-type-codes.h"

#include "rz-lisp-graph-rvalue.h"

#include "vector/rz-lisp-vector.h"
#include "vector/rz-string-plex.h"

#include "rz-graph-token/rz-lisp-graph-core-function.h"

#include "string/rz-match-literal.h"
#include "rz-function-def/rz-function-def-info.h"

#include <QRegularExpression>

//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-graph-embed/rz-graph-run-embedder.h"

#include "rz-graph-core/code/rz-re-block-entry.h"

#include "scope/rz-lisp-graph-block-info.h"

#include "scope/rz-lisp-graph-lexical-scope.h"


#include <QStringList>


#include "rzns.h"

USING_RZNS(GVal)
USING_RZNS(GBuild)


RZ_Lisp_Graph_Valuer::RZ_Lisp_Graph_Valuer(RZ_Lisp_Graph_Visitor& rz_lisp_graph_visitor,
 caon_ptr<RZ_Graph_Run_Embedder> embedder)
 : rz_lisp_graph_visitor_(rz_lisp_graph_visitor),
   embedder_(embedder), fr_(RE_Frame::instance()),
    rq_(RE_Query::instance()),
    current_block_info_(nullptr)
{
 init_type_objects();

 init_core_function_redirect_code_map();
 init_callback_code_map();
 init_callback_defer_code_map();

 caon_ptr<RE_Token> retok = new RE_Token("<monotail>", 0);
 caon_ptr<RZ_Lisp_Token> tok = new RZ_Lisp_Token("<monotail>", 0);
 retok->set_lisp_token(tok);
 tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Null_Value));
 tok->set_value(caon_ptr<RZ_Null_Value>(new RZ_Null_Value("<monotail>")));
 the_monotail_ = new tNode(retok);

 current_lexical_scope_ = new RZ_Lisp_Graph_Lexical_Scope;
 root_lexical_scope_ = current_lexical_scope_;

}

void RZ_Lisp_Graph_Valuer::init_core_function_redirect_code_map()
{
 #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
  core_function_redirect_code_map_[#code] = code;
 #include "rz-graph-run/functions/core-functions-valuer-rn.h"
 #include "rz-graph-run/functions/core-functions-valuer-n.h"
 #include "rz-graph-run/functions/core-functions-valuer-n-t.h"
 #include "rz-graph-run/functions/core-functions-valuer-n-s.h"
 #include "rz-graph-run/functions/core-functions-valuer-n-s-s.h"
 #include "rz-graph-run/functions/core-functions-valuer-cb.h"
 #include "rz-graph-run/functions/core-functions-valuer-dc.h"
 #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
}

void RZ_Lisp_Graph_Valuer::init_callback_defer_code_map()
{
 #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
 callback_defer_code_map_[QString(#rz_name).toUpper().replace(':', "__").prepend(':')] = dc_##code;
 #include "rz-graph-run/functions/core-functions-valuer-dc.h"
 #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
}


void RZ_Lisp_Graph_Valuer::init_callback_code_map()
{
 #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
 callback_code_map_[#rz_name] = cb_##code;
 #include "rz-graph-run/functions/core-functions-valuer-cb.h"
 #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
}


void RZ_Lisp_Graph_Valuer::init_type_objects()
{
#define RZ_RUN_TYPE_NS(ns_name, enum_name, name, cpp_name, embed_name, fam) \
 RZ_RUN_TYPE(enum_name, name, cpp_name, embed_name, fam)

#define RZ_RUN_TYPE(enum_name, name, cpp_name, embed_name, fam) \
 add_type_object(dominion_get_type_code<RE_Dominion, cpp_name>(), \
  type_variety_.add_type_object(RZ_Run_Types::enum_name, #enum_name, #cpp_name, #embed_name, #name));
#include "rz-graph-token/types/type-codes.h"
#undef RZ_RUN_TYPE
#undef RZ_RUN_TYPE_NS


 caon_ptr<RZ_Type_Object> rto_Int = type_variety_.get_type_object(RZ_Run_Types::Int);
 rto_Int->flags.is_direct_value = true;

}

QString RZ_Lisp_Graph_Valuer::get_cpp_type_name(QString name)
{
 int index = name.indexOf(QRegularExpression("[&*/]"));
 QString formation;
 if(index != -1)
 {
  formation = name.mid(index);
  name = name.left(index);
 }

 QString result = type_variety_.get_cpp_type_name(name);
 if(result.isEmpty())
  result = name;
 result += formation;
 return result;
}

caon_ptr<RZ_Function_Def_Info> RZ_Lisp_Graph_Valuer::new_function_def_info(caon_ptr<RE_Function_Def_Entry> fdef)
{
 return new RZ_Function_Def_Info(*fdef,
   [this](QString str){ return get_cpp_type_name(str); },
      [](RZ_Lisp_Graph_Lexical_Scope& ls, QString symbol_name, QString channel_name_code)
        {
         ls.add_channel_symbol_from_symbol_name(symbol_name, channel_name_code);
        }
 );
}


QString RZ_Lisp_Graph_Valuer::rename_function_name(RZ_Lisp_Token& tok)
{
 caon_ptr<RZ_Type_Object> rtop = tok.type_object();
 if(rtop == type_variety_.get_type_object(RZ_Run_Types::GraphCoreFun))
 {
  caon_ptr<RZ_Lisp_Graph_Core_Function> cf = tok.vh().pRestore<RZ_Lisp_Graph_Core_Function>();
  if(cf)
  {
   CAON_PTR_DEBUG(RZ_Lisp_Graph_Core_Function ,cf)
   QString n = cf->name();
   return n;
  }

 }

 return QString();
}



void RZ_Lisp_Graph_Valuer::add_type_object(RE_Dominion::Type_Codes code,
 caon_ptr<RZ_Type_Object> rto)
{
 if(code != RE_Dominion::Type_Codes::N_A)
  type_objects_by_code_.insert(code, rto);

}


void RZ_Lisp_Graph_Valuer::init_opaque_call(tNode& pre_entry_node,
 tNode& entry_node)
{
 caon_ptr<RZ_Lisp_Token> tok = entry_node.lisp_token();

 tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Opc));

 caon_ptr<RZ_Opaque_Call> val = new RZ_Opaque_Call(&pre_entry_node, &entry_node);
 tok->set_value(val);

}


void RZ_Lisp_Graph_Valuer::run_deferred_callback(QString qs)
{
 Callback_Codes code = callback_defer_code_map_.value(qs, Callback_Code_Not_Recognized);
 switch(code)
 {
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
 case dc_##code: \
  run_##code(); \
  break;
  #include "rz-graph-run/functions/core-functions-valuer-dc.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE

 Callback_Code_Not_Recognized:
  // //  Maybe an error...
  break;
 default:
  break;
 }
}


void RZ_Lisp_Graph_Valuer::run_Debug_Hook()
{

}


void RZ_Lisp_Graph_Valuer::check_type_objects()
{
 int len = type_objects_by_code_.size();


 QMapIterator<RE_Dominion::Type_Codes, caon_ptr<RZ_Type_Object>> it(type_objects_by_code_);
 while(it.hasNext())
 {
  it.next();
  RE_Dominion::Type_Codes c = it.key();
  const RZ_Type_Object& rto = *it.value();

 }
}

void RZ_Lisp_Graph_Valuer::redirect_core_function(RZ_Lisp_Graph_Result_Holder& rh,
 QString function_name, tNode& start_node)
{
 Core_Function_Redirect_Codes code =
   core_function_redirect_code_map_.value(function_name, Core_Function_Code_Not_Recognized);
 switch(code)
 {
 case Core_Function_Code_Not_Recognized: break;

  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
   case code: \
    run_dc_rename(rh, #rz_name, start_node); \
    break;
   #include "rz-graph-run/functions/core-functions-valuer-dc.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
   case code: \
    run_rename(rh, #code, start_node); \
    break;

   #include "rz-graph-run/functions/core-functions-valuer-rn.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
   case code: \
     run_##code(rh, start_node); \
     break;
   #include "rz-graph-run/functions/core-functions-valuer-n.h"
   #include "rz-graph-run/functions/core-functions-valuer-cb.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
   case code: \
    { \
     caon_ptr<RZ_Lisp_Token> token = get_next_token(start_node); \
     if(token) \
       run_##code(rh, start_node, *token); \
     break; \
    }
  #include "rz-graph-run/functions/core-functions-valuer-n-t.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
  case code: \
  { \
   caon_ptr<RZ_Lisp_Token> token = get_next_token(start_node); \
   if(token) \
    run_##code(rh, start_node, token->string_value()); \
   break; \
  }
  #include "rz-graph-run/functions/core-functions-valuer-n-s.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
  #define RZ_LISP_GRAPH_FUNCTION_DECLARE(rz_name, code, arity, ftype) \
  case code: \
  { \
   QString arg2; \
   caon_ptr<RZ_Lisp_Token> token = get_second_next_token_string(start_node, arg2); \
   if(token) \
     run_##code(rh, start_node, token->string_value(), arg2); \
   break; \
  }
  #include "rz-graph-run/functions/core-functions-valuer-n-s-s.h"
  #undef RZ_LISP_GRAPH_FUNCTION_DECLARE
 }
}


void RZ_Lisp_Graph_Valuer::enter_new_lexical_scope()
{
 CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
 current_lexical_scope_ = new RZ_Lisp_Graph_Lexical_Scope(current_lexical_scope_);
}

void RZ_Lisp_Graph_Valuer::leave_lexical_scope()
{
 CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
 if(current_lexical_scope_)
 {
  current_lexical_scope_ = current_lexical_scope_->parent();
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
  CAON_DEBUG_NOOP
 }
}

void RZ_Lisp_Graph_Valuer::set_token_as_symbol(caon_ptr<RZ_Lisp_Token> token, caon_ptr<tNode> node)
{
 token->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Sym));
 token->set_value(node);
}


QString RZ_Lisp_Graph_Valuer::value_to_string(QString& type, const RZ_Lisp_Graph_Scope_Token& st)
{
 QString value_type;
 QString result;
 RZ_Run_Types::Enum str_code = RZ_Run_Type_Code<RZ_String>::Value;
 caon_ptr<RZ_Type_Object> rto = type_variety_.get_type_object(str_code);
 if(st.type_matches(rto))
 {
  caon_ptr<RZ_String> rzs = st.vh().pRestore<RZ_String>();
  CAON_PTR_DEBUG(RZ_String ,rzs)
  value_type = rto->name();
  result = rzs->to_string();
 }
 else
 {
  result = st.value_to_string(value_type, type_variety_);
 }
 if(st.declared_type_name().isEmpty())
 {
  type = value_type;
 }
 else
 {
  // // mistake; type-mismatch?
  type = st.declared_type_name();
 }
 return result;
}


void RZ_Lisp_Graph_Valuer::check_node_type(caon_ptr<tNode>& node)
{
 check_monotail(node);
 if(!node)
  return;

 if(caon_ptr<RE_Call_Entry> rce = node->re_call_entry())
 {
  qDebug() << "rce";
 }
 caon_ptr<RZ_Lisp_Token> tok = node->lisp_token();

 if(!tok)
  return;

 CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)

 if(tok->type_object())
  return;
 if(caon_ptr<tNode> value_node = rq_.Static_Init_Value(node))
 {
  RE_Dominion::Type_Codes tc = value_node->type_code();
  caon_ptr<RZ_Type_Object> tobj = type_objects_by_code_[tc];

  return;
 }
 if(tok->flags.is_nested_opaque_call)
 {
  // //   Should have been handled already...
  //?
  //?init_opaque_call(*node);
  //?return;
 }
 if(tok->flags.is_symbol_declaration)
 {
  set_token_as_symbol(tok, node);

  return;
 }
 else if(tok->flags.is_numeric_literal)
  type_numeric_token(*tok);
 else if(tok->flags.is_string_literal)
  type_string_token(*tok);
 else if(tok->flags.is_match_literal)
  type_match_literal_token(*tok);

 else if(tok->flags.is_declaration_arrow)
 {
  tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::FnDefInfo));
  caon_ptr<RE_Node> n = rq_.Run_Function_Def_Entry(node);
  if(n)
  {
   caon_ptr<RZ_Function_Def_Info> fdi = new_function_def_info(n->re_function_def_entry());
   tok->set_value(fdi);
   check_function_def_map_sequence(node, *fdi);
  }
 }
 else if(tok->flags.not_entry)
 {
  // //  Only remaining option now...
  tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Ots));
  tok->set_value(node);
 }
 // //  Use a static function to avoid link dependency
 else if(caon_ptr<RZ_Lisp_Graph_Core_Function> cf =
  rz_lisp_core_function_finder(tok->string_value()))
 {
  tok->flags.is_deferred_core_function_symbol = true;
  tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::GraphCoreFun));
  tok->set_value(cf);
 }
 else
 {
  tok->set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Ots));
  tok->set_value(node);
 }
}


void RZ_Lisp_Graph_Valuer::check_function_def_map_sequence(caon_ptr<tNode> node,
  RZ_Function_Def_Info& fdi)
{
 CAON_PTR_DEBUG(RE_Node ,node)
 caon_ptr<tNode> arrow_node = rq_.Run_Fundef_Map_Key_Sequence(node);

 caon_ptr<RZ_Function_Def_Info> reffdi = nullptr;

 if(!arrow_node)
 {
//?
//  caon_ptr<RE_Function_Def_Entry> fde = fdi.function_def_entry();
//  CAON_PTR_DEBUG(RE_Function_Def_Entry ,fde)
//  caon_ptr<RE_Node> en = fde->prior_node();
//  CAON_PTR_DEBUG(RE_Node ,en)
//    if(caon_ptr<RE_Node> don = rq_.Run_Fundef_Arrow_Sequence(en))

  if(caon_ptr<RE_Node> don = rq_.Run_Fundef_Arrow_Sequence(node))
  {
   CAON_PTR_DEBUG(RE_Node ,don)
   if(caon_ptr<RE_Node> en = rq_.Run_Call_Entry(don))
   {
    CAON_PTR_DEBUG(RE_Node ,en)
    arrow_node = rq_.Run_Call_Sequence(en);
    reffdi = fdi.ref_fdi();
    if(!reffdi)
    {
     reffdi = &fdi;
    }
   }
  }
 }

 if(arrow_node)
 {
  CAON_PTR_DEBUG(tNode ,arrow_node)
    // //   Should the token be already initialized?
  caon_ptr<RZ_Lisp_Token> rzlt = arrow_node->lisp_token();
  if(!rzlt)
  {
   if(caon_ptr<RE_Token> token = arrow_node->re_token())
   {
    RZ_Lisp_Token::init_lisp_token(*token);
    rzlt = arrow_node->lisp_token();
   }
  }
  if(rzlt)
  {
   if(caon_ptr<RE_Node> fdef_node = rq_.Run_Function_Def_Entry(arrow_node))
   {
    if(caon_ptr<RE_Function_Def_Entry> fdef = fdef_node->re_function_def_entry())
    {
//     caon_ptr<RZ_Function_Def_Info> new_fdi = new RZ_Function_Def_Info(*fdef,
//       [this](QString str){ return get_cpp_type_name(str); },

//       [](RZ_Lisp_Graph_Lexical_Scope& ls, QString symbol_name, QString channel_name_code)
//      {
//       ls.add_channel_symbol_from_symbol_name(symbol_name, channel_name_code);
//      }
//       );
     caon_ptr<RZ_Function_Def_Info> new_fdi = new_function_def_info(fdef);
     rzlt->set_value(new_fdi);
     fdi.set_map_key_sequence_ref_node(arrow_node);

     new_fdi->set_map_key_sequence_order(fdi.map_key_sequence_order() + 1);

     new_fdi->flags.has_preceding = true;

     if(reffdi)
     {
      new_fdi->set_ref_fdi(reffdi);
     }

     check_function_def_map_sequence(arrow_node, *new_fdi);
    }
   }
  }
 }
}

void RZ_Lisp_Graph_Valuer::check_monotail(caon_ptr<tNode>& node)
{
 if(node)
  return;
 node = the_monotail_;
}

void RZ_Lisp_Graph_Valuer::type_numeric_token(RZ_Lisp_Token& tok)
{
 QString s = tok.raw_text();
 if(s.contains('.'))
 {
  tok.set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Dbl));
  tok.set_new_copy_value(s.toDouble());
 }
 else
 {
  tok.set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Int));
  tok.set_direct_value(s.toInt());
 }
}

void RZ_Lisp_Graph_Valuer::type_string_token(RZ_Lisp_Token& tok)
{
 tok.set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Str));
 tok.mark_as_string_literal();
}

void RZ_Lisp_Graph_Valuer::type_match_literal_token(RZ_Lisp_Token& tok)
{
 tok.set_type_object(*type_variety_.get_type_object(RZ_Run_Types::Mlt));
}

caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
 RZ_Lisp_Graph_Valuer::check_node_type_with_entry_premise(const RE_Connectors& premise,
  caon_ptr<tNode>& node)
{
 caon_ptr<tNode> result = nullptr;
 CAON_PTR_DEBUG(tNode ,node)
 if(premise)
 {
  switch(premise.case_label)
  {
  case RE_Connectors_Case_Labels::Run_Data_Entry:
   result = initialize_data_entry(*node);
   break;

  case RE_Connectors_Case_Labels::Run_Call_Entry:
   check_node_type(node);
   break;
  }
 }
 else check_node_type(node);
 return result;
}

void RZ_Lisp_Graph_Valuer::add_file_to_process(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Type_Symbol& ots)
{
 QString n = ots.get_name();
 add_file_to_process(n);
}

void RZ_Lisp_Graph_Valuer::add_file_to_process(QString file)
{
 if(file.startsWith('\\'))
 {
  QString dir = rz_lisp_graph_visitor_.document_directory() + "/";
  file.replace(0, 1, dir);
 }
 if(!file.contains('.'))
 {
  file += ".rz";
 }
}

caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
 RZ_Lisp_Graph_Valuer::initialize_data_entry(tNode& node)
{
 caon_ptr<tNode> result = nullptr;
 if(caon_ptr<RE_Tuple_Info> rti = node.re_tuple_info())
 {
  caon_ptr<tNode> first_node = rq_.Run_Data_Entry(&node);
  switch(rti->indicator())
  {
  case RE_Tuple_Info::Tuple_Indicators::Enter_Vector:
  case RE_Tuple_Info::Tuple_Indicators::Enter_Array:
   if(rti->formation() == RE_Tuple_Info::Tuple_Formations::Indicates_Pattern)
   {
    result = initialize_string_plex(*rti, first_node); break;
   }
   else
   {
    result = initialize_vector(*rti, first_node); break;
   }

  default: break;
  }
  if(result)
  {
   if(caon_ptr<tNode> entry_node = rti->call_entry_node())
   {
    entry_node << fr_/rq_.Run_Proxy_Value >> result;
   }

  }
 }
 return result;
}

void RZ_Lisp_Graph_Valuer::check_node_value_proxy(caon_ptr<tNode>& node)
{
 if(caon_ptr<tNode> proxy = rq_.Run_Proxy_Value(node))
 {
  node = proxy;
 }
}

caon_ptr<RZ_Lisp_Token> RZ_Lisp_Graph_Valuer::get_token_from(tNode& node)
{
 if(caon_ptr<RZ_Lisp_Token> result = node.lisp_token())
 {
  return result;
 }
 else if(caon_ptr<RZ_Lisp_Vector> vec = node.vec())
 {
  return vec->token_representation();
 }
 else if(caon_ptr<RZ_String_Plex> rsp = node.str_plex())
 {
  return rsp->token_representation();
 }
 return nullptr;
}

caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
 RZ_Lisp_Graph_Valuer::initialize_string_plex(RE_Tuple_Info& rti, caon_ptr<tNode> first_node)
{
 caon_ptr<RZ_Type_Object> rto = type_variety_.get_type_object(RZ_Run_Types::StrPlex);

 caon_ptr<RZ_String_Plex_Builder> rzspb = nullptr;

 if(caon_ptr<RE_Node> call_entry_node = rti.call_entry_node())
 {
  CAON_PTR_DEBUG(RE_Node ,first_node)
  if(caon_ptr<RE_Node> data_entry_node = rq_.Run_Data_Entry(call_entry_node))
  {
   CAON_PTR_DEBUG(RE_Node ,data_entry_node)
   if(caon_ptr<RE_Node> string_plex_node = rq_.String_Plex_Value(data_entry_node))
   {
    CAON_PTR_DEBUG(RE_Node ,string_plex_node)
    rzspb = string_plex_node->string_plex_builder();
   }
  }
 }
 caon_ptr<RZ_String_Plex> rsp = new RZ_String_Plex(&rti, *rto, rzspb);

 caon_ptr<tNode> vector_node = new tNode(rsp);
 return vector_node;
}

caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
 RZ_Lisp_Graph_Valuer::initialize_vector(RE_Tuple_Info& rti, caon_ptr<tNode> first_node)
{
 caon_ptr<RZ_Type_Object> rto = type_variety_.get_type_object(RZ_Run_Types::Vec);

 caon_ptr<RZ_Lisp_Vector> vect = new RZ_Lisp_Vector(&rti, *rto);
 caon_ptr<tNode> vector_node = new tNode(vect);
 caon_ptr<tNode> n = first_node;
 bool do_check_node_type = vect->elements_are_evaluable();
 while(n)
 {

  if(do_check_node_type)
   check_node_type(n);
  vect->add_node(n);
  caon_ptr<tNode> tn = rq_.Run_Data_Sequence(n);
  if(tn)
   n = tn;
  else
   n = rq_.Run_Call_Sequence(n);
 }
 return vector_node;
}



caon_ptr<RZ_Type_Object>
 RZ_Lisp_Graph_Valuer::get_node_type_object(tNode& node)
{
 if(type_objects_by_code_.find(node.type_code()) != type_objects_by_code_.end())
  return type_objects_by_code_[node.type_code()];
 return nullptr;
}


caon_ptr<RE_Node> RZ_Lisp_Graph_Valuer::register_lexical_symbols
 (RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token, RZ_Lisp_Token& tok, RZ_Lisp_Vector& symvec)
{
 for(caon_ptr<tNode> n : symvec.nodes())
 {
  tNode& node = *n;
  QString str = node.label();
  caon_ptr<RZ_Lisp_Token> symtok = node.lisp_token();

  current_lexical_scope_->add_symbol(*symtok);
 }
 // //  Return for continuing run call
 return symvec.get_call_entry_node();
}

caon_ptr<RE_Node> RZ_Lisp_Graph_Valuer::register_lexical_symbol
 (RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token, RZ_Lisp_Token& tok, RZ_Lisp_Symbol& sym)
{

 current_lexical_scope_->add_symbol(function_token, tok);

 tok.flags.is_untyped_symbol_declaration = true;

 caon_ptr<RE_Node> result = caon_reinterpret_cast<RE_Node>(&sym);

 QStringList qsl;
 caon_ptr<RE_Node> result_fwd = check_skip_symbol_dep_nodes(result, qsl);

 if(!qsl.isEmpty())
 {
  result = result_fwd;
 }


 CAON_PTR_DEBUG(RE_Node ,result)

 return result;
}


caon_ptr<RE_Node> RZ_Lisp_Graph_Valuer::check_skip_symbol_dep_nodes(caon_ptr<RE_Node> start_node,
  QStringList& qsl)
{
 caon_ptr<RE_Node> result = start_node;
 caon_ptr<RE_Node> current = start_node;
 caon_ptr<RE_Node> former = start_node;
 while(current = rq_.Run_Call_Sequence(current))
 {
  if(caon_ptr<RZ_Lisp_Token> tok = current->lisp_token())
  {
   QString rt = tok->string_value();
   if(rt.startsWith('/'))
   {
    tok->flags.is_dep_marker = true;
    if(rt.endsWith('/'))
    {
     result = current;
     rt.chop(1);
     qsl.push_back(rt.mid(1));
     break;
    }
    else
    {
     qsl.push_back(rt.mid(1));
    }
   }
   else if(rt.endsWith('/'))
   {
    result = current;
    rt.chop(1);
    qsl.push_back(rt);
    tok->flags.is_dep_marker = true;
    break;
   }
   else if(qsl.isEmpty())
   {
    result = current;
    break;
   }
   else
   {
    qsl.push_back(rt);
    tok->flags.is_dep_marker = true;
   }
  }
  former = current;
 }
 return result;
}

QString RZ_Lisp_Graph_Valuer::form_type_expression(caon_ptr<RE_Node> entry_node)
{
 QString result = "(";
 for(caon_ptr<RE_Node> node = entry_node; node; node = rq_.Run_Call_Sequence(node))
 {
  CAON_PTR_DEBUG(tNode ,node)
  if(caon_ptr<RZ_Lisp_Token> token = node->lisp_token())
  {
   QString sv = token->string_value();
   // //  Obviously, at some point this has to be more general
   type_variety_.check_embed_type_name(sv);
   result += sv + ' ';
  }
  caon_ptr<RE_Node> nested_entry_node = rq_.Run_Call_Entry(node);
  caon_ptr<RE_Node> prior_nested = nullptr;
  while(nested_entry_node)
  {
   CAON_PTR_DEBUG(RE_Node ,nested_entry_node)
   if(caon_ptr<RE_Call_Entry> rce = nested_entry_node->re_call_entry())
   {
    CAON_PTR_DEBUG(RE_Call_Entry ,rce)
    if(nested_entry_node = rq_.Run_Call_Entry(nested_entry_node))
    {
     QString nested = form_type_expression(nested_entry_node);
     result += nested + ' ';
     prior_nested = nested_entry_node;
     nested_entry_node = rq_.Run_Cross_Sequence(nested_entry_node);
    }
   }
   // else : need to handle cross-continue
  }
 }
 if(result.endsWith(' '))
  result.chop(1);
 result += ')';
 return result;
}

caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
RZ_Lisp_Graph_Valuer::register_lexical_symbol
 (RZ_Lisp_Token& function_token, RZ_Lisp_Token& tok, RZ_Opaque_Call& opc)
{
 caon_ptr<tNode> result = nullptr;
 caon_ptr<tNode> en = opc.entry_node();
 if(en)
 {
  CAON_PTR_DEBUG(tNode ,en)
  caon_ptr<tNode> pen = opc.pre_entry_node();
  CAON_PTR_DEBUG(tNode ,pen)
  if(caon_ptr<tNode> declaration_node = rq_.Run_Cross_Sequence(pen))
  {
   if(caon_ptr<RZ_Lisp_Token> declaration_token = declaration_node->lisp_token())
   {
    CAON_PTR_DEBUG(RZ_Lisp_Token ,declaration_token)
    if(declaration_token->flags.is_symbol_declaration)
    {
     result = declaration_node;
     QString type = form_type_expression(en);
     current_lexical_scope_->add_type_named_symbol(function_token, *declaration_token, type);
    }
   }
  }
 }
 return result;
}


caon_ptr<RZ_Lisp_Graph_Valuer::tNode>
RZ_Lisp_Graph_Valuer::register_lexical_symbol
 (RZ_Lisp_Token& function_token, RZ_Lisp_Token& tok, RZ_Opaque_Type_Symbol& ots)
{
 caon_ptr<tNode> result = nullptr;
 QString type = ots.get_name();
 caon_ptr<tNode> n = ots.get_node();
 caon_ptr<RZ_Lisp_Token> declaration_token = nullptr;
 QStringList keywords;

 while(n = rq_.Run_Call_Sequence(n))
 {
  caon_ptr<RZ_Lisp_Token> next_token = n->lisp_token();
  CAON_PTR_DEBUG(RZ_Lisp_Token ,next_token)
  if(!next_token)
   continue;
  if(next_token->flags.is_symbol_declaration)
  {
   result = n;
   declaration_token = next_token;
  }
  else if(next_token->flags.is_keyword)
   keywords << next_token->string_value();
  else if(declaration_token)
   break;
  else
   keywords << next_token->string_value();
 }

 if(declaration_token)
 {
  CAON_PTR_DEBUG(RZ_Lisp_Token ,declaration_token)
  current_lexical_scope_->add_type_named_symbol(function_token, *declaration_token, type);
  tok.flags.is_type_symbol_in_declaration = true;
 }

 if(result)
 {
  caon_ptr<tNode> nn = rq_.Run_Call_Sequence(result);
  check_node_type(nn);
 }

 CAON_PTR_DEBUG(RE_Node ,result)

 return result;

}


void RZ_Lisp_Graph_Valuer::set_returns_to_equal(RZ_Lisp_Graph_Result_Holder& rh,
 RZ_Lisp_Graph_Value_Holder& rhs)
{
 current_block_info_->add_returns_assignment(rhs);
 rh.skip_redirect();
}


void RZ_Lisp_Graph_Valuer::set_preinit_to_equal(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 if(caon_ptr<RZ_Opaque_Type_Symbol> otsl = lhs.pRestore<RZ_Opaque_Type_Symbol>())
 {
  if(caon_ptr<tNode> n = otsl->get_node())
  {
   set_preinit_to_equal(rh, n, rhs);
  }
 }
}


void RZ_Lisp_Graph_Valuer::preinit_assign_to_type_overloadable(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 rh.skip_redirect();

 // anything here?
}

void RZ_Lisp_Graph_Valuer::add_statement_element_node(caon_ptr<tNode> node, caon_ptr<RZ_Code_Statement> st)
{
 caon_ptr<tNode> stn = new tNode(st);
 node << fr_/rq_.Element_Association >> stn;
}


void RZ_Lisp_Graph_Valuer::assign_to_type(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 rh.skip_redirect();

 caon_ptr<RZ_Type_Object> lto = lhs.type_object();
 caon_ptr<RZ_Type_Object> rto = rhs.type_object();

 CAON_PTR_DEBUG(RZ_Type_Object ,lto)
 CAON_PTR_DEBUG(RZ_Type_Object ,rto)

 // //  check for statement kind ...
 if(caon_ptr<RE_Node> lfn = rh.get_lead_function_node())
 {
  check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds::Type_Declaration,
    "my", lfn);

 }




 if(lhs.type_is(Sym))
 {
  caon_ptr<RZ_Lisp_Symbol> sym = lhs.pRestore<RZ_Lisp_Symbol>();
  caon_ptr<RE_Node> n = sym.caon_reinterpret_cast<RE_Node>();
  if(n)
  {
   caon_ptr<RZ_Lisp_Token> tok = n->lisp_token();
   CAON_PTR_DEBUG(RE_Node ,n)
   CAON_PTR_DEBUG(RZ_Lisp_Token ,tok)
   CAON_DEBUG_NOOP

   if(rto->id() == RZ_Run_Types::Ots)
   {
    if(caon_ptr<RZ_Opaque_Type_Symbol> ots = rhs.pRestore<RZ_Opaque_Type_Symbol>())
    {
     if(caon_ptr<RZ_Lisp_Token> token = ots->get_token())
     {
      CAON_PTR_DEBUG(RZ_Lisp_Token ,token)
      QString rt = token->raw_text();
      token->flags.is_type_symbol_in_declaration = true;
      current_lexical_scope_->mark_type_assertion(*tok, rt);

     }
    }
   }
  }
 }


}


void RZ_Lisp_Graph_Valuer::set_preinit_equal_formula(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 set_preinit_equal(rh, function_token, lhs, rhs);
}



void RZ_Lisp_Graph_Valuer::set_init_or_preinit_equal(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs, caon_ptr<RZ_Opaque_Type_Symbol> otsl)
{
 bool has_assignment_initialization_expression = false;


 if(rhs.type_is(Ots))
 {
  if(caon_ptr<RZ_Opaque_Type_Symbol> otsl = rhs.pRestore<RZ_Opaque_Type_Symbol>())
  {
   if(caon_ptr<tNode> n = otsl->get_node())
   {
    if(caon_ptr<RZ_Lisp_Token> rzlt = n->lisp_token())
    {
     CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
    }
   }
  }
 }
 else if(rhs.type_is(Opc))
 {
  if(caon_ptr<RZ_Opaque_Call> opc = rhs.pRestore<RZ_Opaque_Call>())
  {
   if(caon_ptr<RZ_Lisp_Token> rzlt = opc->get_entry_token())
   {
    CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
    rzlt->flags.is_assignment_initialization_entry = true;
    has_assignment_initialization_expression = true;
   }
  }
 }

 if(caon_ptr<tNode> n = otsl->get_node())
 {
  if(caon_ptr<RZ_Lisp_Token> rzlt = n->lisp_token())
  {
   CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
   if(has_assignment_initialization_expression)
   {
    rzlt->flags.has_assignment_initialization_expression = true;
   }
   else
   {
    rzlt->flags.has_assignment_initialization_token = true;
   }
  }
 }
}


void RZ_Lisp_Graph_Valuer::check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds sk,
  QString check, caon_ptr<RE_Node> fn)
{
 CAON_PTR_DEBUG(RE_Node ,fn)
 if(caon_ptr<RZ_Lisp_Token> rzlt = fn->lisp_token())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
  QString rt = rzlt->raw_text();

  // //  this might better be a flag, maybe?
  if(rt == check)
  {
   caon_ptr<RZ_Code_Statement> st = new RZ_Code_Statement(sk, fn);
   add_statement_element_node(fn, st);
  }
 }
}


void RZ_Lisp_Graph_Valuer::set_preinit_equal(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 if(caon_ptr<RZ_Opaque_Type_Symbol> otsl = lhs.pRestore<RZ_Opaque_Type_Symbol>())
 {
  set_init_or_preinit_equal(rh, function_token, lhs, rhs, otsl);

  // //  check for statement kind ...
  if(caon_ptr<RE_Node> lfn = rh.get_lead_function_node())
  {
   CAON_PTR_DEBUG(RE_Node ,lfn)
   if(caon_ptr<RZ_Lisp_Token> rzlt = lfn->lisp_token())
   {
    // //  do we always need ft.value == rzlt.value?
    caon_ptr<RZ_Lisp_Token> ft = &function_token;
    if(ft == rzlt)
    {
     check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds::Assignment,
       "\\=", lfn);
    }

   }
  }

 }

 caon_ptr<RZ_Type_Object> rto = rhs.type_object();

 CAON_PTR_DEBUG(RZ_Type_Object ,rto)
}


void RZ_Lisp_Graph_Valuer::set_preinit_equal_to_type(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 if(caon_ptr<RZ_Opaque_Type_Symbol> otsr = rhs.pRestore<RZ_Opaque_Type_Symbol>())
 {
  if(caon_ptr<tNode> n = otsr->get_node())
  {
   if(caon_ptr<RZ_Lisp_Token> tok = n->lisp_token())
   {
    if(tok->raw_text() == "default")
    {
     tok->flags.is_assign_to_default_ctor = true;
    }
   }
  }
 }
 // //  check for statement kind ...
 if(caon_ptr<RE_Node> lfn = rh.get_lead_function_node())
 {
  CAON_PTR_DEBUG(RE_Node ,lfn)
  if(caon_ptr<RZ_Lisp_Token> rzlt = lfn->lisp_token())
  {
   // //  do we always need ft.value == rzlt.value?
   caon_ptr<RZ_Lisp_Token> ft = &function_token;
   if(ft == rzlt)
   {
    check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds::Assignment,
      "\\==", lfn);
   }
  }
 }

}


void RZ_Lisp_Graph_Valuer::set_preinit_to_equal(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> n, RZ_Lisp_Graph_Value_Holder& rhs)
{
 CAON_PTR_DEBUG(tNode ,n)

 if(current_block_info_)
 {
  current_block_info_->add_assignment(n, rhs);
  if(caon_ptr<RZ_Lisp_Token> token = n->lisp_token())
  {
   current_block_info_->add_assignment_count(token->lisp_string_value());
  }
 }

 rh.skip_redirect();

 CAON_DEBUG_NOOP
}

void RZ_Lisp_Graph_Valuer::check_assignments()
{
 CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
 CAON_DEBUG_NOOP
}


void RZ_Lisp_Graph_Valuer::set_equal_via_type(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs)
{
 set_equal(rh, function_token, lhs, rhs, Via_Type);
}

void RZ_Lisp_Graph_Valuer::set_equal(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Token& function_token,
 RZ_Lisp_Graph_Value_Holder& lhs, RZ_Lisp_Graph_Value_Holder& rhs, Set_Equal_Modes mode)
{
 QString tts = lhs.type_to_string();
 if(lhs.type_is(Sym))
 {
  caon_ptr<RZ_Lisp_Symbol> sym = lhs.pRestore<RZ_Lisp_Symbol>();
  caon_ptr<RE_Node> n = sym.caon_reinterpret_cast<RE_Node>();
  if(n)
  {
   caon_ptr<RZ_Lisp_Token> tok = n->lisp_token();
   set_symbol_equal(rh, n, function_token, *tok, rhs, mode);
  }
 }
 else if(lhs.type_is(Ots))
 {
  if(caon_ptr<RZ_Opaque_Type_Symbol> otsl = lhs.pRestore<RZ_Opaque_Type_Symbol>())
  {
   set_init_or_preinit_equal(rh, function_token, lhs, rhs, otsl);
  }
 }
 else if(lhs.type_is(Vec))
 {
  RZ_Lisp_Vector& vec = *lhs.pRestore<RZ_Lisp_Vector>();

  int i = 0;
  int rhs_max;

  QVector<caon_ptr<RE_Node>> rhs_nodes;

  if(rhs.type_is(Vec))
  {
   RZ_Lisp_Vector& rvec = *rhs.pRestore<RZ_Lisp_Vector>();
   rhs_nodes = rvec.nodes();
   rhs_max = rhs_nodes.size();
  }
  else
   rhs_max = 0;

  caon_ptr<RZ_Lisp_Token> last_rtok = nullptr;

  caon_ptr<RE_Node> rhs_node = nullptr;

  for(caon_ptr<RE_Node> n : vec.nodes())
  {
   RE_Node& node = *n;
   caon_ptr<RZ_Lisp_Token> tok = n->lisp_token();
   if(i < rhs_max)
   {
    rhs_node = rhs_nodes[i];
    CAON_PTR_DEBUG(RE_Node ,rhs_node)

    caon_ptr<RZ_Lisp_Token> rtok = get_token_from(*rhs_node);

    if(rtok)
     set_symbol_equal(rh, n, function_token, *tok, rtok->vh(), mode);

    last_rtok = rtok;
    ++i;
   }
   // //  Check whether there's a problem with multiple
   //     references to the same vh()...
   else if(last_rtok)
   {
    set_symbol_equal(rh, n, function_token, *tok, last_rtok->vh(), mode);
   }
   else
   {
    set_symbol_equal(rh, n, function_token, *tok, rhs, mode);
   }
  }
 }
 else
 {
  rh.skip_redirect();
 }

 // //  always?
 if(caon_ptr<RE_Node> lfn = rh.get_lead_function_node())
 {
  CAON_PTR_DEBUG(RE_Node ,lfn)
  if(caon_ptr<RZ_Lisp_Token> rzlt = lfn->lisp_token())
  {
   // //  do we always need ft.value == rzlt.value?
   caon_ptr<RZ_Lisp_Token> ft = &function_token;
   if(ft == rzlt)
   {
    switch(mode)
    {
    case Set_Equal_Modes::Normal:
     check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds::Assignment,
      "=", lfn);
     break;
    case Set_Equal_Modes::Via_Type:
     check_identify_statement_kind(RZ_Code_Statement::Statement_Kinds::Assignment,
      "==", lfn);
     break;
    default: break;
    }
   }
  }
 }
}

void RZ_Lisp_Graph_Valuer::set_symbol_equal(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> n, RZ_Lisp_Token& function_token,
 RZ_Lisp_Token& tok, RZ_Lisp_Graph_Value_Holder& vh, Set_Equal_Modes mode)
{
 RZ_Lisp_Graph_Rvalue rv(vh);
 QString sv = function_token.string_value();
 if(sv.startsWith('.'))
 {
  sv.chop(1);
 }
 if(sv == "my")
 {
  set_lexical_symbol_equal(rh, n, function_token, tok, rv, mode);
 }
}


RZ_Lisp_Graph_Basic_Type_Groups
 RZ_Lisp_Graph_Valuer::parse_basic_type_group(const RZ_Lisp_Graph_Scope_Token& st)
{
 if(st.vh().type_is(Opc))
  return RZ_Lisp_Graph_Basic_Type_Groups::Opaque_Call;
 else if(st.vh().type_is(Ots))
  return RZ_Lisp_Graph_Basic_Type_Groups::Opaque_Symbol;
 else if(st.vh().type_is(FnDefInfo))
  return RZ_Lisp_Graph_Basic_Type_Groups::Function_Def_Info;
 else if(st.vh().type_is(GraphCoreFun))
  return RZ_Lisp_Graph_Basic_Type_Groups::Core_Function;
 else if(st.vh().type_is(Vec))
  return RZ_Lisp_Graph_Basic_Type_Groups::Tuple;
 else
 {
  caon_ptr<RZ_Type_Object> rto = st.vh().type_object();
  CAON_PTR_DEBUG(RZ_Type_Object ,rto)
  return RZ_Lisp_Graph_Basic_Type_Groups::N_A;
 }
}


void RZ_Lisp_Graph_Valuer::set_lexical_symbol_equal(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> n, RZ_Lisp_Token& function_token, RZ_Lisp_Token& tok,
 RZ_Lisp_Graph_Rvalue& rv, Set_Equal_Modes mode)
{
 rh.skip_redirect();
 QString sv = tok.string_value();
 current_lexical_scope_->mark_value(tok, rv.vh());
 CAON_PTR_DEBUG(tNode ,n)

 if(embedder_)
 {
  if(caon_ptr<RZ_Lisp_Token> rzlt = rh.function_token())
  {
   CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
   rzlt->flags.is_lex_assignment_entry = true;
  }

  caon_ptr<RZ_Type_Object> rto1 = tok.vh().type_object();
  CAON_PTR_DEBUG(RZ_Type_Object ,rto1)

  caon_ptr<RE_Node> n = caon_reinterpret_cast<RE_Node>(tok.vh().value().raw_pointer());
  CAON_PTR_DEBUG(RE_Node ,n)

  RZ_Type_Object& rto = *rv.vh().type_object();

  if(rto.id() == RZ_Run_Types::FnDefInfo)
  {
   RZ_Function_Def_Info& fdi = rv.vh().retrieve<RZ_Function_Def_Info>();
   RE_Function_Def_Entry& fdef = *fdi.function_def_entry();
   fdi.flags.lexical_lambda = true;
   if(tok.flags.is_type_symbol_declaration)
   {
    fdi.flags.type_symbol_assignment = true;
   }

  }
  if(rto.id() == RZ_Run_Types::GraphCoreFun)
  {
   caon_ptr<tNode> lfn = rh.get_lead_function_node();
   CAON_PTR_DEBUG(tNode ,lfn);

   current_block_info_->add_assignment(n, rv.vh());

   if(caon_ptr<RZ_Lisp_Token> token = n->lisp_token())
   {
    current_block_info_->add_assignment_count(token->lisp_string_value());
   }
  }
  else if(rto.id() == RZ_Run_Types::Opc)
  {
   if(caon_ptr<RZ_Opaque_Call> opc = rv.vh().pRestore<RZ_Opaque_Call>())
   {
    if(mode == Via_Type || mode == Their_Via_Type)
    {
     if(caon_ptr<RZ_Lisp_Token> rzlt = opc->get_entry_token())
     {
      CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
      rzlt->flags.is_via_type_assignment = true;
     }
    }
   }

   if(current_block_info_)
   {
    current_block_info_->add_assignment(n, rv.vh());
    if(caon_ptr<RZ_Lisp_Token> token = n->lisp_token())
    {
     current_block_info_->add_assignment_count(token->lisp_string_value());
    }
   }
  }
  else if(rto.id() == RZ_Run_Types::Vec)
  {
   RZ_Lisp_Vector& vec = *rv.vh().pRetrieve<RZ_Lisp_Vector>();

   tNode& en = *vec.get_call_entry_node();
   embedder_->redirect_to_noop(rh, *rh.get_lead_function_node());
  }
  else if(rto.id() == RZ_Run_Types::Ots)
  {
   CAON_PTR_DEBUG(tNode ,n)

   QString value_string;
   if(caon_ptr<RZ_Opaque_Type_Symbol> ots = rv.vh().pRestore<RZ_Opaque_Type_Symbol>())
   {
    if(caon_ptr<RZ_Lisp_Token> token = ots->get_token())
    {
     if(mode == Via_Type || mode == Their_Via_Type)
     {
      token->flags.is_via_type_assignment = true;
     }
    }
    value_string = ots->get_name();
   }

   if(current_block_info_)
   {
    current_block_info_->add_assignment(n, rv.vh());
    if(caon_ptr<RZ_Lisp_Token> token = n->lisp_token())
    {
     current_block_info_->add_assignment_count(token->lisp_string_value());
    }
   }

   if(value_string == "nil")
   {
    embedder_->redirect_to_noop(*rh.get_lead_function_node());
   }
   else
   {
    rh.skip_redirect();
   }
   CAON_DEBUG_NOOP
  }
  else
  {
   //  My is not a noop, for cl, at file scope...
   //?
   CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
   if(current_lexical_scope_)
   {
    if(current_lexical_scope_->parent())
    {
     embedder_->redirect_to_noop(*rh.get_lead_function_node());
    }
   }
  }
 }

}

QString RZ_Lisp_Graph_Valuer::node_to_string(tNode& n)
{
 if(caon_ptr<RZ_Lisp_Token> tok = n.lisp_token())
 {
  if(tok->type_is(Str))
  {
   if(caon_ptr<RZ_String> rzs = tok->pRestore<RZ_String>())
    return rzs->to_string();
  }
 }
 return QString();
}



void RZ_Lisp_Graph_Valuer::insert_collection_node(tNode& new_node, tNode& lhs_node,
 RE_Connectors& rhs_premise, tNode& rhs_node)
{
//??
}

caon_ptr<tNode> RZ_Lisp_Graph_Valuer::retval_follow(caon_ptr<tNode> n)
{
 return rq_.Retval_Follow(n);
}


void RZ_Lisp_Graph_Valuer::run_rename
 (RZ_Lisp_Graph_Result_Holder& rh, QString function_name, tNode& function_node)
{
 //? just for now...
 if(function_name != "print")
  function_name.prepend("rz-");

 if(embedder_)
  embedder_->embed_rename(rh, function_name, function_node);

 rh.flags.proceed_anticipate_nested_run_call = true;
}

void RZ_Lisp_Graph_Valuer::run_dc_rename(RZ_Lisp_Graph_Result_Holder& rh,
 QString function_name, tNode& function_node)
{
 if(embedder_)
  embedder_->embed_deferred_callback(rh, function_name, function_node);

}

bool RZ_Lisp_Graph_Valuer::check_embed_noop(caon_ptr<tNode> start_node)
{
 CAON_PTR_DEBUG(RE_Node, start_node)

   if(caon_ptr<tNode> sern = rq_.Run_Embed_Redirect(start_node))
   {
    CAON_PTR_DEBUG(RE_Node, sern)
    return embedder_->match_noop_node(sern);
   }

//?
 if(caon_ptr<RE_Node> ce_node = rq_.Run_Call_Entry(start_node))
 {
  CAON_PTR_DEBUG(RE_Node, ce_node)
  ce_node->debug_connections();
  if(caon_ptr<tNode> ern = rq_.Run_Embed_Redirect(ce_node))
  {
   CAON_PTR_DEBUG(RE_Node, ern)
   return embedder_->match_noop_node(ern);
  }
 }
 return false;

}



void RZ_Lisp_Graph_Valuer::run_Enum(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& start_node)
{

}

void RZ_Lisp_Graph_Valuer::init_do_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Function_Def_Info& rfdi)
{
 rfdi.flags.do_lambda = true;

 rfdi.flags.lexical_lambda = true;

 caon_ptr<RE_Node> fnode = rh.get_lead_function_node();
 CAON_PTR_DEBUG(RE_Node ,fnode)

 caon_ptr<RE_Function_Def_Entry> fde = rfdi.function_def_entry();
 caon_ptr<RE_Node> fden = rfdi.function_def_entry_node();

 CAON_PTR_DEBUG(RE_Function_Def_Entry ,fde)
 CAON_PTR_DEBUG(RE_Node ,fden)

 QString label;
 if(caon_ptr<RE_Node> ln = fde->label_node())
 {
  if(caon_ptr<RE_Token> lt = ln->re_token())
  {
   label = lt->raw_text();
  }
 }

 rh.skip_redirect();

}


void RZ_Lisp_Graph_Valuer::check_init_do_map_inner_block(tNode& n, caon_ptr<RZ_Clasp_Source_Element> el)
{
 if(caon_ptr<RZ_Lisp_Token> rzlt = n.lisp_token() )
 {
  if(caon_ptr<RZ_Function_Def_Info> fdi = rzlt->pRestore<RZ_Function_Def_Info>())
  {
   CAON_PTR_DEBUG(RZ_Function_Def_Info ,fdi)
   caon_ptr<RZ_Clasp_Source_Element> next_el = init_do_map_inner_block(*fdi, el);

   if(next_el)
   {
    if(caon_ptr<RE_Node> next_arrow_node = fdi->map_key_sequence_ref_node())
    {
     CAON_PTR_DEBUG(RE_Node ,next_arrow_node)
     check_init_do_map_inner_block(*next_arrow_node, next_el);
     CAON_DEBUG_NOOP
    }
   }
  }
 }
}


caon_ptr<RZ_Clasp_Source_Element> RZ_Lisp_Graph_Valuer::init_do_map_inner_block(RZ_Function_Def_Info& rfdi, caon_ptr<RZ_Clasp_Source_Element> el)
{
 CAON_PTR_DEBUG(RZ_Clasp_Source_Element ,el)
 rfdi.flags.do_lambda = true;

 rfdi.flags.lexical_lambda = true;

 caon_ptr<RE_Function_Def_Entry> fde = rfdi.function_def_entry();
 caon_ptr<RE_Node> fden = rfdi.function_def_entry_node();

 CAON_PTR_DEBUG(RE_Function_Def_Entry ,fde)
 CAON_PTR_DEBUG(RE_Node ,fden)

 caon_ptr<RZ_Clasp_Source_Element> result = nullptr;

 QString fn_name_hint = QString("do: %1").arg(rfdi.map_key_sequence_order());

 return result;
}




void RZ_Lisp_Graph_Valuer::init_scan_block(RZ_Lisp_Graph_Result_Holder& rh,
 RZ_Opaque_Type_Symbol& ots)
{
 caon_ptr<tNode> en = ots.get_node();
 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(en))
 {
  init_scan_block(rh, nullptr, en, ben);
 }
}


void RZ_Lisp_Graph_Valuer::init_scan_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Call& opc)
{
 caon_ptr<tNode> pen = opc.pre_entry_node();
 caon_ptr<tNode> en = opc.entry_node();
 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(pen))
 {
  init_scan_block(rh, pen, en, ben);
 }
}

void RZ_Lisp_Graph_Valuer::init_scan_block(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> pre_entry_node, caon_ptr<tNode> start_node, caon_ptr<tNode> block_entry_node)
{
 CAON_PTR_DEBUG(tNode ,pre_entry_node)
 CAON_PTR_DEBUG(tNode ,start_node)
 CAON_PTR_DEBUG(tNode ,block_entry_node)
 caon_ptr<tNode> fnode = rh.function_node();

 if(caon_ptr<RZ_Lisp_Token> rzlt = fnode->lisp_token())
 {
  rzlt->flags.is_assignment_block_entry = true;
 }

 current_block_info_ = new RZ_Lisp_Graph_Block_Info(block_entry_node, current_block_info_);

 caon_ptr<tNode> current_block_info_node = new RE_Node(current_block_info_);

 CAON_PTR_DEBUG(tNode ,current_block_info_node)

 fnode << fr_/rq_.Block_Info >> current_block_info_node;

 CAON_PTR_DEBUG(tNode ,fnode)

 if(pre_entry_node)
 {
  if(caon_ptr<RE_Call_Entry> rce = pre_entry_node->re_call_entry())
  {
   CAON_PTR_DEBUG(RE_Call_Entry ,rce)
   rce->set_block_continue_node(block_entry_node);
  }
 }
 if(block_entry_node)
 {
  if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
  {
   rbe->flags.scan_block = true;
  }
 }
 if(embedder_)
 {

 }
 rh.flags.skip_redirect = true;
}





void RZ_Lisp_Graph_Valuer::init_if_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Core_Function& corefun)
{
// caon_ptr<tNode> pen = corefun.pre_entry_node();
// caon_ptr<tNode> en = corefun.entry_node();
// if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(pen))
// {
//  init_if_block(rh, pen, en, ben);
// }
}


void RZ_Lisp_Graph_Valuer::init_if_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Call& opc)
{
 caon_ptr<tNode> pen = opc.pre_entry_node();
 caon_ptr<tNode> en = opc.entry_node();
 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(pen))
 {
  init_if_block(rh, pen, en, ben);
 }
}


void RZ_Lisp_Graph_Valuer::init_if_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Type_Symbol& ots)
{
 caon_ptr<tNode> n = ots.get_node();

 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(n))
 {
  init_if_block(rh, n, n, ben);
 }
}

void RZ_Lisp_Graph_Valuer::init_if_block(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> pre_entry_node, caon_ptr<tNode> start_node, caon_ptr<tNode> block_entry_node)
{
 CAON_PTR_DEBUG(tNode ,pre_entry_node)
 CAON_PTR_DEBUG(tNode ,start_node)
 CAON_PTR_DEBUG(tNode ,block_entry_node)
 caon_ptr<tNode> fnode = rh.function_node();

 if(caon_ptr<RZ_Lisp_Token> rzlt = fnode->lisp_token())
 {
  rzlt->flags.is_assignment_block_entry = true;
 }

 current_block_info_ = new RZ_Lisp_Graph_Block_Info(block_entry_node, current_block_info_);

 caon_ptr<tNode> current_block_info_node = new RE_Node(current_block_info_);

 CAON_PTR_DEBUG(tNode ,current_block_info_node)

 fnode << fr_/rq_.Block_Info >> current_block_info_node;

 CAON_PTR_DEBUG(tNode ,fnode)

 if(caon_ptr<RE_Call_Entry> rce = pre_entry_node->re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  rce->set_block_continue_node(block_entry_node);
 }
  if(block_entry_node)
  {
   if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
   {
    rbe->flags.if_block = true;
   }
  }
 if(embedder_)
 {
 }
 rh.flags.skip_redirect = true;
}



void RZ_Lisp_Graph_Valuer::init_elsif_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Lisp_Graph_Core_Function& corefun)
{

}

void RZ_Lisp_Graph_Valuer::init_elsif_block(RZ_Lisp_Graph_Result_Holder& rh, RZ_Opaque_Call& opc)
{
 caon_ptr<tNode> pen = opc.pre_entry_node();
 caon_ptr<tNode> en = opc.entry_node();
 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(pen))
 {
  init_elsif_block(rh, pen, en, ben);
 }
}

void RZ_Lisp_Graph_Valuer::init_elsif_block(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> pre_entry_node, caon_ptr<tNode> start_node, caon_ptr<tNode> block_entry_node)
{
 CAON_PTR_DEBUG(tNode ,pre_entry_node)
 CAON_PTR_DEBUG(tNode ,start_node)
 CAON_PTR_DEBUG(tNode ,block_entry_node)

 caon_ptr<tNode> fnode = rh.function_node();

 CAON_PTR_DEBUG(tNode ,fnode)

 if(caon_ptr<RZ_Lisp_Token> rzlt = fnode->lisp_token())
 {
  rzlt->flags.is_assignment_block_entry = true;
 }

 CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,current_block_info_)

 //? -- not here ... (see below) current_block_info_->set_continue_node(fnode);

 if(caon_ptr<RE_Node> ben = current_block_info_->block_entry_node())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,current_block_info_)
  if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
  {
   // //  copied from init_else_block ...
   CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
   caon_ptr<RE_Block_Entry> nested_rbe = block_entry_node->re_block_entry();
   CAON_PTR_DEBUG(RE_Block_Entry ,nested_rbe)
   while(rbe->nested_depth() > nested_rbe->nested_depth())
   {
    current_block_info_ = current_block_info_->parent_block_info();
    ben = current_block_info_->block_entry_node();
    rbe = ben->re_block_entry();
    CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
    CAON_DEBUG_NOOP
   }

   {
    caon_ptr<RE_Block_Entry> current_rbe = rbe;
    CAON_PTR_DEBUG(RE_Block_Entry ,current_rbe)
    current_rbe->flags.has_elsif_block = true;
    current_rbe->set_notes("HAS_ELSIF_BLOCK");
   }



   if(caon_ptr<RE_Node> sen = rbe->statement_entry_node())
   {
    CAON_PTR_DEBUG(RE_Node ,sen)
    sen << fr_/rq_.Run_Nested_Block_Continue >> fnode;
    if(caon_ptr<RE_Node> ren = rq_.Run_Call_Entry(sen))
    {
     CAON_PTR_DEBUG(RE_Node ,ren)
     if(caon_ptr<RZ_Lisp_Token> rzlt = ren->lisp_token())
     {
      CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
      // //  Maybe this is best with a flag rather than raw test...
      if(rzlt->raw_text() == "if")
      {
       rzlt->flags.is_if_with_elsif = true;
      }
      else
      {
       rzlt->flags.is_elsif_with_elsif = true;
      }
     }
    }
   }

  }
 }
 // this has to be after that block because the block may rewind current_block_info_ ...
 current_block_info_->set_continue_node(fnode);


 current_block_info_ = new RZ_Lisp_Graph_Block_Info(block_entry_node, current_block_info_);

 caon_ptr<tNode> current_block_info_node = new RE_Node(current_block_info_);

 CAON_PTR_DEBUG(tNode ,current_block_info_node)

 fnode << fr_/rq_.Block_Info >> current_block_info_node;


 if(caon_ptr<RE_Call_Entry> rce = pre_entry_node->re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  rce->set_block_continue_node(block_entry_node);
  if(block_entry_node)
  {
   if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
   {
    rbe->flags.elsif_block = true;
   }
  }
 }
 if(embedder_)
 {

 }
 rh.flags.skip_redirect = true;
}


void RZ_Lisp_Graph_Valuer::init_else_block(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> pre_entry_node, caon_ptr<tNode> block_entry_node)
{
 caon_ptr<tNode> fnode = rh.function_node();

 caon_ptr<RE_Block_Entry> current_rbe = nullptr;

 if(caon_ptr<RE_Node> ben = current_block_info_->block_entry_node())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,current_block_info_)
  if(caon_ptr<RE_Block_Entry> rbe = ben->re_block_entry())
  {
   current_rbe = rbe;
   CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
   caon_ptr<RE_Block_Entry> nested_rbe = block_entry_node->re_block_entry();
   CAON_PTR_DEBUG(RE_Block_Entry ,nested_rbe)

   while(rbe->nested_depth() > nested_rbe->nested_depth())
   {
    current_block_info_ = current_block_info_->parent_block_info();
    ben = current_block_info_->block_entry_node();
    rbe = ben->re_block_entry();
    CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
    CAON_DEBUG_NOOP
   }

   rbe->flags.has_else_block = true;
   rbe->set_notes("HAS_ELSE_BLOCK");
   if(caon_ptr<RE_Node> sen = rbe->statement_entry_node())
   {
    sen << fr_/rq_.Run_Nested_Block_Continue >> fnode;

    if(caon_ptr<RE_Node> ren = rq_.Run_Call_Entry(sen))
    {
     CAON_PTR_DEBUG(RE_Node ,ren)
     if(caon_ptr<RZ_Lisp_Token> rzlt = ren->lisp_token())
     {
      CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
      // //  Maybe this is best with a flag rather than raw test...
      if(rzlt->raw_text() == "if")
      {
       rzlt->flags.is_if_with_else = true;
      }
      else
      {

      }
     }
    }
   }
  }
 }

 CAON_PTR_DEBUG(RZ_Lisp_Graph_Block_Info ,current_block_info_)
 current_block_info_->set_continue_node(fnode);

 if(caon_ptr<RZ_Lisp_Token> rzlt = fnode->lisp_token())
 {
  rzlt->flags.is_block_entry_suppressing_expression = true;
 }

 current_block_info_ = new RZ_Lisp_Graph_Block_Info(block_entry_node, current_block_info_);

 caon_ptr<tNode> current_block_info_node = new RE_Node(current_block_info_);

 CAON_PTR_DEBUG(tNode ,current_block_info_node)

 fnode << fr_/rq_.Block_Info >> current_block_info_node;

 CAON_PTR_DEBUG(tNode ,fnode)

 CAON_PTR_DEBUG(tNode ,pre_entry_node)

 if(caon_ptr<RE_Call_Entry> rce = pre_entry_node->re_call_entry())
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,rce)
  rce->set_block_continue_node(block_entry_node);
 }
 if(block_entry_node)
 {
  if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
  {
   CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)
   rbe->flags.else_block = true;
   if(current_rbe)
   {
    if(current_rbe->flags.elsif_block)
    {
     CAON_PTR_DEBUG(RE_Block_Entry ,current_rbe)
     CAON_PTR_DEBUG(RE_Block_Entry ,rbe)
     rbe->flags.follows_elsif_block = true;
     rbe->set_notes("END_COND");
    }
   }
  }
 }
 rh.flags.skip_redirect = true;
}


void RZ_Lisp_Graph_Valuer::run_Else(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& start_node)
{
 if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(&start_node))
 {
  CAON_PTR_DEBUG(RZ_Lisp_Graph_Lexical_Scope ,current_lexical_scope_)

  CAON_PTR_DEBUG(tNode ,ben)
  init_else_block(rh, &start_node, ben);
 }
}

void RZ_Lisp_Graph_Valuer::run_Caserun(RZ_Lisp_Graph_Result_Holder& rh,
 tNode& start_node)
{
 if(caon_ptr<tNode> arg = rq_.Run_Call_Sequence(&start_node))
 {
  CAON_PTR_DEBUG(tNode ,arg)
  if(caon_ptr<tNode> ben = rq_.Run_Block_Entry(arg))
  {
   CAON_PTR_DEBUG(tNode ,ben)
   init_caserun_block(rh, &start_node, arg, ben);
  }
 }
}


void RZ_Lisp_Graph_Valuer::init_caserun_block(RZ_Lisp_Graph_Result_Holder& rh,
 caon_ptr<tNode> start_node, caon_ptr<tNode> arg_node, caon_ptr<tNode> block_entry_node)
{
 caon_ptr<tNode> fnode = rh.function_node();

 if(caon_ptr<RZ_Lisp_Token> rzlt = arg_node->lisp_token())
 {
  CAON_PTR_DEBUG(RZ_Lisp_Token ,rzlt)
  rzlt->flags.is_block_entry_suppressing_expression = true;
  rzlt->flags.is_block_entry_caserun = true;
 }

 current_block_info_ = new RZ_Lisp_Graph_Block_Info(block_entry_node, current_block_info_);

 caon_ptr<tNode> current_block_info_node = new RE_Node(current_block_info_);

 CAON_PTR_DEBUG(tNode ,current_block_info_node)

 fnode << fr_/rq_.Block_Info >> current_block_info_node;

 CAON_PTR_DEBUG(tNode ,fnode)

 if(block_entry_node)
 {
  if(caon_ptr<RE_Block_Entry> rbe = block_entry_node->re_block_entry())
  {
   rbe->flags.caserun_block = true;
  }
 }
 rh.flags.skip_redirect = true;
}

