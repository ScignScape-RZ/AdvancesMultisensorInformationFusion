
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kph-command-package.h"

#include "kph-carrier.h"

#include "kauvir-code-model/kcm-channel-group.h"


#include "textio.h"

#include <QDebug>
#include <QDataStream>

USING_KANS(Phaon)
USING_KANS(TextIO)
USING_KANS(KCM)

KPH_Command_Package::KPH_Command_Package()
  :  fn_code_(0)
{

}

void operator<<(QDataStream& qds, KPH_Carrier* cs)
{
 QByteArray qba;
 cs->supply_data(qba);
 qds << qba;
}


void operator>>(QDataStream& qds, KPH_Carrier*& cs)
{
 QByteArray qba;
 qds >> qba;
 cs = new KPH_Carrier;
 cs->absorb_data(qba);
}

void KPH_Command_Package::supply_data(QByteArray& qba) const
{
 QDataStream qds(&qba, QIODevice::WriteOnly);

 qds << fn_name_;
 qds << fn_code_;

 qds << channel_counts_;
 qds << type_names_;

 qds << carriers_;
 qds << pins_;

 qds << docus_;
}


void KPH_Command_Package::absorb_data(const QByteArray& qba)
{
 QDataStream qds(qba);

 qds >> fn_name_;
 qds >> fn_code_;

 qds >> channel_counts_;
 qds >> type_names_;

 qds >> carriers_;
 qds >> pins_;

 qds >> docus_;

}



void KPH_Command_Package::init_channel_group(Kauvir_Code_Model& kcm,
  KCM_Channel_Group& kcg)
{
 kcg.init_channel_counts(channel_counts_);
 kcg.add_fuxe_carrier(fn_name_);
 for(KPH_Carrier* kpc : carriers_)
 {
  kcg.init_carrier(kcm, kpc->channel_name(), kpc->pos(),
    kpc->type_name(), kpc->value_as_ptr(), kpc->symref());
 }
}


void KPH_Command_Package::parse_from_string(QString path, const QString& qs)
{
 QStringList qsl = qs.split("\n.\n");
 parse_from_string_list(path, qsl);
}

void KPH_Command_Package::parse_from_file(QString path)
{
 QString qs = load_file(path);
 parse_from_string(path, qs);
}

void KPH_Command_Package::parse_from_string(QString path, const QString& qs,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 QStringList qsl = qs.split("\n.\n");
 parse_from_string_list(path, qsl, channel_names, current_expression_code);
}

void KPH_Command_Package::parse_from_file_list(QString path,
  const QStringList& paths,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 for(QString p : paths)
 {
  if(p.contains('/'))
  {
   if(p.contains('.'))
     parse_from_file(p, channel_names, current_expression_code);
   else
     parse_from_file(p + ".kph", channel_names, current_expression_code);
   continue;
  }
  int index = path.lastIndexOf('/');
  if(p.contains('.'))
    parse_from_file(path.left(index + 1) + p, channel_names, current_expression_code);
  else
    parse_from_file(path.left(index + 1) + p + ".kph",
    channel_names, current_expression_code);
 }
}


void KPH_Command_Package::parse_from_file(QString path,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 QString qs = load_file(path);
 parse_from_string(path, qs, channel_names, current_expression_code);
}

void KPH_Command_Package::check_channel_count_maximum(QString key, int max)
{
 if(channel_counts_[key] < max)
   channel_counts_[key] = max;
}

void KPH_Command_Package::parse_from_string_list(QString path, const QStringList& qsl)
{
 QMap<int, QString> channel_names;
 int current_expression_code = 0;
 parse_from_string_list(path, qsl, channel_names, current_expression_code);
}

