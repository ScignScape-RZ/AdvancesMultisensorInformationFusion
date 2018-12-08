
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-series.h"
#include "test-sample.h"

#include "textio.h"

#include <QDebug>

#include <QDataStream>


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

void Test_Series::check_init_cells(int fres, int tres)
{
 if(!cells_.contains({fres, tres}))
 {
  init_cells(fres, tres);
 }
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
  ci->oxy_adj = oxy - min_max_.oxy_min;
  ci->oxy = oval;
  ci->sample = samp;

  qv.push_back(ci);

 });
}

void Test_Series::cells_to_qmap(int fres, int tres,
  QMap<QPair<int, int>, QList<QPair<Cell_Info*, double>>>& qm)
{
 QVector<Cell_Info*>& qv = cells_[{fres, tres}].second;

 for(Cell_Info* ci : qv)
 {
  switch (ci->oxy_adj)
  {
  case 0:
   qm[{ci->fmacro, ci->tmacro}].push_back({ci, 0.5f});
   break;

  case 7:
   qm[{ci->fmacro, ci->tmacro}].push_back({ci, 0.7f});
   break;

  case 10:
   qm[{ci->fmacro, ci->tmacro}].push_back({ci, 0.8f});
   break;

  case 13:
   qm[{ci->fmacro, ci->tmacro}].push_back({ci, 1.0f});
   break;

  default:
   qm[{ci->fmacro, ci->tmacro}].push_back({ci, 0.75f});

   qDebug() << "Wrong oxy adj: " << ci->oxy_adj;
   break;
  }
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

void Test_Series::init_ranks()
{
 if(flow_ranks_.isEmpty())
 {
  auto copy = samples_;
  qSort(copy.begin(), copy.end(),
    [](const Test_Sample* const lhs, const Test_Sample* const rhs)
  {
   if(lhs->flow() < rhs->flow())
     return true;
   if(lhs->flow() > rhs->flow())
     return false;
   if(lhs->oxy() < rhs->oxy())
     return true;
   if(lhs->oxy() > rhs->oxy())
     return false;
   if(lhs->temperature_adj() < rhs->temperature_adj())
     return true;
   if(lhs->temperature_adj() > rhs->temperature_adj())
     return false;
   return lhs->index() < rhs->index();
  });
  flow_ranks_.resize(copy.size());
  inv_flow_ranks_.resize(copy.size());
  for(int i = 0; i < copy.size(); ++i)
  {
   inv_flow_ranks_[i] = copy[i]->index();
   flow_ranks_[copy[i]->index()-1] = i;
  }
 }

 if(temperature_ranks_.isEmpty())
 {
  auto copy = samples_;
  qSort(copy.begin(), copy.end(),
    [](const Test_Sample* const lhs, const Test_Sample* const rhs)
  {
   if(lhs->temperature_adj() < rhs->temperature_adj())
     return true;
   if(lhs->temperature_adj() > rhs->temperature_adj())
     return false;
   if(lhs->flow() < rhs->flow())
     return true;
   if(lhs->flow() > rhs->flow())
     return false;
   if(lhs->oxy() < rhs->oxy())
     return true;
   if(lhs->oxy() > rhs->oxy())
     return false;
   return lhs->index() < rhs->index();
  });
  temperature_ranks_.resize(copy.size());
  inv_temperature_ranks_.resize(copy.size());
  for(int i = 0; i < copy.size(); ++i)
  {
   inv_temperature_ranks_[i] = copy[i]->index();
   temperature_ranks_[copy[i]->index()-1] = i;
  }
 }

 if(oxy_ranks_.isEmpty())
 {
  auto copy = samples_;
  qSort(copy.begin(), copy.end(),
    [](const Test_Sample* const lhs, const Test_Sample* const rhs)
  {
   if(lhs->oxy() < rhs->oxy())
     return true;
   if(lhs->oxy() > rhs->oxy())
     return false;
   if(lhs->flow() < rhs->flow())
     return true;
   if(lhs->flow() > rhs->flow())
     return false;
   if(lhs->temperature_adj() < rhs->temperature_adj())
     return true;
   if(lhs->temperature_adj() > rhs->temperature_adj())
     return false;
   return lhs->index() < rhs->index();
  });
  oxy_ranks_.resize(copy.size());
  inv_oxy_ranks_.resize(copy.size());
  for(int i = 0; i < copy.size(); ++i)
  {
   inv_oxy_ranks_[i] = copy[i]->index();
   oxy_ranks_[copy[i]->index()-1] = i;
  }
 }
}

void Test_Series::save_ranks_to_file(QString path)
{
 QByteArray qba;
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << flow_ranks_;
 qds << temperature_ranks_;
 qds << oxy_ranks_;
 save_file(path, qba);
}

void Test_Series::read_ranks_from_file(QString path)
{

}

void Test_Series::samples_by_flow_rank(QVector<Test_Sample*>& result)
{
 result.reserve(samples_.size());
 for(quint16 i : inv_flow_ranks_)
 {
  result.push_back(samples_.at(i - 1));
 }
}

void Test_Series::samples_by_temperature_rank(QVector<Test_Sample*>& result)
{
 result.reserve(samples_.size());
 for(quint16 i : inv_temperature_ranks_)
 {
  result.push_back(samples_.at(i - 1));
 }
}

void Test_Series::samples_by_oxy_rank(QVector<Test_Sample*>& result)
{
 result.reserve(samples_.size());
 for(quint16 i : inv_oxy_ranks_)
 {
  result.push_back(samples_.at(i - 1));
 }
}

qint16 Test_Series::get_flow_rank(Test_Sample& samp)
{
 return flow_ranks_.value(samp.index() - 1, -1) + 1;
}

qint16 Test_Series::get_temperature_rank(Test_Sample& samp)
{
 return temperature_ranks_.value(samp.index() - 1, -1) + 1;
}

qint16 Test_Series::get_oxy_rank(Test_Sample& samp)
{
 return oxy_ranks_.value(samp.index() - 1, -1) + 1;
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
