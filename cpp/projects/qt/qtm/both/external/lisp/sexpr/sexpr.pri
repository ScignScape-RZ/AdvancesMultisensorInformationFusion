
include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR


DEFINES += USE_QSNS

HEADERS += \
  $$SRC_DIR/sexpresso.hpp \
  $$SRC_DIR/sexp/error.hpp \
  $$SRC_DIR/sexp/io.hpp \
  $$SRC_DIR/sexp/lexer.hpp \
  $$SRC_DIR/sexp/parser.hpp \
  $$SRC_DIR/sexp/util.hpp \
  $$SRC_DIR/sexp/value.hpp \


SOURCES += \
  $$SRC_DIR/io.cpp \
  $$SRC_DIR/lexer.cpp \
  $$SRC_DIR/parser.cpp \
  $$SRC_DIR/sexpresso.cpp \
  $$SRC_DIR/util.cpp \
  $$SRC_DIR/value.cpp \

