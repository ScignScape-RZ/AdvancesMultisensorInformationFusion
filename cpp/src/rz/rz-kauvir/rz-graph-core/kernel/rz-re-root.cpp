
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-re-root.h"

#include "kernel/document/rz-re-document.h"

#include "rzns.h"

USING_RZNS(RECore)


RE_Root::RE_Root(RE_Document* document)
  : document_(document)
{

}

QString RE_Root::document_path()
{
 return document_->local_path();
}
