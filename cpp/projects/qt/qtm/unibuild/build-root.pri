
BUILD_DIR_CODE = $$OUT_PWD

BUILD_DIR_CODE ~= s!.*/(build|release)-build-(\w+)-.*!UNIBUILD-\2

CHOICE_CODE = $$BUILD_DIR_CODE-choices

include(../build-root-both.pri)
