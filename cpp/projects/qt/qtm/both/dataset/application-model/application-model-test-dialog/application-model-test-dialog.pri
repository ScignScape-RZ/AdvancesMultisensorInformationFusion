
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge

INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"
DEFINES += DEFAULT_ICON_FOLDER=\\\"$$CPP_ROOT_DIR/assets/icons\\\"
DEFINES += ARCHIVE_ROOT_FOLDER=\\\"$$ROOT_DIR\\\"

INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR

#INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
#  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
#  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/application-model-test-dialog.h \


SOURCES += \
  $$SRC_DIR/application-model-test-dialog.cpp \
  $$SRC_ROOT_DIR/add-minimize-frame.cpp \


LIBS += -L$$TARGETSDIR -lapplication-model

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
