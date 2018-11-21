
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_TOKEN__H
#define RZ_LISP_TOKEN__H

#include "accessors.h"
#include "flags.h"

#include "rz-graph-token/types/rz-type-variety.h"


#ifndef type_ch
#define type_ch(T) \
 tv_type_is(RZ_Run_Type_Code<T>::Value, type_object(), tv)
#endif

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-token/rz-lisp-graph-value-holder.h"

#include "token-kinds.h"

#include "relae-graph/relae-caon-ptr.h"


#include <QString>

#include <functional>

#include "rzns.h"

RZNS_(RECore)

class RE_Token;

_RZNS(RECore)


RZNS_(GBuild)

class RZ_Type_Object;
class RZ_Lisp_Node;
class RZ_Lisp_Token_Out_Info;
class RZ_Lisp_Lexical_Scope;
class RZ_Type_Variety;


class RZ_Lisp_Token
{
public:

  // // 63 flags ...

 flags_(8)
  bool is_core_function_symbol:1;
  bool is_deferred_core_function_symbol:1;
  bool is_likely_function_symbol:1;
  bool is_numeric_literal:1;
  bool is_string_literal:1;
  bool is_token_representation:1;
  bool unUSED_1:1;
  bool is_declaration_arrow:1;
  bool is_call_arrow:1;
  bool unUSED_2:1;
  bool has_assignment_initialization_token:1;
  bool has_assignment_initialization_expression:1;
  bool is_assignment_initialization_entry:1;
  bool is_dep_marker:1;
  bool holds_direct_value:1;
  bool value_is_raw_text:1;
  bool is_symbol_declaration:1;
  bool is_symbol_matched_to_declaration:1;
  bool is_type_symbol_declaration:1;
  bool is_captured_symbol_declaration:1;
  bool is_keyword:1;
  bool is_quoted:1;
  bool is_double_quoted:1;
  bool is_back_quoted:1;
  bool is_double_back_quoted:1;
  bool is_lex_assignment_entry:1;
  bool is_lex_assignment_form:1;
  bool out_redirect:1;
  bool skip_lisp_out:1;
  bool is_nested_opaque_call:1;
  bool is_empty_tuple:1;
  bool initial_question_mark:1;
  bool final_question_mark:1;
  bool is_direct_lisp_paste:1;
  bool is_string_key:1;
  bool is_function_expression_entry:1;
  bool is_infix_operator_entry:1;
  bool is_prefix_operator_entry:1;
  bool is_assignment_block_entry:1;
  bool is_block_entry_suppressing_expression:1;
  bool is_mapkey:1;
  bool is_do_mapkey:1;
  bool is_block_entry_caserun:1;
  bool has_mapkey:1;
  bool is_match_literal:1;
  bool is_empty_tuple_indicator:1;
  bool is_if_with_elsif:1;
  bool is_cpp_scoped:1;
  bool is_their:1;
  bool is_your:1;
  bool not_entry:1;
  bool is_via_type_assignment:1;
  bool is_type_symbol_in_declaration:1;
  bool is_untyped_symbol_declaration:1;
  bool is_assign_to_default_ctor:1;
  bool is_xq_literal:1;
  bool is_raw_lisp:1;
  bool has_type_indicator:1;
  bool follows_call_arrow:1;
  bool is_elsif_with_elsif:1;
  bool precedes_call_arrow:1;
  bool is_if_with_else:1;
 _flags

private:

 int syntactic_depth_;
 QString raw_text_;
 int line_number_;

 RZ_Lisp_Graph_Value_Holder vh_;

 caon_ptr<RZ_Lisp_Token_Out_Info> out_;

public:

 ACCESSORS(QString ,raw_text)
 ACCESSORS(int ,syntactic_depth)
 ACCESSORS__RGET(RZ_Lisp_Graph_Value_Holder ,vh)
 ACCESSORS(int ,line_number)

 ACCESSORS(caon_ptr<RZ_Lisp_Token_Out_Info> ,out)

 static void init_lisp_token(RE_Token& re_token);
 static caon_ptr<RZ_Lisp_Token> check_init_lisp_token(RE_Token& re_token);

 caon_ptr<RZ_Lisp_Token_Out_Info>
  get_lisp_out(RZ_Type_Variety& tv, QString& result);

 void skip_lisp_out();

 static QString lara_argument_map(QString text);

 caon_ptr<RZ_Lisp_Token_Out_Info>
  get_lisp_out(QString& result,
   std::function<void(QString&)> callback);

 template<typename T>
 caon_ptr<T> pRestore()
 {
#ifdef NO_CAON
  return reinterpret_cast<caon_ptr<T>> ( vh_.value() );
#else
  return vh_.value().template caon_cast<T>();
#endif
 }

 template<typename T>
 caon_ptr<T> pRestore(RZ_Type_Variety& tv)
 {

#define tv_type_is(Type_exp, to_sym, tv_sym) \
 to_sym == tv_sym.get_type_object(Type_exp)

  if(type_ch(T))
   return pRestore<T>();
  return nullptr;
 }

 caon_ptr<RZ_Type_Object> type_object();
 void set_type_object(RZ_Type_Object& cto);

 RZ_Lisp_Token(QString raw_text, int line_number = 0);

 enum class Special_Constructor_Mode { N_A, Raw_Text };

 RZ_Lisp_Token(QString raw_text, Special_Constructor_Mode scm, int line_number = 0);

 void comment_lisp(QString str);
 void redirect_lisp(QString str);

 void redirect_lisp(QString str, RZ_Lisp_Node& node);
 void redirect_lisp_in_form(QString str, RZ_Lisp_Node& node);


 void redirect_paste(QString str);

 void redirect_lisp(QString str,
  std::function<void(QString&)>* callback);

 void check_out();

 template<typename T>
 void set_value(caon_ptr<T> t)
 {
  vh_.set_value(t);
 }

 template<typename T>
 void set_value(T t)
 {
#ifdef NO_CAON
  vh_.set_value<T>(&t);
#else
  vh_.set_value(caon_ptr<T>(t));
#endif
 }

 template<typename T>
 void set_direct_value(T t)
 {
  flags.holds_direct_value = true;
  vh_.set_direct_value(t);
 }

 template<typename T>
 void set_new_value(T& t)
 {
  set_value(new T(t));
 }

 template<typename T>
 void set_new_copy_value(T t)
 {
  set_value(caon_ptr<T>(new T(t)));
 }

 template<typename T, typename ARG_Type>
 void set_new_cast_value(ARG_Type& arg)
 {
  caon_ptr<T> t = new T(arg);
  set_value(t);
 }

 QString literal_string_value() const
 {
  if(flags.is_string_literal)
  {
   return QString("\"%1\"").arg(raw_text());
  }
  return string_value();
 }

 QString string_value() const
 {
  return raw_text();
 }

 QString lisp_string_value();

 QString cpp_string_value();


 void mark_as_string_literal();

 Basic_Token_Kinds kind_and_string_value(QString& result) const;


};

_RZNS(GBuild)

#endif //RZ_LISP_TOKEN__H
