
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-type-declaration.h"
#include "rz-dynamo-form.h"


#include "rzns.h"

USING_RZNS(RECore)
USING_RZNS(GVal)

RZ_Dynamo_Type_Declaration::RZ_Dynamo_Type_Declaration(RZ_Dynamo_Form& form)
  :  form_(form)
{

}

void RZ_Dynamo_Type_Declaration::write(QTextStream& qts)
{
 qts << "\n\n;;type decl \n";
 form_.write_checked_unmediated(qts);
}

