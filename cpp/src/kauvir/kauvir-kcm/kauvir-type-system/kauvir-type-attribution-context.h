
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KAUVIR_TYPE_ATTRIBUTION_CONTEXT__H
#define KAUVIR_TYPE_ATTRIBUTION_CONTEXT__H

#include "kans.h"

#include "accessors.h"

#include <QVector>

KANS_(Kauvir)

class Kauvir_Type_Attribution_Context
{
 QString name_;

public:

 Kauvir_Type_Attribution_Context(QString name);


 ACCESSORS(QString ,name)


};


_KANS(Kauvir)


#endif //KAUVIR_TYPE_ATTRIBUTION_CONTEXT__H

