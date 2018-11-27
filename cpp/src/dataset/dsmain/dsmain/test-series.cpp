
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-series.h"
#include "test-sample.h"

#include "textio.h"

#include <QDebug>


USING_KANS(DSM)
USING_KANS(TextIO)

Test_Series::Test_Series()
  : min_max_{-1,0,-1,0,-1,0}
{

}

void Test_Series::each_sample(std::function<void(Test_Sample*)> fn)
{
 for(Test_Sample* samp : samples_)
 {
  fn(samp);
 }
}

void Test_Series::parse_data(QString path)
{
 Test_Sample::read_samples_from_file(path, samples_);

 each_sample ([this](Test_Sample* samp)
 {
  double fl = samp->flow().getDouble();
  double ta = ((double)samp->temperature_adj())/100;
  int oxy = samp->oxy();

  if(fl > min_max_.flow_max)
    min_max_.flow_max = fl;
  if((min_max_.flow_min == -1) || (fl < min_max_.flow_min))
    min_max_.flow_min = fl;

  if(ta > min_max_.temperature_max)
    min_max_.temperature_max = ta;
  if((min_max_.temperature_min == -1) || (ta < min_max_.temperature_min))
    min_max_.temperature_min = ta;

  if(oxy > min_max_.oxy_max)
    min_max_.oxy_max = oxy;
  if((min_max_.oxy_min == -1) || (oxy < min_max_.oxy_min))
    min_max_.oxy_min = oxy;


 });

}

void Test_Series::init_cells(int fres, int tres)
{
 double frange = min_max_.flow_max - min_max_.flow_min;
 double trange = min_max_.temperature_max - min_max_.temperature_min;
 int oran = min_max_.oxy_max - min_max_.oxy_min;


 each_sample ([this, frange, trange, oran, fres, tres](Test_Sample* samp)
 {
  auto& cs = cells_[{fres, tres}];
  //cs.first =
  QVector<QPair<QPair<int, int>, float>>& qv = cs.second;

  double fl = samp->flow().getDouble();
  double ta = ((double)samp->temperature_adj())/100;
  int oxy = samp->oxy();

  int fcell = (double)fres * (fl - min_max_.flow_min) / frange;
  int tcell = (double)fres * (ta - min_max_.temperature_min) / trange;
  double oval = double(oxy - min_max_.oxy_min) / oran;

  qv.push_back({{fcell, tcell}, oval});
 });
 // sort*(x-min)/(max-min)
}

void Test_Series::cells_to_qmap(int fres, int tres, QMap<QPair<int, int>, float>& qm)
{
 QVector<QPair<QPair<int, int>, float>>& qv = cells_[{fres, tres}].second;

 for(QPair<QPair<int, int>, float>& pr : qv)
 {
  qm[pr.first] = pr.second;
 }
}


void Test_Series::save_cells_to_file(int fres, int tres, QString path)
{
 //auto& cs = cells_[{fres, tres}];
 //cs.first =


 QString text;

 QMap<QPair<int, int>, float> qm;

 cells_to_qmap(fres, tres, qm);

 for(int i = 0; i < fres; ++i)
 {
  for(int j = 0; j < tres; ++j)
  {
   text += QString("%1 ").arg(qm.value({i, j}, -1)).leftJustified(12);
  }
  text += '\n';
 }

 save_file(path, text);
}
