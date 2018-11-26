
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)



QT += widgets multimedia


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

INCLUDEPATH += $$DSMAIN_SRC_GROUP_DIR
INCLUDEPATH += $$XPDF_SRC_GROUP_DIR
INCLUDEPATH += $$PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$QHYP_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR

INCLUDEPATH += $$XPDF_SRC_GROUP_DIR/xpdf/aconf
INCLUDEPATH += $$XPDF_SRC_GROUP_DIR/xpdf/goo

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES

DEFINES += DEFAULT_FOLDER=\\\"$$CPP_ROOT_DIR/assets\\\"
DEFINES += DEFAULT_ICON_FOLDER=\\\"$$CPP_ROOT_DIR/assets/icons\\\"

DEFINES += ABOUT_FILE_FOLDER=\\\"$$CPP_ROOT_DIR/about/about-files\\\"

DEFINES += SAMPLES_FOLDER=\\\"$$DATA_ROOT_DIR/samples\\\"


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS


HEADERS += \
  $$SRC_DIR/scignstage-3d-chart-dialog.h \


SOURCES += \
  $$SRC_DIR/scignstage-3d-chart-dialog.cpp \



LIBS += -L$$TARGETSDIR -ldsmain -lposit-lib


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
