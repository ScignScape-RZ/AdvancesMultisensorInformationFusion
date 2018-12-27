
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-form.h"
#include "rz-dynamo-block.h"

#include "rz-graph-core/code/rz-re-block-entry.h"

#include "rz-graph-valuer/scope/rz-lisp-graph-block-info.h"

#include "rz-dynamo-type-declaration.h"
#include "rz-dynamo-expression.h"

#include "rz-dynamo-form-annotation.h"

#include "rz-code-elements/rz-code-statement.h"
#include "rz-code-elements/rz-expression-review.h"

#include <functional>

#include "rzns.h"

#define ANNOTATION_FLAG(x) \
  (annotation_ && annotation_->flags.x)

USING_RZNS(GVal)

RZ_Dynamo_Form::RZ_Dynamo_Form(caon_ptr<RZ_Dynamo_Form> parent)
  :  parent_(parent), parent_lambda_position_(-1),
     first_nested_block_(nullptr), implicit_added_depth_(0),
     nesting_level_(0),
     type_declaration_(nullptr), expression_(nullptr),
     assignment_token_(MS_Token::Null()),
     annotation_(nullptr),
     code_statement_(nullptr),
     expression_review_(nullptr), hdcode_(0)
{

}

RZ_Dynamo_Form::RZ_Dynamo_Form(caon_ptr<RZ_Dynamo_Block> block)
  :  parent_(nullptr), plene_block_(block),
     first_nested_block_(nullptr), implicit_added_depth_(0),
     type_declaration_(nullptr), expression_(nullptr),
     assignment_token_(MS_Token::Null())
{

}

QString RZ_Dynamo_Form::get_assignment_target()
{
 return assignment_token_.raw_text;
}

void RZ_Dynamo_Form::write_as_statement(QTextStream& qts)
{
 if(code_statement_)
 {
  qts << "\n\n ;; Identified as code statement kind: "
      << code_statement_->kind_to_string();

  if(!code_statement_->annotation().isEmpty())
  {
   qts << " " << code_statement_->annotation();
  }
  qts << "\n";
 }
 if(expression_review_)
 {
  qts << "\n\n ;; Expression Review: "
      << expression_review_->text() << "\n";
 }

 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RZ_Dynamo_Type_Declaration ,type_declaration_)
  type_declaration_->write(qts);
 }
 else if(expression_)
 {
  expression_->write_as_statement(qts);
 }
 else
 {
  write(qts);
 }

}

void RZ_Dynamo_Form::add_prin1_quoted_form(QString text, MS_Token mt)
{
 check_init_annotation();
 annotation_->flags.has_prin1_quoted_form = true;

 RZ_Dynamo_Form* new_form = new RZ_Dynamo_Form(this);

 new_form->set_raw_text(QString("\n\n(prin1-to-string '(%1))\n\n").arg(text));

 inner_elements_.push_back({new_form, mt});

}

void RZ_Dynamo_Form::init_type_declaration(QString cmd)
{
 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RZ_Dynamo_Type_Declaration ,type_declaration_)
  // // this is an error ...
  return;
 }
 // // should distinguish cmd == "my" and "our" ...
 type_declaration_ = new RZ_Dynamo_Type_Declaration(*this);
 type_declaration_->set_cmd(cmd);
}

void RZ_Dynamo_Form::init_expression()
{
 expression_ = new RZ_Dynamo_Expression(*this);
}

void RZ_Dynamo_Form::init_assignment_expression(QString tok)
{
 init_expression();
 expression_->set_assignment_token(tok);
}

void RZ_Dynamo_Form::init_formula_expression(QString tok)
{
 init_expression();
 expression_->set_assignment_token(tok);
}

void RZ_Dynamo_Form::write(QTextStream& qts)
{
 check_init_annotation_flags();
 CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
 if(type_declaration_)
 {
  CAON_PTR_DEBUG(RZ_Dynamo_Type_Declaration ,type_declaration_)
  type_declaration_->write(qts);
 }
 else if(expression_)
 {
  if(ANNOTATION_FLAG(is_deferred))
  {
   qts << "kb::hold-deferred " << hdcode_ << " '(progn (;; annotation_flag_ deferred ...\n";
   expression_->write(qts);
   qts << "\n)) ;; ... annotation_flag_ deferred\n";
  }
  else
  {
   expression_->write(qts);
  }
 }
 else if(!raw_text_.isEmpty())
 {
  qts << raw_text_;
 }
 else
 {
  write_unmediated(qts);
 }
}

