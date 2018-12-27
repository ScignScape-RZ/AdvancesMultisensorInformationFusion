
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kauvir-type-object.h"

#include "kans.h"


#include <QRegularExpression>

USING_KANS(Kauvir)


Kauvir_Type_Object::Kauvir_Type_Object(QString name)
  :  name_(name), qmo_(nullptr), pqmo_(nullptr),
     fn_doc_info_(nullptr), signature_(nullptr),
     qvariant_type_(QVariant::Invalid), qmetatype_code_(0)
{

}

Kauvir_Type_Object::Kauvir_Type_Object(Kauvir_Channel_Group* signature)
 :  qmo_(nullptr), pqmo_(nullptr),
    fn_doc_info_(nullptr), signature_(signature),
    qvariant_type_(QVariant::Invalid), qmetatype_code_(0)
{

}


void Kauvir_Type_Object::check_register_variant_and_metatype_info(QVariant::Type qvt, int qmetatype_code)
{
 qvariant_type_ = qvt;
 qmetatype_code_ = qmetatype_code;
}

void Kauvir_Type_Object::parse_simplified_signature(QString rep, Kauvir_Runtime& runtime)
{
 // // obsolete, though also TODO ...
}

