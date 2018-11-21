
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-function-def

include(../build-group.pri)

TARGET = $$PROJECT_NAME


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_GROUP_DIR/rz-graph-build \
  $$SRC_GROUP_DIR/rz-graph-token  $$SRC_GROUP_DIR/rz-graph-core  \


INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


LIBS += -L$$TARGETSDIR -lrz-graph-token -lrz-graph-build \
 -lrz-graph-embed -lrz-graph-core

HEADERS += \
   $$SRC_DIR/rz-function-def-info.h \
   $$SRC_DIR/rz-type-formation.h \
   $$SRC_DIR/rz-function-def-syntax.h \


SOURCES += \
   $$SRC_DIR/rz-function-def-info.cpp \
   $$SRC_DIR/rz-type-formation.cpp \
   $$SRC_DIR/rz-function-def-syntax.cpp \

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
