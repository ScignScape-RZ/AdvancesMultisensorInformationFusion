
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-direct-eval

include(../build-group.pri)


INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR



HEADERS +=  \
  $$SRC_DIR/kcm-direct-eval.h \


LIBS += -L$$TARGETSDIR -lkcm-command-package  -lkcm-scopes \
  -lkauvir-code-model -lkcm-command-runtime


SOURCES +=  \
  $$SRC_DIR/kcm-direct-eval.cpp \


CONFIG += no_keywords

DEFINES += USE_KANS


contains(CHOICE_FEATURES, "kcm_ecl") \#/
{
 include(../../../../find-ecl-sexp.pri)
 LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge
}

contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  message(DEFINE\'ing ISO__USING_ECL)
  DEFINES += ISO__USING_ECL
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge
 }

 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-phaon--kph-generator) \#/
 {
  message(DEFINE\'ing ISO__USING_KPH_GEN)
  DEFINES += ISO__USING_KPH_GEN
 #? LIBS += -L$$TARGETSDIR -lkph-generator
 }
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
