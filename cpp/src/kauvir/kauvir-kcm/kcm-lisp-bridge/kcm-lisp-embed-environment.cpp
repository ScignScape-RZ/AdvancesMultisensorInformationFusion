
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-lisp-embed-environment.h"

#include "object.hpp"

USING_KANS(KCL)

KCM_Lisp_Embed_Environment::KCM_Lisp_Embed_Environment(int argc, char *argv[])
{
 cl_boot(argc, argv);

 process_name_ = QString::fromLatin1(argv[0]);

 for(int i = 1; i < argc; ++i)
 {
  if(i > 1)
  {
   process_arguments_.append("; ");
  }
  process_arguments_.append(QString::fromLatin1(argv[i]));
 }

}
