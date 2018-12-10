
#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR
INCLUDEPATH += $$KAUVIR_KCM_SRC_GROUP_DIR $$KAUVIR_KCM_SRC_GROUP_DIR/kcm-lisp-bridge

INCLUDEPATH += $$POSIT_SRC_GROUP_DIR

exists($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/kauvir--kauvir-kcm--kcm-lisp-bridge) \#/
{
 #? INCLUDEPATH += $$SEXP_DIR
 #? INCLUDEPATH += $$SEXP_DIR/pingus/
}


LIBS += -L$$TARGETSDIR -lposit-lib

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$RZ_KAUVIR_SRC_GROUP_DIR \
  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-core  $$RZ_KAUVIR_SRC_GROUP_DIR/rz-graph-token  \
  $$RELAE_SRC_GROUP_DIR  $$KAUVIR_KCM_SRC_GROUP_DIR


CONFIG += no_keywords

DEFINES += USE_KANS
DEFINES += USE_RZNS



HEADERS += \
  $$SRC_DIR/range-int.h \
  $$SRC_DIR/range-dbl.h \
  $$SRC_DIR/pri.h \
  $$SRC_DIR/precon.h \
  $$SRC_DIR/test-sample.h \
  $$SRC_DIR/test-series.h \


SOURCES += \
  $$SRC_DIR/test-sample.cpp \
  $$SRC_DIR/test-series.cpp \

#message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
