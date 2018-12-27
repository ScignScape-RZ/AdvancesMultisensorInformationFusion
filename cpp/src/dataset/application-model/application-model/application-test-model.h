
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef APPLICATION_TEST_MODEL__H
#define APPLICATION_TEST_MODEL__H

#include <QMap>

class QNetworkAccessManager;

class ScignStage_2d_Chart_Dialog;
class ScignStage_3d_Chart_Dialog;
class QDialog;

class ScignStage_Tree_Table_Dialog;

#include <functional>

#include "kans.h"

KANS_(DSM)

class Application_Test_Model
{
 QNetworkAccessManager* qnam_;

 static void init_kph_qba(QByteArray& qba, QString path);

public:

 Application_Test_Model();
 ~Application_Test_Model();

 void run_kph_test(QString path,
   std::function<void()> ok_cb, std::function<void()> err_cb);

};

_KANS(DSM)

#endif  // APPLICATION_TEST_MODEL__H
