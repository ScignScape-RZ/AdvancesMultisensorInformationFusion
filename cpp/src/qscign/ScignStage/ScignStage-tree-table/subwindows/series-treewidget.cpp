
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "series-treewidget.h"

#include "dsmain/test-sample.h"
#include "dsmain/test-series.h"

#include <QHeaderView>

#include "qsns.h"

//USING_QSNS(ScignStage)


Series_TreeWidget::Series_TreeWidget(Test_Series* ts, Sort_Options so, QWidget* parent)
  : QTreeWidget(parent)
{
 QVector<Test_Sample*>* samples;

 if(ts)
 {
  switch(so)
  {
  case Sort_Options::Index:
   samples = &ts->samples();
   break;
  case Sort_Options::Flow:
   samples = new QVector<Test_Sample*>;
   ts->samples_by_flow_rank(*samples);
   break;
  case Sort_Options::Temperature:
   samples = new QVector<Test_Sample*>;
   ts->samples_by_temperature_rank(*samples);
   break;
  case Sort_Options::Oxy:
   samples = new QVector<Test_Sample*>;
   ts->samples_by_oxy_rank(*samples);
   break;
  }
 }
 else
   samples = nullptr;


 if(samples)
 {

  int r = 0;

  QStringList headers {
   "Index",
   "Flow",
   "Time With\n / Average",
   "Time Against\n / Delta",
   "Temperature C\u00b0\n / K\u00b0",
   "Oxygen \n (calculated)"
  };

  this->setColumnCount(6);
  this->setHeaderLabels(headers);

  this->setColumnWidth(0, 80);
  this->setColumnWidth(1, 65);
  this->setColumnWidth(2, 105);
  this->setColumnWidth(3, 105);
  this->setColumnWidth(4, 105);
  this->setColumnWidth(5, 65);

  this->header()->setStretchLastSection(false);
  this->header()->setSectionResizeMode(5, QHeaderView::Stretch);

  int c = 0;
  for(Test_Sample* samp : *samples)
  {
   ++c;

   QStringList qsl;

   qsl.push_back(QString::number(samp->index()));
   qsl.push_back(QString::number(samp->flow().getDouble()));
   qsl.push_back(QString::number(samp->time_with_flow().getDouble()));
   qsl.push_back(QString::number(samp->time_against_flow().getDouble()));

   QString s = QString::number(samp->temperature_adj());
   s.insert(s.size() - 2, '.');
   qsl.push_back(s);

   QTreeWidgetItem* twi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     qsl);

   QStringList sqsl {{"", ""}};

   sqsl.push_back(" " + QString::number(samp->average_time().getDouble()));
   sqsl.push_back(" " + QString::number(samp->delta_time().getDouble()));
   sqsl.push_back(" " + QString::number(samp->temperature_kelvin().getDouble()));
   sqsl.push_back(" " + QString::number(samp->oxy()));

   QTreeWidgetItem* stwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     sqsl);

   twi->addChild(stwi);

   QStringList pqsl {"%"};

   pqsl.push_back(QString::number(ts->get_flow_as_percentage(*samp)));
   pqsl.push_back("");
   pqsl.push_back("");
   pqsl.push_back(QString::number(ts->get_temperature_as_percentage(*samp)));
   pqsl.push_back(QString::number(ts->get_oxy_as_percentage(*samp)));

   QTreeWidgetItem* ptwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     pqsl);

   twi->addChild(ptwi);

   QStringList rqsl {"#"};

   rqsl.push_back(QString::number(ts->get_flow_rank(*samp)));
   rqsl.push_back("");
   rqsl.push_back("");
   rqsl.push_back(QString::number(ts->get_temperature_rank(*samp)));
   rqsl.push_back(QString::number(ts->get_oxy_rank(*samp)));

   QTreeWidgetItem* rtwi = new QTreeWidgetItem((QTreeWidget*) nullptr,
     rqsl);

   twi->addChild(rtwi);

   this->addTopLevelItem(twi);

   //twi->setData(0, Qt::UserRole, QVariant::fromValue(group)
  }
 }

}

Series_TreeWidget::~Series_TreeWidget() {}


