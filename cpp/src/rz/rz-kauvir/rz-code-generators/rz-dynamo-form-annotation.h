
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_FORM_ANNOTATION__H
#define RZ_DYNAMO_FORM_ANNOTATION__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>

#include <QTextStream>

#include "rzns.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-function-def/rz-function-def-syntax.h"

RZNS_(GVal)

class RZ_Dynamo_Form_Annotation
{
public:

 flags_(4)
  bool checked:1;
  bool is_if:1;
  bool is_if_with_elsif:1;
  bool is_if_with_else:1;
  bool is_elsif_with_elsif:1;
  bool is_general_if:1;
  bool end_form_before_nested:1;
  bool surround_nested:1;
  bool surround_nested_secondary:1;
  bool write_pull_nested_form_group:1;
  bool write_push_nested_form_group:1;
  bool skip_write_command_package:1;
  bool has_instruction_token:1;
  bool infer_write_s0_statement:1;
  bool unsurrounded_nested:1;
  bool skip_implicit_end_form_before_nested:1;
  bool statement_form_closed_before_nested:1;
  bool first_nested_is_assignment:1;
  bool is_nested_as_assignment:1;
  bool has_prin1_quoted_form:1;
  bool implict_end_form_before_nested_written:1;
  bool parent_implict_end_form_before_nested_written:1;
  bool skip_close_paren_on_parent_written:1;
  bool is_fn_no_block:1;
  bool child_implict_end_form_before_nested_written:1;
  bool is_deferred:1;
  bool s1_assignment_preempts_s0:1;
  bool parent_s1_assignment_preempts_s0:1;
  bool first_inner_element_is_s1_assignment_preempts_s0:1;
 _flags


public:

 RZ_Dynamo_Form_Annotation();


};

_RZNS(GVal)

#endif //RZ_DYNAMO_FORM_ANNOTATION__H
