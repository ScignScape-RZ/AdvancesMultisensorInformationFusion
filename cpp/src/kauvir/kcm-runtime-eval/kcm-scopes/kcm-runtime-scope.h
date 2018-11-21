
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_RUNTIME_SCOPE__H
#define KCM_RUNTIME_SCOPE__H

#include "kans.h"

#include "accessors.h"

#include <QMap>
#include <QVector>

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)
KANS_CLASS_DECLARE(KCM ,KCM_Lexical_Scope)
KANS_CLASS_DECLARE(KCM ,KCM_Expression)
KANS_CLASS_DECLARE(KCM ,KCM_Source_Function)


USING_KANS(KCM)

KANS_(CMD)

class KCM_Runtime_Scope
{
 KCM_Runtime_Scope* parent_scope_;

 QMap<QString, QMap<const KCM_Type_Object*, QPair<const KCM_Type_Object*, quint64> > > values_;

 KCM_Lexical_Scope* associated_lexical_scope_;

 QVector<QString*> str_ptrs_;

 QMap<QString, QVector<const KCM_Type_Object*>> declared_fn_types_;

public:

 explicit KCM_Runtime_Scope(KCM_Runtime_Scope* parent_scope);

 ACCESSORS(KCM_Runtime_Scope* ,parent_scope)
 ACCESSORS(KCM_Lexical_Scope* ,associated_lexical_scope)

 const KCM_Type_Object* get_type_object_from_symbol_name(QString symbol_name);

 void add_declared_fn_type(QString str, const KCM_Type_Object* kto);

 void add_value(QString symbol_name, const KCM_Type_Object* kto, quint64 v);
 void add_string_value(QString symbol_name, const KCM_Type_Object* kto, QString s);

 void find_value(QString symbol_name, KCM_Expression* kcm_expression, quint64*& v,
   const KCM_Type_Object*& kto, const KCM_Type_Object*& ckto,
   QString& encoded_value, QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto = nullptr);

 quint64 find_held_lisp_list(QString key);
 quint64 find_held_value_by_hdcode(int hdcode);

 KCM_Source_Function* find_source_function_value(QString symbol_name);

};

_KANS(CMD)


#endif //KCM_RUNTIME_SCOPE__H

