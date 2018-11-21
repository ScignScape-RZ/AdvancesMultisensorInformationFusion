
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_BLOCK_ENTRY__H
#define RZ_RE_BLOCK_ENTRY__H

#include "accessors.h"
#include "flags.h"


#include <QString>
#include <QMap>


#include "relae-graph/relae-caon-ptr.h"

#include "flags.h"

#include "rzns.h"

RZNS_(GVal)

class RZ_Lisp_Graph_Lexical_Scope;

_RZNS(GVal)

USING_RZNS(GVal)

RZNS_(RECore)

class RE_Node;

class RE_Block_Entry
{
public:
 flags_(3)
  bool file_default:1;
  bool monad_definition:1;
  bool function_definition:1;
  bool if_block:1;
  bool else_block:1;
  bool elsif_block:1;
  bool has_else_block:1;
  bool caserun_block:1;
  bool presumptive_else_block:1;
  bool do_block_entry:1;
  bool scan_block:1;
  bool ghost_block:1;
  bool likely_if_block:1;
  bool async:1;
  bool do_map:1;
  bool presumptive_elsif_block:1;
  bool likely_elsif_block:1;
  bool has_elsif_block:1;
  bool follows_elsif_block:1;
 _flags

 bool quasi_statements()
 {
  return !(flags.file_default || flags.monad_definition);
 }

private:

 caon_ptr<RE_Node> statement_entry_node_;
 caon_ptr<RZ_Lisp_Graph_Lexical_Scope> lexical_scope_;

 int call_id_;

 int nested_depth_;

 QString notes_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,statement_entry_node)
 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Lexical_Scope> ,lexical_scope)

 ACCESSORS__GET(int ,call_id)
 ACCESSORS(int ,nested_depth)
 ACCESSORS(QString ,notes)


 RE_Block_Entry(int call_id);

};

_RZNS(RECore)

#endif //RZ_RE_BLOCK_ENTRY__H
