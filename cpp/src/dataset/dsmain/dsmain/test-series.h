
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_SERIES__H
#define TEST_SERIES__H

#include "kans.h"
#include "accessors.h"

#include <functional>

#include <QVector>
#include <QString>
#include <QMap>

KANS_(DSM)

class Test_Sample;

struct Cell_Info
{
 Test_Sample* sample;

 int fmacro;
 int tmacro;

 double oxy;
 int oxy_adj;

 double fmicro;
 double tmicro;
};

class Test_Series
{
 template<typename T1, typename T2, typename T3>
 struct Cell_Coords {
   T1 flow_min;
   T1 flow_max;
   T1 temperature_min;
   T1 temperature_max;
   T2 oxy_min;
   T2 oxy_max;
   T3 flow_span;
   T3 temperature_span;
 };

 Cell_Coords<double, int, double> min_max_;

 QVector<Test_Sample*> samples_;

 QMap<QPair<int, int>, QPair<Cell_Coords<int, float, double>,
   QVector<Cell_Info*>>> cells_;

 QVector<quint16> flow_ranks_;
 QVector<quint16> temperature_ranks_;
 QVector<quint16> oxy_ranks_;

 QVector<quint16> inv_flow_ranks_;
 QVector<quint16> inv_temperature_ranks_;
 QVector<quint16> inv_oxy_ranks_;

public:

 Test_Series();

 ACCESSORS__RGET(QVector<Test_Sample*> ,samples)

 void samples_by_flow_rank(QVector<Test_Sample*>& result);
 void samples_by_oxy_rank(QVector<Test_Sample*>& result);
 void samples_by_temperature_rank(QVector<Test_Sample*>& result);


 void parse_data(QString path);
 void init_cells(int fres, int tres);

 void check_init_cells(int fres, int tres);

 void init_ranks();

 void each_sample(std::function<void(Test_Sample*)>);

 void save_cells_to_file(int fres, int tres, QString path);

 void save_ranks_to_file(QString path);
 void read_ranks_from_file(QString path);

 void cells_to_qmap(int fres, int tres, QMap<QPair<int, int>,
   QList<QPair<Cell_Info*, double>>>& qm);

 void get_cell_coords(int fres, int tres,
   double& flow_min, double& flow_span,
   double& temperature_min, double& temperature_span);

 double get_flow_as_percentage(Test_Sample& samp);
 double get_temperature_as_percentage(Test_Sample& samp);
 double get_oxy_as_percentage(Test_Sample& samp);

 qint16 get_flow_rank(Test_Sample& samp);
 qint16 get_temperature_rank(Test_Sample& samp);
 qint16 get_oxy_rank(Test_Sample& samp);

};


_KANS(DSM)

#endif // TEST_SERIES__H
