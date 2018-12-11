
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "application-model/application-config-model.h"

#include <QApplication>


#include "kans.h"

#include <QThread>


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
 acm.parse_config_code("cc");
 return 0;
}
