
BUILD_DIR_CODE = $$OUT_PWD
BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3

CHOICE_CODE = isobuild-choices

include(../build-root-both.pri)
