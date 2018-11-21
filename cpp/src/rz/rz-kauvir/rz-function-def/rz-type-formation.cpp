
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-type-formation.h"

#include <QRegularExpression>
#include <QStringList>

#include "rzns.h"
USING_RZNS(GVal)

RZ_Type_Formation::RZ_Type_Formation(QString str)
{
 init(str);
}

void RZ_Type_Formation::init(QString str)
{
 QStringList parts = str.split(QRegularExpression("(?=[&*])"));
 if(parts.isEmpty())
  return;
 main_component_ = parts.takeFirst();
 for(QString s : parts)
 {
  init_component(s);
 }
}

void RZ_Type_Formation::init_component(QString str)
{
 QString kstr;
 if(str.startsWith("&&"))
 {
  kstr = str.left(2);
  str.remove(0, 2);
 }
 else
 {
  kstr = str.left(1);
  str.remove(0, 1);
 }
 QStringList qsl = str.split('/');
 QString kind_str = qsl.takeLast();
 Modifier modifier = modifier_from_string(kind_str);
 QString named_modifier = qsl.join(' ');
 Type_Component_Kind kind = type_component_kind_from_string(kstr);
 components_.append({kind, modifier, named_modifier});
}

QString RZ_Type_Formation::cpp_out()
{
 QString result = main_component_;
 int count = 0;
 for(const Type_Component& tc : components_)
 {
  if(count > 0)
  {
   QString temp;
   write_type_component_cpp(tc, temp);
   if(temp.indexOf(QRegularExpression("\\A\\w")) == 0)
    result += ' ' + temp;
   else
    result += temp;
  }
  else
   write_type_component_cpp(tc, result);
  ++count;
 }
 return result;
}

void RZ_Type_Formation::write_type_component_cpp(const Type_Component& tc, QString& result)
{
 switch(tc.kind)
 {
 case Type_Component_Kind::Ptr_Indicator:
  result.append('*');
  if(tc.modifier == Modifier::Const || tc.modifier == Modifier::Const_To_Const)
   result.append(" const");
  break;
 case Type_Component_Kind::Ref_Indicator:
  result.append('&');
  break;
 case Type_Component_Kind::Move_Indicator:
  result.append("&&");
  break;

 default: break;
 }

 switch(tc.modifier)
 {
 case Modifier::Const_To_Const:
 case Modifier::To_Const:
  result.prepend("const ");
  break;

 case Modifier::Const:
  if(tc.kind == Type_Component_Kind::Ref_Indicator)
   result.prepend("const ");
  break;

 default: break;
 }
}
