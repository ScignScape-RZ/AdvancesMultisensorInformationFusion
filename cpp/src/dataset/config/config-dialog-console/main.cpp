
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>
#include <QVector>

#include <QApplication>

#include "config-dialog/config-dialog.h"

#include "kans.h"


int main(int argc, char* argv[])
{
 QApplication qapp(argc, argv);

 Config_Dialog dlg(nullptr);

 dlg.set_proceed_callback([](QString qs)
 {
  qDebug() << qs;
 });

 dlg.show();

 return qapp.exec();

}
