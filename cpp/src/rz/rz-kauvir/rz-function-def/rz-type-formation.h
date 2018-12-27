
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_TYPE_FORMATION__H
#define RZ_TYPE_FORMATION__H

#include "accessors.h"

#include "flags.h"

#include <functional>

#include <QString>
#include <QVector>
#include <QMap>

#include "rzns.h"

RZNS_(GVal)

class RZ_Type_Formation
{
 enum class Type_Component_Kind
 { N_A, Main_Component, Ref_Indicator, Ptr_Indicator,
    Move_Indicator, Cursor_Indicator };

 static Type_Component_Kind type_component_kind_from_string(QString str)
 {
  static QMap<QString, Type_Component_Kind> static_map {{
   {"*", Type_Component_Kind::Ptr_Indicator}, {"&", Type_Component_Kind::Ref_Indicator},
   {"&&", Type_Component_Kind::Move_Indicator}, {"@", Type_Component_Kind::Cursor_Indicator}
   }};
  return static_map.value(str, Type_Component_Kind::N_A);
 }

 enum class Modifier
 { N_A, Const, To_Const, Const_To_Const, Mutable };

 static Modifier modifier_from_string(QString str)
 {
  static QMap<QString, Modifier> static_map {{
   {"tc", Modifier::To_Const}, {"cc", Modifier::Const_To_Const},
   {"c", Modifier::Const}, {"m", Modifier::Mutable}
   }};
  return static_map.value(str, Modifier::N_A);
 }

 struct Type_Component
 {
  Type_Component_Kind kind;
  Modifier modifier;
  QString named_modifier;
 };

 QVector<Type_Component> components_;
 QString main_component_;

 void init(QString str);
 void init_component(QString str);

public:

 RZ_Type_Formation(QString str);

 QString cpp_out();
 void write_type_component_cpp(const Type_Component& tc, QString& result);



};

_RZNS(GVal)

#endif //RZ_TYPE_FORMATION__H
