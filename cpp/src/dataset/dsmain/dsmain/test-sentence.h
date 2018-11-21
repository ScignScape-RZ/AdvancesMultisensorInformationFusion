
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_SENTENCE__H
#define TEST_SENTENCE__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>
#include <QString>
#include <QVector>

#include "range-int.h"
#include "precon.h"


KANS_(DSM)

class Test_Sample;

class Test_Sentence
{
 QString raw_text_;

 QVector<Test_Sample*> applicable_samples_;

public:

 Test_Sentence(QString raw_text);

 ACCESSORS(QString ,raw_text)

 QVector<Test_Sample*>* applicable_samples_ptr();

};


_KANS(DSM)

#endif // TEST_SENTENCE__H
