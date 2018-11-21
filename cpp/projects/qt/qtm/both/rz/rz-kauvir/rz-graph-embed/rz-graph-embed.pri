
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-embed

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR  \
   $$SRC_GROUP_DIR/rz-graph-token $$SRC_GROUP_DIR/rz-graph-build \
   $$SRC_GROUP_DIR/rz-graph-core

INCLUDEPATH += $$QHYP_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


LIBS += -L$$TARGETSDIR  -lrz-graph-build -lrz-graph-token -lrz-graph-core


HEADERS += \
   $$SRC_DIR/rz-graph-embed-package.h \
   $$SRC_DIR/rz-graph-embed-token.h \
   $$SRC_DIR/rz-graph-run-embedder.h \
   $$SRC_DIR/rz-graph-embed-check.h \



SOURCES += \
   $$SRC_DIR/rz-graph-embed-package.cpp \
   $$SRC_DIR/rz-graph-embed-token.cpp \
   $$SRC_DIR/rz-graph-run-embedder.cpp \
   $$SRC_DIR/rz-graph-embed-check.cpp \

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
