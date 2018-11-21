
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "test-functions.h"


#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kcm-command-runtime/kcm-command-runtime-table.h"

#include "kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "PhaonLib/phaon-channel-group-table.h"
#include "PhaonLib/phaon-symbol-scope.h"
#include "PhaonLib/phaon-function.h"


#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)
USING_KANS(PhaonLib)

KANS_(Phaon)

void test_0_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
}

void test_0_s(QString s1)
{
 qDebug() << "s1 = " << s1;
}

QString test_s_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: s_ss";
 return "s_ss";
}

QString test_s_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: s_s";
 return "s_s";
}

int test_i_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: 66";
 return 66;
}

int test_i_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: 66";
 return 66;
}


void init_test_functions(Kauvir_Code_Model& kcm,
  Phaon_Channel_Group_Table& table, Phaon_Symbol_Scope& pss)
{

 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Channel_Group g1(kcm.channel_names());
 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_0_ss", 700, &test_0_ss);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_0_s", 700, &test_0_s);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, pss, "test_s_ss", 600, &test_s_ss);

  g1.clear_all();
 }
}

_KANS(Phaon)