void RZ_Dynamo_Form::add_expression_wrapper(caon_ptr<RZ_Dynamo_Form> form,
  QString text, int hdcode)
{
 wrapped_inner_elements_[form] = {text, hdcode};
}

void RZ_Dynamo_Form::add_expression(caon_ptr<RZ_Dynamo_Form> form)
{
 inner_elements_.push_back({form, MS_Token::Null()});
}

void RZ_Dynamo_Form::add_nested_block(caon_ptr<RZ_Dynamo_Block> block)
{
 if(!first_nested_block_)
 {
  first_nested_block_ = block;
 }
 caon_ptr<RZ_Dynamo_Form> form = new RZ_Dynamo_Form(block);
 inner_elements_.push_back({form, MS_Token::Null()});
}

void RZ_Dynamo_Form::mark_as_fn_no_block()
{
 check_init_annotation();
 annotation_->flags.is_fn_no_block = true;
 CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
}

void RZ_Dynamo_Form::mark_as_s1_assignment_preempts_s0()
{
 check_init_annotation();
 annotation_->flags.s1_assignment_preempts_s0 = true;
}

void RZ_Dynamo_Form::mark_as_parent_s1_assignment_preempts_s0()
{
 check_init_annotation();
 annotation_->flags.parent_s1_assignment_preempts_s0 = true;
}

void RZ_Dynamo_Form::mark_as_assignment_expression()
{
 check_init_annotation();
 annotation_->flags.is_nested_as_assignment = true;
 CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
}

void RZ_Dynamo_Form::check_init_annotation()
{
 if(!annotation_)
 {
  annotation_ = new RZ_Dynamo_Form_Annotation();
 }
}

bool RZ_Dynamo_Form::s1_assignment_preempts_s0()
{
 return ANNOTATION_FLAG(s1_assignment_preempts_s0);
}


void RZ_Dynamo_Form::check_init_annotation(QString fn)
{
 typedef std::function<void(RZ_Dynamo_Form*)> fn_type;
 static QMap<QString, fn_type> static_map {{
  {"kb::if-without-elsif", [](RZ_Dynamo_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if = true;
   }
  },
  {"kb::if-with-else", [](RZ_Dynamo_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if_with_else = true;
   }
  },
  {"kb::if-with-elsif", [](RZ_Dynamo_Form* _this)
   {
    _this->check_init_annotation();
    _this->annotation_->flags.is_general_if = true;
    _this->annotation_->flags.is_if_with_elsif = true;
   }
  },
 }};
 if(static_map.contains(fn))
 {
  static_map[fn](this);
 }
}

bool RZ_Dynamo_Form::implict_end_form_before_nested_written()
{
 if(annotation_)
 {
  return annotation_->flags.implict_end_form_before_nested_written;
 }
 return false;
}

void RZ_Dynamo_Form::check_init_annotation_flags()
{
 if(annotation_)
 {
  if(!annotation_->flags.checked)
  {
   annotation_->flags.checked = true;
   if(annotation_->flags.is_general_if)
   {
    annotation_->flags.end_form_before_nested = true;
    annotation_->flags.surround_nested_secondary = true;
    annotation_->flags.write_pull_nested_form_group = true;
    annotation_->flags.write_push_nested_form_group = true;
    annotation_->flags.skip_write_command_package = true;
   }
  }
 }
}

void RZ_Dynamo_Form::write_statement_entry(QTextStream& qts)
{
 qts << "\n;statement_\n";
 qts << "\n( ; from write_statement_entry\n";
}

void RZ_Dynamo_Form::write_statement_leave(QTextStream& qts)
{
 if(ANNOTATION_FLAG(skip_write_command_package))
 {

 }
 else
 {
  if(!ANNOTATION_FLAG(statement_form_closed_before_nested))
  {
   qts << "\n);_statement\n";
  }
  qts << "\n(kb::write-promote-expression)";
  qts << "\n(kb::write-cmd-eval)";
  qts << "\n(kb::write-statement-clear)";
 }
}

