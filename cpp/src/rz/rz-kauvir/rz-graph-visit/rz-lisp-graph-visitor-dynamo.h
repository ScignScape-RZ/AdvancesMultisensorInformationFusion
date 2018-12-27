
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_VISITOR_DYNAMO__H
#define RZ_LISP_GRAPH_VISITOR_DYNAMO__H

#include "accessors.h"

#include "flags.h"

#include "rz-graph-core/kernel/rz-re-dominion.h"
#include "rz-graph-core/kernel/query/rz-re-query.h"
#include "rz-graph-core/kernel/frame/rz-re-frame.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-token/types/run-types.h"

#include "rz-graph-token/token/token-kinds.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-lexical-scope.h"

#include "rz-lisp-graph-visitor-run-state.h"

#include "rz-lisp-graph-visitor.h"

#include "multistep-token.h"

#include <stack>
#include <QStack>

#include <map>

#include "rzns.h"


RZNS_(RECore)

class RE_Graph;
class RE_Node;
class RE_Call_Entry;
class RZ_Cpp_Project;
class RZ_Clasp_Project;
class RZ_SRE_Token;

_RZNS(RECore)

USING_RZNS(RECore)


RZNS_(GRun)

class RZ_Graph_Run_Token;

_RZNS(GRun)


RZNS_(GBuild)

class RZ_Lisp_Graph_Core_Function;
class RZ_Lisp_Token;

_RZNS(GBuild)

USING_RZNS(GBuild)


RZNS_(GEmbed)

class RZ_Graph_Run_Embedder;
class RZ_Graph_Embed_Token;
class RZ_Graph_Cpp_Token;
class RZ_Graph_Embed_Run_Valuer;

_RZNS(GEmbed)

USING_RZNS(GEmbed)


RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;
class RZ_Code_Statement;
class RZ_Expression_Review;

_RZNS(GVal)

USING_RZNS(GVal)

RZNS_(RZClasp)

 class RZ_Clasp_Code_Generator;
 class RZ_Clasp_Source_Element;

_RZNS(RZClasp)

USING_RZNS(RZClasp)



RZNS_(GRun)

class RZ_Lisp_Graph_Runner;

_RZNS(GRun)

USING_RZNS(GRun)


RZNS_(GBuild)


class RZ_Lisp_Graph_Visitor_Run_Plugin;
class RZ_Lisp_Graph_Visitor;


class RZ_Lisp_Graph_Visitor_Dynamo
{
 RZ_Lisp_Graph_Visitor& visitor_;

 caon_ptr<RZ_Lisp_Graph_Block_Info> pending_block_info_;

public:

 enum class Special_Form_Flags
 {
  N_A, Type_Declare, Assignment, Formula
 };

 RZ_Lisp_Graph_Visitor_Dynamo(RZ_Lisp_Graph_Visitor& visitor);

 ACCESSORS__GET(RZ_Lisp_Graph_Visitor& ,visitor)
 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Block_Info> ,pending_block_info)

 static Special_Form_Flags parse_special_form_flag(QString text);

 caon_ptr<RZ_Lisp_Graph_Block_Info> check_pending_block_info(caon_ptr<RE_Node> node);

 caon_ptr<RZ_Lisp_Graph_Block_Info> block_info_from_block_entry_node(caon_ptr<RE_Node> ben);

 caon_ptr<RZ_Lisp_Graph_Block_Info> clear_pending_block_info();

 caon_ptr<RE_Node> leave_nested_block(caon_ptr<RZ_Lisp_Graph_Block_Info> rbi, caon_ptr<RZ_Lisp_Graph_Block_Info>& nn_bi);

 void check_assignment_annotation(caon_ptr<RE_Node> statement_entry_node,
   caon_ptr<RZ_Code_Statement> st);

 RZ_Lisp_Graph_Valuer& valuer()
 {
  return *visitor_.valuer();
 }

 caon_ptr<RZ_Code_Statement> get_code_statement_from_statement_entry_node(caon_ptr<RE_Node> statement_entry_node);

 caon_ptr<RZ_Expression_Review> get_expression_review_from_entry_node(caon_ptr<RE_Node> entry_node);

 caon_ptr<RE_Node> start_node_from_call_entry_node(caon_ptr<RE_Node> entry_node);

 caon_ptr<RE_Node> get_next_statement_node(caon_ptr<RE_Node> statement_entry_node);

 void find_top_scope();

 QString function_name_from_token_text(QString text);

 caon_ptr<RE_Node> get_next_node(caon_ptr<RE_Node> start_node,
   RZ_Lisp_Graph_Visitor::Next_Node_Premise& next_node_premise);

 MS_Token lisp_token_from_token_text(QString text, QString& bridge_code);

 QString wrap_token_with_bridge_code(QString token, QString bridge_code, QString es_argument);

 caon_ptr<RE_Node> find_statement_cross_sequence_node(caon_ptr<RE_Node> start_node);

 caon_ptr<RE_Node> block_entry_node_from_function_def_entry_node(caon_ptr<RE_Node> start_node);
 caon_ptr<RE_Node> call_entry_node_from_block_entry_node(caon_ptr<RE_Node> start_node);

 caon_ptr<RZ_Function_Def_Info> get_function_def_info_from_entry(caon_ptr<RE_Function_Def_Entry> fde);
};

_RZNS(GBuild)




#endif //RZ_LISP_GRAPH_VISITOR_DYNAMO__H
