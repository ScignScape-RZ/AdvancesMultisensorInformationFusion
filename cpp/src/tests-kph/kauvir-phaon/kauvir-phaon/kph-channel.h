
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KPH_CHANNEL__H
#define KPH_CHANNEL__H


#include "kans.h"

#include <QString>
#include <QMap>
#include <QVector>


#include "accessors.h"


KANS_(Phaon)

class KPH_Carrier;

class KPH_Channel
{
 QString channel_name_;
 QVector<KPH_Carrier*> carriers_;

public:

 KPH_Channel();

 ACCESSORS(QString ,channel_name)


};


_KANS(Phaon)


#endif //KPH_CHANNEL__H
