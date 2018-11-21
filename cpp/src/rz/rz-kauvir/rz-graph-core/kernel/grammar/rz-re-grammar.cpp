
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-grammar.h"

#include "kernel/grammar/rz-re-parse-context.h"

#include "kernel/grammar/rz-re-graph-build.h"

#include "kernel/grammar/rz-re-parser.h"

#include "relae-graph/relae-parser.templates.h"

USING_RZNS(RECore)

RE_Grammar::RE_Grammar()
{
}

void RE_Grammar::init(RE_Parser& p, RE_Graph& g, RE_Graph_Build& graph_build)
{

 pre_rule( "script-word", "(?:[^{}()\\[\\]\\s`;,:]|(?:\\w::?\\w))+" );
 pre_rule( "ns-word", "(?: [^{}()\\[\\]\\s`;,:]+ )" );

 pre_rule( "space-to-end-of-line", "[__\\t]* (?: ;- [^\\n]+ )? (?= \\n )" );
 pre_rule( "end-of-line", "[__\\t\\S]* \\n" );
 pre_rule( "single-space", "[__\\t]" );
 pre_rule( "namespaced-word", "[\\w-:]+" );

 Context run_context = add_context("run-context");

 Context data_context = add_context("data-context");

 Context lisp_context = add_context("lisp-context");

 track_context({&run_context,
                &data_context,
                &lisp_context});

 activate(run_context);

 RE_Parse_Context& parse_context = graph_build.parse_context();

 parse_context.flags.pre_markup = true;

 add_rule(flags_all_(parse_context ,take_a_space), run_context, "take-a-space",
   " .single-space. ",
   [&]
  {
   graph_build.finalize_take_a_space();
  } );

 add_rule( flags_all_(parse_context ,inside_string_literal), run_context,
  "string-literal-character",
  " (?: [^\\\"] | \\\\\" )+ ",
  [&]
 {
  QString str = p.match_text();
  if(str == "\\\"")
   str = "\"";
  graph_build.add_to_string_literal(str);
 });


 add_rule( flags_all_(parse_context ,inside_string_literal), run_context,
  "string-literal-end",
  " \" ",
  [&]
 {
  graph_build.process_string_literal();
  parse_context.flags.inside_string_literal = false;
 });


 add_rule(flags_all_(parse_context ,inside_run_comment), run_context,
  "multi-line-run-comment-end",
  " (?<left> - -+ ) (?<right> ;+ ) "
           ,[&]
 {
  QString left = p.matched("left");
  QString right = p.matched("right");
  graph_build.check_run_comment_end(left.size(), right.size());
 });

 add_rule( run_context, "multi-line-run-comment-begin",
  " (?<left> ;+ ) (?<right> - -+ ) .end-of-line. "
  ,[&]
 {
  QString left = p.matched("left");
  QString right = p.matched("right");
  graph_build.check_run_comment_begin(left.size(), right.size());
 });

 add_rule(flags_all_(parse_context ,inside_run_comment), run_context,
  "multi-line-run-comment-body",
  " (?: [^-;]+ ) | [;-] "
   ,[&]
 {
  // //  chance to preview the comment ...
  // QString s = p.match_text();
 });



 add_rule(flags_none_(parse_context ,inside_run_comment), run_context,
  "run-comment",
  " (?<left> ;+ - ) [^\\n]* "
           ,[&]
 {
 });


 add_rule( run_context, "raw-lisp-start",
  " lisp_ ",
   [&]
 {
  graph_build.raw_lisp_start();
 });

 add_rule( run_context, "raw-lisp-end",
  " _lisp ",
   [&]
 {
  graph_build.process_raw_lisp();
  parse_context.flags.inside_raw_lisp = false;
 });


 add_rule(flags_all_(parse_context ,inside_raw_lisp), run_context, "raw-lisp-text",
          " . "
          ,[&]
 {
  graph_build.add_to_raw_lisp(p.match_text());
 });


 add_rule( run_context, "string-literal-start",
  " \" ",
   [&]
 {
  graph_build.string_literal_start();
 });

 add_rule(flags_all_(parse_context ,inside_string_plex), run_context, "string-plex-switch",
          " : (?<key> \\S* ) : "
          ,[&]
 {
  QString key = p.matched("key");
  graph_build.string_plex_switch(key);
 });


 add_rule(flags_all_(parse_context ,inside_string_plex), run_context, "end-string-plex",
          " (?<entry> \\] ) (?<suffix> -- ) "
          ,[&]
 {
  QString name = QString();
  QString prefix = QString();
  QString entry = p.matched("entry");
  QString suffix = p.matched("suffix");
  graph_build.enter_tuple(name, prefix, entry, suffix);
 });

 add_rule(flags_all_(parse_context ,inside_string_plex), run_context, "string-plex-text",
          " (?: [^:] | (?: : \\S* \\s+) ) "
          ,[&]
 {
  graph_build.string_plex_acc(p.match_text());
 });


 add_rule( run_context, "run-tuple-indicator-opens",
  " (?<name> \\w* ) "
  " (?<prefix> [;,:_+`'#$%*~\\\\^!@\\-\\.]* )"
  " (?<entry> (?: \\{{2,3} ) | "
  "   (?: \\[{2,3} ) | [ [({ ] )"
  " (?<suffix> [*~]* (?=\\s) )?"
   ,[&]
 {
  QString name = p.matched("name");
  QString prefix = p.matched("prefix");
  QString entry = p.matched("entry");
  QString suffix = p.matched("suffix");
  graph_build.enter_tuple(name, prefix, entry, suffix);
 });

 add_rule( run_context, "run-tuple-indicator-closes",
  " (?<prefix> [;:\\.]* )"
  " (?<entry> (?: \\}{2,3}) | "
  "   (?: \\]{2,3}) | [\\])] )"
  " (?<suffix> [*~]* (?=\\s) )?"
   ,[&]
 {
  QString prefix = p.matched("prefix");
  QString entry = p.matched("entry");
  QString suffix = p.matched("suffix");
  graph_build.enter_tuple(QString(), prefix, entry, suffix);
 });

 add_rule( run_context, "run-token-with-ns",
  " (?<prefix> [:,;`']* )"
  " (?<ns> (?: .ns-word. : :? )+ )"
  " (?<word> .script-word.) "
  " (?<eol> .space-to-end-of-line. \\n)?",
   [&]
 {
  QString prefix = p.matched("prefix");
  QString ns = p.matched("ns");
  QString m = p.matched("word");
  QString s = p.matched("eol");
  if(ns.endsWith("::"))
  {
   graph_build.add_run_token(prefix, ns + m, "", RE_Graph_Build::Token_Formations::Cpp_Scoped, s);
  }
  else
  {
   graph_build.add_run_token(prefix, ns + m, "", RE_Graph_Build::Token_Formations::Normal, s);
  }
 });

 add_rule( run_context, "type-indicator",
  " <- ",
   [&]
 {
  QString match_text = p.match_text();
  graph_build.add_type_indicator(match_text);
 });

 add_rule( run_context, "equalizer-to-type",
  " == ",
   [&]
 {
  QString match_text = p.match_text();
  graph_build.add_equalizer_to_type(match_text);
 });

 add_rule( run_context, "run-token-type-related-function",
  " (?<word> ::: ) "
  " (?<eol> .space-to-end-of-line. \\n)?",
   [&]
 {
  QString m = p.matched("word");
  QString s = p.matched("eol");
  graph_build.add_run_token("", m, "", RE_Graph_Build::Token_Formations::Normal, s);
 });

 add_rule( run_context, "run-token-with-eol",
  " (?<prefix> [:,;`']* )"
  " (?<word> .script-word.) "
  " (?<suffix> :? ) "
  " (?<eol> .space-to-end-of-line. \\n)?",
   [&]
 {
  QString prefix = p.matched("prefix");
  QString m = p.matched("word");
  QString suffix = p.matched("suffix");
  QString s = p.matched("eol");
  graph_build.add_run_token(prefix, m, suffix, RE_Graph_Build::Token_Formations::Normal, s);
 });


 add_rule( run_context, "run-token-semis",
  " (?<word> ;+ )"
  " (?<suffix> [,/.]? )"
  " (?<eol> .space-to-end-of-line. \\n)?",
   [&]
 {
  QString m = p.matched("word");
  QString s = p.matched("suffix");
  QString e = p.matched("eol");
  graph_build.add_semis(m, s, e);
 });

}

