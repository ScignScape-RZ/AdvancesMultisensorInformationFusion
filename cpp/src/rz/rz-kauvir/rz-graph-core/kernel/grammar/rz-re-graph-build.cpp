
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-graph-build.h"

USING_RZNS(RECore)


#include "rz-re-graph-build.h"

#include "kernel/graph/rz-re-node.h"

#include "kernel/rz-re-root.h"

#include "rz-re-grammar.h"

#include "code/rz-re-call-entry.h"
#include "code/rz-re-block-entry.h"

#include "kernel/graph/rz-re-graph.h"

#include "kernel/rz-re-dominion.h"


#include "token/rz-re-token.h"


#include "kernel/document/rz-re-document.h"

#include "code/rz-re-code-representation.h"

#include "code/rz-re-function-def-entry.h"

#include "rz-re-string-plex-builder.h"

#include "rzns.h"
USING_RZNS(RECore)

USING_RZNS(Text)

RE_Graph_Build::RE_Graph_Build(RE_Document* d,
  RE_Parser& p, RE_Graph& g)
 : Flags(0)
  ,document_(d)
  ,graph_(g)
  ,parser_(p)
  ,current_line_(1)
  ,fr_(RE_Frame::instance())
  ,markup_position_(this)
  ,active_run_node_(nullptr)
  ,active_chief_token_(nullptr)
  ,current_run_comment_left_(0)
  ,current_run_comment_right_(0)
  ,call_entry_count_(0)
  ,block_entry_count_(0)
  ,tuple_entry_count_(0)
  ,current_string_plex_builder_(nullptr)
{
}

void RE_Graph_Build::init()
{
 caon_ptr<RE_Root> root = new RE_Root(document_);
 active_run_node_ = root_node_ = new RE_Node(root);

 RELAE_SET_NODE_LABEL(root_node_, "<root>");
 graph_.set_root_node(root_node_);
 markup_position_.set_current_node(root_node_);

 QString sct = "_lisp";
 QStringList sctl = sct.split(' ');

 for(QString s : sctl)
  automatic_statement_closing_tokens_.insert(s);

}


void RE_Graph_Build::check_run_comment_begin(int left, int right)
{
 if(current_run_comment_left_)
 {
  return;
 }
 if(left > 6)
  left = 6;
 if(right > 6)
  right = 6;
 current_run_comment_left_ = left;
 current_run_comment_right_ = right;
 parse_context_.flags.inside_run_comment = true;
}

void RE_Graph_Build::check_run_comment_end(int left, int right)
{
 if(current_run_comment_left_)
 {
  if(left > 6)
   left = 6;
  if(right > 6)
   right = 6;
  if(current_run_comment_left_ != right)
   return;
  if(current_run_comment_right_ != left)
   return;

  current_run_comment_left_ = 0;
  current_run_comment_right_ = 0;
  parse_context_.flags.inside_run_comment = false;
 }
 // // If not, for now just ignore ...
 //    Otherwise syntax error ...
}


caon_ptr<RE_Node> RE_Graph_Build::make_new_node(caon_ptr<RE_Token> token)
{
 caon_ptr<RE_Node> result = new RE_Node(token);
 RELAE_SET_NODE_LABEL(result, token->string_summary());
 return result;
}


caon_ptr<RE_Node> RE_Graph_Build::make_new_node(caon_ptr<RZ_String_Plex_Builder> rzspb)
{
 caon_ptr<RE_Node> result = new RE_Node(rzspb);

 return result;
}


caon_ptr<RE_Node> RE_Graph_Build::make_new_node(caon_ptr<RE_Call_Entry> rce)
{
 caon_ptr<RE_Node> result = new RE_Node(rce);
 RELAE_SET_NODE_LABEL(result, QString("<call %1>").arg(rce->call_id()));
 return result;
}

