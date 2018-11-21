
include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/op2.h \
  $$SRC_DIR/pack.h \
  $$SRC_DIR/posit.h \
  $$SRC_DIR/posit_types.h \
  $$SRC_DIR/util.h \


SOURCES += \
  $$SRC_DIR/posit.cpp \
  $$SRC_DIR/op2.c \
  $$SRC_DIR/pack.c \
  $$SRC_DIR/util.c \

