
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-generator.h"

#include "kph-generator-substitutions.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kcm-type-object.h"
#include "kcm-command-package/kcm-command-package.h"

#include "textio.h"

#include <QDebug>
#include <QDataStream>

USING_KANS(Phaon)
USING_KANS(TextIO)


KPH_Generator::KPH_Generator(QString file_path,
  KPH_Generator_Substitutions* subs)
  :  file_path_(file_path), subs_(subs)
{

}

KPH_Generator::KPH_Generator(KPH_Generator_Substitutions* subs)
  :  subs_(subs)
{

}

void KPH_Generator::close_line(QTextStream& qts)
{
 qts << "\n.\n";
}

void KPH_Generator::encode(KCM_Channel_Group& kcg, QMap<QString, QString> docus,
  QString fn)
{
 KCM_Command_Package kcp(kcg);
 encode(kcp, docus, fn);
}


void KPH_Generator::encode(KCM_Command_Package& kcp, QMap<QString, QString> docus,
  QString fn)
{
 QString fuxe_name = fn;
 QMap<QString, QPair<int, const KCM_Channel*>> channel_codes;
 kcp.channel_names_to_codes(channel_codes);

 QTextStream qts(&text_);
 qts << "-\nAuto Generated";
 close_line(qts);

 QMapIterator<QString, QString> dit(docus);
 while(dit.hasNext())
 {
  dit.next();
  qts << "%" << dit.key() << ' ' << dit.value();
  close_line(qts);
 }

 QString args;
 QTextStream aqts(&args);

 QString types;
 QTextStream tqts(&types);

 QMap<const KCM_Type_Object*, int> tycodes;
 int tyc = 1;

 QMapIterator<QString, QPair<int, const KCM_Channel*>> it(channel_codes);
 while(it.hasNext())
 {
  it.next();
  const KCM_Channel& kch = *it.value().second;
  if(it.key() == "fuxe")
    fuxe_name = kch.get_carrier_at_position(0)->symbol();
  else
  {
   QString chc = QString::number(it.value().first);
   qts << ';' << it.key() << ':' << chc;
   close_line(qts);
   int c = 1;
   const QVector<KCM_Carrier>& cars = kch.carriers();
   for(const KCM_Carrier& car : cars)
   {
    const KCM_Type_Object* kto = car.type_object();
    int ty = tycodes.value(kto);
    if(ty == 0)
    {
     ty = tyc;
     tycodes[kto] = tyc;
     tqts << '@' << kto->get_name_string() << "::" <<
       QString::number(tyc);
     close_line(tqts);
     ++tyc;
    }
    QString src_val = subs_? subs_->get_src_value(it.key(), car, c - 1)
      : car.get_src_value();
    aqts << chc << ':' << QString::number(c) << "::"
      << QString::number(ty) << "::::"
      << src_val;
    close_line(aqts);
   }
  }
 }
 qts << types;
 qts << "#1";
 close_line(qts);
 qts << "&:" << fuxe_name;
 close_line(qts);
 qts << args;
 qts << '-';
}

void KPH_Generator::save_kph_file()
{
 save_file(file_path_, text_);

// QMapIterator<QString, QString> it(docus_);

// while(it.hasNext())
// {
//  it.next();
//  save_file(file_path_ + '.' + it.key(), it.value());
// }

}