caon_ptr<RE_Node> RE_Graph_Build::make_new_node(caon_ptr<RE_Function_Def_Entry> fdef)
{
 caon_ptr<RE_Node> result = new RE_Node(fdef);
 RELAE_SET_NODE_LABEL(result, "<fdef>");
 return result;
}

caon_ptr<RE_Node> RE_Graph_Build::make_new_node(caon_ptr<RE_Block_Entry> rbe)
{
 caon_ptr<RE_Node> result = new RE_Node(rbe);
 RELAE_SET_NODE_LABEL(result, QString("<block %1>").arg(rbe->call_id()));
 return result;
}

void RE_Graph_Build::add_assignment_annotation(QString text)
{
 caon_ptr<RE_Token> aa_token = new RE_Token(text);
 caon_ptr<RE_Node> aa_node = make_new_node(aa_token);
 markup_position_.hold_assignment_annotation_node(aa_node);
}

void RE_Graph_Build::check_line_increment(QString text)
{
 if(text.endsWith('\\n'))
  line_increment();
}

void RE_Graph_Build::line_increment()
{
 ++current_line_;
}

void RE_Graph_Build::set_expected_token_end(QString text)
{
 expected_token_end_ = text;
 expected_token_end_.chop(1);
 expected_token_end_.prepend('_');
}


void RE_Graph_Build::complete_function_declaration()
{
 caon_ptr<RE_Token> arrow_token = new RE_Token("->def", "", "");
 caon_ptr<RE_Node> arrow_node = make_new_node(arrow_token);

 caon_ptr<RE_Token> token = new RE_Token("<undef-function-body>", "", "");
 caon_ptr<RE_Node> node = make_new_node(token);

 markup_position_.complete_function_declaration(arrow_node, node);


}

void RE_Graph_Build::add_semis(QString raw_text, QString suffix,
                               QString space_to_end_of_line)
{
 int length = raw_text.length();
 if(length > 6)
 {
  raw_text.truncate(6);
  length = 6;
 }

 if(flags.added_lr_mode)
 {
  flags.added_lr_mode = false;
  markup_position_.leave_expression();
 }

 switch(length)
 {
 case 1:
  if(suffix.isEmpty())
    markup_position_.close_statement();
  else
    markup_position_.leave_lexical_scope(2, suffix);
  return;
 case 2:
  markup_position_.leave_lexical_scope(2, suffix);
  return;
 case 5:
  terminate_parse();
  // fallthrough
 case 6:
  terminate_read();
  // fallthrough
 default:
  add_run_token(raw_text, space_to_end_of_line);
 }
}

void RE_Graph_Build::terminate_read()
{

}

void RE_Graph_Build::terminate_parse()
{

}

void RE_Graph_Build::string_plex_switch(QString key)
{
 current_string_plex_builder_->add_part(string_literal_acc_.trimmed());
 current_string_plex_builder_->set_current_key(key);
 string_literal_acc_.clear();

}

caon_ptr<RE_Node> RE_Graph_Build::close_string_plex()
{
 current_string_plex_builder_->add_part(string_literal_acc_.trimmed());
 string_literal_acc_.clear();
 caon_ptr<RE_Node> result = make_new_node(current_string_plex_builder_);
 current_string_plex_builder_ = nullptr;
 return result;

}

void RE_Graph_Build::string_plex_acc(QString text)
{
 string_literal_acc_ += text;
}

caon_ptr<RE_Node> RE_Graph_Build::create_tuple(RE_Tuple_Info::Tuple_Formations tf,
 RE_Tuple_Info::Tuple_Indicators ti, RE_Tuple_Info::Tuple_Formations sf, bool increment_id)
{
 int tuple_id;
 if(increment_id)
  tuple_id = ++tuple_entry_count_;
 else
  tuple_id = 0;

 caon_ptr<RE_Tuple_Info> tinfo = new RE_Tuple_Info(tf, ti, tuple_id);
 caon_ptr<RE_Node> result = new RE_Node(tinfo);

 result->set_label(QString("<tinfo %1>").arg(tuple_id));
 return result;
}

