
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-expression.h"

#include "rz-dynamo-form.h"

#include "rzns.h"

USING_RZNS(RECore)
USING_RZNS(GVal)

RZ_Dynamo_Expression::RZ_Dynamo_Expression(RZ_Dynamo_Form& form)
  :  form_(form)
{

}

caon_ptr<RZ_Dynamo_Form> RZ_Dynamo_Expression::ptr_to_form()
{
 return &form_;
}


void RZ_Dynamo_Expression::write_as_statement(QTextStream& qts)
{
 if(assignment_token_.isEmpty())
 {
  form_.write_statement_entry(qts);

  write(qts);

  form_.write_statement_leave(qts);

 }
 else
 {
  MS_Token& mst = form_.assignment_token();

  MS_Token askt = MS_Token {MS_Token_Kinds::Assignment_Kind, assignment_token_};

  if(mst.kind == MS_Token_Kinds::Scoped_Symbol_Literal_Init)
  {
   mst.kind = MS_Token_Kinds::Scoped_Symbol;
   qts << "\n ;;- tb_\n(kb::write-assignment-initialization-via-token ";
   qts << askt.encode();
   qts << ' ';
   qts << mst.encode();
   write(qts);
   qts << "\n) ;;- _tb";
  }
  else
  {
   QString s1 = form_.get_s1_assignment_check();

   if(s1 == "/->")
   {
    qts << "\n ;;- tb_\n(kb::write-s1-assignment-expression ";
    form_.mark_as_s1_assignment_preempts_s0();
   }
   else
   {
    qts << "\n ;;- tb_\n(kb::write-s0-expression ";
   }

   qts << askt.encode();
   qts << ' ';
   write(qts);
     // nested expression?

   form_.check_write_first_nested_is_assignment_leave(qts);

   qts << "\n(kb::write-promote-type-binding-expression " << mst.encode() << ")";
  }

  qts << "\n(kb::write-cmd-eval)";
  qts << "\n(kb::write-statement-clear)";


 }
}

QString RZ_Dynamo_Expression::encode_assignment_token()
{
 if(assignment_token_ == "\\=")
 {
  return "sng";
 }
 else if(assignment_token_ == "\\\\=")
 {
  return "dbl";
 }
 else
 {
  // others? ...
  return "?";
 }
}

void RZ_Dynamo_Expression::mark_form_as_assignment_expression()
{
 form_.mark_as_assignment_expression();
}

void RZ_Dynamo_Expression::write(QTextStream& qts)
{
 form_.write_unmediated(qts);
}
