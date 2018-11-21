
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "test-series-folder.h"

#include "test-series.h"

#include "textio.h"


#include <QDir>
#include <QDebug>

USING_KANS(DSM)

USING_KANS(TextIO)


Test_Series_Folder::Test_Series_Folder(QString ring_path)
  : ring_path_(ring_path)
{

}

void Test_Series_Folder::read_files(Test_Series& ts)
{
 QDir dir(ring_path_);
 QFileInfoList qfil = dir.entryInfoList();
 QStringList qsl;

 QStringList sm;
 QStringList nm;
 QStringList gm;

 QStringList lsm;
 QStringList lnm;
 QStringList lgm;

 QStringList ds;


 QMap<QString, int> files;

 for(QFileInfo qfi : qfil)
 {
  if(qfi.suffix() == "wav")
  {
   qsl.push_back(qfi.fileName());
  }
  else if(qfi.fileName() == "data.txt")
  {
   ts.parse_data(qfi.absoluteFilePath());
  }
  else if(qfi.fileName() == "smos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   sm = qs.split('\n');
  }
  else if(qfi.fileName() == "nmos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   nm = qs.split('\n');
  }
  else if(qfi.fileName() == "gmos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   gm = qs.split('\n');
  }
  else if(qfi.fileName() == "l-smos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   lsm = qs.split('\n');
  }
  else if(qfi.fileName() == "l-nmos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   lnm = qs.split('\n');
  }
  else if(qfi.fileName() == "l-gmos.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   lgm = qs.split('\n');
  }
  else if(qfi.fileName() == "files.txt")
  {
   QString qs = load_file(qfi.absoluteFilePath());
   QStringList l = qs.split('\n');
   int c = 0;
   for(QString s : l)
   {
    files[s] = c;
    ++c;
   }
  }
 }
}

