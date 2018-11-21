
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-lisp-bridge

include(../build-group.pri)



INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$RZ_DYNAMO_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR

CONFIG += no_keywords

include(../../../../find-ecl-sexp.pri)


DEFINES += USE_KANS

HEADERS += \
  $$SRC_DIR/kcm-lisp-bridge.h \
  $$SRC_DIR/kcm-lisp-runtime.h \
  $$SRC_DIR/kcm-lisp-runtime-argument.h \
  $$SRC_DIR/kcm-lisp-embed-environment.h \
  $$SRC_DIR/kcm-lisp-eval.h \



SOURCES += \
  $$SRC_DIR/kcm-lisp-bridge.cpp \
  $$SRC_DIR/kcm-lisp-runtime.cpp \
  $$SRC_DIR/kcm-lisp-runtime-argument.cpp \
  $$SRC_DIR/kcm-lisp-embed-environment.cpp \
  $$SRC_DIR/kcm-lisp-eval.cpp \


LIBS += -L$$TARGETSDIR -lrz-dynamo-generator -lkauvir-code-model \
  -lkcm-scopes

LIBS += -L$$ECL_DIR -lecl
LIBS += -L$$CL_CXX_DIR/install/lib64 -lcl_cxx


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)


