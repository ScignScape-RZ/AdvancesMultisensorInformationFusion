
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_SCOPE_SYSTEM__H
#define KCM_SCOPE_SYSTEM__H

#include "kans.h"


#include "accessors.h"

#include <QtGlobal>
#include <QQueue>

#include <QMap>

KANS_CLASS_DECLARE(KCM ,KCM_Lexical_Scope)
KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Overloadable_Symbol)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)
KANS_CLASS_DECLARE(KCM ,KCM_Expression)
KANS_CLASS_DECLARE(KCM ,KCM_Source_Function)
USING_KANS(KCM)

KANS_CLASS_DECLARE(PhaonLib ,Phaon_Symbol_Scope)
USING_KANS(PhaonLib)

KANS_(CMD)

class KCM_Runtime_Scope;


class KCM_Scope_System
{
 KCM_Runtime_Scope* current_scope_;
 QQueue<Phaon_Symbol_Scope*> phaon_scope_queue_;

 QMap<QString, QPair<quint64, const KCM_Type_Object*>> temporary_bridge_values_;


public:

 KCM_Scope_System();

 ACCESSORS(KCM_Runtime_Scope* ,current_scope)
 ACCESSORS__RGET(QQueue<Phaon_Symbol_Scope*> ,phaon_scope_queue)

 quint64 find_temporary_bridge_value(QString code, const KCM_Type_Object*& kto);
 void hold_temporary_bridge_value(QString code, quint64 value, const KCM_Type_Object* kto);

 quint64 find_held_lisp_list_from_current_scope(QString key);

 void join_lexical_scope(KCM_Lexical_Scope* associated_lexical_scope);

 KCM_Source_Function* find_source_function_from_current_scope(QString local_name);

 quint64* find_raw_value_from_current_scope(QString bind_code,
   void*(*efn)(void*), KCM_Expression* kcm_expression, const KCM_Type_Object*& kto,
   const KCM_Type_Object*& ckto, QString& encoded_value,
   QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto = nullptr);

 quint64* find_raw_value_from_scope(KCM_Runtime_Scope* scope,
   QString bind_code, KCM_Expression* kcm_expression, const KCM_Type_Object*& kto,
   const KCM_Type_Object*& ckto, QString& encoded_value,
   QPair<int, quint64>& qclo_value, const KCM_Type_Object** skto = nullptr);

 void enter_scope();
 void leave_scope();

 quint64 find_held_value_by_hdcode(int hdcode);

 const KCM_Type_Object* get_type_object_from_symbol_name(QString sn);

};

_KANS(CMD)


#endif //KCM_SCOPE_SYSTEM__H

