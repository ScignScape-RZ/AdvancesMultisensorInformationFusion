
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KAUVIR_TYPE_OBJECT__H
#define KAUVIR_TYPE_OBJECT__H


#include "kans.h"

#include "accessors.h"

#include <QVector>

#include <QVariant>

class Fn_Doc_Info;

KANS_(Kauvir)

class Kauvir_Channel_Group;

class Kauvir_Runtime;

class Kauvir_Type_Object
{
 QString name_;

 const QMetaObject* qmo_;
 const QMetaObject* pqmo_;
 Fn_Doc_Info* fn_doc_info_;

 Kauvir_Channel_Group* signature_;

 QVariant::Type qvariant_type_;
 int qmetatype_code_;


public:

 enum class Inheritance_Modes {
   N_A, Public, Private, Protected
 };

private:

 QVector<QPair<const Kauvir_Type_Object* const, Inheritance_Modes>> supertypes_;


public:

 Kauvir_Type_Object(QString name);
 Kauvir_Type_Object(Kauvir_Channel_Group* signature);


 ACCESSORS(QString ,name)
 ACCESSORS(const QMetaObject* ,qmo)
 ACCESSORS(const QMetaObject* ,pqmo)

 void parse_simplified_signature(QString rep, Kauvir_Runtime& runtime);

 // //  this needs to distinguish pointer from non ...
 void check_register_variant_and_metatype_info(QVariant::Type qvt, int qmetatype_code);

};


_KANS(Kauvir)


#endif //KAUVIR_TYPE_OBJECT__H

