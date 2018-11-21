
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_CORE_FUNCTION__H
#define RZ_LISP_CORE_FUNCTION__H


#include "valuer/rz-lisp-graph-function-info.h"

#include "accessors.h"

#include "flags.h"

#include <QString>

#include "rzns.h"
RZNS_(GBuild)


class RZ_Lisp_Core_Function
{
public:
 enum Status_Codes {
  Preempt, Defer, Valuer_DC, Valuer_CB, Valuer_RN, Valuer_N,
  Valuer_N_S, Valuer_N_S_S, Valuer_N_T, Paste, Both,
  CO_Preempt, CO_Defer, CO_Both
 };

 flags_(1)
  bool preempt:1;
  bool defer:1;
  bool use_out_name:1;
  bool use_rz_out_name:1;
  bool paste:1;
  bool valuer:1;
 _flags

private:

 QString rz_name_;
 QString name_;
 int arity_;
 RZ_Lisp_Graph_Function_Info info_;
 QString out_name_;

 static QMap<QString, QString> out_pastes_;

public:

 ACCESSORS(QString ,rz_name)
 ACCESSORS(QString ,name)
 ACCESSORS(int ,arity)
 ACCESSORS__RGET(RZ_Lisp_Graph_Function_Info ,info)
 ACCESSORS(QString ,out_name)

 RZ_Lisp_Core_Function(QString rz_name, QString name, int arity, Status_Codes sc);

 QString get_out_name();
 QString get_out_name_or_string();

};

_RZNS(GBuild)


#endif //RZ_LISP_CORE_FUNCTION__H
