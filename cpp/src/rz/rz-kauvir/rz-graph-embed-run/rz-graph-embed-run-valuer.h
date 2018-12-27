
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_EMBED_RUN_VALUER__H
#define RZ_GRAPH_EMBED_RUN_VALUER__H


#include <QMap>
#include <QString>

#include "rzns.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)


RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;
class RZ_Lisp_Graph_User_Package;
class RZ_Lisp_Graph_User_Class;
class RZ_Lisp_Vector;

_RZNS(GVal)


USING_RZNS(GBuild)
USING_RZNS(GVal)

void rztemptest();



RZNS_(GEmbed)


class RZ_Graph_Embed_Run_Valuer
{
 RZ_Lisp_Graph_Valuer& valuer_;

 caon_ptr<RZ_Lisp_Graph_User_Package> current_user_package_;
 caon_ptr<RZ_Lisp_Graph_User_Package> default_user_package_;

 caon_ptr<RZ_Lisp_Graph_User_Class> current_user_class_;
 caon_ptr<RZ_Lisp_Graph_User_Class> default_user_class_;

public:

 ACCESSORS__GET(RZ_Lisp_Graph_Valuer& ,valuer)

 RZ_Graph_Embed_Run_Valuer(RZ_Lisp_Graph_Valuer& valuer);


 void valuer_deferred_callback(QString qs);


};

_RZNS(GEmbed)


#endif //RZ_GRAPH_EMBED_RUN_VALUER__H
