
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYNAMO_NESTED_ACC__H
#define RZ_DYNAMO_NESTED_ACC__H


#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QSet>
#include <QStringList>

#include <QMap>

class QTextStream;

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)

USING_KANS(KCM)

KANS_(Dynamo)

class RZ_Dynamo_Nested_Acc
{

 QString out_code_;

 QMap<QString, int> trigger_tracker_;

 QSet<QString> nonzero_triggers_;

 QStringList readies_;

public:


 RZ_Dynamo_Nested_Acc(const QString& oc);

 void add_trigger(QString key);
 void subtract_trigger(QString key);

 void add_triggers(const QStringList& keys,
   QMap<QString, QList<RZ_Dynamo_Nested_Acc*>>& triggers);

 QString check_finalize(QStringList& absorbed_readies);

 void absorb_readies(QStringList& readies);

};

_KANS(Dynamo)

#endif //RZ_DYNAMO_NESTED_ACC__H
