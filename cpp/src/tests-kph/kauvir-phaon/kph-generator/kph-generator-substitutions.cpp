
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator-substitutions.h"

#include "kauvir-code-model/kcm-carrier.h"
#include "kauvir-code-model/kcm-type-object.h"


USING_KANS(Phaon)


KPH_Generator_Substitutions::KPH_Generator_Substitutions
  (QString text)
  :  text_(text)
{
 QStringList qsl = text_.simplified().split(' ');
 int i = 0;
 for(QString qs : qsl)
 {
  lambdas_[i] = qs;
  ++i;
 }
}

QString KPH_Generator_Substitutions::get_src_value(QString channel_name,
  const KCM_Carrier& car, int index)
{
 QString result = car.get_src_value();
 if(result.isEmpty())
 {
  if(channel_name == "lambda")
    result = get_lambda(index);
  else
  {
   result = car.type_object()->get_name_string();
   if(channel_name == "sigma")
      result = get_sigma(result);
  }
 }
 return result;
}

QString KPH_Generator_Substitutions::get_sigma(QString type_name)
{
 return type_name.prepend("#*");
}

QString KPH_Generator_Substitutions::get_lambda(int i)
{
 return lambdas_.value(i);
}

