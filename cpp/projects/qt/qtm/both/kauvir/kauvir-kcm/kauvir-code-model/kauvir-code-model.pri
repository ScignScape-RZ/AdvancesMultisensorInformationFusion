
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kauvir-code-model

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS

DEFINES += DEFAULT_PTR_BYTE_CODE=QT_POINTER_SIZE

HEADERS += \
  $$SRC_DIR/kauvir-code-model.h \
  $$SRC_DIR/kcm-carrier.h \
  $$SRC_DIR/kcm-channel.h \
  $$SRC_DIR/kcm-channel-group.h \
  $$SRC_DIR/kcm-channel-bridge.h \
  $$SRC_DIR/kcm-type-object.h \
  $$SRC_DIR/kcm-proxy-scope.h \
  $$SRC_DIR/kcm-expression.h \
  $$SRC_DIR/kcm-statement.h \
  $$SRC_DIR/kcm-block.h \
  $$SRC_DIR/kcm-file.h \
  $$SRC_DIR/kcm-overloadable-symbol.h \
  $$SRC_DIR/kcm-report-syntax.h \
  $$SRC_DIR/kcm-source-function.h \
  $$SRC_DIR/kcm-callable-value.h \
  $$SRC_DIR/kcm-function-package.h \


SOURCES += \
  $$SRC_DIR/kauvir-code-model.cpp \
  $$SRC_DIR/kcm-carrier.cpp \
  $$SRC_DIR/kcm-channel.cpp \
  $$SRC_DIR/kcm-channel-group.cpp \
  $$SRC_DIR/kcm-channel-bridge.cpp \
  $$SRC_DIR/kcm-type-object.cpp \
  $$SRC_DIR/kcm-proxy-scope.cpp \
  $$SRC_DIR/kcm-expression.cpp \
  $$SRC_DIR/kcm-statement.cpp \
  $$SRC_DIR/kcm-block.cpp \
  $$SRC_DIR/kcm-file.cpp \
  $$SRC_DIR/kcm-overloadable-symbol.cpp \
  $$SRC_DIR/kcm-report-syntax.cpp \
  $$SRC_DIR/kcm-source-function.cpp \
  $$SRC_DIR/kcm-callable-value.cpp \
  $$SRC_DIR/kcm-function-package.cpp \



LIBS += -L$$TARGETSDIR -lkauvir-type-system -lkcm-scopes


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

