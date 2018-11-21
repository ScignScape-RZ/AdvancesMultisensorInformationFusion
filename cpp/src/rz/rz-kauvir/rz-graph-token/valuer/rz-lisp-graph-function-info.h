
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_FUNCTION_INFO__H
#define RZ_LISP_GRAPH_FUNCTION_INFO__H


#include <QMap>

#include "rz-lisp-graph-function-family-enum.h"


typedef int RZ_Lisp_Graph_Function_Code;

RZNS_(GBuild)

struct RZ_Lisp_Graph_Function_Info
{
 RZ_Lisp_Graph_Function_Family Core_Function_Family;
 RZ_Lisp_Graph_Function_Code Core_Function_Code;
 void pre_init();
};

_RZNS(GBuild)


#endif //RZ_LISP_GRAPH_FUNCTION_INFO__H
