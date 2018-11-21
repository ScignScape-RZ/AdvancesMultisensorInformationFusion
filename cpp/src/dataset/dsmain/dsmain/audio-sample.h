
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef AUDIO_SAMPLE__H
#define AUDIO_SAMPLE__H

#include "kans.h"
#include "accessors.h"

#include <QtGlobal>
#include <QString>

#include "range-int.h"
#include "precon.h"


KANS_(DSM)

class Distractor;

class Audio_Sample
{
 QString file_name_;
 Distractor* distractor_;

public:

 Audio_Sample(QString file_name);

 ACCESSORS(QString ,file_name)
 ACCESSORS(Distractor* ,distractor)

 QString distractor_to_string();

};


_KANS(DSM)

#endif // AUDIO_SAMPLE__H
