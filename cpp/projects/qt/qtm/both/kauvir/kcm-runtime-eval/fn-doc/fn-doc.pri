
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


PROJECT_NAME = fn-doc


include(../build-group.pri)


DEFINES += AR_ROOT_DIR=\\\"$$ROOT_DIR\\\"

DEFINES += USE_KANS

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-code-model

INCLUDEPATH += $$KCM_RUNTIME_EVAL_SRC_GROUP_DIR


HEADERS +=  \
  $$SRC_DIR/fn-doc.h \
  $$SRC_DIR/fn-doc-multi.h \

SOURCES +=  \
  $$SRC_DIR/fn-doc.cpp \
  $$SRC_DIR/fn-doc-multi.cpp \

CONFIG += no_keywords


LIBS += -L$$TARGETSDIR -lkcm-scopes -lkcm-env
