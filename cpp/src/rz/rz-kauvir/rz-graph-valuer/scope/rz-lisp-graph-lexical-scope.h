
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_LISP_GRAPH_LEXICAL_SCOPE__H
#define RZ_LISP_GRAPH_LEXICAL_SCOPE__H

#include "accessors.h"
#include "flags.h"

#include <QString>
#include <QMap>
#include <QList>

#include <QMultiMap>

#include "rz-lisp-graph-scope-token.h"

#include "rzns.h"

RZNS_(RECore)

class RE_Node;

_RZNS(RECore)



RZNS_(GBuild)

class RZ_Lisp_Token;

_RZNS(GBuild)



RZNS_(GVal)

class RZ_Lisp_Graph_Lexical_Scope
{
 QMap<QString, RZ_Lisp_Graph_Scope_Token> function_symbols_;

 QMap<QString, RZ_Lisp_Graph_Scope_Token> symbols_;


 QList<QString> symbol_order_;

 QMultiMap<QString, QString> annotations_;

 typedef QMap<QString, RZ_Lisp_Graph_Scope_Token> symbols_type;

 caon_ptr<RZ_Lisp_Graph_Lexical_Scope> parent_;


public:

 typedef QMapIterator<QString, RZ_Lisp_Graph_Scope_Token> iterator_type;

 ACCESSORS__RGET(symbols_type ,symbols)
 ACCESSORS__RGET(symbols_type ,function_symbols)
 ACCESSORS__RGET(QList<QString> ,symbol_order)

 ACCESSORS(caon_ptr<RZ_Lisp_Graph_Lexical_Scope> ,parent)

 RZ_Lisp_Graph_Lexical_Scope(caon_ptr<RZ_Lisp_Graph_Lexical_Scope> p = nullptr);

 void add_symbol(RZ_Lisp_Token& tok);

 void add_channel_symbol_from_symbol_name(QString name, QString channel_code);

 QString channel_code_for_symbol_name(QString name);

 void add_function_symbol(RZ_Lisp_Token& tok);
 RZ_Lisp_Graph_Scope_Token* contains_symbol(QString symbol_name);

 RZ_Lisp_Graph_Scope_Token* contains_function_symbol(QString symbol_name);

 RZ_Lisp_Graph_Scope_Token* contains_symbol_without_parent(QString symbol_name);
 RZ_Lisp_Graph_Scope_Token* contains_function_symbol_without_parent(QString symbol_name);

 void add_type_named_symbol(RZ_Lisp_Token& function_token,
  RZ_Lisp_Token& tok, QString type_name);

 void add_symbol(RZ_Lisp_Token& function_token,
  RZ_Lisp_Token& tok);

 QStringList get_annotations(RZ_Lisp_Token& tok);
 QStringList get_annotations(QString key);

 void add_annotations(RZ_Lisp_Token& tok, QStringList& sl);

 void relocate_function_symbol(const RZ_Lisp_Token& tok, RE_Node& value_node);
 void mark_value_node(const RZ_Lisp_Token& tok, RE_Node& value_node);
 void mark_value(const RZ_Lisp_Token& tok, RZ_Lisp_Graph_Value_Holder& vh);

 void mark_type_assertion(const RZ_Lisp_Token& tok, QString ta);



};

_RZNS(GVal)

#endif //RZ_LISP_GRAPH_LEXICAL_SCOPE__H
