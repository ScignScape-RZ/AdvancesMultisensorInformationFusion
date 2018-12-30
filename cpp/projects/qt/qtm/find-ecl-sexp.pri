
DEFINES += FIND_ECL__USING_ECL

# ecl
ECL_ROOT_DIR = $$ROOT_DIR/../../../ecl
ECL_DIR = $$ECL_ROOT_DIR/install

CL_CXX_DIR = $$ECL_ROOT_DIR/cl-cxx-master

# sexp
SEXP_DIR = $$SRC_ROOT_DIR/external/lisp/sexpr

INCLUDEPATH += $$ECL_DIR/install/include
INCLUDEPATH += $$CL_CXX_DIR/install/include/cl-cxx
INCLUDEPATH += $$CL_CXX_DIR/install/include
INCLUDEPATH += $$ECL_DIR/install/include
INCLUDEPATH += $$CL_CXX_DIR/include/cl-cxx
INCLUDEPATH += $$CL_CXX_DIR/include


DEFINES += IN_QT

## for future reference ...
#ecl.h line 69-71
# ifdef IN_QT
  #... typedef uintptr_t pthread_t;
#else
