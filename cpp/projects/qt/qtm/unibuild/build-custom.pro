
TEMPLATE = subdirs

#__CHOICE_SUBDIRS__#

SUBDIRS = \
  external/posit/posit-lib \
  dataset/dsmain/dsmain \
  qscign/ScignStage/ScignStage-2d-chart \
  qscign/ScignStage/ScignStage-3d-chart \
  external/xpdf/xpdf \
  kauvir/kauvir-kcm/kauvir-type-system \
  kauvir/kcm-runtime-eval/kcm-scopes \
  kauvir/kauvir-kcm/kauvir-code-model \
  kauvir/kauvir-runtime/kcm-command-package \
  phaon/phaon/PhaonLib \
  kauvir/kauvir-runtime/kcm-command-runtime \
  kauvir/kcm-runtime-eval/kcm-direct-eval \
  tests-kph/kauvir-phaon/kauvir-phaon \
  phaon/phaon/phaon-console \
  tests-kph/kauvir-phaon/kauvir-phaon-console \
  tests-kph/kauvir-phaon/kph-tcp-console \
  phaon/phaon-xml/phaon-xml \
  phaon/phaon-xml/phaon-xml-console \
  qscign/ScignStage/ScignStage-tree-table \
  dataset/application-model/application-model \
  dataset/application-model/application-model-test-dialog \
  dataset/application-model/amtd-console \
  dataset/dsmain/_run__dsmain-console \


#__END_INSERT__#


# e.g.
#SUBDIRS = \
#  external/posit/posit-lib \
#  dataset/dsmain/dsmain \
#  qscign/ScignStage/ScignStage-2d-chart \
#  qscign/ScignStage/ScignStage-3d-chart \
#  qscign/ScignStage/ScignStage-tree-table \
#  dataset/application-model/application-model \
#  external/xpdf/xpdf \
#  dataset/dsmain/_run__dsmain-console \

CONFIG += ordered
