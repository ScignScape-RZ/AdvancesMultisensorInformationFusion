
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_TYPE_OBJECT__H
#define KCM_TYPE_OBJECT__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)


class KCM_Channel_Group;
class Kauvir_Code_Model;
class KCM_Report_Syntax;

class KCM_Type_Object
{
public:

 enum class Modifiers {

  N_A, Pointer, Reference, Const,
  Const_Pointer_To_Const, Const_Pointer,
  Pointer_To_Const, Const_Reference,
  Reference_To_Pointer

 };

private:

 const Kauvir_Type_Object* kauvir_type_object_;
 KCM_Channel_Group* channel_group_;

 int array_length_;
 Modifiers modifier_;

 int qmetatype_ptr_code_;

 int byte_code_;

public:

 KCM_Type_Object(KCM_Channel_Group* channel_group);
 KCM_Type_Object(const Kauvir_Type_Object* kauvir_type_object, int byte_code = 0);
 KCM_Type_Object();


 ACCESSORS(KCM_Channel_Group* ,channel_group)
 ACCESSORS(const Kauvir_Type_Object* ,kauvir_type_object)
 ACCESSORS(int ,array_length)
 ACCESSORS(Modifiers ,modifier)
 ACCESSORS(int ,qmetatype_ptr_code)

 ACCESSORS(int ,byte_code)

 static Modifiers get_modifier_by_string(QString str);

 bool is_string_like() const;
 bool is_lisp_list_like() const;
 bool is_callable_lisp_deferred_value_like() const;
 bool is_argvec_like() const;
 bool is_number_like() const;

 void report(QTextStream& qts, Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs) const;

 QString token_report(Kauvir_Code_Model& kcm) const;

 QString get_name_string() const;

 KCM_Type_Object* base_clone() const;
};


_KANS(KCM)


#endif //KCM_TYPE_OBJECT__H