caon_ptr<RE_Node> RE_Graph_Build::make_new_empty_tuple_node(caon_ptr<RE_Tuple_Info> rti)
{
 QString rep = rti->token_representation();
 caon_ptr<RE_Token> token = new RE_Token(rep);
 token->flags.is_empty_tuple_indicator = true;
 caon_ptr<RE_Node> result = make_new_node(token);
 result->set_label(rep);
 return result;
}

void RE_Graph_Build::check_hold_tuple_suffix(RE_Tuple_Info::Tuple_Indicators ti, QString& suffix)
{
 if(suffix.isEmpty())
  return;
 switch(ti)
 {
 case RE_Tuple_Info::Tuple_Indicators::Enter_Array:
 case RE_Tuple_Info::Tuple_Indicators::Enter_Vector:
 case RE_Tuple_Info::Tuple_Indicators::Enter_Map:
 case RE_Tuple_Info::Tuple_Indicators::Enter_Set:
  held_suffix_ = suffix;
  parse_context_.flags.take_a_space = true;
  suffix = QString();
  break;
 default:
  break;
 }
}

void RE_Graph_Build::finalize_take_a_space()
{
 QString hs = held_suffix_;
 held_suffix_ = QString();
 parse_context_.flags.take_a_space = false;
 add_run_token(hs);
}


void RE_Graph_Build::enter_tuple(QString name, QString prefix, QString entry, QString suffix)
{
 RE_Tuple_Info::Tuple_Formations tf = RE_Tuple_Info::get_tuple_formation(prefix);
 RE_Tuple_Info::Tuple_Indicators ti = RE_Tuple_Info::get_tuple_indicator(entry);

 // //  want to hold suffix character if ti is an entry ...
 check_hold_tuple_suffix(ti, suffix);

 RE_Tuple_Info::Tuple_Formations sf = RE_Tuple_Info::get_tuple_formation(suffix);

 int tuple_id;



 if(tf == RE_Tuple_Info::Tuple_Formations::Indicates_Declarations)
 {
  if(markup_position_.current_entry_is_backquoted())
  {
   if(ti == RE_Tuple_Info::Tuple_Indicators::Enter_Array)
   {
    markup_position_.add_call_entry(false, prefix);
    return;
   }
   else
   {
    tf = RE_Tuple_Info::Tuple_Formations::Indicates_Unquote;
   }
  }
 }

 if(tf == RE_Tuple_Info::Tuple_Formations::N_A)
 {
  if(ti == RE_Tuple_Info::Tuple_Indicators::Enter_Array)
  {
   markup_position_.add_call_entry(false, prefix);
   return;
  }
  else if(ti == RE_Tuple_Info::Tuple_Indicators::Leave_Array)
  {
   RE_Tuple_Info::Tuple_Indicators ti1 = markup_position_.data_chief_indicator();
   if(ti1 == RE_Tuple_Info::Tuple_Indicators::N_A)
   {
    markup_position_.leave_expression();
    return;
   }
  }
  else if(ti == RE_Tuple_Info::Tuple_Indicators::Enter_Map)
  {
   markup_position_.add_block_map_entry();
   return;
  }
  else if(ti == RE_Tuple_Info::Tuple_Indicators::Leave_Map)
  {
   if(caon_ptr<RE_Tuple_Info> rti = markup_position_.current_tuple_info())
   {
    if(rti->indicator() == RE_Tuple_Info::Tuple_Indicators::Enter_Map)
     goto good_to_go;
   }
   markup_position_.add_block_map_leave();
   return;
  }
  else
  {
   tuple_id = 0;
  }
 }
 else
good_to_go:
  tuple_id = ++tuple_entry_count_;


 caon_ptr<RE_Tuple_Info> tinfo = new RE_Tuple_Info(tf, ti, tuple_id);
 caon_ptr<RE_Node> tinfo_node = new RE_Node(tinfo);

 tinfo_node->set_label(QString("<tinfo %1>").arg(tuple_id));

 switch(ti)
 {
 case RE_Tuple_Info::Tuple_Indicators::Enter_Vector:
  if(tf == RE_Tuple_Info::Tuple_Formations::Indicates_Plex)
  {
   parse_context_.flags.inside_string_plex = true;
   current_string_plex_builder_ = new RZ_String_Plex_Builder(tinfo_node);
  }
  // fallthrough
 case RE_Tuple_Info::Tuple_Indicators::Enter_Array:
  {
   if(tf != RE_Tuple_Info::Tuple_Formations::N_A)
   {
    flags.inside_array_with_formation = true;
   }
  }
  // fallthrough
 case RE_Tuple_Info::Tuple_Indicators::Enter_Map:
 case RE_Tuple_Info::Tuple_Indicators::Enter_Set:
 case RE_Tuple_Info::Tuple_Indicators::Enter_Annotation:
  markup_position_.add_data_entry(tinfo_node);
  break;

 case RE_Tuple_Info::Tuple_Indicators::Leave_Vector:
  if(sf == RE_Tuple_Info::Tuple_Formations::Indicates_Plex)
  {
   caon_ptr<RE_Node> string_plex_node = close_string_plex();
   CAON_PTR_DEBUG(RE_Node ,tinfo_node)
   markup_position_.add_string_plex_node(tinfo_node, string_plex_node);
   parse_context_.flags.inside_string_plex = false;
  }
  //  fallthrough

 case RE_Tuple_Info::Tuple_Indicators::Leave_Array:
  flags.inside_array_with_formation = false;
  //  fallthrough
 case RE_Tuple_Info::Tuple_Indicators::Leave_Map:
 case RE_Tuple_Info::Tuple_Indicators::Leave_Set:
 case RE_Tuple_Info::Tuple_Indicators::Leave_Annotation:
  markup_position_.add_data_leave(tinfo_node);
  break;
 }
}

