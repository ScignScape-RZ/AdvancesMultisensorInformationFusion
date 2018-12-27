
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$POSIT_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += SAMPLES_FOLDER=\\\"$$DATA_ROOT_DIR/samples\\\"
DEFINES += DATA_FOLDER=\\\"$$DATA_ROOT_DIR\\\"

LIBS += -L$$TARGETSDIR -lposit-lib

CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS




SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -ldsmain


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
