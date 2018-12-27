
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "ro-info.h"

#include "textio.h"

#include "kans.h"

USING_KANS(DSM)
USING_KANS(TextIO)


RO_Info::RO_Info()
{

}

void RO_Info::parse_kai_signatures_from_file(QString class_name,
  QString path)
{
 QString lines = load_file(path);
 if(!lines.isEmpty())
 {
  kai_signatures_[class_name] = lines.split('\n', QString::SkipEmptyParts);
 }
}

