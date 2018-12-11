
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-command-runtime

QT += widgets

include(../build-group.pri)

INCLUDEPATH += $$SRC_GROUP_DIR

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR

HEADERS +=  \
  $$SRC_DIR/kcm-command-runtime-router.h \
  $$SRC_DIR/kcm-command-runtime-router-qob.h \
  $$SRC_DIR/kcm-command-runtime-argument.h \
  $$SRC_DIR/kcm-command-runtime-table.h \
  $$SRC_DIR/kcm-command-runtime-router-cast-schedule.h \


SOURCES +=  \
  $$SRC_DIR/kcm-command-runtime-router.cpp \
  $$SRC_DIR/kcm-command-runtime-argument.cpp \
  $$SRC_DIR/kcm-command-runtime-table.cpp \



CONFIG += no_keywords

DEFINES += USE_KANS

LIBS += -L$$TARGETSDIR -lkcm-scopes -lkauvir-code-model \
  -lkcm-command-package -lPhaonLib


contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
 {
  message(DEFINE\'ing USING_ECL)
  include(../../../../find-ecl-sexp.pri)
  LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge
 }
}

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
