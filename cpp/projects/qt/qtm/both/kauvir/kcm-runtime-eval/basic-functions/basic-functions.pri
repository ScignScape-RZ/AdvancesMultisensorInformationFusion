
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = basic-functions


include(../build-group.pri)

include(../../../../find-ecl-sexp.pri)


INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR  $$SRC_GROUP_DIR  \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system


INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_RUNTIME_SRC_GROUP_DIR


HEADERS +=  \
  $$SRC_DIR/rz-dynamo-basic-functions.h \


SOURCES +=  \
  $$SRC_DIR/rz-dynamo-basic-functions.cpp \
  $$SRC_DIR/rz-dynamo-test-functions.cpp \

CONFIG += no_keywords

DEFINES += USE_KANS

LIBS += -L$$TARGETSDIR -lkauvir-code-model -lkcm-command-runtime \
  -lkcm-lisp-bridge -lfn-doc -lPhaonLib

