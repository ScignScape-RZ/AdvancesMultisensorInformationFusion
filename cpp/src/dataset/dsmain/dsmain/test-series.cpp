
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
  : min_max_{-1,0,-1,0,-1,0,0,0}
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

 min_max_.flow_span = min_max_.flow_max - min_max_.flow_min;
 min_max_.temperature_span = min_max_.temperature_max - min_max_.temperature_min;
}

void Test_Series::init_cells(int fres, int tres)
{
 double frange = min_max_.flow_span;
 double trange = min_max_.temperature_span;
 int oran = min_max_.oxy_max - min_max_.oxy_min;

 cells_[{fres, tres}].first = {0, fres, 0, tres, 0, 1, frange/fres, trange/tres};

 each_sample ([this, frange, trange, oran, fres, tres](Test_Sample* samp)
 {
  auto& cs = cells_[{fres, tres}];
  //cs.first =
  QVector<Cell_Info*>& qv = cs.second;

  double fl = samp->flow().getDouble();
  double ta = ((double)samp->temperature_adj())/100;
  int oxy = samp->oxy();

  double fmacmic = (double)fres * (fl - min_max_.flow_min) / frange;
  double tmacmic = (double)fres * (ta - min_max_.temperature_min) / trange;
  double oval = double(oxy - min_max_.oxy_min) / oran;

  Cell_Info* ci = new Cell_Info;
  ci->fmacro = (int) fmacmic;
  ci->fmicro = fmacmic - ci->fmacro;
  ci->tmacro = (int) tmacmic;
  ci->tmicro = tmacmic - ci->tmacro;
  ci->oxy = oval;
  ci->sample = samp;
  //ci->fmicro = (frange/fres) *;

  qv.push_back(ci);

 });
 // sort*(x-min)/(max-min)
}

void Test_Series::cells_to_qmap(int fres, int tres,
  QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>>& qm)
{
 QVector<Cell_Info*>& qv = cells_[{fres, tres}].second;

 for(Cell_Info* ci : qv)
 {
  qm[{ci->fmacro, ci->tmacro}].push_back({ci, ci->oxy});
 }
}

double Test_Series::get_flow_as_percentage(Test_Sample& samp)
{
 double result = samp.flow().getDouble();
 result -= min_max_.flow_min;
 result /= min_max_.flow_span;
 return result;
}

double Test_Series::get_temperature_as_percentage(Test_Sample& samp)
{
 double result = (double) samp.temperature_adj();
 result -= min_max_.temperature_min;
 result /= min_max_.temperature_span;
 return result;
}

double Test_Series::get_oxy_as_percentage(Test_Sample& samp)
{
 double result = samp.oxy();
 result -= min_max_.oxy_min;
 result /= min_max_.oxy_max - min_max_.oxy_min;
 return result;
}


void Test_Series::get_cell_coords(int fres, int tres,
  double& flow_min, double& flow_span,
  double& temperature_min, double& temperature_span)
{
 Cell_Coords<int, float, double>& cc = cells_[{fres, tres}].first;
 flow_min = min_max_.flow_min;
 flow_span = cc.flow_span;
 temperature_min = min_max_.temperature_min;
 temperature_span = cc.temperature_span;
}

void Test_Series::save_cells_to_file(int fres, int tres, QString path)
{
 //auto& cs = cells_[{fres, tres}];
 //cs.first =


 QString text;

 QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>> qm;

 cells_to_qmap(fres, tres, qm);

 for(int i = 0; i < fres; ++i)
 {
  for(int j = 0; j < tres; ++j)
  {
   text += QString("%1 ").arg(qm.value({i, j},
     {{nullptr, -1}}).first().second).leftJustified(12);
  }
  text += '\n';
 }

 save_file(path, text);
}
