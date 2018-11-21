
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_FUNCTION_DEF_SYNTAX__H
#define RZ_FUNCTION_DEF_SYNTAX__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>

#include "rzns.h"

RZNS_(GVal)

class RZ_Function_Def_Syntax
{
public:
 flags_(1)
  bool type_before_symbol:1;
  bool hide_type:1;
  bool hide_symbol:1;
  bool type_required:1;
 _flags

private:

 QString symbol_separator_;
 QString type_from_symbol_separator_;
 QString argument_default_type_;

 QMap<QString, QString> symbol_renames_;

public:

 RZ_Function_Def_Syntax();

 ACCESSORS(QString ,symbol_separator)
 ACCESSORS(QString ,type_from_symbol_separator)
 ACCESSORS(QString ,argument_default_type)

 void check_symbol_rename(QString& sym) const;


};

_RZNS(GVal)

#endif //RZ_FUNCTION_DEF_SYNTAX__H
