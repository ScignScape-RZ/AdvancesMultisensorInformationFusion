
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

QT += widgets network

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

#INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge

INCLUDEPATH += $$KAUVIR_PHAON_SRC_GROUP_DIR
INCLUDEPATH += $$SCIGNSTAGE_SRC_GROUP_DIR

#INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


#INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
#  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
#  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/application-model.h \
  $$SRC_DIR/application-test-model.h \
  $$SRC_DIR/application-config-model.h \


SOURCES += \
  $$SRC_DIR/application-model.cpp \
  $$SRC_DIR/application-test-model.cpp \
  $$SRC_DIR/application-config-model.cpp \


LIBS += -L$$TARGETSDIR  -lScignStage-tree-table

contains(CHOICE_FEATURES, "kph") \#/
{
 #?message(DEFINE\'ing USING_KPH)
 #?DEFINES += USING_KPH
 LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-phaon -lkauvir-code-model
}


contains(CHOICE_FEATURES, "iso-choice") \#/
{
 exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/tests-kph--kauvir-phaon--kauvir-phaon) \#/
 {
  message(DEFINE\'ing ISO__USING_XPDF)
  DEFINES += ISO__USING_KPH
  LIBS += -L$$TARGETSDIR -lPhaonLib -lkauvir-phaon -lkauvir-code-model
 }
}


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
