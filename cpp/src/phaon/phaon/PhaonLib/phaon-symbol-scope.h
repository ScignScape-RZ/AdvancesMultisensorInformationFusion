
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_SYMBOL_SCOPE__H
#define PHAON_SYMBOL_SCOPE__H


#include "kans.h"

#include <QString>
#include <QMap>

#include "accessors.h"

#include "phaon-function-vector.h"


KANS_(PhaonLib)

class Phaon_Namespace;

class Phaon_Symbol_Scope : public QMap<QString, Phaon_Function_Vector>
{

public:

 Phaon_Symbol_Scope();



};


_KANS(PhaonLib)


#endif //PHAON_SYMBOL_SCOPE__H
