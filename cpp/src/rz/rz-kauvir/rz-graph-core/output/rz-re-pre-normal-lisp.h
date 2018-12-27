
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_PRE_NORMAL_LISP__H
#define RZ_RE_PRE_NORMAL_LISP__H

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

class RE_Pre_Normal_Lisp : public RE_Lisp_Output
{
public:

#ifdef NO_CAON
 RE_Pre_Normal_Lisp(RE_Document* document);
#else
 RE_Pre_Normal_Lisp(caon_ptr<RE_Document> document);
#endif

 virtual void report_token(QTextStream& qts,
  const RE_Token& token);

 virtual void report_tuple_info_entry(QTextStream& qts,
  const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr = nullptr);

 virtual void report_tuple_info_leave(QTextStream& qts,
  const RE_Tuple_Info& rti, caon_ptr<RE_Call_Entry> rce_ptr = nullptr);

 virtual void report_call_entry(QTextStream& qts,
  const RE_Call_Entry& rce);

 virtual void report_call_leave(QTextStream& qts,
  const RE_Call_Entry& rce);


};

_RZNS(RECore)

#endif //RZ_RE_PRE_NORMAL_LISP__H
