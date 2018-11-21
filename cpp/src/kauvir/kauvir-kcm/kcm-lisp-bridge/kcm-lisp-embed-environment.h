
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LISP_EMBED_ENVIRONMENT__H
#define KCM_LISP_EMBED_ENVIRONMENT__H



#include <QObject>

#include "kauvir-code-model/kauvir-code-model.h"

USING_KANS(KCM)

KANS_(KCL)

class KCM_Lisp_Embed_Environment
{

 QString quicklisp_location_;
 QString process_name_;
 QString process_arguments_;


public:

 KCM_Lisp_Embed_Environment(int argc, char *argv[]);

 ACCESSORS(QString ,quicklisp_location)
 ACCESSORS(QString ,process_name)
 ACCESSORS(QString ,process_arguments)



};

_KANS(KCL)

#endif //KCM_LISP_EMBED_ENVIRONMENT__H
