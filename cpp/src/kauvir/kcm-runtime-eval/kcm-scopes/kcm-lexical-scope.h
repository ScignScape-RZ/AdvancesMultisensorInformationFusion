
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LEXICAL_SCOPE__H
#define KCM_LEXICAL_SCOPE__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QMap>

KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_System)
USING_KANS(Kauvir)

KANS_(KCM)


class KCM_Type_Object;
class KCM_Channel_Group;
class KCM_Block;

class KCM_Expression;


class KCM_Lexical_Scope
{
 KCM_Lexical_Scope* parent_;
 KCM_Block* associated_block_;

 QString file_path_;

 QMap<QString, const KCM_Type_Object*> symbols_;

 QMap<QString, QPair<KCM_Expression*, int>> nested_expression_key_index_;

 QMap<QPair< QPair<KCM_Expression*, int>, QPair<int, int>>,
   QPair<const KCM_Type_Object*, QPair<QString, QString>>> nested_expression_store_;

 QMap<QPair<KCM_Expression*, QPair<int, int>>,
   QPair<const KCM_Type_Object*, QPair<int, quint64>>> held_deferred_store_;

 QMap<QString, quint64> keys_for_storing_;

 quint32 last_key_for_storing_;

 QMap<int, QPair<KCM_Expression*, QPair<int, int>>> nested_expression_key_index_map_;

public:

 KCM_Lexical_Scope(KCM_Lexical_Scope* parent = nullptr);
 KCM_Lexical_Scope(QString file_path);

 ACCESSORS(KCM_Block* ,associated_block)
 ACCESSORS(KCM_Lexical_Scope* ,parent)

 ACCESSORS__GET(quint32 ,last_key_for_storing)

 void increment_key_for_storing();


 void add_symbol(QString symbol_name, const KCM_Type_Object* kto);

 void store_key(QString key, quint64 clo);
 quint64 find_held_lisp_list(QString key);

 const KCM_Type_Object* get_type_object_from_symbol_name(QString symbol_name);

 const KCM_Type_Object* get_type_object_from_symbol_name(QString symbol_name, bool& found);

 void hold_runtime_value(const QPair< QPair<KCM_Expression*, int>, QPair<int, int> >& coords,
   const KCM_Type_Object* kto, QString value_encoding, QString key);

 void hold_deferred(const QPair<KCM_Expression*, QPair<int, int> >& coords,
   const KCM_Type_Object* qto, int hdcode, quint64 qclo_value);


 const KCM_Type_Object* find_runtime_value(KCM_Expression* kcx, int level, int index,
   QString& encoded_value, QPair<int, quint64>& qclo_value, int hdcode = 0);

 quint64 find_held_value_by_hdcode(int hdcode);

 KCM_Expression* get_kcm_expression_from_nested_key(QString key);
};


_KANS(KCM)


#endif //KCM_LEXICAL_SCOPE__H

