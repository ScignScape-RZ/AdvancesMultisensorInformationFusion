
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

QT += widgets

PROJECT_NAME = rz-dynamo-runtime-console

include(../build-group.pri)

include(../../../../find-ecl-sexp.pri)


TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR

CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += RZ_DIR=\\\"$$ROOT_DIR/scripts/rz\\\"


SOURCES += \
  $$SRC_DIR/main.cpp \



LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge  \
  -lkauvir-code-model -lkauvir-type-system -lrz-dynamo-generator

LIBS += -L$$TARGETSDIR -lkcm-command-package -lkcm-command-runtime \
  -lkcm-scopes -lkcm-direct-eval -lbasic-functions -lfn-doc -lkcm-env -lPhaonLib


LIBS += -L$$ECL_DIR -lecl
LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx

LIBS += -L$$TARGETSDIR -lsexpr

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
