
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-statement.h"

#include "kcm-expression.h"
#include "kauvir-code-model.h"

#include "kcm-block.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Statement::KCM_Statement(Statement_Kinds statement_kind, KCM_Expression* expression)
 :  statement_kind_(statement_kind), expression_(expression),
   nested_block_(nullptr), bind_qob_(nullptr)
{

}

KCM_Statement::KCM_Statement(Statement_Kinds statement_kind, KCM_Overloadable_Symbol symbol)
 :  statement_kind_(statement_kind), symbol_(symbol),
    expression_(nullptr), nested_block_(nullptr),
    bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Statement::KCM_Statement(Statement_Kinds statement_kind,
   QString symbol_name, KCM_Expression* expression)
 :  statement_kind_(statement_kind),
    symbol_(KCM_Overloadable_Symbol(symbol_name, 0)),
    expression_(expression),
    nested_block_(nullptr),
    bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Statement::KCM_Statement(Statement_Kinds statement_kind,
  QString symbol_name, const KCM_Type_Object* kto, QString val)
 :  statement_kind_(statement_kind),
    symbol_(KCM_Overloadable_Symbol(symbol_name, 0)),
    expression_(nullptr),
    nested_block_(nullptr),
    bind_kto_(kto), bind_val_(val), bind_qob_(nullptr)
{

}

KCM_Statement::KCM_Statement(Statement_Kinds statement_kind,
  QString symbol_name, const KCM_Type_Object* kto, QObject* qob)
 :  statement_kind_(statement_kind),
    symbol_(KCM_Overloadable_Symbol(symbol_name, 0)),
    expression_(nullptr),
    nested_block_(nullptr),
    bind_kto_(kto), bind_qob_(qob)
{

}

