
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

#include "range-int.h"
#include "precon.h"


KANS_(DSM)

class Test_Sample;
class Assessment_Scores;

class Test_Sentence;


class Test_Series
{
 QVector<Test_Sample*> samples_;
 QVector<Test_Sentence*> sentences_;


public:

 Test_Series();

 ACCESSORS__RGET(QVector<Test_Sample*> ,samples)

 void parse_data_regen(QString path);
 void parse_data(QString path);





};


_KANS(DSM)

#endif // TEST_SERIES__H
