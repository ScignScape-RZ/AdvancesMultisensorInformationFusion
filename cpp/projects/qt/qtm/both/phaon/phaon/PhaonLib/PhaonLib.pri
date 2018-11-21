
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = PhaonLib

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS


INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/phaon-namespace.h \
  $$SRC_DIR/phaon-class.h \
  $$SRC_DIR/phaon-function.h \
  $$SRC_DIR/phaon-channel-group-table.h \
  $$SRC_DIR/phaon-symbol-scope.h \
  $$SRC_DIR/phaon-function-vector.h \
  $$SRC_DIR/phaon-runner.h \


SOURCES += \
  $$SRC_DIR/phaon-namespace.cpp \
  $$SRC_DIR/phaon-class.cpp \
  $$SRC_DIR/phaon-function.cpp \
  $$SRC_DIR/phaon-channel-group-table.cpp \
  $$SRC_DIR/phaon-symbol-scope.cpp \
  $$SRC_DIR/phaon-function-vector.cpp \
  $$SRC_DIR/phaon-runner.cpp \


LIBS += -L$$TARGETSDIR  -lkauvir-code-model \
  -lkcm-command-package -lkcm-scopes \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

