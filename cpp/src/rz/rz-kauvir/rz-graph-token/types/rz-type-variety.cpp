
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-type-variety.h"

#include "rz-type-object.h"

#include <QDebug>

USING_RZNS(GBuild)

caon_ptr<RZ_Type_Object> RZ_Type_Variety::add_type_object(int key, QString type_name,
 QString cpp_name, QString embed_name, QString rz_name)
{
 caon_ptr<RZ_Type_Object> result = new RZ_Type_Object(type_name, cpp_name, key);
 type_objects_[key] = result;
 type_object_cpp_names_[rz_name] = cpp_name;
 type_object_embed_names_[rz_name] = embed_name;
 return result;
}

caon_ptr<RZ_Type_Object> RZ_Type_Variety::get_type_object(int key)
{
 return type_objects_.value(key, nullptr);
}

QString RZ_Type_Variety::get_cpp_type_name(QString name)
{
 return type_object_cpp_names_.value(name);
}

QString RZ_Type_Variety::get_embed_type_name(QString name)
{
 return type_object_embed_names_.value(name);
}

void RZ_Type_Variety::check_embed_type_name(QString& sv)
{
 if(type_object_embed_names_.contains(sv))
 {
  sv = type_object_embed_names_.value(sv);
 }
}

void RZ_Type_Variety::check_type_objects()
{
 QMapIterator<int, caon_ptr<RZ_Type_Object>> it(type_objects_);
 while(it.hasNext())
 {
  it.next();
  int code = it.key();
  const RZ_Type_Object& rzt = *it.value();
  QString s = rzt.name();
  qDebug() << s;
 }


}
