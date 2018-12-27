
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kauvir-phaon/kph-command-package.h"

#include "kauvir-code-model/kauvir-code-model.h"
#include "kauvir-code-model/kcm-channel-group.h"
#include "kcm-scopes/kcm-scope-system.h"

#include "PhaonLib/phaon-namespace.h"
#include "PhaonLib/phaon-class.h"
#include "PhaonLib/phaon-function.h"
#include "PhaonLib/phaon-symbol-scope.h"

#include "relae-graph/relae-caon-ptr.h"

#include "test-functions.h"

#include "PhaonLib/phaon-channel-group-table.h"
#include "PhaonLib/phaon-runner.h"

#include "kcm-direct-eval/kcm-direct-eval.h"

#include "kcm-command-package/kcm-command-package.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QDateTime>

#include "kans.h"

USING_KANS(KCM)
USING_KANS(Phaon)
USING_KANS(PhaonLib)


void init_qba(QByteArray& qba)
{
 KPH_Command_Package kcp;
 kcp.parse_from_file( DEFAULT_KPH_FOLDER "/dataset/raw/t1.kph" );


 kcp.supply_data(qba);


 qba.append("<//>");

 QByteArray pre = "<<>>kph@";
 quint64 ms = QDateTime::currentMSecsSinceEpoch();
 pre.append(QByteArray::number(ms));
 pre.append(':');
 qba.prepend(pre);

}

int main_via_socket(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QTcpSocket* tcpSocket = new QTcpSocket;
 int port = 18261; // // r z 1

 tcpSocket->connectToHost("Localhost", port);

 QObject::connect(tcpSocket, &QNetworkReply::readyRead,
  [tcpSocket, &app, &qba]()
 {
  QString result = QString::fromLatin1( tcpSocket->readAll() );
  if(result == "OK")
  {
   tcpSocket->write(qba);
  }
  else if(result == "END")
  {
   qDebug() << "OK\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
  else
  {
   qDebug() << "Unexpected response: " << result << "\n";
   tcpSocket->disconnectFromHost();
   tcpSocket->deleteLater();
   app.exit();
  }
 });

 return app.exec();
}

int main_via_qnam(int argc, char* argv[])
{
 QCoreApplication app(argc, argv);
 QByteArray qba;

 init_qba(qba);

 QNetworkAccessManager qnam;

 int port = 18261; // // r z 1
 QString addr = QString("http://localhost:%1/").arg(port);

 QNetworkRequest req;

 req.setUrl( QUrl(addr) );
 req.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

 QNetworkReply* reply = qnam.post(req, qba);

 QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
  [reply, &app](QNetworkReply::NetworkError code)
 {
  if(code != QNetworkReply::RemoteHostClosedError)
  {
   qDebug() << "Unexpected error: " << code << "\n";
  }
  else
  {
   qDebug() << "OK\n";
  }
  reply->deleteLater();
  app.exit();
 });

 return app.exec();
}


int main(int argc, char* argv[])
{
 // choose one ...
 // // return main_via_socket(argc, argv);
 return main_via_qnam(argc, argv);
}

