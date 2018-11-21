
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_FUNCTION_VECTOR__H
#define PHAON_FUNCTION_VECTOR__H


#include "kans.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include <QVector>

#include <QSet>

#include "phaon-function.h"

KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)
USING_KANS(KCM)

KANS_(PhaonLib)


class Phaon_Function_Vector : public QVector<Phaon_Function>
{

public:

 Phaon_Function_Vector();

 void* match_against_codes(const QSet<int>& codes, int& mc, int& rbc,
   const KCM_Type_Object** pkto = nullptr);

 void* find_argvec_function(int& mc, int& rbc,
   const KCM_Type_Object** pkto = nullptr);

 void* get_first();

};


_KANS(PhaonLib)


#endif //PHAON_FUNCTION_VECTOR__H
