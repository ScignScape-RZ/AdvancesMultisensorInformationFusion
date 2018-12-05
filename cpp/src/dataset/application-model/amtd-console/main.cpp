
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-model-test-dialog/application-model-test-dialog.h"

#include <QApplication>

//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "kans.h"

#include <QThread>


USING_KANS(DSM)


int main(int argc, char **argv)
{
 QApplication qapp(argc, argv);

 Application_Model_Test_Dialog dlg(nullptr);

 dlg.show();

 return qapp.exec();
}
