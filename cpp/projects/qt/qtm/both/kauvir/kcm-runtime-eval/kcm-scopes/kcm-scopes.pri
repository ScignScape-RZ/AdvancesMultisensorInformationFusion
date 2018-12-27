
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-scopes

include(../build-group.pri)

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system

DEFINES += USE_KANS

HEADERS +=  \
  $$SRC_DIR/kcm-scope-system.h \
  $$SRC_DIR/kcm-runtime-scope.h \
  $$SRC_DIR/kcm-lexical-scope.h \


SOURCES +=  \
  $$SRC_DIR/kcm-scope-system.cpp \
  $$SRC_DIR/kcm-runtime-scope.cpp \
  $$SRC_DIR/kcm-lexical-scope.cpp \


CONFIG += no_keywords


LIBS += -L$$TARGETSDIR


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