caon_ptr<RE_Node> RE_Graph_Build::new_function_def_entry_node(RE_Node& prior_node,
  RE_Function_Def_Kinds kind, caon_ptr<RE_Node> label_node)
{
 caon_ptr<RE_Function_Def_Entry> fdef = new RE_Function_Def_Entry(&prior_node, kind, label_node);
 caon_ptr<RE_Node> result = make_new_node(fdef);
 fdef->set_node(result);
 return result;
}

void RE_Graph_Build::add_run_token(QString raw_text, QString space_to_end_of_line)
{
 add_run_token(QString(), raw_text, QString(), Token_Formations::Normal, space_to_end_of_line);
}

caon_ptr<RE_Node> RE_Graph_Build::new_autogenerated_token_node(QString raw_text)
{
 caon_ptr<RE_Token> token = new RE_Token(raw_text);
 CAON_PTR_DEBUG(RE_Token ,token)
 caon_ptr<RE_Node> result = make_new_node(token);
 return result;
}

caon_ptr<RE_Node> RE_Graph_Build::new_run_call_entry_node(bool is_statement_entry,
  QString prefix, caon_ptr<RE_Call_Entry> parent_entry)
{
 caon_ptr<RE_Call_Entry> new_entry = new RE_Call_Entry(call_entry_count_, prefix);

 CAON_PTR_DEBUG(RE_Call_Entry ,new_entry)

 if(is_statement_entry)
  new_entry->flags.is_statement_entry = true;

 if(parent_entry)
 {
  CAON_PTR_DEBUG(RE_Call_Entry ,parent_entry)
  if(!new_entry->flags.no_normalize)
   new_entry->flags.no_normalize = parent_entry->flags.no_normalize;
  if(!new_entry->flags.no_anticipate)
   new_entry->flags.no_anticipate = parent_entry->flags.no_anticipate;
 }

 ++call_entry_count_;
 caon_ptr<RE_Node> result = make_new_node(new_entry);
 return result;
}

