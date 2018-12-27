
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_NAMESPACE__H
#define PHAON_NAMESPACE__H


#include "kans.h"
#include "accessors.h"


#include <QString>


KANS_(PhaonLib)


class Phaon_Namespace
{
 QString name_;

public:

 Phaon_Namespace(QString name);

 ACCESSORS(QString ,name)


};



_KANS(PhaonLib)


#endif //PHAON_NAMESPACE__H
