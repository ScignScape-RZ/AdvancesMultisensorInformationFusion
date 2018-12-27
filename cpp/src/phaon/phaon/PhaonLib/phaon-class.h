
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_CLASS__H
#define PHAON_CLASS__H


#include "kans.h"

#include <QString>

#include "accessors.h"


KANS_(PhaonLib)

class Phaon_Namespace;

class Phaon_Class
{
 Phaon_Namespace* phaon_namespace_;
 QString name_;

public:

 Phaon_Class(QString name, Phaon_Namespace* phaon_namespace);

 ACCESSORS(QString ,name)
 ACCESSORS(Phaon_Namespace* ,phaon_namespace)


};


_KANS(PhaonLib)


#endif //PHAON_CLASS__H
