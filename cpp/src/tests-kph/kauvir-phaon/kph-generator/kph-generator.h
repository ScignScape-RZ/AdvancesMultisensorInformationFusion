
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KPH_GENERATOR__H
#define KPH_GENERATOR__H


#include "kans.h"

#include <QString>
#include <QMap>

class QTextStream;

#include "accessors.h"

KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
USING_KANS(KCM)

KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
USING_KANS(CMD)

KANS_(Phaon)

class KPH_Generator_Substitutions;

class KPH_Generator
{
 QString file_path_;
 QString text_;
 KPH_Generator_Substitutions* subs_;

 QString docus_string_;

 static void close_line(QTextStream& qts);

public:

 KPH_Generator(QString file_path,
   KPH_Generator_Substitutions* subs = nullptr);

 KPH_Generator(KPH_Generator_Substitutions* subs = nullptr);

 ACCESSORS(QString ,file_path)
 ACCESSORS(QString ,text)
 ACCESSORS(KPH_Generator_Substitutions* ,subs)

 void save_kph_file();

 void encode(KCM_Channel_Group& kcg, QMap<QString, QString> docus,
   QString fn = QString());

 void encode(KCM_Command_Package& kcp, QMap<QString, QString> docus,
   QString fn = QString());

};


_KANS(Phaon)


#endif //KPH_GENERATOR__H
