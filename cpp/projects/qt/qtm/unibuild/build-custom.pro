
TEMPLATE = subdirs

#__CHOICE_SUBDIRS__#

SUBDIRS = \
  dataset/ro-info/ro-info \
  external/posit/posit-lib \
  dataset/config/config-dialog \
  dataset/dsmain/dsmain \
  qscign/ScignStage/ScignStage-2d-chart \
  dataset/ro-info/ro-info-console \
  external/xpdf/xpdf \
  external/xpdf/xpdf-console \
  qscign/ScignStage/ScignStage-tree-table \
  dataset/application-model/application-model \
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
