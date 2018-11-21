
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-report-syntax.h"

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)


KCM_Report_Syntax::KCM_Report_Syntax()
  :  Flags(0)
{
}

QString KCM_Report_Syntax::get_channel_kind_code(KCM_Channel::Kinds kind)
{
 return channel_kind_codes_.value(kind);
}

