
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "application-model/application-config-model.h"

#include <QApplication>


#include "kans.h"

#include "textio.h"
USING_KANS(TextIO)

#include <QDebug>


USING_KANS(DSM)



//int main(int argc, char **argv)
//{
// Application_Config_Model acm;
// acm.parse_config_code("cc");
// return 0;
//}


int main(int argc, char **argv)
{
 Application_Config_Model acm;
 acm.parse_config_code("gen_test__xq-1");

 {
  QString result;
  QString f = acm.insert_to_defines(DEFINES_SRC_FOLDER "/UNIBUILD-custom_defines.h", result);
  save_file(f, result);
 }

 {
  QString result;
  QString f = acm.insert_to_choices(CHOICES_PRI_FOLDER "/UNIBUILD-custom_choices.pri", result);
  save_file(f, result);
 }

 {
  QMap<QString, QString> result;
  QMap<QString, QString> files {{
    { "xpdf", CUSTOM_LIBS_PRI_FOLDER "/_xpdf.pri" },
    { "kph", CUSTOM_LIBS_PRI_FOLDER "/_kph.pri" },
    { "ss3d", CUSTOM_LIBS_PRI_FOLDER "/_ss3d.pri" }
   }};
  acm.insert_to_custom_libs(files, result);

  QMapIterator<QString, QString> it(result);

  while(it.hasNext())
  {
   it.next();
   save_file(it.key(), it.value());
  }
 }

 return 0;
}
