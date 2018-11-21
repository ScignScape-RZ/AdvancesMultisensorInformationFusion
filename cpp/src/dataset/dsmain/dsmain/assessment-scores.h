
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ASSESSMENT_SCORES__H
#define ASSESSMENT_SCORES__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>

#include "range-int.h"
#include "precon.h"

KANS_(DSM)

class Assessment_Scores
{
 typedef Range_Int<quint16, 1, 5> rint_t;

 quint16 raw_;

 void set_background_nondisruption(precon_pr<rint_t> pr);
 void set_speech_nondistortion(precon_pr<rint_t> pr);
 void set_overall_quality(precon_pr<rint_t> pr);

 void set_background_nondisruption(quint8 q, precon<rint_t> pre);
 void set_speech_nondistortion(quint8 q, precon<rint_t> pre);
 void set_overall_quality(quint8 q, precon<rint_t> pre);

public:

 Assessment_Scores();

 ACCESSORS__DECLARE__DO(quint8 ,background_nondisruption)
 ACCESSORS__DECLARE__DO(quint8 ,speech_nondistortion)
 ACCESSORS__DECLARE__DO(quint8 ,overall_quality)
};


_KANS(DSM)

#endif // ASSESSMENT_SCORES__H
