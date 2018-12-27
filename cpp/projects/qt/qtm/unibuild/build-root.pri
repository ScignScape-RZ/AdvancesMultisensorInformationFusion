
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


BUILD_DIR_CODE = $$OUT_PWD

BUILD_DIR_CODE ~= s!.*/(build|release)-build-(\w+)-.*!UNIBUILD-\2

CHOICE_CODE = $$BUILD_DIR_CODE-choices

WHICH_BUILD_DIR_CODE = $$BUILD_DIR_CODE

include(../_choices/$${WHICH_BUILD_DIR_CODE}_choices.pri)

include(../build-root-both.pri)
