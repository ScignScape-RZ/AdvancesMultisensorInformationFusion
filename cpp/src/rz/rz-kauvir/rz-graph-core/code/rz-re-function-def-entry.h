
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_FUNCTION_DEF_ENTRY__H
#define RZ_RE_FUNCTION_DEF_ENTRY__H

#include "accessors.h"
#include "flags.h"


#include <QString>
#include <QMap>

#include "relae-graph/relae-caon-ptr.h"

#include "rz-re-function-def-kinds.h"

#include "rzns.h"
RZNS_(RECore)


class RE_Node;

class RE_Function_Def_Entry
{
 caon_ptr<RE_Node> prior_node_;
 caon_ptr<RE_Node> node_;
 caon_ptr<RE_Node> label_node_;
 caon_ptr<RE_Node> note_node_;

 RE_Function_Def_Kinds kind_;

public:

 ACCESSORS(caon_ptr<RE_Node> ,prior_node)
 ACCESSORS(caon_ptr<RE_Node> ,node)
 ACCESSORS(caon_ptr<RE_Node> ,label_node)
 ACCESSORS(RE_Function_Def_Kinds ,kind)
 ACCESSORS(caon_ptr<RE_Node> ,note_node)

 RE_Function_Def_Entry(caon_ptr<RE_Node> prior_node, RE_Function_Def_Kinds kind, caon_ptr<RE_Node> label_node = nullptr);


};

_RZNS(RECore)

#endif //RZ_RE_FUNCTION_DEF_ENTRY__H
