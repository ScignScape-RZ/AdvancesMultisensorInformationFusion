
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-string-plex.h"

#include "valuer/rz-lisp-graph-valuer.h"

#include "rz-graph-core/tuple/rz-re-tuple-info.h"

#include "rz-graph-token/token/rz-lisp-token.h"

#include "rz-graph-core/kernel/grammar/rz-re-string-plex-builder.h"

#include "rzns.h"


USING_RZNS(GVal)

RZ_String_Plex::RZ_String_Plex(caon_ptr<RE_Tuple_Info> tuple_info,
 RZ_Type_Object& rto, caon_ptr<RZ_String_Plex_Builder> builder)
 :
   tuple_info_(tuple_info), builder_(builder)
{
 token_representation_ = new RZ_Lisp_Token(tuple_info_->token_representation());
 token_representation_->flags.is_token_representation = true;
 token_representation_->set_value(caon_ptr<RZ_String_Plex>(this));
 token_representation_->set_type_object(rto);
}

QString RZ_String_Plex::get_value(QString key)
{
 if(builder_)
 {
  return builder_->get_part(key);
 }
 else
  return QString();
}


caon_ptr<RZ_String_Plex::tNode> RZ_String_Plex::get_call_entry_node()
{
 if(tuple_info_)
  return tuple_info_->call_entry_node();
 return nullptr;
}


