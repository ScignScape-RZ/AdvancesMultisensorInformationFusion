
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-overloadable-symbol.h"

#include "kcm-report-syntax.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Overloadable_Symbol::KCM_Overloadable_Symbol(QString symbol_name, int overload_index)
  :  symbol_name_(symbol_name), overload_index_(overload_index)
{

}

KCM_Overloadable_Symbol::KCM_Overloadable_Symbol()
{

}

QString KCM_Overloadable_Symbol::encode_to_symbol_name() const
{
 if(overload_index_ == 0)
   return symbol_name_;
 return QString("%1#%2").arg(overload_index_).arg(symbol_name_);
}


void KCM_Overloadable_Symbol::report(QTextStream& qts,
  Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs)
{
 if(kcrs.flags.use_block_statement_syntax)
 {
  qts << symbol_name_;
 }
 else
 {
  qts << "(" << encode_to_symbol_name() << ")";
 }
}