QString RZ_Dynamo_Form::get_s1_assignment_check()
{
 QString result = s1_assignment_check_;
 return result;
}

void RZ_Dynamo_Form::check_write_first_nested_is_assignment_leave(QTextStream& qts)
{
 CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
 if(ANNOTATION_FLAG(first_nested_is_assignment))
 {
  if(!annotation_->flags.child_implict_end_form_before_nested_written)
  {
   qts << "\n ) ; end nested assignment expression ... \n ";
  }
 }
}


void RZ_Dynamo_Form::write_checked_unmediated(QTextStream& qts)
{
 qts << "( ; write_unmediated_ \n";
 write_unmediated(qts);
 if(ANNOTATION_FLAG(has_prin1_quoted_form))
 {
  if(annotation_->flags.is_fn_no_block)
  {
   qts << ") ; _write_unmediated (with prin1; no block) \n";
  }
  else
  {
   qts << " ; _write_unmediated (with prin1) \n";
  }
 }
 else
 {
  qts << ") ; _write_unmediated \n";
 }
}

void RZ_Dynamo_Form::write_unmediated(QTextStream& qts)
{
 check_init_annotation_flags();
 QString icd = QString(implicit_added_depth_, '(');

 qts << icd;

 if(!ANNOTATION_FLAG(has_instruction_token))
 {
  if(ANNOTATION_FLAG(infer_write_s0_statement))
  {
   qts << "kb::write-s0-expression ";

   MS_Token askt = MS_Token {MS_Token_Kinds::Assignment_Kind, "none"};
   qts << askt.encode();
   qts << ' ';

  }
  else if(ANNOTATION_FLAG(unsurrounded_nested))
  {
   MS_Token mst {MS_Token_Kinds::Paren_Entry, QString::number(nesting_level_)};
   QString mste = mst.encode();
   qts << "\n " << mste << ' ';
  }
  else if(ANNOTATION_FLAG(first_nested_is_assignment))
  {
   qts << " ; for assignment ... \n ";
  }
  else if(ANNOTATION_FLAG(is_nested_as_assignment))
  {
   qts << " ; nested for assignment ... \n ";
  }
  else if(plene_block_)
  {
   qts << "kb::write-plene-block ";
  }
  else
  {
   MS_Token lisp_call_mode_token {MS_Token_Kinds::Note_Symbol, ":lc-f"};
   qts << "kb::prepare-expression " << lisp_call_mode_token.encode();
  }
 }

 if(plene_block_)
 {
  qts << "\n;block_\n";

  if(caon_ptr<RE_Block_Entry> rbe = plene_block_->get_block_entry())
  {
   if(rbe->flags.if_block)
   {
   }
  }
  else
  {
   // so get info plene_block_ mode ...
   qts << "\n;; fn body"
     "\n(kb::write-enter-plebod)";

  }

  qts << "\n(kb::write-enter-plene-block)\n";
  plene_block_->write(qts);
  qts << "\n(kb::write-leave-plene-block)\n";
 }
 else
 {
 }

 QList<caon_ptr<RZ_Dynamo_Form>> nested_forms;
 int nf_count = 0;
 int count = 0;

 int skip = -1;
 int pseudo_first = -1;

 for(QPair<caon_ptr<RZ_Dynamo_Form>, MS_Token> element : inner_elements_)
 {
  if(count == skip)
  {
   ++count;
   continue;
  }

  if(element.first)
  {
   caon_ptr<RZ_Dynamo_Form> ef = element.first;
   CAON_PTR_DEBUG(RZ_Dynamo_Form ,ef)

   QString note = element.second.raw_text;

#ifdef HIDE
   // //  would this only apply to tokens?
   if( (count == pseudo_first) && (assignment_token_.has_text() ) )
   {
    if(ANNOTATION_FLAG(first_nested_is_assignment))
    {
     // // should I set this here or elsewhere?
     element.first->mark_as_assignment_expression();
    }
    element.first->write(qts);
    ++count;
    continue;
   }
#endif // HIDE
   if( (count == 0) && (assignment_token_.has_text() ) )
   {
#ifdef HIDE
   // //  again, would this only apply to tokens?

    CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
    if(parent_ && parent_->s1_assignment_preempts_s0())
    {
     skip = 1;
    }
    else if(ANNOTATION_FLAG(first_inner_element_is_s1_assignment_preempts_s0))
    {
     pseudo_first = 1;
     ++count;
     continue;
    }
#endif // HIDE

    if(ANNOTATION_FLAG(first_nested_is_assignment))
    {
     // // should I set this here or elsewhere?
     element.first->mark_as_assignment_expression();
    }

    element.first->write(qts);
   }
   else if(note.isEmpty())
   {
    // //  these are deferred to after ...
    nested_forms.push_back(ef);
    ++nf_count;

    MS_Token mst {MS_Token_Kinds::Nested_Forward,
      QString("%1-%2").arg(nesting_level_).arg(nf_count)};
    qts << ' ' << mst.encode() << ' ';
   }
   else
   {
    qts << ' ' << element.second.encode() << ' ';
    element.first->write(qts);
    qts << ' ';
   }
  }
  else
  {
   CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
   if(count == 0)
   {
    if(parent_ && parent_->s1_assignment_preempts_s0())
    {
     skip = 1;
    }
    else if(ANNOTATION_FLAG(first_inner_element_is_s1_assignment_preempts_s0))
    {
     pseudo_first = 1;
     ++count;
     continue;
    }
   }

   QString rt = element.second.raw_text;
   MS_Token_Kinds mstk = element.second.kind;

   QString str = element.second.encode();

   qts << ' ' << str << ' ';
  }
  ++count;
 }

 if(chief_.startsWith('.'))
 {
  qts << "\n;;instruction\n)\n";
 }

 if(plene_block_)
 {
  qts << "\n;_plene_block";
 }
 else
 {
 }

 // ?? always end ...?
 if(!nested_forms.isEmpty())
 {
  check_init_annotation();
  annotation_->flags.surround_nested = true;
 }

 if(ANNOTATION_FLAG(end_form_before_nested))
 {
  qts << "\n) ;end form before nested...\n";
 }
 //?
 else if(nested_forms.isEmpty())
 {
  qts << "\n ; nothing nested...\n";
 }
 else if(!ANNOTATION_FLAG(skip_implicit_end_form_before_nested))
 {
  annotation_->flags.statement_form_closed_before_nested = true;
  annotation_->flags.implict_end_form_before_nested_written = true;

  CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)

  qts << "\n) ;implicit end form before nested...\n";

 }

 if(ANNOTATION_FLAG(write_push_nested_form_group))
 {
  qts << "\n(kb::push-nested-form-group)\n";
 }

 if(ANNOTATION_FLAG(unsurrounded_nested))
 {
  MS_Token mst {MS_Token_Kinds::Paren_Leave, QString::number(nesting_level_)};
  qts << "\n " << mst.encode() << ' ';
 }

 int nfb_count = 0;

 for(caon_ptr<RZ_Dynamo_Form> nf: nested_forms)
 {
  CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)
  ++nfb_count;

  if(ANNOTATION_FLAG(implict_end_form_before_nested_written))
  {
   nf->mark_parent_implict_end_form_before_nested_written();
   if(parent_)
   {
    parent_->mark_child_implict_end_form_before_nested_written();
   }
  }

  if(ANNOTATION_FLAG(surround_nested_secondary))
  {
   MS_Token mst {MS_Token_Kinds::Nested_Back,
     QString("%1-%2").arg(nesting_level_).arg(nfb_count)};
   qts << "\n(kb::enter-secondary-nested-form " << mst.encode() << ")\n";

   qts << "( ; secondary-nested-form-body_ \n";
  }
  else if(ANNOTATION_FLAG(surround_nested))
  {
   MS_Token mst {MS_Token_Kinds::Nested_Back,
     QString("%1-%2").arg(nesting_level_).arg(nfb_count)};

   auto fnd = wrapped_inner_elements_.find(nf);
   if(fnd == wrapped_inner_elements_.end())
   {
    qts << "\n(kb::enter-nested-form " << mst.encode() << ")\n";
    qts << "( ; nested-form-body_ \n";
   }
   else
   {
    QString note = fnd.value().first;
    int hdcode = fnd.value().second;
    MS_Token cmst {MS_Token_Kinds::Literal, QString::number(hdcode)};
    if(note.endsWith('\''))
    {
     note.chop(1);
     MS_Token nmst{MS_Token_Kinds::Note_Symbol, note};
     qts << "\n(kb::enter-nested-form " << nmst.encode() << " "
          << cmst.encode() << " "<< mst.encode() << ")\n";
     qts << "( ; nested-form-body_ \n";
     nf->mark_deferred(hdcode);
    }
    else
    {
     MS_Token nmst{MS_Token_Kinds::Note_Symbol, note};
     qts << "\n(kb::enter-nested-form " << nmst.encode() << " "
          << cmst.encode() << " "<< mst.encode() << ")\n";
     qts << "( ; nested-form-body_ \n";
    }
   }
  }
  else
  {
   nf->mark_unsurrounded_nested();
  }
  nf->set_nesting_level(nesting_level_ + 1);
  qts << ' ';
  nf->write(qts);
  qts << ' ';
  if(ANNOTATION_FLAG(surround_nested_secondary))
  {
   qts << "\n) ; _nested-form-body \n";
   qts << "\n(kb::leave-secondary-nested-form)\n";
  }
  else if(ANNOTATION_FLAG(surround_nested))
  {

   CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)

   if(annotation_->flags.parent_implict_end_form_before_nested_written)
   {
    if(annotation_->flags.skip_close_paren_on_parent_written)
    {
     qts << "\n ; _nested-form-body (lisp form already closed; parent) \n";
    }
    else if(nf->implict_end_form_before_nested_written())
    {
     qts << "\n ; _nested-form-body (nested form already closed; parent closed) \n";
    }
    else
    {
     qts << "\n) ; _nested-form-body (despite parent closed) \n";
    }
   }
   else
   {
    // // make sure this is always kosher
    if(nf->implict_end_form_before_nested_written())
    {
     qts << "\n ; _nested-form-body (lisp form already closed) \n";
    }
    else
    {
     qts << "\n) ; _nested-form-body \n";
    }
   }


   qts << "\n(kb::leave-nested-form)\n";
  }
 }

 if(ANNOTATION_FLAG(write_pull_nested_form_group))
 {
  qts << "\n(kb::pull-nested-form-group)\n";
 }

}

