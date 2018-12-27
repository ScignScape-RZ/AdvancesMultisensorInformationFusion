
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_PRE_RUN_LISP__H
#define RZ_RE_PRE_RUN_LISP__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-node-ptr.h"

#include "rz-re-lisp-output.h"

#include <QString>
#include <QTextStream>
#include <QMap>

#include <functional>

#include "rzns.h"
RZNS_(RECore)


class RE_Document;
class RE_Node;

class RE_Pre_Run_Lisp : public RE_Lisp_Output
{
public:

 RE_Pre_Run_Lisp(caon_ptr<RE_Document> document);

 virtual void output_from_node(QTextStream& qts,
  const RE_Node& node, int indent = 0);

 virtual void report_call_entry(QTextStream& qts,
  const RE_Call_Entry& rce) override;

 virtual void report_call_leave(QTextStream& qts,
  const RE_Call_Entry& rce) override;



};

_RZNS(RECore)

#endif //RZ_RE_PRE_RUN_LISP__H
