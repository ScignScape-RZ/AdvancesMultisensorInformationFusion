
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>
#include <QVector>

#include "dsmain/test-sample.h"

#include "dsmain/test-series.h"

#include "kans.h"

USING_KANS(DSM)

#include "textio.h"


USING_KANS(DSM)
USING_KANS(TextIO)

int main(int argc, char* argv[])
{
 Test_Series ts;
 ts.parse_data(DATA_FOLDER "/t1.txt");

 ts.init_ranks();
 ts.save_ranks_to_file(DATA_FOLDER "/r1.txt");

 ts.init_cells(25, 25);
 ts.save_cells_to_file(25, 25, DATA_FOLDER "/c1.txt");

 ts.init_cells(110, 75);
 ts.save_cells_to_file(110, 75, DATA_FOLDER "/c2.txt");

 return 0;

}


int main1(int argc, char* argv[])
{
  QVector<Test_Sample*> ts;
  Test_Sample::read_samples_from_file(DATA_FOLDER "/t1.txt", ts);

 QMap<QPair<float, int>, int> qm;
 for(Test_Sample* samp : ts)
 {
  qm.insert({samp->flow().getDouble(),
             samp->temperature_adj()}, samp->oxy());
 }

 int max_ta = 0;
 int min_ta = -1;

 int max_oxy = 0;
 int min_oxy = -1;

 float max_fl = 0;
 float min_fl = -1;

 QString text;
 for(QPair<float, int> pr : qm.keys())
 {
  float fl = pr.first;
  int ta = pr.second;
  int oxy = qm[pr];

  if(ta > max_ta)
    max_ta = ta;
  if((min_ta == -1) || (ta < min_ta))
    min_ta = ta;

  if(oxy > max_oxy)
    max_oxy = oxy;
  if((min_oxy == -1) || (oxy < min_oxy))
    min_oxy = oxy;

  if(fl > max_fl)
    max_fl = fl;
  if((min_fl == -1) || (fl < min_fl))
    min_fl = fl;

  text += QString("%1 %2 %3\n").arg(fl)
    .arg(ta).arg(oxy);
 }

 QString min_max = QString("%1 %2 %3 %4 %5 %6\n").arg(min_fl)
   .arg(max_fl).arg(min_ta).arg(max_ta).arg(min_oxy).arg(max_oxy);
 text.prepend(min_max);

 save_file(DATA_FOLDER "/t11.txt", text);

 text = min_max.replace('.', "");

 min_fl *= 1000;
 max_fl *= 1000;

 QString text1 = QString("%1 %2 %3 %4 %5 %6\n").arg(min_fl)
   .arg((int)(max_fl - min_fl)/100)
   .arg(min_ta/100)
   .arg((max_ta - min_ta)/100)
   .arg(min_oxy)
   .arg(max_oxy - min_oxy);

 QString text2 = QString("%1 %2 %3 %4 %5 %6\n").arg(min_fl)
   .arg((int)(max_fl - min_fl)/400)
   .arg(min_ta/400)
   .arg((max_ta - min_ta)/400)
   .arg(min_oxy)
   .arg(max_oxy - min_oxy);


 for(QPair<float, int> pr : qm.keys())
 {
  int fl = (pr.first * 1000.0f) - min_fl;
  int ta = pr.second - min_ta;
  int oxy = qm[pr] - min_oxy;
  text += QString("%1 %2 %3\n").arg(fl)
    .arg(ta).arg(oxy);

  text1 += QString("%1 %2 %3\n").arg(fl/100)
    .arg(ta/100).arg(oxy);

  text2 += QString("%1 %2 %3\n").arg(fl/400)
    .arg(ta/400).arg(oxy);
 }


 save_file(DATA_FOLDER "/t12.txt", text);
 save_file(DATA_FOLDER "/t13.txt", text1);
 save_file(DATA_FOLDER "/t21.txt", text2);

 return 0;
}
