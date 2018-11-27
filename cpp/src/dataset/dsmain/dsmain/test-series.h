
//           Copyright Nathaniel Christen 2018.
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

 double fmicro;
 double tmicro;
};

class Test_Series
{
 template<typename T1, typename T2>
 struct Cell_Coords {
   T1 flow_min;
   T1 flow_max;
   T1 temperature_min;
   T1 temperature_max;
   T2 oxy_min;
   T2 oxy_max;
 };

 Cell_Coords<double, int> min_max_;

 QVector<Test_Sample*> samples_;

 QMap<QPair<int, int>, QPair<Cell_Coords<int, float>,
   QVector<Cell_Info*>>> cells_;

public:

 Test_Series();

 ACCESSORS__RGET(QVector<Test_Sample*> ,samples)

 void parse_data(QString path);
 void init_cells(int fres, int tres);

 void each_sample(std::function<void(Test_Sample*)>);

 void save_cells_to_file(int fres, int tres, QString path);
 void cells_to_qmap(int fres, int tres, QMap<QPair<int, int>,
   QPair<Test_Sample*, double>>& qm);

};


_KANS(DSM)

#endif // TEST_SERIES__H
