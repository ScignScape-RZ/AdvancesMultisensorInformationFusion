
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-series.h"
#include "test-sample.h"
#include "audio-sample.h"
#include "assessment-scores-average.h"
#include "test-sentence.h"
#include "distractor.h"

#include "textio.h"

#include <QDebug>

USING_KANS(DSM)
USING_KANS(TextIO)

Test_Series::Test_Series()
{

}



void Test_Series::parse_data(QString path)
{
 QVector<Test_Sentence*> _sentences;

 QMap<Test_Sentence*, QList<QPair<int, Test_Sample*>>> peer_map;

 QString text = load_file(path);
 if(text.endsWith('\n'))
   text.chop(1);

 QStringList lines = text.split('\n');

 int i = 0;
 Test_Sample* ts;

 for(QString qs : lines)
 {
  if(i == 0)
  {
   ts = new Test_Sample();
   Audio_Sample* sa = new Audio_Sample(qs);
   ts->set_audio_sample(sa);
   samples_.push_back(ts);
   ++i;
  }
  else if(i == 1)
  {
   Assessment_Scores_Average* avg = new Assessment_Scores_Average;
   QStringList qsl = qs.split('-');
   avg->set_background_nondisruption(qsl[0].toDouble());
   avg->set_speech_nondistortion(qsl[1].toDouble());
   avg->set_overall_quality(qsl[2].toDouble());
   ts->set_assessment_scores(avg);

   Assessment_Scores_Average* lavg = new Assessment_Scores_Average;
   lavg->set_background_nondisruption(qsl[3].toDouble());
   lavg->set_speech_nondistortion(qsl[4].toDouble());
   lavg->set_overall_quality(qsl[5].toDouble());
   ts->set_assessment_scores_with_load(lavg);

   ++i;
  }
  else if(i == 2)
  {
   if(qs.startsWith('#'))
   {
    qs = qs.mid(1);
    int j = qs.toInt() - 1;
    Test_Sentence* sent = _sentences[j];
    ts->set_sentence(sent);
    QPair<int, Test_Sample*>& pr = peer_map[sent].back();
    int f = pr.first + 1;
    peer_map[sent].push_back({f, ts});
   }
   else if(qs.startsWith("+:"))
   {
    qs = qs.mid(2);
    Test_Sentence* sent = new Test_Sentence(qs);
    ts->set_sentence(sent);
    _sentences.push_back(sent);
    QPair<int, Test_Sample*> pr = {0, ts};
    peer_map[sent].push_back(pr);
   }
   ++i;
  }
  else if(i == 3)
  {
   i = 0;
   Distractor* dr = Distractor::get_by_name(qs);
   ts->audio_sample()->set_distractor(dr);
  }
 }
 int sz = _sentences.size();
 sentences_.resize(sz);



 for(int i = 0; i < sz; ++i)
 {
  Test_Sentence* ts = _sentences.value(i);

  QVector<Test_Sample*> peers;
  for(QPair<int, Test_Sample*> pr : peer_map[ts] )
  {
   pr.second->set_index_in_peer_set(pr.first);
   peers.push_back(pr.second);
  }

  QVector<Test_Sample*>* p = ts->applicable_samples_ptr();
  int psz = peers.size();
  p->resize(psz);
  for(int h = 0; h < psz; ++h)
  {
   p->replace(h, peers[h]);
  }


  sentences_.replace(i, ts);
 }



}





void Test_Series::parse_data_regen(QString path)
{
 QMap<QString, int> sentences;
 QString newt;
 int scount = 0;

 QString text = load_file(path);
 if(text.endsWith('\n'))
   text.chop(1);
 QStringList lines = text.split('\n');
 int c = 0;
 int i = 0;
 Test_Sample* ts;
 for(QString qs : lines)
 {
  if(i == 0)
  {
   newt += qs + '\n';
   ts = new Test_Sample();
   Audio_Sample* sa = new Audio_Sample(qs);
   ts->set_audio_sample(sa);
   samples_.push_back(ts);
   ++i;
  }
  else if(i == 1)
  {
   newt += qs + '\n';
   Assessment_Scores_Average* avg = new Assessment_Scores_Average;
   QStringList qsl = qs.split('-');
   avg->set_background_nondisruption(qsl[0].toDouble());
   avg->set_speech_nondistortion(qsl[1].toDouble());
   avg->set_overall_quality(qsl[2].toDouble());
   ts->set_assessment_scores(avg);
   ++i;
  }
  else if(i == 2)
  {
   if(sentences.contains(qs))
   {
    int i = sentences.value(qs);
    newt += QString("#%1\n").arg(i);
   }
   else
   {
    sentences[qs] = ++scount;
    newt += QString("+:%1\n").arg(qs);
   }
   i = 0;
  }
 }
 save_file(path + ".rev", newt);
}


