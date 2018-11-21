
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_EMBED_TOKEN__H
#define RZ_GRAPH_EMBED_TOKEN__H


#include <QMap>
#include <QString>

#include "rzns.h"

#include "accessors.h"

#include "rz-graph-token/token/token-kinds.h"

#include "relae-graph/relae-caon-ptr.h"

RZNS_(RECore)

class RE_Node;
class RE_Function_Def_Entry;

_RZNS(RECore)

USING_RZNS(RECore)



RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)


RZNS_(GRun)

class RZ_Graph_Run_Token;

_RZNS(GRun)

RZNS_(GVal)

class RZ_Function_Def_Info;

_RZNS(GVal)


USING_RZNS(GBuild)
USING_RZNS(GRun)
USING_RZNS(GVal)


RZNS_(GEmbed)

class RZ_Graph_Embed_Package;


class RZ_Graph_Embed_Token
{
 Basic_Token_Kinds kind_;

 QString raw_text_;

 caon_ptr<RZ_Graph_Embed_Package> embed_package_;

 caon_ptr<QStringList> args_;

 caon_ptr<RE_Node> entry_node_;

 void init_from_lisp_token(const RZ_Lisp_Token& rlt);

 caon_ptr<RZ_Function_Def_Info> function_def_info_;

public:

 ACCESSORS(QString ,raw_text)
 ACCESSORS__CGET(caon_ptr<QStringList> ,args)
 ACCESSORS(caon_ptr<RE_Node> ,entry_node)
 ACCESSORS(caon_ptr<RZ_Function_Def_Info> ,function_def_info)

 ACCESSORS(Basic_Token_Kinds ,kind)


 RZ_Graph_Embed_Token(QString raw_text,
  caon_ptr<RZ_Graph_Embed_Package> embed_package = nullptr);

 RZ_Graph_Embed_Token(QString raw_text, Basic_Token_Kinds kind,
  caon_ptr<RZ_Graph_Embed_Package> embed_package = nullptr);

 RZ_Graph_Embed_Token(QString raw_text, QString arg,
  caon_ptr<RZ_Graph_Embed_Package> embed_package = nullptr);

 RZ_Graph_Embed_Token(RZ_Lisp_Token& rz_lisp_token,
  caon_ptr<RZ_Graph_Embed_Package> embed_package = nullptr);


 QString string_value();

 QString string_value(int position);

 QString padded_string_value(int position);

 void set_args(QStringList& qsl);

 void advance_arg(int& position);

 void convey(int position, RZ_Graph_Run_Token& rzt);

 Basic_Token_Kinds kind_and_string_value(QString& sv) const;
};

_RZNS(GEmbed)


#endif //RZ_GRAPH_EMBED_TOKEN__H
