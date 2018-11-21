
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_FORM__H
#define RZ_DYNAMO_FORM__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>
#include <QVector>
#include <QPair>

#include <QTextStream>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

#include "multistep-token.h"

RZNS_(GBuild)
 class RZ_Lisp_Graph_Visitor;
 class RZ_Lisp_Graph_Visitor_Kauvir;
_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(GVal)

class RZ_Dynamo_Block;
class RZ_Dynamo_Type_Declaration;
class RZ_Dynamo_Expression;
class RZ_Dynamo_Form_Annotation;
class RZ_Code_Statement;
class RZ_Expression_Review;

class RZ_Dynamo_Form
{
 QVector<QPair<caon_ptr<RZ_Dynamo_Form>, MS_Token>> inner_elements_;

 typedef QVector<QPair<caon_ptr<RZ_Dynamo_Form>, MS_Token>> inner_elements_type;

 caon_ptr<RZ_Dynamo_Form> parent_;

 caon_ptr<RZ_Dynamo_Block> plene_block_;

 caon_ptr<RZ_Dynamo_Block> first_nested_block_;

 caon_ptr<RZ_Dynamo_Form_Annotation> annotation_;

 int parent_lambda_position_;

 // // do we need this?
 int implicit_added_depth_;

 int nesting_level_;

 QString raw_text_;

 QString chief_;

 caon_ptr<RZ_Dynamo_Type_Declaration> type_declaration_;
 caon_ptr<RZ_Dynamo_Expression> expression_;

 MS_Token assignment_token_;

 caon_ptr<RZ_Code_Statement> code_statement_;
 caon_ptr<RZ_Expression_Review> expression_review_;

 QMap<caon_ptr<RZ_Dynamo_Form>, QPair<QString, int>> wrapped_inner_elements_;

 int hdcode_;

 QString s1_assignment_check_;

 void mark_unsurrounded_nested();
 void add_string_token(QString tok);

public:

 RZ_Dynamo_Form(caon_ptr<RZ_Dynamo_Form> parent = nullptr);

 RZ_Dynamo_Form(caon_ptr<RZ_Dynamo_Block> block);

 ACCESSORS__RGET(inner_elements_type ,inner_elements)
 ACCESSORS(caon_ptr<RZ_Dynamo_Form> ,parent)
 ACCESSORS(int ,parent_lambda_position)
 ACCESSORS(int ,implicit_added_depth)
 ACCESSORS(QString ,raw_text)
 ACCESSORS__RGET(MS_Token ,assignment_token)
 ACCESSORS(int ,nesting_level)
 ACCESSORS(caon_ptr<RZ_Code_Statement> ,code_statement)
 ACCESSORS(caon_ptr<RZ_Expression_Review> ,expression_review)
 ACCESSORS(QString ,s1_assignment_check)

 bool s1_assignment_preempts_s0();

 void write(QTextStream& qts);
 void write_unmediated(QTextStream& qts);
 void write_as_statement(QTextStream& qts);

 void add_expression_wrapper(caon_ptr<RZ_Dynamo_Form> form, QString text, int hdcode);

 QString get_s1_assignment_check();

 void init_type_declaration(QString cmd);
 void init_expression();

 void init_assignment_expression(QString tok);
 void init_formula_expression(QString tok);

 void write_statement_entry(QTextStream& qts);
 void write_statement_leave(QTextStream& qts);

 void check_write_first_nested_is_assignment_leave(QTextStream& qts);

 void mark_deferred(int hdcode);
 void mark_as_assignment_expression();
 void mark_as_fn_no_block();
 void mark_as_s1_assignment_preempts_s0();
 void mark_as_parent_s1_assignment_preempts_s0();


 QString get_assignment_target();


 void check_init_annotation();
 void check_init_annotation(QString fn);
 void check_init_annotation_flags();

 void init_inferred_s0_statement();

 void add_expression(caon_ptr<RZ_Dynamo_Form> form);

 void add_nested_block(caon_ptr<RZ_Dynamo_Block> block);

 void add_prin1_quoted_form(QString text, MS_Token mt);

 void write_checked_unmediated(QTextStream& qts);

 void mark_parent_implict_end_form_before_nested_written();
 void mark_child_implict_end_form_before_nested_written();

 bool implict_end_form_before_nested_written();

 void set_assignment_token(MS_Token mt);
 void add_assignment_initialization_token(MS_Token mt);
 void add_literal_token(MS_Token mt);
 void add_carrier_token(MS_Token mt);
 void add_kauvir_token(MS_Token mt);
 void add_fn_token(MS_Token mt);
 void add_bridge_token(MS_Token mt);
 void add_instruction_token(MS_Token mt);
 void add_argument_token(MS_Token mt);
 void add_insert_token(MS_Token mt);

};

_RZNS(GVal)

#endif //RZ_DYNAMO_FORM__H
