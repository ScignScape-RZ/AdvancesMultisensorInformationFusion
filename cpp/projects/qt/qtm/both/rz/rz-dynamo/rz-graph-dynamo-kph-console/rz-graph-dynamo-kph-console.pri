
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-dynamo-kph-console


include(../build-group.pri)

include(../../../../find-ecl-sexp.pri)


TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR


INCLUDEPATH += $$SEXP_DIR
INCLUDEPATH += $$SEXP_DIR/pingus/

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS

DEFINES += RZ_KPH_DIR=\\\"$$ROOT_DIR/scripts/rz-kph\\\"
DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"


SOURCES += \
  $$SRC_DIR/main.cpp \




LIBS += -L$$TARGETSDIR -lkcm-lisp-bridge  \
  -lkauvir-code-model -lkauvir-type-system -lrz-dynamo-generator

LIBS += -L$$TARGETSDIR -lkcm-command-package -lkcm-command-runtime \
   -lkcm-direct-eval -lfn-doc -lPhaonLib -lkph-generator


# R/Z ...

LIBS += -L$$TARGETSDIR  \
   -lrz-graph-core \
   -lrz-graph-token \
   -lrz-graph-code \
   -lrz-graph-visit \
   -lrz-code-generators \
   -lrz-graph-build \
   -lrz-graph-valuer \
   -lrz-graph-embed \
   -lrz-graph-embed-run \
   -lrz-graph-run \
   -lrz-graph-sre \
   -lrz-function-def \
   -lrz-code-elements \
   -lkcm-scopes \
   -lbasic-functions \
   -lkcm-env \




LIBS += -L$$ECL_DIR -lecl
LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx

LIBS += -L$$TARGETSDIR -lsexpr

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

