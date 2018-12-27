
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-file.h"

#include "kcm-statement.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_File::KCM_File(QString file_name)
  :  file_name_(file_name)
{
}

void KCM_File::add_statement(KCM_Statement* statement)
{
 statements_.push_back(statement);
}


