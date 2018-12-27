
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QtEndian>

#include <QtGlobal>
#include <QtCore>

#include <QDebug>

#include "rzns.h"

#include "rz-graph-core/kernel/document/rz-re-document.h"
#include "rz-graph-core/output/rz-re-pre-normal-lisp.h"

#include "rz-graph-code/prerun/rz-re-prerun-tokens.h"
#include "rz-graph-code/prerun/rz-re-prerun-normalize.h"
#include "rz-graph-code/prerun/rz-re-prerun-anticipate.h"

#include "rz-graph-visit/rz-lisp-graph-visitor.h"
#include "rz-code-generators/rz-dynamo-output.h"


#include "sexp/parser.hpp"
#include "lisp/writer.hpp"


#include "kcm-lisp-bridge/kcm-lisp-runtime.h"

#include "kans.h"

#include "kauvir-type-system/kauvir-universal-class.h"

#include "basic-functions/rz-dynamo-basic-functions.h"

#include "fn-doc/fn-doc.h"
#include "kcm-env/kcm-env.h"

#include "rz-graph-visit/rz-lisp-graph-visitor-dynamo.h"

#include "kcm-lisp-bridge/kcm-lisp-bridge.h"
#include "kcm-lisp-bridge/kcm-lisp-embed-environment.h"
#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "kauvir-code-model/kauvir-code-model.h"
#include "kauvir-code-model/kcm-channel-group.h"

#include "kcm-command-runtime/kcm-command-runtime-table.h"
#include "kcm-scopes/kcm-scope-system.h"
#include "kcm-direct-eval/kcm-direct-eval.h"

#include "textio.h"

#include "rz-graph-visit/rz-lisp-graph-visitor-dynamo.h"

#include <functional>
#include <QDebug>
#include <QRegularExpression>


USING_KANS(KCM)
USING_KANS(KCL)
USING_KANS(TextIO)


void compile_rz(QString file_name)
{
 QString result;

 RE_Document* doc = new RE_Document(file_name);
 doc->parse();

 doc->report_graph(file_name + ".txt");

 RE_Pre_Normal_Lisp prenorm(doc);
 prenorm.output("..prenorm.txt");

 RE_Prerun_Tokens tokens(doc);
 tokens.output("..prenorm2.txt");


 RE_Prerun_Normalize normalize(*doc->graph());


 caon_ptr<RZ_Lisp_Graph_Visitor> visitor = normalize.scan();

 visitor->set_document_directory(doc->local_directory());

 RZ_Lisp_Graph_Visitor_Dynamo visitor_dynamo(*visitor);
 RZ_Dynamo_Output rdo(visitor_dynamo);

 visitor->set_dynamo_output(&rdo);

 doc->report_graph(file_name + ".re1.txt");
 RE_Pre_Normal_Lisp prenorm1(doc);
 prenorm1.output("..prenorm1.txt");
 RE_Prerun_Anticipate anticipate(*visitor);
 anticipate.scan([](RZ_Dynamo_Output& rzdo){rzdo.init_top_level_block();});

 QString output;
 QTextStream qts(&output);
 rdo.write(qts);
 QString result_file = doc->local_path() + ".cl";
 QFile outfile(result_file);
 if(outfile.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream out(&outfile);
  out << output;
  outfile.close();
 }
 result = output;

 result.prepend("\n(:|RZ_GENERATED| ");
 result.append(')');
 sexp::Value value = sexp::Parser::from_string(result.toStdString());
 QString clean_result_file = doc->local_path() + ".lisp";
 QFile clean_outfile(clean_result_file);

 if(clean_outfile.open(QIODevice::WriteOnly | QIODevice::Text))
 {
  QTextStream out(&clean_outfile);

  QString vstr = QString::fromStdString(value.str_with_indent(0));
  QString start = "\n(:|RZ_GENERATED| ";
  if(vstr.startsWith(start))
  {
   vstr = vstr.mid(start.length());
  }
  if(vstr.endsWith(')'))
  {
   vstr.chop(1);
  }

  out << vstr;
  clean_outfile.close();
 }
}

void prepare_runtime()
{
 qRegisterMetaType<KCM_Lisp_Bridge>();
 qRegisterMetaType<KCM_Lisp_Bridge*>();


 qRegisterMetaType<Fn_Doc>();
 qRegisterMetaType<Fn_Doc*>();


}

