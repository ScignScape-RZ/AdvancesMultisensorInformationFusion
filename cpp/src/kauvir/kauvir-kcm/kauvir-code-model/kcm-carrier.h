
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CARRIER__H
#define KCM_CARRIER__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>

KANS_CLASS_DECLARE(CMD ,KCM_Runtime_Scope)

USING_KANS(CMD)

KANS_(KCM)


class KCM_Type_Object;
class Kauvir_Code_Model;
class KCM_Report_Syntax;


class KCM_Carrier
{

public:

 flags_(2)

  bool non_opaque:1;
  bool read_disallowed:1;
  bool read_mandated:1;
  bool write_disallowed:1;
  bool write_mandated:1;
  bool self_bound:1;
  bool literal_string:1;
  bool value_string:1;
  bool default_string:1;
  bool src_val:1;

 _flags


 enum Effect_Protocols {
  Unrestricted, Const_Literal, Run_Chief,
  Read_Disallowed,
  Read_Mandated, Write_Disallowed,
  Write_Mandated
 };

private:

 const KCM_Type_Object* type_object_;
 const KCM_Type_Object* cast_type_object_;
 QString symbol_;

 KCM_Runtime_Scope* declaration_scope_;

 QString src_value_;

public:

 KCM_Carrier(const KCM_Type_Object* type_object = nullptr,
   Effect_Protocols ep = Effect_Protocols::Unrestricted,
   QString symbol = QString(),
   const KCM_Type_Object* cast_type_object = nullptr, KCM_Runtime_Scope* scope = nullptr);

 KCM_Carrier(const KCM_Type_Object* type_object,
   Effect_Protocols ep,
   QString symbol, KCM_Runtime_Scope* scope);


 KCM_Carrier(const KCM_Type_Object* type_object, Flags_type flags,
   QString symbol, const KCM_Type_Object* cast_type_object = nullptr);

 ACCESSORS(const KCM_Type_Object* ,type_object)
 ACCESSORS(QString ,symbol)
 ACCESSORS(KCM_Runtime_Scope* ,declaration_scope)

 QString get_src_value() const;

 void set_value_string(QString vs)
 {
  set_symbol(vs);
  flags.value_string = true;
 }

 QString* symbol_as_pointer();

 friend bool operator <(const KCM_Carrier& lhs, const KCM_Carrier& rhs)
 {
  return lhs.type_object() < rhs.type_object();
 }

 KCM_Carrier branch_copy() const;

 void report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs) const;

 QString token_report(Kauvir_Code_Model& kcm) const;

};


_KANS(KCM)


#endif //KCM_CARRIER__H
