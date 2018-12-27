
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phaon-runner.h"

#include "phaon-symbol-scope.h"
#include "phaon-function-vector.h"

#include "kauvir-code-model/kauvir-code-model.h"
#include "kcm-scopes/kcm-scope-system.h"

#include "phaon-channel-group-table.h"


#include "kcm-command-package/kcm-command-package.h"


USING_KANS(PhaonLib)


Phaon_Runner::Phaon_Runner()
  :  kcm_(new Kauvir_Code_Model), table_(nullptr), scopes_(nullptr)
{
 init_scope_system();
}

void Phaon_Runner::init_scope_system()
{
 scopes_ = new KCM_Scope_System;
 kcm_->set_scope_system(scopes_);
 kcm_->init_scope_system();

 Kauvir_Type_System* type_system = kcm_->type_system();
 table_ = new Phaon_Channel_Group_Table(*type_system);

}


void Phaon_Runner::run(KCM_Channel_Group& kcg)
{
 KCM_Command_Package kcp(kcg);
 kcm_->direct_eval(&kcp, nullptr);
}


QQueue<Phaon_Symbol_Scope*>& Phaon_Runner::get_phaon_scope_queue()
{
 return scopes_->phaon_scope_queue();
}