void KPH_Command_Package::parse_from_string_list(QString path, const QStringList& qsl,
  QMap<int, QString>& channel_names, int& current_expression_code)
{
 for(QString qs : qsl)
 {
  switch(qs[0].toLatin1())
  {
  case '-' : break; // comment

  case '~' :
   {
    QStringList files = qs.mid(1).simplified().split(' ');
    parse_from_file_list(path, files, channel_names, current_expression_code);
   }
   break;
  case ';' : // channel name
   {
    int index = qs.indexOf(':');
    QString channel_name = qs.mid(1, index - 1);
    int code = qs.mid(index + 1).toInt();
    channel_names[code] = channel_name;
   }
   break;
  case '#' : // expression
   {
    if(qs[1] != '#')
      current_expression_code = qs.mid(1).toInt();
   }
   break;
  case '@' : // type name
   {
    int index = qs.indexOf(':');
    QString type_name = qs.mid(1, index - 1);
    int index1 = qs.indexOf(':', index + 1);
    QString mode = qs.mid(index, index1 - index - 1);
    int code = qs.mid(index1 + 1).toInt();
    type_names_[code] = {type_name, mode};
   }
   break;
  case '&' : // fn name
   {
    int index = qs.indexOf(':');
    fn_code_ = qs.mid(1, index - 1).toInt();
    fn_name_ = qs.mid(index + 1);
   }
   break;
  case '+' : // pins
   {
    pins_.push_back(qs.mid(1));
   }
   break;
  case '%' : // documentation
   {
    int index = qs.indexOf(':');
    if(index != -1)
    {
     docus_[qs.mid(1, index - 1)] = qs.mid(index + 1).trimmed();
    }
   }
   break;
  default : // carrier
   {
    int index = qs.indexOf(':');
    int channel = qs.left(index).toInt();
    int index1 = qs.indexOf(':', index + 1);
    int pos = qs.mid(index + 1, index1 - index - 1).toInt();
    int index2 = qs.indexOf(':', index1 + 1);
    QString mode = qs.mid(index1 + 1, index2 - index1 - 1);
    int index3 = qs.indexOf(':', index2 + 1);
    int typec = qs.mid(index2 + 1, index3 - index2 - 1).toInt();
    int index4 = qs.indexOf(':', index3 + 1);
    QString kw = qs.mid(index4 + 1, index4 - index3 - 1);
    int index5 = qs.indexOf(':', index4 + 1);
    int expref = qs.mid(index5 + 1, index5 - index4 - 1).toInt();
    int index6 = qs.indexOf(':', index5 + 1);
    QString symref = qs.mid(index5 + 1, index6 - index5 - 1);
    QString value = qs.mid(index6 + 1);
    KPH_Carrier* kpc = new KPH_Carrier;
    kpc->set_channel_name(channel_names[channel]);
    kpc->set_carrier_mode(mode);
    kpc->set_type_name(type_names_[typec].first);
    kpc->set_type_mode(type_names_[typec].second);
    kpc->set_pos(pos);
    kpc->set_key(kw);
    kpc->set_expref(expref);
    kpc->set_symref(symref);
    kpc->set_value(value);
    check_channel_count_maximum(kpc->channel_name(), pos);
    carriers_.push_back(kpc);
   }
   break;
  }
 }
}


QVector<KPH_Command_Package*> KPH_Command_Package::parse_multi_from_file(QString path)
{
 QString qs = load_file(path);
 return parse_multi_from_string(path, qs);
}

QVector<KPH_Command_Package*> KPH_Command_Package::parse_multi_from_string(QString path,
  const QString& qs)
{
 int index = qs.indexOf("\n.\n##\n.\n");
 if(index == -1)
 {
  KPH_Command_Package* kph = new KPH_Command_Package;
  kph->parse_from_string(path, qs);
  return {kph};
 }
 QVector<KPH_Command_Package*> result;
 parse_multi_from_string(path, qs, 0, index + 6, result);
 return result;
}

void KPH_Command_Package::parse_multi_from_string(QString path,
  const QString& qs, int i1, int i2, QVector<KPH_Command_Package*>& result)
{
 QString mid = qs.mid(i1, i2 - i1);
 KPH_Command_Package* kph = new KPH_Command_Package;
 kph->parse_from_string(path, mid);
 result.push_back(kph);
 i2 += 2;
 int i3 = qs.indexOf("\n.\n##\n.\n", i2);
 if(i3 == -1)
 {
  QString mid = qs.mid(i2);
  KPH_Command_Package* kph = new KPH_Command_Package;
  kph->parse_from_string(path, mid);
  result.push_back(kph);
  return;
 }
 parse_multi_from_string(path, qs, i2, i3 + 6, result);
}

void KPH_Command_Package::multi_to_map(const QVector<KPH_Command_Package*>& kcps,
  QMap<QString, QVector<KPH_Command_Package*>>& qmap)
{
 for(KPH_Command_Package* kcp: kcps)
 {
  QString sigma = kcp->sigma_type_name();
  if(sigma.isEmpty())
    continue;
  qmap[sigma].push_back(kcp);
 }
}

QString KPH_Command_Package::sigma_type_name()
{
 for(KPH_Carrier* kpc : carriers_)
 {
  if(kpc->channel_name() == "sigma")
  {
   return kpc->type_name();
  }
 }
 return QString();
}

QString KPH_Command_Package::moc_signature()
{
 QString result = fn_name_ + '(';
 for(KPH_Carrier* kpc : carriers_)
 {
  if(kpc->channel_name() == "lambda")
  {
   result += kpc->type_name() + ", ";
  }
 }
 if(result.endsWith(", "))
   result.chop(2);
 result += ')';
 return result;
}



//void KPH_Command_Package::read_docus(QString file_path, QMap<QString, QString>& docus)
//{
// QString qs = load_file(file_path);
// QStringList qsl = qs.split("\n.\n");
// for(QString qs : qsl)
// {
//  switch(qs[0].toLatin1())
//  {
//  case '%' : // documentation
//   {
//    int index = qs.indexOf(':');
//    if(index != -1)
//    {
//     docus[qs.mid(1, index - 1)] = qs.mid(index).trimmed();
//    }
//   }
//   break;
//  default: break;
//  }
// }
//}

