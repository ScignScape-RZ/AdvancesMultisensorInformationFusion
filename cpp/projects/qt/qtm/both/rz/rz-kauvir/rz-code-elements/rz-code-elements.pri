
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-code-elements

include(../build-group.pri)


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR \
  $$SRC_GROUP_DIR/rz-graph-token \
  $$SRC_GROUP_DIR/rz-graph-core \

INCLUDEPATH += $$QHYP_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


TEMPLATE = lib


HEADERS += \
  $$SRC_DIR/rz-code-statement.h \
  $$SRC_DIR/rz-expression-review.h \


SOURCES += \
  $$SRC_DIR/rz-code-statement.cpp \
  $$SRC_DIR/rz-expression-review.cpp \


LIBS += -L$$TARGETSDIR -lrz-graph-core -lrz-graph-token  \
  -lrz-function-def


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
