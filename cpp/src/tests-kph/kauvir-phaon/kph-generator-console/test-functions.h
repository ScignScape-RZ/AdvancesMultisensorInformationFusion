
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST_FUNCTIONS__H
#define TEST_FUNCTIONS__H


#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QStringList>

#include <QMap>


KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
USING_KANS(KCM)

KANS_CLASS_DECLARE(PhaonLib ,Phaon_Channel_Group_Table)
KANS_CLASS_DECLARE(PhaonLib ,Phaon_Symbol_Scope)
USING_KANS(PhaonLib)


KANS_(Phaon)

void init_test_functions(Kauvir_Code_Model& kcm,
  Phaon_Channel_Group_Table& table, Phaon_Symbol_Scope& pss);

_KANS(Phaon)


#endif //TEST_FUNCTIONS__H
