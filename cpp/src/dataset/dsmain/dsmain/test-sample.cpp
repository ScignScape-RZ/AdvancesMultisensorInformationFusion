
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-sample.h"
#include "test-sentence.h"
#include "audio-sample.h"


USING_KANS(DSM)


Test_Sample::Test_Sample()
  :  audio_sample_(nullptr), assessment_scores_(nullptr),
     sentence_(nullptr),
     index_in_peer_set_(0)
{

}

QVector<Test_Sample*>* Test_Sample::get_peer_samples()
{
 if(sentence_)
 {
  return sentence_->applicable_samples_ptr();
 }
 return nullptr;
}

QString Test_Sample::distractor_to_string()
{
 if(audio_sample_)
   return audio_sample_->distractor_to_string();
 return QString();
}
