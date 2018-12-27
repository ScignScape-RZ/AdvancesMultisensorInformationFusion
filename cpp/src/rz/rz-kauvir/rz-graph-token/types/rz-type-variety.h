
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_TYPE_VARIETY__H
#define RZ_TYPE_VARIETY__H

#include <QMap>

#include "rzns.h"


#include "relae-graph/relae-caon-ptr.h"


#define tv_type_is(Type_exp, to_sym, tv_sym) \
 to_sym == tv_sym.get_type_object(Type_exp)

RZNS_(GBuild)

class RZ_Type_Object;

class RZ_Type_Variety
{
 QMap<int, caon_ptr<RZ_Type_Object>> type_objects_;

 QMap<QString, QString> type_object_cpp_names_;
 QMap<QString, QString> type_object_embed_names_;

public:

 caon_ptr<RZ_Type_Object> add_type_object(int key,
  QString type_name, QString cpp_name, QString embed_name, QString rz_name);
 caon_ptr<RZ_Type_Object> get_type_object(int key);

 void check_type_objects();

 QString get_cpp_type_name(QString name);
 QString get_embed_type_name(QString name);
 void check_embed_type_name(QString& sv);

};

_RZNS(GBuild)

#endif //RZ_TYPE_VARIETY__H