void RZ_Dynamo_Form::mark_unsurrounded_nested()
{
 check_init_annotation();
 annotation_->flags.unsurrounded_nested = true;
}


void RZ_Dynamo_Form::mark_deferred(int hdcode)
{
 check_init_annotation();
 annotation_->flags.is_deferred = true;
 hdcode_ = hdcode;
}

void RZ_Dynamo_Form::mark_parent_implict_end_form_before_nested_written()
{
 check_init_annotation();
 annotation_->flags.parent_implict_end_form_before_nested_written = true;
}

void RZ_Dynamo_Form::mark_child_implict_end_form_before_nested_written()
{
 check_init_annotation();
 annotation_->flags.child_implict_end_form_before_nested_written = true;
}

void RZ_Dynamo_Form::set_assignment_token(MS_Token mt)
{
 // always?
 check_init_annotation();
 annotation_->flags.first_nested_is_assignment = true;

 CAON_PTR_DEBUG(RZ_Dynamo_Form_Annotation ,annotation_)

 assignment_token_ = mt;
}

void RZ_Dynamo_Form::add_assignment_initialization_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_literal_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_insert_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_carrier_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_kauvir_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::init_inferred_s0_statement()
{
 check_init_annotation();
 annotation_->flags.infer_write_s0_statement = true;
}

void RZ_Dynamo_Form::add_fn_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_bridge_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_instruction_token(MS_Token mt)
{
 check_init_annotation();
 annotation_->flags.has_instruction_token = true;

 if(annotation_->flags.parent_s1_assignment_preempts_s0)
 {
  QString ch = parent_->s1_assignment_check();
  MS_Token mt1 = {MS_Token_Kinds::Preempted_Instruction_Symbol, ch};
  inner_elements_.push_back({nullptr, mt1});
  annotation_->flags.first_inner_element_is_s1_assignment_preempts_s0 = true;
 }

 inner_elements_.push_back({nullptr, mt});
}

void RZ_Dynamo_Form::add_argument_token(MS_Token mt)
{
 inner_elements_.push_back({nullptr, mt});
}
