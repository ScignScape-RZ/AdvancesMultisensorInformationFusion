
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-sample.h"

#include "posit-lib/posit.h"

#include <QStringList>
#include <QDebug>

#include "textio.h"


USING_KANS(DSM)
USING_KANS(TextIO)


Test_Sample::Test_Sample(int index)
  :  index_(index), temperature_adj_(0)
{

}

void Test_Sample::set_temperature_adj(quint16 q)
{
 set_temperature_adj(q, precon<temperature_adj_t>(q));
}

void Test_Sample::set_temperature_adj(precon_pr<temperature_adj_t> pr)
{
 temperature_adj_ = pr.data;
}

void Test_Sample::set_temperature_adj(quint16 q, precon<temperature_adj_t> pre)
{
 if(pre.pass_fn)
   set_temperature_adj(precon_pr<temperature_adj_t>{q, pre});
}

void Test_Sample::read_samples_from_file(QString path, QVector<Test_Sample*>& samps)
{
 QString text = load_file(path);
 QStringList qsl = text.split('\n');
 int sz = qsl.takeFirst().mid(1).toInt();
 samps.resize(sz);
 int current_index = 0;
 int field = 0;
 char fields [4] = {'t', 'f', 'w', 'a'};
 Test_Sample* samp = nullptr;
 for(QString qs : qsl)
 {
  if(qs.isEmpty())
    continue;
  if(qs.startsWith('#'))
  {
   current_index = qs.mid(1).toInt();

   if(samp)
     samp->finalize();

   samp = new Test_Sample(current_index);
   samps[current_index - 1] = samp;
   field = 0;
   continue;
  }
  switch(fields[field])
  {
  case 't':
   {
    samp->set_temperature_adj(qs.toInt());
   }
   break;

  case 'f':
   {
    samp->set_flow(Posit(qs.toDouble()));
   }
   break;

  case 'w':
   {
    samp->set_time_with_flow(Posit(qs.toDouble()));
   }
   break;

  case 'a':
   {
    samp->set_time_against_flow(Posit(qs.toDouble()));
   }
   break;
  }
  ++field;
 }
}

void Test_Sample::finalize()
{
 temperature_kelvin_ = Posit( double(temperature_adj_/100) + 273.15 );
 average_time_ = (time_with_flow_ + time_against_flow_) / 2;
 delta_time_ = time_against_flow_ - time_with_flow_;
}

void Test_Sample::read_samples_from_raw_file(QString path, QVector<Test_Sample*>& samps)
{
 QString text = load_file(path);
 QStringList qsl = text.split('\n');

 char c = 0;
 int i = 0;

 for(QString qs : qsl)
 {
  if(qs.isEmpty())
    continue;

  ++i;

  if(qs.startsWith(':'))
  {
   c = qs[1].toLatin1();
   i = 0;
   continue;
  }

  Test_Sample* samp;

  if(c == 'f')
  {
   samp = new Test_Sample(i);
   double dbl = qs.toDouble();
   Posit p = Posit(dbl);
   samp->set_flow(p);
   samps.push_back(samp);
   continue;
  }

  samp = samps[i - 1];

  if(c == 't')
  {
   qs.replace('.', "");
   samp->set_temperature_adj(qs.toInt());
   continue;
  }

  double dbl = qs.toDouble();
  Posit p = Posit(dbl);

  if(c == 'w')
    samp->set_time_with_flow(p);
  else if(c == 'a')
    samp->set_time_against_flow(p);

 }
}

void Test_Sample::write_samples_to_file(QString path, QVector<Test_Sample*>& samps)
{
 QString text = QString("=%1").arg(samps.size());

 for(Test_Sample* samp : samps)
 {
  text += QString("\n#%1\n%2\n%3\n%4\n%5").arg(samp->index_)
    .arg(samp->temperature_adj())
    .arg(samp->flow().getDouble())
    .arg(samp->time_with_flow().getDouble())
    .arg(samp->time_against_flow().getDouble());
 }
 save_file(path, text);
}
