
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-runtime-argument.h"

USING_KANS(CMD)

KCM_Command_Runtime_Argument::KCM_Command_Runtime_Argument()
  :  raw_value_(nullptr), qmo_(nullptr),
     pqmo_(nullptr), qmt_(nullptr),
     value_classification_(Value_Classification::N_A)
{

}

QString KCM_Command_Runtime_Argument::type_name_to_qt_type_name(QString tn)
{
 static QMap<QString, QString> static_map{{
#ifdef AVOID_INT_AS_U32
  {"u32","quint32"},
#else
  {"u32","int"},
#endif
  {"u64","quint64"},
  {"u8","quint8"},
  {"str","QString"},
 }};

 return static_map.value(tn);
}

QString KCM_Command_Runtime_Argument::qob_reflection_type_name()
{
 QString result = type_name_to_qt_type_name(this->type_name());
 if(result.isEmpty())
 {
  // other things?
  result = this->type_name();
 }
 return result;
}

QString KCM_Command_Runtime_Argument::qob_reflection_modifier()
{
 return "";
}


