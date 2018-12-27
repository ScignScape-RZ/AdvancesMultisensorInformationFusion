
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_DOCUMENT__H
#define RZ_RE_DOCUMENT__H

#include "relae-graph/relae-node-ptr.h"

#include "kernel/rz-re-dominion.h"

#include "accessors.h"

#include "rzns.h"

#include <QFile>
#include <QTextStream>


RZNS_CLASS_DECLARE(NL ,NL_Lexicon)
USING_RZNS(NL)


RZNS_(RECore)

class RE_Parser;
class RE_Grammar;
class RE_Graph_Build;
class RE_Word_Entry_List;
class RE_Graph;

class RE_Document
{
 caon_ptr<RE_Graph> graph_;
 caon_ptr<RE_Parser> parser_;
 caon_ptr<RE_Graph_Build> graph_build_;
 caon_ptr<RE_Grammar> grammar_;

 QString local_path_;
 QString raw_text_;

 QString local_directory_;

 QString xquery_text_;

 void resolve_report_path(QString& path);

 int number_of_lines_;

 caon_ptr<NL_Lexicon> nl_lexicon_;

 void preprocess_raw_text();
 static QString insert_block_map_signatures(QString original_source, QString sig);
 void finalize_raw_text();

public:


 ACCESSORS(QString ,local_path)
 ACCESSORS(QString ,raw_text)
 ACCESSORS(QString ,local_directory)
 ACCESSORS(caon_ptr<RE_Graph> ,graph)
 ACCESSORS__GET(caon_ptr<RE_Grammar> ,grammar)

 ACCESSORS(caon_ptr<RE_Graph_Build> ,graph_build)
 ACCESSORS(caon_ptr<NL_Lexicon> ,nl_lexicon)

 RE_Document(QString path);

 ~RE_Document();

 void load_file(QString path);
 void report_graph(QString path);

 void report_raw_text(QString path);

 void report_raw_text(QString path, QString pre);

 void write_report(QString path);

 void set_grammar(RE_Grammar* grammar = nullptr);

 void parse(int start_position = 0, int end_position = -1);

 template<typename T>
 void write_report(QString path, T& report)
 {
  resolve_report_path(path);
  QFile file(path);
  if(file.open(QFile::WriteOnly | QIODevice::Text))
  {
   QTextStream qts(&file);
   report.write_report(qts);
  }
 }



};

_RZNS(RECore)


#endif //RZ_RE_DOCUMENT__H
