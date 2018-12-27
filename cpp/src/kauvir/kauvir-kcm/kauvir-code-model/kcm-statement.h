
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_STATEMENT__H
#define KCM_STATEMENT__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include "kcm-overloadable-symbol.h"

#include <QVector>
#include <QTextStream>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)

class KCM_Channel_Group;
class KCM_Block;
class KCM_Lexical_Scope;

class KCM_Expression;
class KCM_Report_Syntax;
class KCM_Type_Object;

class KCM_Statement
{
public:
 enum class Statement_Kinds {
   N_A, Promoted_Expression,
   Type_Binding_With_Expression,
   Type_Binding_With_Token,
   Type_Binding, Expression_Binding,
   Tarried_Expression_Binding,
   Type_Binding_With_Block,
   Type_Binding_With_QObject,
 };

private:

 Statement_Kinds statement_kind_;


 KCM_Expression* expression_;
 KCM_Block* nested_block_;

 KCM_Overloadable_Symbol symbol_;

 QString annotation_;

 const KCM_Type_Object* bind_kto_;
 QString bind_val_;

 QObject* bind_qob_;

public:

 KCM_Statement(Statement_Kinds statement_kind, KCM_Expression* expression);
 KCM_Statement(Statement_Kinds statement_kind, KCM_Overloadable_Symbol symbol);

 KCM_Statement(Statement_Kinds statement_kind, QString symbol_name, KCM_Expression* expression = nullptr);
 KCM_Statement(Statement_Kinds statement_kind, QString symbol_name, const KCM_Type_Object* kto, QString val);
 KCM_Statement(Statement_Kinds statement_kind, QString symbol_name, const KCM_Type_Object* kto, QObject* qob);

 ACCESSORS(Statement_Kinds ,statement_kind)
 ACCESSORS(KCM_Block* ,nested_block)
 ACCESSORS(QString ,annotation)

 ACCESSORS(KCM_Expression* ,expression)
 ACCESSORS__RGET(KCM_Overloadable_Symbol ,symbol)

 ACCESSORS(const KCM_Type_Object* ,bind_kto)
 ACCESSORS(QString ,bind_val)
 ACCESSORS(QObject* ,bind_qob)

};


_KANS(KCM)


#endif //KCM_STATEMENT__H
