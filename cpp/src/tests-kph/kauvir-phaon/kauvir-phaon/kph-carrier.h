
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KPH_CARRIER__H
#define KPH_CARRIER__H


#include "kans.h"

#include <QString>
#include <QMap>

#include "accessors.h"


KANS_(Phaon)

class KPH_Carrier
{
 QString channel_name_;
 QString carrier_mode_;
 QString type_name_;
 QString type_mode_;
 QString key_;
 int pos_;
 int expref_;
 QString symref_;
 QString value_;

public:

 KPH_Carrier();

 ACCESSORS(QString ,channel_name)
 ACCESSORS(QString ,carrier_mode)
 ACCESSORS(QString ,type_name)
 ACCESSORS(QString ,type_mode)
 ACCESSORS(QString ,key)
 ACCESSORS(int ,pos)
 ACCESSORS(int ,expref)
 ACCESSORS(QString ,symref)
 ACCESSORS(QString ,value)

 QString* value_as_ptr()
 {
  if(symref_.isEmpty())
    return &value_;
  if(value_.isEmpty());
    return nullptr;
  return &value_;
 }

 void supply_data(QByteArray& qba) const;
 void absorb_data(const QByteArray& qba);

};


_KANS(Phaon)


#endif //KPH_CARRIER__H
