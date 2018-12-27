
#include "rz-lisp-document.h"


#include "rz-graph-token/token/rz-lisp-token.h"


//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rzns.h"
USING_RZNS(GBuild)


RZ_Lisp_Document::RZ_Lisp_Document(RE_Document& re_document)
 : re_document_(re_document)
{

}

