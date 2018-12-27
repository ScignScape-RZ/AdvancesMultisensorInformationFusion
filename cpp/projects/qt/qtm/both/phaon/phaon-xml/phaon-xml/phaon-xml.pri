
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = phaon-xml

include(../build-group.pri)



INCLUDEPATH += $$SRC_DIR


CONFIG += no_keywords


DEFINES += USE_KANS




HEADERS += \
  $$SRC_DIR/phaon-xml-document.h \
  $$SRC_DIR/phaon-xml-line.h \

SOURCES += \
  $$SRC_DIR/phaon-xml-document.cpp \
  $$SRC_DIR/phaon-xml-line.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)


