
TEMPLATE = subdirs

SUBDIRS = \
  external/posit/posit-lib \
  dataset/ro-info/ro-info \
  dataset/dsmain/dsmain \
  qscign/ScignStage/ScignStage-2d-chart \
  qscign/ScignStage/ScignStage-3d-chart \
 
SUBDIRS += \
  external/xpdf/xpdf \
  
SUBDIRS += \
  qscign/ScignStage/ScignStage-tree-table \
  dataset/application-model/application-model \

SUBDIRS += \
  dataset/dsmain/_run__dsmain-console \


CONFIG += ordered
