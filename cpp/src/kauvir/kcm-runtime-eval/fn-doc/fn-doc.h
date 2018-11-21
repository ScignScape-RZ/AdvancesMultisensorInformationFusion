
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef FN_DOC__H
#define FN_DOC__H


#include "kans.h"

#include "kauvir-type-system/kauvir-universal-class.h"

#include <QString>
#include <QObject>

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)
KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)

class KCM_Lisp_Bridge;

KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)

USING_KANS(CMD)

class KCM_Env;

class Fn_Doc : public QObject, public Kauvir_Universal_Class
{
 Q_OBJECT

 KCM_Scope_System* scopes_;
 KCM_Env* kenv_;

public:

 Fn_Doc();

 Fn_Doc(const Fn_Doc& rhs);

 ~Fn_Doc();

 ACCESSORS(KCM_Scope_System* ,scopes)

 Q_INVOKABLE void read(QString fn);
 Q_INVOKABLE void init(KCM_Env* kenv);
 Q_INVOKABLE void kph_gen(QString fn, QString subs);

 const KCM_Type_Object* get_type_object_from_symbol_name(QString fn);

 QString test_summary();

 void kph_gen(const KCM_Type_Object* kto, QString fn, QString& text);

};


Q_DECLARE_METATYPE(Fn_Doc)
Q_DECLARE_METATYPE(Fn_Doc*)

#endif //FN_DOC__H
