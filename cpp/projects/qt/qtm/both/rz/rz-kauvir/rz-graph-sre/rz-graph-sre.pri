
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-sre

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_GROUP_DIR/rz-graph-core \


INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


LIBS += -L$$TARGETSDIR -lrz-graph-run

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES
DEFINES += RZ_CPP_GEN


TEMPLATE = lib


HEADERS += \
  $$SRC_DIR/rz-read-table-state.h \
  $$SRC_DIR/rz-sre-token.h \


SOURCES += \
  $$SRC_DIR/rz-sre-token.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
