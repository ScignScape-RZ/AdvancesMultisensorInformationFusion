
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += network

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge

INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR

#INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/application-model.h \
  $$SRC_DIR/application-test-model.h \

SOURCES += \
  $$SRC_DIR/application-model.cpp \
  $$SRC_DIR/application-test-model.cpp \


exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/tests-kph--kauvir-phaon--kauvir-phaon) \#/
{
 message(DEFINE\'ing USING_KPH)
 DEFINES += USING_KPH
 LIBS += -L$$TARGETSDIR  -lkauvir-phaon \

}


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
