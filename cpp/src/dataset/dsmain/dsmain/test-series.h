
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_SERIES__H
#define TEST_SERIES__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>
#include <QMap>

KANS_(DSM)

class Test_Sample;



class Test_Series
{
 struct Cell_Coords {
   int flow_min;
   int flow_max;
   int temperature_min;
   int temperature_max;
   float oxy_min;
   float oxy_max;
 };

 QVector<Test_Sample*> samples_;

 QMap<int, QPair<Cell_Coords,
   QVector<QPair<QPair<int, int>, float>>>> cells_;

public:

 Test_Series();

 ACCESSORS__RGET(QVector<Test_Sample*> ,samples)

 void parse_data(QString path);
 void init_cells(int res);


};


_KANS(DSM)

#endif // TEST_SERIES__H
