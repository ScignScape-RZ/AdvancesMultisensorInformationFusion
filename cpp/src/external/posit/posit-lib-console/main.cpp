#include "posit-lib/posit.h"

#include <cstdio>

#include <QtGlobal>
#include <QDebug>


int main(int argc, char *argv[])
{
 // // example from lib implementation
    auto p = Posit(5, 1);

    for (unsigned i = 0; i < (unsigned)(1 << p.nbits()); i++) {
        p.setBits(i);
        p.print();
    }

 // //  for current

    qreal qr = 0.000000435900;
    qDebug() << qr;

    Posit p1 = Posit(qr);

    p1.print();

    double d1 = p1.getDouble();

    qDebug() << d1;

    return 0;
}
