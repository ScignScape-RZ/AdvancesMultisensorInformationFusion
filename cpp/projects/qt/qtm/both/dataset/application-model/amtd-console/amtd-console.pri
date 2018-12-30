
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
 #INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge
INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR


INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"


#INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
#  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
#  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS

HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lapplication-model-test-dialog  -lapplication-model \
   -lScignStage-tree-table -ldsmain -lposit-lib


contains(CHOICE_FEATURES, "xpdf") \#/
{
 LIBS += -L$$TARGETSDIR -lxpdf
}

contains(CHOICE_FEATURES, "kph") \#/
{
 LIBS += -L$$TARGETSDIR -lkcm-direct-eval -lkcm-scopes  -lkauvir-phaon \
   -lPhaonLib -lkauvir-code-model -lkcm-command-runtime -lkcm-command-package \
   -lkauvir-type-system
}

contains(CHOICE_FEATURES, "kcm_ecl") \#/
{
 LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
 message(DEFINE\'ing USING_ECL)
 include(../../../../find-ecl-sexp.pri)
 LIBS += -L$$ECL_DIR -lecl
 LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
}

contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/external--xpdf--xpdf) \#/
 {
  message(DEFINE\'ing ISO__USING_XPDF)
  DEFINES += ISO__USING_XPDF
  LIBS += -L$$TARGETSDIR -lxpdf
 }

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/tests-kph--kauvir-phaon--kauvir-phaon) \#/
 {
  message(DEFINE\'ing ISO__USING_KPH)
  DEFINES += ISO__USING_KPH
  LIBS += -L$$TARGETSDIR -lkcm-direct-eval -lkcm-scopes  -lkauvir-phaon \
    -lPhaonLib -lkauvir-code-model -lkcm-command-runtime -lkcm-command-package \
    -lkauvir-type-system
 }
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
