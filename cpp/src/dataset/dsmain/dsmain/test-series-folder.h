
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_SERIES_FOLDER__H
#define TEST_SERIES_FOLDER__H

#include "kans.h"
#include "accessors.h"

#include <QVector>
#include <QString>

#include "range-int.h"
#include "precon.h"


KANS_(DSM)

class Test_Sample;
class Test_Series;

class Test_Series_Folder
{
 QString ring_path_;

public:

 Test_Series_Folder(QString ring_path);

 void read_files(Test_Series& ts);

};


_KANS(DSM)

#endif // TEST_SERIES_FOLDER__H
