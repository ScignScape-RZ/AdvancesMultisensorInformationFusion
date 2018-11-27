
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
{

}

void Test_Series::parse_data(QString path)
{
 Test_Sample::read_samples_from_file(path, samples_);
}

void Test_Series::init_cells(int res)
{

}

