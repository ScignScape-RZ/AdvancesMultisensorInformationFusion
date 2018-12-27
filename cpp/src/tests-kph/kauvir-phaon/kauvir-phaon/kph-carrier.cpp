
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-carrier.h"


#include <QDebug>
#include <QDataStream>

USING_KANS(Phaon)

KPH_Carrier::KPH_Carrier()
  :  pos_(0), expref_(0)
{

}

void KPH_Carrier::supply_data(QByteArray& qba) const
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 qds << channel_name_;
 qds << carrier_mode_;
 qds << type_name_;
 qds << type_mode_;
 qds << key_;
 qds << pos_;
 qds << expref_;
 qds << symref_;
 qds << value_;
}

void KPH_Carrier::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);

 qds >> channel_name_;
 qds >> carrier_mode_;
 qds >> type_name_;
 qds >> type_mode_;
 qds >> key_;
 qds >> pos_;
 qds >> expref_;
 qds >> symref_;
 qds >> value_;
}
