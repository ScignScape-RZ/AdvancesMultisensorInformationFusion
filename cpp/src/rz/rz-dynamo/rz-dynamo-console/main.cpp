
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kcm-lisp-bridge/kcm-lisp-bridge.h"
#include "kcm-lisp-bridge/kcm-lisp-embed-environment.h"
#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "kcm-direct-eval/kcm-direct-eval.h"

#include "kcm-lisp-bridge/kcm-lisp-runtime.h"



USING_KANS(KCM)
USING_KANS(KCL)

int main(int argc, char* argv[])
{
 qRegisterMetaType<KCM_Lisp_Bridge>();
 qRegisterMetaType<KCM_Lisp_Bridge*>();

 KCM_Lisp_Embed_Environment env(argc, argv);

 QString out_string;
 QTextStream qts(&out_string);

 KCM_Lisp_Eval kle(&env, qts);

 kle.prepare_callbacks();

 KCM_Lisp_Eval::get_make_kcm_channel_bridge_fn_type(&make_kcm_channel_bridge);


 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 bridge.init_kcm();

 Kauvir_Code_Model& kcm = *bridge.kcm();

 kcm.set_direct_eval_fn(&kcm_direct_eval);
 kcm.set_make_kcm_command_package_from_channel_group_fn(&make_kcm_command_package_from_channel_group);
 kcm.set_make_kcm_command_package_fn(&make_kcm_command_package);

 kle.eval_script_file(RZ_DIR "/t1.rz.lisp");

 QFile qf(RZ_DIR "/t1.rz.dyn.cl");


 if(qf.open(QIODevice::WriteOnly))
 {
  QTextStream os(&qf);
  os << out_string;
  qf.close();
 }


 return 0;
}

