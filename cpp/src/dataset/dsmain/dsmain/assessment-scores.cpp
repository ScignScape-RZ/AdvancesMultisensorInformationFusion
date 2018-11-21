
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "assessment-scores.h"

USING_KANS(DSM)


Assessment_Scores::Assessment_Scores()
  :  raw_(0)
{

}

void Assessment_Scores::set_background_nondisruption(precon_pr<rint_t> pr)
{
 int x = background_nondisruption();
 int q = pr.data;
 x *= 10;
 raw_ -= x;
 q *= 10;
 raw_ += q;
}

quint8 Assessment_Scores::background_nondisruption() const
{
 int r = raw_ % 100;
 r /= 10;
 return r;
}

void Assessment_Scores::set_speech_nondistortion(precon_pr<rint_t> pr)
{
 int x = speech_nondistortion();
 int q = pr.data;
 x *= 100;
 raw_ -= x;
 q *= 100;
 raw_ += q;
}

quint8 Assessment_Scores::speech_nondistortion() const
{
 int r = raw_ % 1000;
 r /= 100;
 return r;
}


void Assessment_Scores::set_overall_quality(precon_pr<rint_t> pr)
{
 int x = overall_quality();
 raw_ -= x;
 raw_ += pr.data;
}

quint8 Assessment_Scores::overall_quality() const
{
 return raw_ % 10;
}

void Assessment_Scores::set_background_nondisruption(quint8 q)
{
 set_background_nondisruption(q, precon<rint_t>(q));
}

void Assessment_Scores::set_speech_nondistortion(quint8 q)
{
 set_speech_nondistortion(q, precon<rint_t>(q));
}

void Assessment_Scores::set_overall_quality(quint8 q)
{
 set_overall_quality(q, precon<rint_t>(q));
}


void Assessment_Scores::set_background_nondisruption(quint8 q, precon<rint_t> pre)
{
 if(pre.pass_fn)
  set_background_nondisruption(precon_pr<rint_t>{q, pre});
}

void Assessment_Scores::set_speech_nondistortion(quint8 q, precon<rint_t> pre)
{
 if(pre.pass_fn)
   set_speech_nondistortion(precon_pr<rint_t>{q, pre});
}

void Assessment_Scores::set_overall_quality(quint8 q, precon<rint_t> pre)
{
 if(pre.pass_fn)
   set_overall_quality(precon_pr<rint_t>{q, pre});
}
