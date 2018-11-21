
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

QT += network

PROJECT_NAME = rz-dynamo-generator

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS

HEADERS += \
  $$SRC_DIR/rz-dynamo-generator.h \
  $$SRC_DIR/rz-dynamo-nested-acc.h \

SOURCES += \
  $$SRC_DIR/rz-dynamo-generator.cpp \
  $$SRC_DIR/rz-dynamo-nested-acc.cpp \


LIBS += -L$$TARGETSDIR  -lkauvir-code-model

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

