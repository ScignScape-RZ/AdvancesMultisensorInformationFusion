
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

TEMPLATE = app


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$SCIGNSTAGE_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR

INCLUDEPATH += $$CONFIG_SRC_GROUP_DIR
INCLUDEPATH += $$APPLICATION_MODEL_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


DEFINES += SAMPLES_FOLDER=\\\"$$DATA_ROOT_DIR/samples\\\"
DEFINES += SCREENSHOTS_FOLDER=\\\"$$ROOT_DIR/screenshots\\\"
DEFINES += DATA_FOLDER=\\\"$$DATA_ROOT_DIR\\\"

DEFINES += DEFAULT_ICON_FOLDER=\\\"$$CPP_ROOT_DIR/assets/icons\\\"

DEFINES += DEFINES_SRC_FOLDER=\\\"$$SRC_ROOT_DIR/_defines\\\"
DEFINES += CHOICES_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_choices\\\"
DEFINES += CUSTOM_LIBS_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_custom_libs\\\"
DEFINES += UNIBUILD_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/unibuild\\\"



DEFINES += USE_KANS
DEFINES += USE_RZNS
DEFINES += USE_QSNS

INCLUDEPATH += $$POSIT_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/test-functions.h \
  $$SRC_DIR/graphic-dialog-container.h


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/test-functions.cpp \
  $$SRC_DIR/graphic-dialog-container.cpp


LIBS += -L$$TARGETSDIR -ldsmain  -lposit-lib  -lScignStage-tree-table \
    -lScignStage-2d-chart  -lapplication-model  -lconfig-dialog  \


contains(CHOICE_FEATURES, "xpdf") \#/
{
 #? message(DEFINE\'ing USING_XPDF)
#?  DEFINES += USING_XPDF
 LIBS += -L$$TARGETSDIR -lxpdf
}

contains(CHOICE_FEATURES, "ss3d") \#/
{
 LIBS += -L$$TARGETSDIR -lScignStage-3d-chart
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
 include(../../../../find-ecl-sexp.pri)
 LIBS += -L$$ECL_DIR -lecl
 LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
 message($$ECL_DIR)
}

contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/qscign--ScignStage--ScignStage-3d-chart) \#/
 {
  message(DEFINE\'ing ISO__USING_SCIGNSTAGE_3D)
  DEFINES += ISO__USING_SCIGNSTAGE_3D
  LIBS += -L$$TARGETSDIR -lScignStage-3d-chart
 }

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

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
  message(DEFINE\'ing ISO__USING_ECL)
  DEFINES += ISO__USING_ECL
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$ECL_DIR -lecl
  LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
  message($$ECL_DIR)
 }
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
