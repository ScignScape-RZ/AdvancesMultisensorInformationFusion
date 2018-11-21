
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef KCM_REPORT_SYNTAX__H
#define KCM_REPORT_SYNTAX__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include <QVector>
#include <QTextStream>
#include <QMap>

#include "kcm-channel.h"


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)
USING_KANS(Kauvir)



KANS_(KCM)


class KCM_Report_Syntax
{
public:

 flags_(3)
  bool compress_fluxe_channel:1;
  bool identify_channel_names:1;
  bool identify_types:1;
  bool merge_fuxe_and_lambda:1;
  bool surround_carriers:1;
  bool types_after_values:1;
  bool types_colon_separator:1;
  bool use_block_statement_syntax:1;
  bool use_block_braces:1;
  bool use_keyword_for_function_types:1;
  bool write_empty_lambda_channel:1;
  bool write_empty_result_channel:1;
  bool arrow_before_result_channel:1;
  bool use_statement_annotations:1;
  bool use_thorin_type_names:1;
  bool use_thorin_array_types:1;
  bool comma_separate_channel_carriers:1;
  bool cast_after_expression:1;
  bool expand_array_indicators:1;
  bool surround_type_expressions:1;
 _flags

private:

 QMap<KCM_Channel::Kinds, QString> channel_kind_codes_;

 typedef QMap<KCM_Channel::Kinds, QString> channel_kind_codes_type;


public:

 KCM_Report_Syntax();


 ACCESSORS__RGET(channel_kind_codes_type ,channel_kind_codes)

 QString get_channel_kind_code(KCM_Channel::Kinds kind);

};


_KANS(KCM)


#endif //KCM_REPORT_SYNTAX__H
