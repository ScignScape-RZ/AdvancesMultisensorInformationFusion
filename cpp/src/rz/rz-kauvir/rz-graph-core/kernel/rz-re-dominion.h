
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_RE_DOMINION__H
#define RZ_RE_DOMINION__H


#include "relae-graph/relae-node-ptr.h"
#include "relae-graph/relae-caon-ptr.h"

#include "rz-graph-sre/rz-read-table-state.h"

#include "rzns.h"



#define DOMINION_HIDE_NO_NAMESPACE
#define DOMINION_TYPE DOMINION_TYPE_DECLARE
#include "dominion/types.h"
#undef DOMINION_TYPE
#undef DOMINION_HIDE_NO_NAMESPACE


RZNS_(RZClasp)
 class RZ_Clasp_Source_Element;
_RZNS(RZClasp)

USING_RZNS(RZClasp)

RZNS_(RECore)

struct RE_Galaxy;
class RE_Node;
class RE_Connectors;
class RE_Connection;
class RE_Annotated_Connectors;
class RE_Frame;
class RE_Document;
class RE_Graph;
class RE_Root;
class RZ_SRE_Token;

struct RE_Dominion
{
 typedef RE_Galaxy Galaxy_type;
 typedef RE_Node Node_type;
 typedef RE_Frame Frame_type;
 typedef RE_Connectors Connectors_type;
 typedef RE_Connection Connection_type;
 typedef RE_Annotated_Connectors Annotated_Connectors_type;
 typedef RE_Document Document_type;
 typedef RE_Graph Graph_type;
 typedef RE_Root Root_type;

 enum class Type_Codes { N_A,
  #define DOMINION_TYPE DOMINION_TYPE_ENUM
  #include "dominion/types.h"
  #undef DOMINION_TYPE
 };

 template<typename T>
 Type_Codes get_type_code()
 {
 }

};



struct RE_Galaxy : Node_Ptr_Default_Galaxy<RE_Dominion>
{
 typedef RZ_SRE_Token SRE_Token_type;
 typedef RZ_SRE_State SRE_State_type;
 typedef RZ_Clasp_Source_Element Source_Element_type;

};

enum class RE_Connectors_Case_Labels
{
 #define DOMINION_CONNECTOR(name, label) \
  name,
 #include "rz-graph-core/kernel/dominion/connectors.h"
 #undef DOMINION_CONNECTOR
};

struct RE_Connectors : node_connectors<RE_Dominion>
{
  RE_Connectors(RE_Connectors_Case_Labels cl = RE_Connectors_Case_Labels::N_A,
    QString label = QString())
   : node_connectors<RE_Dominion>(label), case_label(cl),
     priority(0), order(0){}
  RE_Connectors_Case_Labels case_label;
  int priority;
  int order;
  bool operator<(const RE_Connectors& rhs) const
  {
   return order < rhs.order;
  }
  operator bool() const
  {
   return order > 0;
  }
};

struct RE_Annotated_Connectors :
  node_annotated_connectors<RE_Dominion>
{
 RE_Annotated_Connectors(const RE_Connectors& conn,
   caon_ptr<RE_Connection> cion)
   : node_annotated_connectors<RE_Dominion>{conn, cion} {}

};


_RZNS(RECore)


#endif //RZ_RE_DOMINION__H
