
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-package/kcm-command-package.h"

#include "kauvir-code-model/kauvir-code-model.h"


#include "kcm-lisp-bridge/kcm-lisp-bridge.h"
#include "kcm-lisp-bridge/kcm-lisp-embed-environment.h"
#include "kcm-lisp-bridge/kcm-lisp-eval.h"
#include "kcm-lisp-bridge/kcm-lisp-runtime.h"

#include "kcm-command-runtime/kcm-command-runtime-table.h"

#include "kcm-scopes/kcm-scope-system.h"

#include "basic-functions/rz-dynamo-basic-functions.h"

#include "kcm-direct-eval/kcm-direct-eval.h"

#include "fn-doc/fn-doc.h"
#include "kcm-env/kcm-env.h"

#include <QApplication>

#include <QDebug>


USING_KANS(KCM)
USING_KANS(KCL)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);

 qRegisterMetaType<KCM_Lisp_Bridge>();
 qRegisterMetaType<KCM_Lisp_Bridge*>();

 qRegisterMetaType<Fn_Doc>();
 qRegisterMetaType<Fn_Doc*>();


 KCM_Lisp_Embed_Environment env(argc, argv);
 KCM_Lisp_Eval kle(&env);

 kle.prepare_callbacks();

 KCM_Lisp_Eval::get_make_kcm_channel_bridge_fn_type(&make_kcm_channel_bridge);

 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 bridge.init_kcm();

 Kauvir_Code_Model& kcm = *bridge.kcm();

 kcm.set_direct_eval_fn(&kcm_direct_eval);
 kcm.set_make_kcm_command_package_from_channel_group_fn(&make_kcm_command_package_from_channel_group);
 kcm.set_make_kcm_command_package_fn(&make_kcm_command_package);

 Kauvir_Type_System* type_system = kcm.type_system();

 kcm.create_and_register_type_object("Fn_Doc");
 kcm.create_and_register_type_object("Fn_Doc*");

 KCM_Env* kenv = new KCM_Env(&kcm);
 QString kenv_typename = "KCM_Env*";
 insert_envv(&kenv_typename, kenv);

 KCM_Command_Runtime_Table table(*type_system);
 kcm.set_table(&table);

 KCM_Scope_System scopes;
 kcm.set_scope_system(&scopes);

 kcm.init_scope_system();

 kenv->set_scopes(&scopes);

 kenv->set_report_channel_group_fn([](Kauvir_Code_Model* kcm, KCM_Channel_Group* kcg)
 {
  QString qs;
  QTextStream qts(&qs);

  kcg->report(qts, *kcm, kcm->detailed_report_synax(),
    KCM_Channel::Code_Environments::Statement);

  qDebug() << qs;
 });

 init_basic_functions_kci(kcm);

 kle.eval_script_file(RZ_DIR "/t1.rz.dyn.cl");

}

