
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-nested-acc.h"


#include <QTextStream>

#include <QDebug>
#include <QProcess>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QEventLoop>

USING_KANS(Dynamo)


RZ_Dynamo_Nested_Acc::RZ_Dynamo_Nested_Acc(const QString& oc)
  :  out_code_(oc)
{

}

void RZ_Dynamo_Nested_Acc::add_trigger(QString key)
{
 ++trigger_tracker_[key];
 nonzero_triggers_.insert(key);
}

void RZ_Dynamo_Nested_Acc::absorb_readies(QStringList& readies)
{
 readies_.append(readies);
}

void RZ_Dynamo_Nested_Acc::add_triggers(const QStringList& keys, QMap<QString,
  QList<RZ_Dynamo_Nested_Acc*>>& triggers)
{
 for(const QString& key : keys)
 {
  add_trigger(key);
  triggers[key].push_back(this);
 }
}

QString RZ_Dynamo_Nested_Acc::check_finalize(QStringList& absorbed_readies)
{
 if(nonzero_triggers_.isEmpty())
 {
  absorbed_readies.append(readies_);
  return out_code_;
 }
 return QString();
}


void RZ_Dynamo_Nested_Acc::subtract_trigger(QString key)
{
 if(trigger_tracker_.contains(key))
 {
  int v = trigger_tracker_.value(key);
  if(v > 1)
  {
   --trigger_tracker_[key];
  }
  else if(v == 1)
  {
   trigger_tracker_[key] = 0;
   nonzero_triggers_.remove(key);
  }
  else
  {
   // // error?
  }
 }
}




