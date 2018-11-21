
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_LISP_OUTPUT__H
#define RZ_RE_LISP_OUTPUT__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-node-ptr.h"

#include "kernel/query/rz-re-query.h"
#include "kernel/frame/rz-re-frame.h"

#include <QString>
#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"
RZNS_(RECore)


class RE_Document;
class RE_Node;

class RE_Lisp_Output
{
protected:

 caon_ptr<RE_Document> document_;

 const RE_Frame& fr_;
 const RE_Query& rq_;

 virtual void output_from_node(QTextStream& qts,
  const RE_Node& node, int indent = 0,
  caon_ptr<RE_Call_Entry> rce_ptr = nullptr);

 virtual QString get_lisp_out(const RE_Token& token);

 virtual void report_call_entry(QTextStream& qts,
  const RE_Call_Entry& rce) = 0;

 virtual void report_call_leave(QTextStream& qts,
  const RE_Call_Entry& rce) = 0;

 virtual void report_tuple_info_entry(QTextStream& qts,
  const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> = nullptr) = 0;

 virtual void report_tuple_info_leave(QTextStream& qts,
  const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> = nullptr) = 0;

 virtual void report_token(QTextStream& qts,
  const RE_Token& token) = 0;

 virtual void init_token(RE_Token& token) {}

public:

 RE_Lisp_Output(caon_ptr<RE_Document> document);

 virtual void output(QString path);
 virtual void write_report(QTextStream& qts);

};

_RZNS(RECore)

#endif //RZ_RE_LISP_OUTPUT__H
