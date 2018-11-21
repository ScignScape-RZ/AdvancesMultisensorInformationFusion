
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef Fn_Doc_Multi__H
#define Fn_Doc_Multi__H


#include "kans.h"

#include "kauvir-type-system/kauvir-universal-class.h"

#include <QString>
#include <QObject>
#include <QList>
#include <QPair>


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
class Fn_Doc;

class Fn_Doc_Multi : public QObject, public Kauvir_Universal_Class
{
 Q_OBJECT

 Fn_Doc* fnd_;

 QList<QPair<QString, const KCM_Type_Object*>> fns_;

public:

 Fn_Doc_Multi();

 Fn_Doc_Multi(const Fn_Doc_Multi& rhs);

 ~Fn_Doc_Multi();

 Q_INVOKABLE void read(QString fn);
 Q_INVOKABLE void init(KCM_Env* kenv);

 Q_INVOKABLE void kph_gen_multi(QString path);

};


Q_DECLARE_METATYPE(Fn_Doc_Multi)
Q_DECLARE_METATYPE(Fn_Doc_Multi*)

#endif //Fn_Doc_Multi__H
