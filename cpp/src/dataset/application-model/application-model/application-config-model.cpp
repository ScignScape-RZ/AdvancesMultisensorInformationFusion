
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-config-model.h"

#include <QDebug>


#include "kans.h"

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
 qDebug() << cc;
 int index = cc.indexOf('-');

 int ul = cc.mid(index + 1).toInt();
 cc = cc.left(index);

 usrl_ = (User_Levels) ul;
  qDebug() << ul;

}
