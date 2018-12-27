
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-token

include(../build-group.pri)


DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES


INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR \
  $$SRC_GROUP_DIR/rz-graph-core \

INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


HEADERS += \
    $$SRC_DIR/token/rz-lisp-token.h \
    $$SRC_DIR/token/token-kinds.h \
    $$SRC_DIR/types/run-types.h \
    $$SRC_DIR/types/run-type-list.h \
    $$SRC_DIR/types/type-codes.h \
    $$SRC_DIR/types/type-codes.namespaced.h \
    $$SRC_DIR/types/type-families.h \
    $$SRC_DIR/types/rz-type-variety.h \
    $$SRC_DIR/types/rz-type-object.h \
    $$SRC_DIR/valuer/rz-lisp-core-function.h \
    $$SRC_DIR/valuer/rz-lisp-graph-function-info.h \
    $$SRC_DIR/valuer/rz-lisp-graph-function-family-enum.h \
    $$SRC_DIR/valuer/rz-null-value.h \
    $$SRC_DIR/valuer/rz-monotail.h \
    $$SRC_DIR/rz-lisp-graph-typedefs.h \
    $$SRC_DIR/rz-lisp-graph-value-holder.h \
    $$SRC_DIR/rz-lisp-graph-core-function.h \


SOURCES += \
    $$SRC_DIR/token/rz-lisp-token.cpp \
    $$SRC_DIR/types/rz-type-variety.cpp \
    $$SRC_DIR/types/rz-type-object.cpp \
    $$SRC_DIR/valuer/rz-lisp-core-function.cpp \
    $$SRC_DIR/valuer/rz-lisp-graph-function-info.cpp \
    $$SRC_DIR/valuer/rz-null-value.cpp \
    $$SRC_DIR/rz-lisp-graph-value-holder.cpp \
    $$SRC_DIR/rz-lisp-graph-core-function.cpp \


message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
