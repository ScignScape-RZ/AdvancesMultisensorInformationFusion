
include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


LIBS += -L$$TARGETSDIR -lposit-lib

HEADERS += \


SOURCES += \
  $$SRC_DIR/main.cpp \


