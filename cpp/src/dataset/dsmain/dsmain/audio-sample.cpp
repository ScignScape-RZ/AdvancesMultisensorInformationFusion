
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "audio-sample.h"
#include "distractor.h"


USING_KANS(DSM)


Audio_Sample::Audio_Sample(QString file_name)
  :  file_name_(file_name), distractor_(Distractor::get_by_name("N_A"))
{

}

QString Audio_Sample::distractor_to_string()
{
 return distractor_->name();
}
