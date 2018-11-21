
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-sentence.h"

USING_KANS(DSM)

Test_Sentence::Test_Sentence(QString raw_text)
  :  raw_text_(raw_text)
{

}

QVector<Test_Sample*>* Test_Sentence::applicable_samples_ptr()
{
 return &applicable_samples_;
}

