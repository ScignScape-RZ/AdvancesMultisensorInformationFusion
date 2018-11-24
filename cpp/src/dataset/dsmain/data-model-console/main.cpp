
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QDebug>
#include <QVector>


#include "dsmain/pri.h"

#include "dsmain/test-sample.h"

//#include "dsmain/assessment-scores.h"
//#include "dsmain/test-series-folder.h"
//#include "dsmain/test-series.h"

#include "kans.h"

USING_KANS(DSM)

//void qdb(QString str)
//{
// qDebug() << str;
//}

//void test(QString str)
//{
// pri_(str)
//  str.replace('-', '_');
// _pri(str);

// qdb( pri(str) );
//}


int main(int argc, char* argv[])
{
 QVector<Test_Sample*> ts;
 Test_Sample::read_samples_from_file(DATA_FOLDER "/t1.txt", ts);

 Test_Sample::write_samples_to_file(DATA_FOLDER "/t1.out.txt", ts);

// Test_Series_Folder tsf(SAMPLES_FOLDER);

// Test_Series ts;
// tsf.read_files(ts);
 return 0;
}

//int mainx(int argc, char* argv[])
//{
// Assessment_Scores scores;


// scores.set_speech_nondistortion(3);
// scores.set_background_nondisruption(4);

// scores.set_overall_quality(2);

// scores.with_ (quint8,background_nondisruption ,bq)
//  qDebug() << "bq: " << bq;
// _with;

// scores.with_ (quint8,speech_nondistortion ,sq)
//  qDebug() << "sq: " << sq;
// _with;

// scores.with_ (quint8,overall_quality ,oq)
//  qDebug() << "oq: " << oq;
// _with;

// return 0;
//}
