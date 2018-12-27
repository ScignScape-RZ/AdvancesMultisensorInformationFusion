
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
 #INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge

INCLUDEPATH += $$APPLICATION_MODEL_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DEFAULT_KPH_FOLDER=\\\"$$CPP_ROOT_DIR/kph\\\"


#INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
#  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
#  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS

DEFINES += DEFINES_SRC_FOLDER=\\\"$$SRC_ROOT_DIR/_defines\\\"
DEFINES += CHOICES_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_choices\\\"
DEFINES += CUSTOM_LIBS_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/_custom_libs\\\"
DEFINES += UNIBUILD_PRI_FOLDER=\\\"$$CPP_ROOT_DIR/projects/qt/qtm/unibuild\\\"


HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


LIBS += -L$$TARGETSDIR -lapplication-model -lconfig-dialog


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
