
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kauvir-phaon/kph-command-package.h"

#include "kauvir-code-model/kauvir-code-model.h"
#include "kauvir-code-model/kcm-channel-group.h"
#include "kcm-scopes/kcm-scope-system.h"


#include "PhaonLib/phaon-namespace.h"
#include "PhaonLib/phaon-class.h"
#include "PhaonLib/phaon-function.h"
#include "PhaonLib/phaon-symbol-scope.h"

#include "relae-graph/relae-caon-ptr.h"

#include "test-functions.h"

#include "PhaonLib/phaon-channel-group-table.h"
#include "PhaonLib/phaon-runner.h"

#include "kcm-direct-eval/kcm-direct-eval.h"



#include "kans.h"

USING_KANS(KCM)
USING_KANS(Phaon)
USING_KANS(PhaonLib)



int main(int argc, char* argv[])
{
 Phaon_Runner phr;

 Kauvir_Code_Model& kcm = phr.get_kcm();
 kcm.set_direct_eval_fn(&kcm_direct_eval);

 Phaon_Symbol_Scope pss;
 init_test_functions(kcm, phr.get_table(), pss);
 phr.get_phaon_scope_queue().push_front(&pss);

 KPH_Command_Package khp;
 khp.parse_from_file( DEFAULT_KPH_FOLDER "/test/raw/t1.kph" );

 KCM_Channel_Group kcg(kcm.channel_names());

 khp.init_channel_group(kcm, kcg);
 phr.run(kcg);

 return 0;
}
