
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_GRAPH_RUN_EMBEDDER__H
#define RZ_GRAPH_RUN_EMBEDDER__H


#include <QMap>
#include <QString>

#include "rzns.h"

#include "accessors.h"

#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-core/kernel/query/rz-re-query.h"
#include "rz-graph-core/kernel/frame/rz-re-frame.h"

#include "rz-graph-token/token/token-kinds.h"

RZNS_(RECore)

class RE_Node;
class RZ_Cpp_Project;


_RZNS(RECore)


USING_RZNS(RECore)


RZNS_(GBuild)

class RZ_Lisp_Token;
class RZ_Lisp_Graph_Result_Holder;

_RZNS(GBuild)

RZNS_(GVal)

class RZ_Lisp_Graph_Valuer;

_RZNS(GVal)


USING_RZNS(GBuild)
USING_RZNS(GVal)


RZNS_(GEmbed)

class RZ_Graph_Embed_Package;
class RZ_Graph_Cpp_Token;

class RZ_Graph_Run_Embedder
{
 caon_ptr<RZ_Lisp_Graph_Valuer> valuer_;

 RE_Frame& fr_;
 const RE_Query& rq_;


 typedef RE_Node tNode;

 caon_ptr<tNode> noop_node_;

 caon_ptr<RZ_Graph_Embed_Package> rz_cpp_embed_package_;

 caon_ptr<RZ_Cpp_Project> cpp_project_;


public:

 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Valuer> ,valuer)
 ACCESSORS(caon_ptr<RZ_Cpp_Project> ,cpp_project)


 RZ_Graph_Run_Embedder(caon_ptr<RZ_Lisp_Graph_Valuer> valuer);
 void init_noop_node();

 bool match_noop_node(caon_ptr<tNode> n)
 {
  return n == noop_node_;
 }

 void check_redirect(RZ_Lisp_Graph_Result_Holder& rh, tNode& current_start_node);

 void redirect_to_noop(tNode& n);

 void redirect_to_noop(RZ_Lisp_Graph_Result_Holder& rh, tNode& current_start_node);

 caon_ptr<RZ_Graph_Cpp_Token> redirect_cpp(tNode& n, QString str,
  Basic_Token_Kinds kind = Basic_Token_Kinds::Symbol_Token);

 caon_ptr<RZ_Graph_Embed_Token> redirect(tNode& n, QStringList& qsl, bool no_package = false);

 void redirect(tNode& n, QString function_name);

 void redirect_with_call_no_package(RZ_Lisp_Graph_Result_Holder& rh, tNode& redirect_entry_node,
  std::initializer_list<QString> args, caon_ptr<tNode> function_node = nullptr);

 void redirect_no_package(RZ_Lisp_Graph_Result_Holder& rh, std::initializer_list<QString> args,
  caon_ptr<tNode> function_node = nullptr);

 void redirect(RZ_Lisp_Graph_Result_Holder& rh, std::initializer_list<QString> args,
  caon_ptr<tNode> function_node = nullptr);

 void redirect(RZ_Lisp_Graph_Result_Holder& rh, QStringList& qsl, tNode& function_node);

 void redirect(RZ_Lisp_Graph_Result_Holder& rh, QString function_name, tNode& function_node);

 void embed_rename(RZ_Lisp_Graph_Result_Holder& rh,
  QString function_name, tNode& function_node);

 void embed_deferred_callback(RZ_Lisp_Graph_Result_Holder& rh,
  QString function_name, tNode& function_node);

 void embed_rename(tNode&, QString function_name);
 void embed_deferred_callback(tNode&, QString function_name);


};

_RZNS(GEmbed)


#endif //RZ_GRAPH_RUN_EMBEDDER__H