caon_ptr<RE_Node> RE_Graph_Build::new_run_block_entry_node()
{
 caon_ptr<RE_Block_Entry> new_entry = new RE_Block_Entry(block_entry_count_);
 ++block_entry_count_;
 caon_ptr<RE_Node> result = make_new_node(new_entry);
 return result;
}


void RE_Graph_Build::add_to_raw_lisp(QString str)
{
 raw_lisp_acc_ += str;
}

void RE_Graph_Build::process_raw_lisp()
{
 caon_ptr<RE_Token> token = new RE_Token(raw_lisp_acc_);
 raw_lisp_acc_.clear();
 token->flags.is_raw_lisp = true;
 add_raw_lisp_token(*token);
}


void RE_Graph_Build::process_string_literal()
{
 caon_ptr<RE_Token> token = new RE_Token(string_literal_acc_);
 string_literal_acc_.clear();
 token->flags.is_string_literal = true;
 add_run_token(*token);
}


void RE_Graph_Build::string_literal_start()
{
 parse_context_.flags.inside_string_literal = true;
}


void RE_Graph_Build::raw_lisp_start()
{
 parse_context_.flags.inside_raw_lisp = true;
}

void RE_Graph_Build::add_run_token(RE_Token& token)
{
 caon_ptr<RE_Node> node = make_new_node(&token);
 markup_position_.add_token_node(node);
}

void RE_Graph_Build::add_raw_lisp_token(RE_Token& token)
{
 caon_ptr<RE_Node> node = make_new_node(&token);
 markup_position_.add_raw_lisp_token(node);
}

void RE_Graph_Build::add_token_plus_block(QString token, QString block_entry)
{
 // //  Currently this only has token == "do", "in", or "/do/", block_entry = ".."
 if(token.startsWith('/'))
 {
  token.remove(0, 1).chop(1);
  add_run_token("", token, "", Token_Formations::Strong_Do_Plus_Block);
 }
 else
 {
  if(token != "do")
  {
   if(token == "in")
   {
    if(flags.ghost_in_closes_expression)
    {
     flags.ghost_in_closes_expression = false;
     markup_position_.leave_expression();
    }
   }
   token.prepend(';').append(';');
  }
  add_run_token("", token, "", Token_Formations::Do_Plus_Block);
 }
 markup_position_.add_block_map_entry();
}


void RE_Graph_Build::add_run_token(QString raw_text)
{
 add_run_token(QString(), raw_text, QString(), Token_Formations::Normal);
}

void RE_Graph_Build::add_equalizer_to_type(QString raw_text)
{
 if(markup_position_.current_node_is_symbol_declaration())
 {
  add_run_token(raw_text);
 }
 else
 {
  flags.pending_convert_to_type_symbol = true;
 }
}


void RE_Graph_Build::add_type_indicator(QString raw_text)
{
 if(flags.inside_array_with_formation)
 {
  add_run_token(raw_text);
  return;
 }
 caon_ptr<RE_Token> token = new RE_Token(raw_text);
 CAON_PTR_DEBUG(RE_Token ,token)
 caon_ptr<RE_Node> node = make_new_node(token);
 markup_position_.add_type_indicator(node);
}


