
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-block.h"

#include "kcm-statement.h"

#include "kcm-report-syntax.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)

KCM_Block::KCM_Block(KCM_Lexical_Scope* lexical_scope)
  :  lexical_scope_(lexical_scope)
{
}

void KCM_Block::add_statement(KCM_Statement* statement)
{
 statements_.push_back(statement);
}
