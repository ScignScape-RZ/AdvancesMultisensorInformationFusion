
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-config-model.h"

#include <QDebug>

#include "kans.h"

#include "textio.h"

USING_KANS(TextIO)

USING_KANS(DSM)


Application_Config_Model::Application_Config_Model()
 : usrl_(User_Levels::N_A), insert_text_{{
     { "xpdf",
      {{{"external/xpdf/xpdf"},
       {"USING_XPDF"},
       {""} }}},

    { "ss3d",
      {{{"qscign/ScignStage/ScignStage-3d-chart"},
       {"USING_SCIGNSTAGE_3D"},
       {"ScignStage-3d-chart"} }}},

    { "kph",
      {{
       {
        "kauvir/kauvir-kcm/kauvir-type-system",
        "kauvir/kcm-runtime-eval/kcm-scopes",
        "kauvir/kauvir-kcm/kauvir-code-model",
        "kauvir/kauvir-runtime/kcm-command-package",
        "phaon/phaon/PhaonLib",
        "kauvir/kauvir-runtime/kcm-command-runtime",
        "kauvir/kcm-runtime-eval/kcm-direct-eval",
        "tests-kph/kauvir-phaon/kauvir-phaon",
        "phaon/phaon/phaon-console",
        "tests-kph/kauvir-phaon/kauvir-phaon-console",
        "dataset/application-model/application-model",
        "dataset/application-model/application-model-test-dialog",
        "dataset/application-model/amtd-console",
        "tests-kph/kauvir-phaon/kph-tcp-console",
        "phaon/phaon-xml/phaon-xml",
        "phaon/phaon-xml/phaon-xml-console",
       },

       {"USING_KPH"},
       {""} }}}
                }}
{


}

void Application_Config_Model::parse_config_code(QString cc)
{
 if(cc.startsWith("gen_test__"))
 {
  gen_test_ = ".gen.txt";
  cc = cc.mid(10);
 }

 qDebug() << cc;
 int index = cc.indexOf('-');

 int ul = cc.mid(index + 1).toInt();
 cc = cc.left(index);

 usrl_ = (User_Levels) ul;
  qDebug() << ul;

 if(cc.contains("xq"))
 {
  insert_text_["xpdf"][0].pri_libs.append(
    QString("libqtpng libqtfreetyped").split(' '));
 }
 else if(cc.contains("xs"))
 {
  insert_text_["xpdf"][0].pri_libs.append(
    QString("png freetype").split(' '));
 }
 else
   insert_text_.remove("xpdf");
}

QString Application_Config_Model::insert_to_defines(QString file_path, QString& result)
{
 load_file(file_path, result);

 QString locator = "\n//__CUSTOM_DEFINES__//\n";

 int index = result.indexOf(locator);

 if(index == -1)
   return file_path += ".err.txt";

 index += locator.size();

 QString insert;

 QMapIterator<QString, QList<Gen_Targets>> it(insert_text_);

 while(it.hasNext())
 {
  it.next();
  for(QString def : it.value()[0].defines)
  {
   insert += QString("#define %1\n").arg(def);
  }
 }

 result.replace(index, 0, insert);

 return file_path += gen_test_;
}
