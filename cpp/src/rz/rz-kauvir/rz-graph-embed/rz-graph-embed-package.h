
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_EMBED_PACKAGE__H
#define RZ_GRAPH_EMBED_PACKAGE__H

#include <QMap>
#include <QString>

#include "rzns.h"

#include "accessors.h"

RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(GEmbed)



class RZ_Graph_Embed_Package
{
 QString name_;


public:

 ACCESSORS(QString ,name)

 RZ_Graph_Embed_Package(QString name);


};

_RZNS(GEmbed)


#endif //RZ_GRAPH_EMBED_PACKAGE__H
