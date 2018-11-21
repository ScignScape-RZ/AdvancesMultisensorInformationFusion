
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_SAMPLE__H
#define TEST_SAMPLE__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>
#include <QString>

#include "range-int.h"
#include "precon.h"


KANS_(DSM)

class Audio_Sample;
class Assessment_Scores_Average;
class Test_Sentence;
class Distractor;


class Test_Sample
{
 Audio_Sample* audio_sample_;
 Assessment_Scores_Average* assessment_scores_;
 Assessment_Scores_Average* assessment_scores_with_load_;
 Test_Sentence* sentence_;

 int index_in_peer_set_;

public:

 Test_Sample();

 ACCESSORS(Audio_Sample* ,audio_sample)
 ACCESSORS(Assessment_Scores_Average* ,assessment_scores)
 ACCESSORS(Assessment_Scores_Average* ,assessment_scores_with_load)
 ACCESSORS(Test_Sentence* ,sentence)
 ACCESSORS(int ,index_in_peer_set)

 QVector<Test_Sample*>* get_peer_samples();

 QString distractor_to_string();

};


_KANS(DSM)

#endif // TEST_SAMPLE__H
