
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-lisp-core-function.h"

#include <QString>

#include "rzns.h"


USING_RZNS(GBuild)

RZ_Lisp_Core_Function::RZ_Lisp_Core_Function
 (QString rz_name, QString name, int arity, Status_Codes sc)
 : Flags(0), rz_name_(rz_name), name_(name), arity_(arity)
{
 info_.pre_init();
 switch(sc)
 {
 case Preempt:
  flags.preempt = true;
  break;
 case Defer:
  flags.defer = true;
  break;
 case Paste:
  flags.paste = true;
  break;
 case Both:
  flags.preempt = true;
  flags.defer = true;
  break;
 case Valuer_DC:
 case Valuer_CB:
 case Valuer_RN:
 case Valuer_N:
 case Valuer_N_S:
 case Valuer_N_S_S:
 case Valuer_N_T:
  flags.valuer = true;
  break;
 case CO_Preempt:
  flags.preempt = true;
  flags.use_rz_out_name = true;
  break;
 case CO_Defer:
  flags.defer = true;
  flags.use_rz_out_name = true;
  break;
 case CO_Both:
  flags.preempt = true;
  flags.defer = true;
  flags.use_rz_out_name = true;
  break;

 }
}

QMap<QString, QString> RZ_Lisp_Core_Function::out_pastes_
 {{{ "Generate_Clos", "(self -> generate-clos)" }}};


QString RZ_Lisp_Core_Function::get_out_name()
{
 if(flags.use_out_name)
  return out_name_;
 if(flags.use_rz_out_name)
  return QString("rz::%1").arg(name_);

 return rz_name_;
}

QString RZ_Lisp_Core_Function::get_out_name_or_string()
{
 if(flags.paste)
 {
  return out_pastes_[get_out_name()];
 }
 return get_out_name();
}



