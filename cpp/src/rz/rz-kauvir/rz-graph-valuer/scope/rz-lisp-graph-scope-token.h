
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_SCOPE_TOKEN__H
#define RZ_LISP_GRAPH_SCOPE_TOKEN__H

#include "accessors.h"
#include "flags.h"


#include <QString>
#include <QMap>

#include "rz-graph-token/rz-lisp-graph-value-holder.h"
#include "rz-graph-token/token/token-kinds.h"


#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)


RZNS_(GBuild)

class RZ_Lisp_Token;
class RZ_Type_Variety;
class RZ_Type_Object;

_RZNS(GBuild)

USING_RZNS(GBuild)

RZNS_(GVal)


class RZ_Lisp_Graph_Scope_Token
{

 caon_ptr<RZ_Lisp_Token> function_token_;
 caon_ptr<RZ_Lisp_Token> declaration_token_;
 caon_ptr<RE_Node> value_node_;

 QString declared_type_name_;

 QString channel_code_;

 RZ_Lisp_Graph_Value_Holder vh_;

public:


 RZ_Lisp_Graph_Scope_Token(QString channel_code);

 RZ_Lisp_Graph_Scope_Token(caon_ptr<RZ_Lisp_Token> f = nullptr,
  caon_ptr<RZ_Lisp_Token> d = nullptr, caon_ptr<RE_Node> n = nullptr);

 RZ_Lisp_Graph_Scope_Token(RZ_Lisp_Token& f,
  RZ_Lisp_Token& d, QString dtn, caon_ptr<RE_Node> n = nullptr);

 RZ_Lisp_Graph_Scope_Token(RZ_Lisp_Token& f, RZ_Lisp_Token& d);



 ACCESSORS(caon_ptr<RZ_Lisp_Token> ,function_token)
 ACCESSORS(caon_ptr<RZ_Lisp_Token> ,declaration_token)
 ACCESSORS(caon_ptr<RE_Node> ,value_node)
 ACCESSORS(QString ,declared_type_name)

 ACCESSORS(RZ_Lisp_Graph_Value_Holder ,vh)

 ACCESSORS(QString ,channel_code)

 Basic_Token_Kinds initial_kind_and_string_value(QString& result) const;

 QString type_to_string() const;
 QString value_to_string() const;
 QString value_to_lisp_string() const;
 QString value_to_string(QString& type) const;
 QString value_to_string(QString& type, RZ_Type_Variety& tv) const;
 bool type_matches(caon_ptr<RZ_Type_Object> rto) const;

};

_RZNS(GVal)

#endif //RZ_LISP_GRAPH_SCOPE_TOKEN__H
