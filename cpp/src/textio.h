
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEXTIO__H
#define TEXTIO__H

#include "kans.h"

#include <QFile>
#include <QTextStream>


KANS_(TextIO)


inline QString load_file(QString path)
{
 QString result;
 QFile infile(path);
 if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
   return result;
 QTextStream in_ts(&infile);
 result = in_ts.readAll();
 infile.close();
 return result;
}

inline void load_file(QString path, QString& result)
{
 QFile infile(path);
 if (!infile.open(QIODevice::ReadOnly | QIODevice::Text))
   return;
 QTextStream in_ts(&infile);
 result = in_ts.readAll();
 infile.close();
}

inline void load_file(QString path, QByteArray& contents)
{
 QFile infile(path);
 if (!infile.open(QIODevice::ReadOnly))
   return;
 contents = infile.readAll();
 infile.close();
}

inline void save_file(QString path, QByteArray& contents)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly))
   return;
 outfile.write(contents);
 outfile.close();
}

inline void save_file(QString path, QString text)
{
 QFile outfile(path);
 if (!outfile.open(QIODevice::WriteOnly | QIODevice::Text))
   return;
 QTextStream outstream(&outfile);
 outstream << text;
 outfile.close();
}

_KANS(TextIO)


#endif //TEXTIO__H
