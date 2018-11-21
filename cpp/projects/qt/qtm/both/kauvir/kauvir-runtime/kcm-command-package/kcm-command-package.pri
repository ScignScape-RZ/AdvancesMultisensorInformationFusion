
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kcm-command-package

include(../build-group.pri)

DEFINES += USE_KANS

INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR


HEADERS +=  \
  $$SRC_DIR/kcm-command-package.h  \


SOURCES +=  \
  $$SRC_DIR/kcm-command-package.cpp \


CONFIG += no_keywords



LIBS += -L$$TARGETSDIR -lkauvir-code-model


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)

