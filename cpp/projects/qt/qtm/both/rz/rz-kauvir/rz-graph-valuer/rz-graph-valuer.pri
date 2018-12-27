
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-valuer

include(../build-group.pri)

TARGET = $$PROJECT_NAME


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR $$SRC_GROUP_DIR/rz-graph-build \
  $$SRC_GROUP_DIR/rz-clasp-code  $$SRC_GROUP_DIR/rz-graph-token  $$SRC_GROUP_DIR/rz-graph-core


INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


LIBS += -L$$TARGETSDIR -lrz-graph-token -lrz-graph-build \
 -lrz-graph-embed -lrz-graph-core -lrz-function-def -lrz-code-elements


HEADERS += \
   $$SRC_DIR/valuer/rz-lisp-graph-valuer.h \
   $$SRC_DIR/valuer/rz-lisp-symbol.h \
   $$SRC_DIR/scope/rz-lisp-graph-scope-token.h \
   $$SRC_DIR/scope/rz-lisp-graph-lexical-scope.h \
   $$SRC_DIR/scope/rz-lisp-graph-block-info.h \
   $$SRC_DIR/rz-lisp-graph-rvalue.h \
   $$SRC_DIR/valuer/rz-opaque-call.h \
   $$SRC_DIR/valuer/rz-opaque-type-symbol.h \
   $$SRC_DIR/vector/rz-lisp-vector.h \
   $$SRC_DIR/vector/rz-lisp-map.h \
   $$SRC_DIR/vector/rz-string-plex.h \
   $$SRC_DIR/string/rz-string.h \
   $$SRC_DIR/string/rz-keyword.h \
   $$SRC_DIR/string/rz-match-literal.h \


SOURCES += \
   $$SRC_DIR/valuer/rz-lisp-graph-valuer.cpp \
   $$SRC_DIR/valuer/rz-lisp-symbol.cpp \
   $$SRC_DIR/scope/rz-lisp-graph-scope-token.cpp \
   $$SRC_DIR/scope/rz-lisp-graph-lexical-scope.cpp \
   $$SRC_DIR/scope/rz-lisp-graph-block-info.cpp \
   $$SRC_DIR/rz-lisp-graph-rvalue.cpp \
   $$SRC_DIR/valuer/rz-opaque-call.cpp \
   $$SRC_DIR/valuer/rz-opaque-type-symbol.cpp \
   $$SRC_DIR/vector/rz-lisp-vector.cpp \
   $$SRC_DIR/vector/rz-lisp-map.cpp \
   $$SRC_DIR/vector/rz-string-plex.cpp \
   $$SRC_DIR/string/rz-string.cpp \
   $$SRC_DIR/string/rz-keyword.cpp \
   $$SRC_DIR/string/rz-match-literal.cpp \

   
message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
