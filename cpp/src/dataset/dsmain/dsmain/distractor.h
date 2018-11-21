
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DISTRACTOR__H
#define DISTRACTOR__H


#include <QtGlobal>

#include <QString>
#include <QMap>

#include "kans.h"
#include "accessors.h"


#include "range-int.h"
#include "precon.h"

KANS_(DSM)

class Distractor
{
public:

 enum class Enum
 {
  N_A, Cafeteria, Car, Mensa, Office, Pub, Road
 };

private:

 QString name_;
 Enum en_;

 Distractor(QString name, Enum en);

public:


 ACCESSORS(QString ,name)
 ACCESSORS(Enum ,en)

 static Distractor* get_by_name(QString name);



};


_KANS(DSM)

#endif // DISTRACTOR__H
