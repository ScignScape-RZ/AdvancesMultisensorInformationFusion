
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "assessment-scores-average.h"

USING_KANS(DSM)


Assessment_Scores_Average::Assessment_Scores_Average()
  :  background_nondisruption_(0), speech_nondistortion_(0),
     overall_quality_(0)
{

}

void Assessment_Scores_Average::set_background_nondisruption(precon_pr<rdbl_t> pr)
{
 background_nondisruption_ = pr.data;
}

double Assessment_Scores_Average::background_nondisruption() const
{
 return background_nondisruption_;
}

void Assessment_Scores_Average::set_speech_nondistortion(precon_pr<rdbl_t> pr)
{
 speech_nondistortion_ = pr.data;
}

double Assessment_Scores_Average::speech_nondistortion() const
{
 return speech_nondistortion_;
}


void Assessment_Scores_Average::set_overall_quality(precon_pr<rdbl_t> pr)
{
 overall_quality_ = pr.data;
}

double Assessment_Scores_Average::overall_quality() const
{
 return overall_quality_;
}

void Assessment_Scores_Average::set_background_nondisruption(double q)
{
 set_background_nondisruption(q, precon<rdbl_t>(q));
}

void Assessment_Scores_Average::to_strings(QStringList& qsl)
{
 qsl.push_back(QString::number(background_nondisruption_, 'f', 3));
 qsl.push_back(QString::number(speech_nondistortion_, 'f', 3));
 qsl.push_back(QString::number(overall_quality_, 'f', 3));
}


void Assessment_Scores_Average::set_speech_nondistortion(double q)
{
 set_speech_nondistortion(q, precon<rdbl_t>(q));
}

void Assessment_Scores_Average::set_overall_quality(double q)
{
 set_overall_quality(q, precon<rdbl_t>(q));
}


void Assessment_Scores_Average::set_background_nondisruption(double q, precon<rdbl_t> pre)
{
 if(pre.pass_fn)
  set_background_nondisruption(precon_pr<rdbl_t>{q, pre});
}

void Assessment_Scores_Average::set_speech_nondistortion(double q, precon<rdbl_t> pre)
{
 if(pre.pass_fn)
   set_speech_nondistortion(precon_pr<rdbl_t>{q, pre});
}

void Assessment_Scores_Average::set_overall_quality(double q, precon<rdbl_t> pre)
{
 if(pre.pass_fn)
   set_overall_quality(precon_pr<rdbl_t>{q, pre});
}
