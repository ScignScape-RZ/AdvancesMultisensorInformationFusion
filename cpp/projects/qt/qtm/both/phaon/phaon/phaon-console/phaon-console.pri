
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phaon-console

include(../build-group.pri)

TEMPLATE = app

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS



HEADERS += \
  $$SRC_DIR/test-functions.h \


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/test-functions.cpp \


LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-code-model -lkauvir-type-system \
   -lkcm-command-package -lkcm-direct-eval -lkcm-scopes -lkauvir-phaon -lkcm-command-runtime


contains(CHOICE_FEATURES, "kcm_ecl") \#/
{
 LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
 include(../../../../find-ecl-sexp.pri)
 LIBS += -L$$ECL_DIR -lecl
 LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
}


contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge -lrz-dynamo-generator
  message(DEFINE\'ing ISO__USING_ECL)
  DEFINES += ISO__USING_ECL
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$ECL_DIR -lecl
  LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx
 }
}




message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

