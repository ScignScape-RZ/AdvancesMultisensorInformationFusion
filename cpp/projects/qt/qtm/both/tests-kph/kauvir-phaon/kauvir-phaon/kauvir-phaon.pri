
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = kauvir-phaon

include(../build-group.pri)




INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


CONFIG += no_keywords


DEFINES += USE_KANS



INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-type-system \
  $$KAUVIR_KCM_SRC_GROUP_DIR/kauvir-code-model


HEADERS += \
  $$SRC_DIR/kph-command-package.h \
  $$SRC_DIR/kph-carrier.h \
  $$SRC_DIR/kph-channel.h \


SOURCES += \
  $$SRC_DIR/kph-command-package.cpp \
  $$SRC_DIR/kph-carrier.cpp \
  $$SRC_DIR/kph-channel.cpp \

LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-code-model -lkauvir-type-system \
   -lkcm-command-package -lkcm-direct-eval -lkcm-scopes


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
