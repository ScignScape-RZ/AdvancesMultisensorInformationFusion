
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef RZ_FUNCTION_DEF_INFO__H
#define RZ_FUNCTION_DEF_INFO__H

#include "accessors.h"

#include "flags.h"

#include <functional>

#include <QString>

#include "rz-graph-core/code/rz-re-function-def-entry.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rzns.h"

#include "flags.h"

#include <QStack>

RZNS_(RECore)

class RE_Node;
class RE_Function_Def_Entry;
class RE_Query;

_RZNS(RECore)

USING_RZNS(RECore)

RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;
class RZ_Function_Def_Syntax;
class RZ_Lisp_Graph_Lexical_Scope;

class RZ_Function_Def_Info
{
public:
 flags_(2)
  bool lambda:1;
  bool type_expression:1;
  bool type_symbol_assignment:1;
  bool monad:1;
  bool with_matching:1;
  bool no_impl:1;
  bool lexical_lambda:1;
  bool logical_lambda:1;
  bool do_lambda:1;
  bool no_def:1;
  bool async:1;
  bool has_preceding:1;
 _flags

 enum class Channel_Types {
  N_A, Lambda, Sigma, Error, Return, Context, CTOR_Mem, CTOR_Ret, Monad
 };

private:

 typedef RE_Node tNode;

 typedef std::function<QString(QString)> type_name_callback_type;
 typedef std::function<void(RZ_Lisp_Graph_Lexical_Scope&, QString, QString)> ls_callback_type;


 caon_ptr<RE_Function_Def_Entry> function_def_entry_;
 type_name_callback_type type_name_callback_;
 ls_callback_type ls_callback_;

 QMap<Channel_Types, caon_ptr<tNode>> entry_nodes_map_;

 caon_ptr<tNode> map_key_sequence_ref_node_;

 void init_channels(tNode& fdef_node);

 caon_ptr<RZ_Lisp_Token> channel_sequence(caon_ptr<tNode>& sequence_node, signed int& depth_change);

 const RE_Query& rq_;

 QStack<caon_ptr<RE_Node>> entry_nodes_;

 int map_key_sequence_order_;
 caon_ptr<RZ_Function_Def_Info> ref_fdi_;


public:

 RZ_Function_Def_Info(RE_Function_Def_Entry& function_def_entry
  ,type_name_callback_type type_name_callback
  ,ls_callback_type ls_callback);

 ACCESSORS(caon_ptr<RE_Function_Def_Entry> ,function_def_entry)
 ACCESSORS(caon_ptr<RE_Node> ,map_key_sequence_ref_node)
 ACCESSORS(int ,map_key_sequence_order)
 ACCESSORS(caon_ptr<RZ_Function_Def_Info> ,ref_fdi)


 QString channel_string(const RZ_Function_Def_Syntax& syntax, caon_ptr<RE_Node> sequence_node);
 QString lambda_channel_string(const RZ_Function_Def_Syntax& syntax);
 QString sigma_channel_string(const RZ_Function_Def_Syntax& syntax);
 QString return_channel_string(int& token_count);
 QString channel_string(Channel_Types ct, const RZ_Function_Def_Syntax& syntax);

 QString kauvir_entry_code_string(RZ_Lisp_Graph_Lexical_Scope& ls);

 QString kauvir_entry_code_string_by_channel_type(Channel_Types ct, RZ_Lisp_Graph_Lexical_Scope& ls);

 QString context_channel_string();

 caon_ptr<tNode> function_def_entry_node();

 caon_ptr<tNode> function_def_entry_prior_node()
 {
  return function_def_entry_->prior_node();
 }

 QString get_label();

 QString dynamo_signature_code_for_type(QString carrier_kind, QString type_name);
 QString dynamo_signature_code_for_symbol(QString carrier_kind, QString symbol_name);
 QString dynamo_signature_code_for_symbol(QString carrier_kind, QString symbol_name, QString type_name);

 QString dynamo_signature_code_for_empty_channel(QString carrier_kind);

 QString dynamo_signature_code_string();
 QString dynamo_signature_code_string_by_channel_type(Channel_Types ct);

};

_RZNS(GVal)

#endif //RZ_FUNCTION_DEF_INFO__H