void run_dynamo(KCM_Lisp_Eval& kle, QString script_file, KCM_Env* kenv)
{
 kle.prepare_callbacks();

 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 Kauvir_Code_Model& kcm = *bridge.kcm();
 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table table(*type_system);
 kcm.set_table(&table);

 KCM_Scope_System scopes;
 kcm.set_scope_system(&scopes);

 kcm.init_scope_system();

 kenv->set_scopes(&scopes);
 kenv->set_kcm(&kcm);

 kenv->set_report_channel_group_fn([](Kauvir_Code_Model* kcm, KCM_Channel_Group* kcg)
 {
  QString qs;
  QTextStream qts(&qs);

  kcg->report(qts, *kcm, kcm->detailed_report_synax(),
    KCM_Channel::Code_Environments::Statement);

  qDebug() << qs;
 });

 init_basic_functions_kci(kcm);
 kle.eval_script_file(script_file);
}


void run_rz(KCM_Lisp_Embed_Environment& env, QString fn)
{
 qDebug() << "Compiling R/Z to PreDynamo: " << QString(RZ_DIR "/%1").arg(fn);

 compile_rz(QString(RZ_DIR "/%1").arg(fn));

 prepare_runtime();

 QString out_string;
 QTextStream qts(&out_string);

 KCM_Lisp_Eval kle(&env, qts);

 kle.prepare_callbacks();

 KCM_Lisp_Eval::get_make_kcm_channel_bridge_fn_type(&make_kcm_channel_bridge);
 KCM_Lisp_Runtime* lisp_runtime = kle.kcm_lisp_runtime();
 KCM_Lisp_Bridge& bridge = lisp_runtime->bridge();
 bridge.init_kcm();

 Kauvir_Code_Model& kcm = *bridge.kcm();

 kcm.set_direct_eval_fn(&kcm_direct_eval);
 kcm.set_make_kcm_command_package_from_channel_group_fn(&make_kcm_command_package_from_channel_group);
 kcm.set_make_kcm_command_package_fn(&make_kcm_command_package);


 kcm.create_and_register_type_object("Fn_Doc");
 kcm.create_and_register_type_object("Fn_Doc*");

 KCM_Env* kenv = new KCM_Env(nullptr);
 QString kenv_typename = "KCM_Env*";
 insert_envv(&kenv_typename, kenv);

 qDebug() << "Compiling PreDynamo to DynamoIR:" << QString(RZ_DIR "/%1").arg(fn);
 kle.eval_script_file(QString(RZ_DIR "/%1.lisp").arg(fn));
 qDebug() << "Saving DynamoIR to: " << QString(RZ_DIR "/%1.dyn.cl").arg(fn);
 QFile qf(QString(RZ_DIR "/%1.dyn.cl").arg(fn));


 if(qf.open(QIODevice::WriteOnly))
 {
  QTextStream os(&qf);
  os << out_string;
  qf.close();
 }

 qDebug() << "Running DynamoIR: " << QString(RZ_DIR "/%1.dyn.cl").arg(fn);

 run_dynamo(kle, QString(RZ_DIR "/%1.dyn.cl").arg(fn), kenv);

}

int main(int argc, char* argv[])
{
 KCM_Lisp_Embed_Environment env(argc, argv);

 QString lines = ::load_file(RZ_DIR "/m1.txt");

 QStringList qsl = lines.split('\n');

 QStringList fns;

 for(QString line : qsl)
 {
  QString fn = line.simplified();
  if(fn.isEmpty())
    continue;
  if(fn.startsWith(';'))
    continue;
  if(fn.startsWith('#'))
    continue;
  QRegularExpressionMatch rxm;
  if(fn.indexOf(QRegularExpression("\\(\\s*(\\d+)\\s*-\\s*(\\d+)\\s*\\)"), 0, &rxm))
  {
   int sn = rxm.captured(1).toInt();
   int en = rxm.captured(2).toInt();
   int s = rxm.capturedStart();
   int e = rxm.capturedEnd();
   for(int i = sn; i <= en; ++i)
   {
    QString nfn = fn;
    nfn.replace(s, e-s, QString::number(i));
    fns.push_back(nfn);
   }
   continue;
  }
  fns.push_back(fn);
 }

 for(QString fn : fns)
 {
  run_rz(env, fn);
 }

 return 0;
}


