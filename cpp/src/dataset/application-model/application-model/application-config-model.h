
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef APPLICATION_CONFIG_MODEL__H
#define APPLICATION_CONFIG_MODEL__H

#include <QMap>


#include <functional>

#include "kans.h"

KANS_(DSM)

class Application_Config_Model
{
 enum class User_Levels {
   N_A = 0, Unidentified = 1, User = 2, Author = 3,
   Editor = 4, Tester = 5, Administrator = 6
 };

 struct Gen_Targets {
   QStringList subdirs;
   QStringList defines;
   QStringList pri_libs;

   Gen_Targets(QStringList s, QStringList d, QStringList p)
    :  subdirs(s), defines(d), pri_libs(p) {}

 };
 //QStringList subdirs_text_;

 User_Levels usrl_;

 QMap<QString, QList<Gen_Targets>> insert_text_;

public:

 Application_Config_Model();

 void parse_config_code(QString cc);


};

_KANS(DSM)

#endif  // APPLICATION_CONFIG_MODEL__H
