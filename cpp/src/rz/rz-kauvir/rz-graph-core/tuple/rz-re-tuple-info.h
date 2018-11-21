
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_TUPLE_INFO__H
#define RZ_RE_TUPLE_INFO__H

#include "accessors.h"
#include "flags.h"

#include "relae-graph/relae-caon-ptr.h"

#include <QString>

#include <QMap>

#include <functional>

#include "rzns.h"
RZNS_(RECore)

class RE_Node;


class RE_Tuple_Info
{
public:

 typedef RE_Node tNode;

 enum class Function_Def_Channels {
  N_A, Lambda_Channel, Sigma_Channel, Return_Channel, Error_Channel,
  Context_Channel, CTOR_Mem_Channel, CTOR_Ret_Channel,
 };

 enum class Tuple_Formations {
  N_A, Indicates_Declarations, Indicates_Input,
   Indicates_Plex, Indicates_Final, Indicates_String,
   Indicates_Multi, Indicates_Functional,
   Indicates_Text_Map, Indicates_Text_Vector,
   Indicates_Pattern, Indicates_Assignment, Indicates_Unquote,
   Indicates_CTOR_Ret, Indicates_CTOR_Mem
 };

 static Tuple_Formations get_tuple_formation(QString s)
 {
  static QMap<QString, Tuple_Formations> static_map
  {{
    { ",", Tuple_Formations::Indicates_Declarations },
    { ".", Tuple_Formations::Indicates_Input },
    { "..", Tuple_Formations::Indicates_Final },
    { "$", Tuple_Formations::Indicates_String },
    { "@", Tuple_Formations::Indicates_Multi },
    { "#", Tuple_Formations::Indicates_Functional },
    { "~", Tuple_Formations::Indicates_Text_Map },
    { "*", Tuple_Formations::Indicates_Text_Vector },
    { "-", Tuple_Formations::Indicates_Pattern },
    { "--", Tuple_Formations::Indicates_Plex },
    { "=", Tuple_Formations::Indicates_Assignment },
    { "@.", Tuple_Formations::Indicates_CTOR_Mem },
    { "@..", Tuple_Formations::Indicates_CTOR_Ret },
  }};

  return static_map.value(s, Tuple_Formations::N_A);
 }

 enum class Tuple_Indicators {
  N_A, Enter_Array, Enter_Vector, Enter_Map, Enter_Set, Enter_Annotation,
       Leave_Array, Leave_Vector, Leave_Map, Leave_Set, Leave_Annotation
 };

 static Tuple_Indicators get_tuple_indicator(QString s)
 {
  static QMap<QString, Tuple_Indicators> static_map
  {{
    { "(",  Tuple_Indicators::Enter_Array },
    { "[",  Tuple_Indicators::Enter_Vector },
    { "{",  Tuple_Indicators::Enter_Map },
    { "{{", Tuple_Indicators::Enter_Set },
    { "[[", Tuple_Indicators::Enter_Annotation },

    { ")",  Tuple_Indicators::Leave_Array },
    { "]",  Tuple_Indicators::Leave_Vector },
    { "}",  Tuple_Indicators::Leave_Map },
    { "}}", Tuple_Indicators::Leave_Set },
    { "]]", Tuple_Indicators::Leave_Annotation },

  }};

  return static_map.value(s, Tuple_Indicators::N_A);
 }

private:

 Tuple_Formations formation_;
 Tuple_Indicators indicator_;

 caon_ptr<tNode> call_entry_node_;

 int data_id_;

public:

 ACCESSORS(Tuple_Formations ,formation)
 ACCESSORS(Tuple_Indicators ,indicator)
 ACCESSORS__GET(int ,data_id)
 ACCESSORS(caon_ptr<tNode> ,call_entry_node)

 RE_Tuple_Info(Tuple_Formations tf, Tuple_Indicators ti, int data_id);

 QString lisp_out(bool with_prefix = false) const;

 QString lisp_out_with_id(bool with_prefix = false) const;

 QString token_representation() const;

 QString base_token_representation() const;

 Function_Def_Channels match_function_def_channel() const
 {
  if(indicator_ == Tuple_Indicators::Enter_Array)
  {
   if(formation_ == Tuple_Formations::Indicates_Input)
    return Function_Def_Channels::Lambda_Channel;
   else if(formation_ == Tuple_Formations::Indicates_Final)
    return Function_Def_Channels::Return_Channel;
   else if(formation_ == Tuple_Formations::Indicates_CTOR_Ret)
    return Function_Def_Channels::CTOR_Ret_Channel;
  }
  else if(indicator_ == Tuple_Indicators::Enter_Vector)
  {
   if(formation_ == Tuple_Formations::Indicates_Input)
    return Function_Def_Channels::Sigma_Channel;
   else if(formation_ == Tuple_Formations::Indicates_Final)
    return Function_Def_Channels::Error_Channel;
   else if(formation_ == Tuple_Formations::Indicates_CTOR_Mem)
    return Function_Def_Channels::CTOR_Mem_Channel;
   else if(formation_ == Tuple_Formations::Indicates_Pattern)
    return Function_Def_Channels::Context_Channel;
  }
  else return Function_Def_Channels::N_A;
 }

 void mark_as_empty();
 bool is_empty() const;

 bool indicates_function_def_entry() const
 {
  return is_entry() &&
    (formation_ == Tuple_Formations::Indicates_Input)
     && ( (indicator_ == Tuple_Indicators::Enter_Array)
      ||
       (indicator_ == Tuple_Indicators::Enter_Vector) )
    ;
 }

 bool is_entry() const
 {
  switch(indicator_)
  {
  case Tuple_Indicators::Enter_Array:
  case Tuple_Indicators::Enter_Vector:
  case Tuple_Indicators::Enter_Map:
  case Tuple_Indicators::Enter_Set:
   return true;
  default:
   return false;
  }
 }
};

_RZNS(RECore)

#endif //RZ_RE_TUPLE_INFO__H
