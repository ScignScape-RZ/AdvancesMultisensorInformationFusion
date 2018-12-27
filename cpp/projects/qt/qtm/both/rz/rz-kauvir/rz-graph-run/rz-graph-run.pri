
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-run

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR  $$SRC_GROUP_DIR/rz-graph-core  \
 $$SRC_GROUP_DIR/rz-graph-valuer  $$SRC_GROUP_DIR/rz-graph-token \
 $$SRC_GROUP_DIR/rz-graph-build


INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


LIBS += -L$$TARGETSDIR -lrz-graph-valuer -lrz-graph-token -lrz-graph-build \
  -lrz-graph-core -lrz-graph-embed


HEADERS += \
   $$SRC_DIR/rz-lisp-graph-core-function-declarations.h \
   $$SRC_DIR/rz-temp-cases.h \
   $$SRC_DIR/functions/rz-lisp-graph-function-family-enum.h \
   $$SRC_DIR/functions/core-functions-v-v.h \
   $$SRC_DIR/functions/core-functions-valuer-n-t.h \
   $$SRC_DIR/functions/core-functions-valuer-n-s-s.h \
   $$SRC_DIR/functions/core-functions-valuer-n-s.h \
   $$SRC_DIR/functions/core-functions-valuer-n.h \
   $$SRC_DIR/functions/core-functions-valuer-cb.h \
   $$SRC_DIR/functions/core-functions-valuer-rn.h \
   $$SRC_DIR/functions/core-functions-t-v.h \
   $$SRC_DIR/functions/core-functions-tv.h \
   $$SRC_DIR/functions/core-functions-t-c.h \
   $$SRC_DIR/functions/core-functions-tc.h \
   $$SRC_DIR/functions/core-functions-t.h \
   $$SRC_DIR/functions/core-functions-s.h \
   $$SRC_DIR/functions/core-functions-c-t.h \
   $$SRC_DIR/functions/core-functions-c-c.h \
   $$SRC_DIR/functions/core-functions-c.h \
   $$SRC_DIR/functions/core-functions-out.h \
   $$SRC_DIR/functions/rz-lisp-graph-run-router.h \
   $$SRC_DIR/functions/rz-lisp-graph-function-map.h \
   $$SRC_DIR/functions/rz-lisp-graph-function-families.h \
   $$SRC_DIR/functions/graph-call-v-v.h \
   $$SRC_DIR/functions/graph-call-v-t.h \
   $$SRC_DIR/functions/graph-call-t-v.h \
   $$SRC_DIR/functions/graph-call-tv.h \
   $$SRC_DIR/functions/graph-call-t-c.h \
   $$SRC_DIR/functions/graph-call-tc.h \
   $$SRC_DIR/functions/graph-call-t.h \
   $$SRC_DIR/functions/graph-call-s.h \
   $$SRC_DIR/functions/graph-call-c-t.h \
   $$SRC_DIR/functions/graph-call-c-c.h \
   $$SRC_DIR/functions/graph-call-c.h \
   $$SRC_DIR/rz-lisp-graph-function-info.h \
   $$SRC_DIR/rz-lisp-graph-function-info.h \
   $$SRC_DIR/token/rz-graph-run-token.h \
   $$SRC_DIR/rz-lisp-graph-runner.run-from-node.h \
   $$SRC_DIR/rz-lisp-graph-runner.h \
   $$SRC_DIR/rz-lisp-graph-core-runner.h \
   $$SRC_DIR/rz-lisp-graph-core-runner.templates.h \
   $$SRC_DIR/rz-lisp-graph-core-function-declarations.h \
   $$SRC_DIR/rz-temp-cases.h \


SOURCES += \
   $$SRC_DIR/rz-lisp-graph-core-runner.cpp \
   $$SRC_DIR/token/rz-graph-run-token.cpp \
   $$SRC_DIR/rz-lisp-graph-runner.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
