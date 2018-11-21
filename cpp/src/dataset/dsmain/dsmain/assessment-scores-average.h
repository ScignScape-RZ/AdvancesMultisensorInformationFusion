
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef ASSESSMENT_SCORES_AVERAGE__H
#define ASSESSMENT_SCORES_AVERAGE__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>
#include <QStringList>


#include "range-dbl.h"
#include "precon.h"

KANS_(DSM)

class Assessment_Scores_Average
{
 typedef Range_Dbl<double, quint8, 1, 5> rdbl_t;

 double background_nondisruption_;
 double speech_nondistortion_;
 double overall_quality_;

 void set_background_nondisruption(precon_pr<rdbl_t> pr);
 void set_speech_nondistortion(precon_pr<rdbl_t> pr);
 void set_overall_quality(precon_pr<rdbl_t> pr);

 void set_background_nondisruption(double q, precon<rdbl_t> pre);
 void set_speech_nondistortion(double q, precon<rdbl_t> pre);
 void set_overall_quality(double q, precon<rdbl_t> pre);

public:

 Assessment_Scores_Average();

 void to_strings(QStringList& qsl);

 ACCESSORS__DECLARE__DO(double ,background_nondisruption)
 ACCESSORS__DECLARE__DO(double ,speech_nondistortion)
 ACCESSORS__DECLARE__DO(double ,overall_quality)
};


_KANS(DSM)

#endif // ASSESSMENT_SCORES_AVERAGE__H