void RE_Graph_Build::add_run_token(QString prefix, QString raw_text,
 QString suffix, Token_Formations tf, QString space_to_end_of_line)
{
 bool matches_expected_token_end = false;
 bool this_token_closes_expression = false;

 if(flags.next_token_closes_expression)
 {
  flags.next_token_closes_expression = false;
  this_token_closes_expression = true;
 }

 bool raw_text_to_type_symbol = false;

 if(raw_text.startsWith("$:"))
 {
  raw_text.replace(0, 2, ":|");
  raw_text.append('|');
  raw_text_to_type_symbol = true;
 }

 if(flags.pending_convert_to_type_symbol)
 {
  flags.pending_convert_to_type_symbol = false;

  if(!raw_text_to_type_symbol)
  {
   raw_text.prepend(":|");
   raw_text.append('|');
  }
 }

 caon_ptr<RE_Token> token = new RE_Token(raw_text, prefix, suffix);

 CAON_PTR_DEBUG(RE_Token ,token)

 if(token->flags.is_symbol_declaration)
 {
  markup_position_.check_add_implied_my();
 }

 caon_ptr<RE_Node> node = make_new_node(token);

 if(tf == Token_Formations::Cpp_Scoped)
 {
  token->flags.is_cpp_scoped = true;
 }
 else if(tf == Token_Formations::Do_Plus_Block)
 {
  token->flags.is_do = false;
  token->flags.precedes_ghost_scope = true;
  token->flags.not_entry = true;
 }
 else if(tf == Token_Formations::Strong_Do_Plus_Block)
 {
  token->flags.precedes_ghost_scope = true;
  // // do we need this, for other potential /.../ formations?
   //?token->flags.strong_ghost_scope = true;
 }

 if(token->flags.is_equalizer)
 {
  markup_position_.add_equalizer_token_node(node);
 }
 else if(token->flags.is_arrow)
 {
  markup_position_.add_arrow_token_node(node);
 }
 else if(token->flags.is_mapkey)
 {
  if(token->flags.is_do_mapkey)
  {
   markup_position_.hold_do_mapkey_node(node);
  }
  else
  {
   markup_position_.hold_mapkey_node(node);
  }
 }
 else if(token->special_token() == RE_Code_Representation::Special_Tokens::Auto_Expand_To_Null_Test)
 {
  markup_position_.add_call_entry(false);
  markup_position_.add_token_node(node);
  flags.next_token_closes_expression = true;
 }
 else if(token->special_token() == RE_Code_Representation::Special_Tokens::Auto_Expand_To_Not_Null_Test)
 {
  markup_position_.add_call_entry(false);
  markup_position_.add_token_node(node);
  flags.next_token_closes_expression = true;
 }
 else if(token->special_token() == RE_Code_Representation::Special_Tokens::Return_Value_Blank_Or_Identity)
 {
  markup_position_.hold_retval_node(node);
 }
 else if(raw_text.startsWith('@') && raw_text != "@" && raw_text != "@@")
 {
  if(markup_position_.awaiting_statement_call_entry())
  {
   raw_text = raw_text.mid(1);
   token->set_raw_text(raw_text);
   caon_ptr<RE_Token> ntoken = new RE_Token("&lr", QString(), QString());

   CAON_PTR_DEBUG(RE_Token ,ntoken)

   caon_ptr<RE_Node> nnode = make_new_node(ntoken);
   markup_position_.add_token_node(nnode);

   markup_position_.add_call_entry(false, "\\");
   markup_position_.add_token_node(node);

   flags.added_lr_mode = true;

  }
  else
  {
   markup_position_.add_token_node(node);
  }
 }
 else
 {
  markup_position_.add_token_node(node);
 }

 if(this_token_closes_expression)
 {
  markup_position_.leave_expression();
 }

 switch(token->special_token_kind())
 {
 case RE_Code_Representation::Special_Token_Kind::Auto_Statement_End:
  markup_position_.close_statement();
  break;
 case RE_Code_Representation::Special_Token_Kind::Auto_Statement_End_If_EOL:
  if(!space_to_end_of_line.isEmpty())
  {
   markup_position_.close_statement();
  }
  break;
 case RE_Code_Representation::Special_Token_Kind::Text_Map_Leave:
  markup_position_.close_statement();
  //fallthrough...
 case RE_Code_Representation::Special_Token_Kind::Text_Map_Leave_In_Statement:
  parse_context_.flags.inside_text_map_acc = false;
  flags.inside_text_map = false;
  break;
 case RE_Code_Representation::Special_Token_Kind::Text_Map_Enter:
  parse_context_.flags.inside_text_map_acc = true;
  flags.inside_text_map = true;
  set_expected_token_end(raw_text);
  break;
 default:
  break;
 }


 check_line_increment(space_to_end_of_line);

}


