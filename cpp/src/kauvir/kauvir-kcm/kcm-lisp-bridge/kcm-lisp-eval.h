
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LISP_EVAL__H
#define KCM_LISP_EVAL__H

#include "kans.h"

#include "defines.h"


#ifdef USING_ECL

#include <QObject>
#include <QDir>

#include <functional>

#include "kauvir-code-model/kauvir-code-model.h"

#include "multistep-token.h"

#include "cl-cxx/object.hpp"

KANS_CLASS_DECLARE(Dynamo ,RZ_Dynamo_Generator)

KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)

USING_KANS(KCM)
USING_KANS(Dynamo)
USING_KANS(CMD)

class QTextStream;

KANS_(KCL)

class KCM_Lisp_Embed_Environment;
class KCM_Lisp_Runtime;
class KCM_Lisp_Runtime_Argument;



class KCM_Lisp_Eval
{
 KCM_Lisp_Embed_Environment* env_;
 KCM_Lisp_Runtime* kcm_lisp_runtime_;

 std::function<void(QString, QString&, const QStringList&, QString)> embed_callback_;

 typedef std::function<KCM_Channel_Bridge*(KCM_Command_Runtime_Router& kcrr)>
   make_kcm_channel_bridge_fn_type;


public:

 KCM_Lisp_Eval(KCM_Lisp_Embed_Environment* env);
 KCM_Lisp_Eval(KCM_Lisp_Embed_Environment* env, QTextStream& qts);

 ACCESSORS(KCM_Lisp_Embed_Environment* ,env)
 ACCESSORS(std::function<void(QString, QString&, const QStringList&, QString)> ,embed_callback)
 ACCESSORS(KCM_Lisp_Runtime* ,kcm_lisp_runtime)

 static make_kcm_channel_bridge_fn_type get_make_kcm_channel_bridge_fn_type(make_kcm_channel_bridge_fn_type fn = nullptr);

 enum class Opaque_Lisp_Value_Types
 {
  N_A, Fixnum_U32, Str, Held_List
  // etc. ...
 };

 QString initial_generated_string_;

 void eval_quicklisp_setup();

 static void parse_opaque_lisp_value(Opaque_Lisp_Value olv, Opaque_Lisp_Value_Types& olvt, QString& encoded_value);


 static QString cl_arglist_to_qstring(cl_cxx_backend::cl_arglist arglist);
 static QString cl_arglist_to_qstring(cl_cxx_backend::cl_arglist arglist, int index);

 static void* opaque_lisp_value_to_pVoid(Opaque_Lisp_Value olv);

 static QString get_string_rep(cl_object clo);

 static void run_source_function(KCM_Command_Runtime_Router& kcrr, quint64 qclo);
 static void eval_lisp_callable_deferred_value(quint64 qclo, quint64& result, QString convention);

 void check_flags_replace(QString& eval_text);

 QString parse_arglist_to_queues(cl_cxx_backend::cl_arglist arglist);

 void clear_queues();

 void define_callback(cl_cxx_backend::callback_t cb,
  QString package_name, QString symbol_name, void* argument);

 void test_callback(cl_cxx_backend::callback_t cb);

 void prepare_callbacks();

 static void run_held_lisp_list(quint64 lisp_val, quint64& mem);

 void eval_held_form(quint64 qclo);

 void prepare_dynamo_callbacks(void** pass_on);

 void cl_arglist_to_arguments(cl_cxx_backend::cl_arglist arglist,
   QVector<KCM_Lisp_Runtime_Argument>& klras);

 QString cl_arglist_to_opaque_arguments(cl_cxx_backend::cl_arglist arglist,
   QVector<KCM_Lisp_Runtime_Argument>& klras);

 static void cl_arglist_to_flagged_strings(int size, int offset, cl_cxx_backend::cl_arglist arglist,
   QStringList& flags, QStringList& strings);

 static void cl_arglist_to_tagged_strings(int size, int offset, cl_cxx_backend::cl_arglist arglist,
   QStringList& strings);

 static void cl_arglist_to_ms_tokens(int size, int offset, cl_cxx_backend::cl_arglist arglist,
   QList<MS_Token>& tokens);

 static MS_Token cl_object_to_ms_token(cl_object clo);


 static void cl_arglist_to_strings(int size, int offset, cl_cxx_backend::cl_arglist arglist,
   QStringList& strings);

 static QString cl_object_to_qstring(cl_object clo);
 static cl_object qstring_to_cl_object(QString qs);

 static quint64 encode_value_to_cl_object(const KCM_Type_Object* kto, void* val);

 static quint64 encode_encoded_value_to_cl_object(const KCM_Type_Object* kto, QString);

 QString eval_string(QString eval_text);

 void eval_loaded_file(QString eval_text, QString extra_support, QString file_name);

 void eval_file(QString file_name, int load_depth = 0, QString top_file = QString());

 void eval_script_file(QString file_name, int load_depth = 0, QString top_file = QString());

 QString eval(QString eval_text, QString extra_support, QString file_name = QString(), int load_depth = 0, QString top_file = QString(), QDir* default_dir = nullptr);

 void eval_raw_file(QString file_name);

 void eval_raw_file_via_load(QString file_name);

 static cl_object eval_raw_text(QString eval_text);

 void minimal_eval(QString eval_text);

};

_KANS(KCL)

#else

KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Router)
USING_KANS(CMD)

KANS_(KCL)

struct KCM_Lisp_Eval
{
 static void run_held_lisp_list(quint64 lisp_val, quint64& mem) {}
 static void run_source_function(KCM_Command_Runtime_Router& kcrr, quint64 qclo){}
};

_KANS(KCL)

#endif // USING_KCL


#endif //KCM_LISP_EVAL__H
