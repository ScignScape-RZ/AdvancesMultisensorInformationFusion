
TEMPLATE = subdirs

SUBDIRS = \
  external/posit/posit-lib \
  dataset/dsmain/dsmain \
  qscign/ScignStage/ScignStage-2d-chart \
  qscign/ScignStage/ScignStage-3d-chart \
  qscign/ScignStage/ScignStage-tree-table \
  dataset/application-model/application-model \

SUBDIRS += \
  external/xpdf/xpdf \

SUBDIRS += \
  dataset/dsmain/_run__dsmain-console \


CONFIG += ordered
