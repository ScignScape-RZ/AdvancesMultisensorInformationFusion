
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)

PROJECT_NAME = rz-graph-core

include(../build-group.pri)

INCLUDEPATH += $$SRC_DIR $$SRC_GROUP_DIR

INCLUDEPATH += $$QHYP_SRC_GROUP_DIR


INCLUDEPATH += $$SRC_GROUP_DIR/rz-graph-token


DEFINES += RELAE_LABEL_NODES
DEFINES += CAON_DEBUG



HEADERS += \
  $$SRC_DIR/kernel/rz-re-dominion.h \
  $$SRC_DIR/kernel/rz-re-root.h \
  $$SRC_DIR/kernel/dominion/types.h \
  $$SRC_DIR/kernel/dominion/connectors.h \
  $$SRC_DIR/token/rz-re-token.h \
  $$SRC_DIR/kernel/graph/rz-re-node.h \
  $$SRC_DIR/kernel/graph/rz-re-node-proxy.h \
  $$SRC_DIR/kernel/graph/rz-re-graph.h \
  $$SRC_DIR/kernel/graph/rz-re-markup-position.h \
  $$SRC_DIR/kernel/graph/rz-re-connection.h \
  $$SRC_DIR/kernel/query/rz-re-query.h \
  $$SRC_DIR/kernel/frame/rz-re-frame.h \
  $$SRC_DIR/kernel/document/rz-re-document.h \
  $$SRC_DIR/kernel/grammar/rz-re-parser.h \
  $$SRC_DIR/kernel/grammar/rz-re-grammar.h \
  $$SRC_DIR/kernel/grammar/rz-re-graph-build.h \
  $$SRC_DIR/kernel/grammar/rz-re-parse-context.h \
  $$SRC_DIR/kernel/grammar/rz-re-string-plex-builder.h \
  $$SRC_DIR/code/rz-re-call-entry.h \
  $$SRC_DIR/code/rz-re-block-entry.h \
  $$SRC_DIR/code/rz-re-function-def-entry.h \
  $$SRC_DIR/code/rz-re-function-def-kinds.h \
  $$SRC_DIR/code/rz-re-code-representation.h \
  $$SRC_DIR/code/rz-re-code-representation.special-tokens.h \
  $$SRC_DIR/tuple/rz-re-tuple-info.h \
  $$SRC_DIR/output/rz-re-lisp-output.h \
  $$SRC_DIR/output/rz-re-pre-init-lisp.h \
  $$SRC_DIR/output/rz-re-pre-normal-lisp.h \
  $$SRC_DIR/output/rz-re-pre-run-lisp.h \

DEFINES += CAON_DEBUG
DEFINES += RELAE_LABEL_NODES



SOURCES += \
  $$SRC_DIR/kernel/rz-re-dominion.cpp \
  $$SRC_DIR/kernel/rz-re-root.cpp \
  $$SRC_DIR/token/rz-re-token.cpp \
  $$SRC_DIR/kernel/graph/rz-re-node.cpp \
  $$SRC_DIR/kernel/graph/rz-re-node-proxy.cpp \
  $$SRC_DIR/kernel/graph/rz-re-graph.cpp \
  $$SRC_DIR/kernel/graph/rz-re-markup-position.cpp \
  $$SRC_DIR/kernel/graph/rz-re-connection.cpp \
  $$SRC_DIR/kernel/query/rz-re-query.cpp \
  $$SRC_DIR/kernel/frame/rz-re-frame.cpp \
  $$SRC_DIR/kernel/document/rz-re-document.cpp \
  $$SRC_DIR/kernel/grammar/rz-re-parser.cpp \
  $$SRC_DIR/kernel/grammar/rz-re-grammar.cpp \
  $$SRC_DIR/kernel/grammar/rz-re-graph-build.cpp \
  $$SRC_DIR/kernel/grammar/rz-re-parse-context.cpp \
  $$SRC_DIR/kernel/grammar/rz-re-string-plex-builder.cpp \
  $$SRC_DIR/code/rz-re-code-representation.cpp \
  $$SRC_DIR/code/rz-re-call-entry.cpp \
  $$SRC_DIR/code/rz-re-function-def-entry.cpp \
  $$SRC_DIR/code/rz-re-block-entry.cpp \
  $$SRC_DIR/tuple/rz-re-tuple-info.cpp \
  $$SRC_DIR/output/rz-re-lisp-output.cpp \
  $$SRC_DIR/output/rz-re-pre-init-lisp.cpp \
  $$SRC_DIR/output/rz-re-pre-normal-lisp.cpp \
  $$SRC_DIR/output/rz-re-pre-run-lisp.cpp \

message(choice: $$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
mkpath($$CPP_ROOT_DIR/targets/$$CHOICE_CODE/$$PROJECT_SET--$$PROJECT_GROUP--$$PROJECT_NAME)
