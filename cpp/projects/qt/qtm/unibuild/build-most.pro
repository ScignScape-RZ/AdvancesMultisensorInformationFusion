
#           Copyright Nathaniel Christen 2019.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)


TEMPLATE = subdirs


SUBDIRS = \
  external/posit/posit-lib \
  dataset/config/config-dialog \
  dataset/dsmain/dsmain \
  dataset/dsmain/data-model-console \
  qscign/ScignStage/ScignStage-2d-chart \
  qscign/ScignStage/ScignStage-3d-chart \
  dataset/ro-info/ro-info \
  dataset/ro-info/ro-info-console \

SUBDIRS += \
  external/xpdf/xpdf \
  external/xpdf/xpdf-console \
  kauvir/kauvir-kcm/kauvir-type-system \
  kauvir/kcm-runtime-eval/kcm-scopes \
  kauvir/kauvir-kcm/kauvir-code-model \
  kauvir/kauvir-runtime/kcm-command-package \
  phaon/phaon/PhaonLib \
  kauvir/kauvir-runtime/kcm-command-runtime \
  kauvir/kcm-runtime-eval/kcm-direct-eval \
  tests-kph/kauvir-phaon/kauvir-phaon \

SUBDIRS += \
  qscign/ScignStage/ScignStage-tree-table \

SUBDIRS += \
  phaon/phaon/phaon-console \
  tests-kph/kauvir-phaon/kauvir-phaon-console \

SUBDIRS += \
  dataset/application-model/application-model \
  dataset/application-model/application-model-test-dialog \
  dataset/config/config-dialog-console \
  dataset/application-model/amtd-console \
  dataset/dsmain/_run__dsmain-console \

SUBDIRS += \
  tests-kph/kauvir-phaon/kph-tcp-console \
  phaon/phaon-xml/phaon-xml \
  phaon/phaon-xml/phaon-xml-console \


CONFIG += ordered
