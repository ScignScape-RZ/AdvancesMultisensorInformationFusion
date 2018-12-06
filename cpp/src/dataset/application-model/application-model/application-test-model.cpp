
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "application-test-model.h"

//#include "ScignStage-2d-chart/ScignStage-2d-chart-dialog.h"

//#include "ScignStage-3d-chart/ScignStage-3d-chart-dialog.h"

//#include "ScignStage-tree-table/ScignStage-tree-table-dialog.h"


//#include "dsmain/test-sample.h"
//#include "dsmain/test-series.h"

#include "kauvir-phaon/kph-command-package.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>

USING_KANS(Phaon)
USING_KANS(DSM)

#include <QDebug>


Application_Test_Model::Application_Test_Model()
  :  qnam_(nullptr)
{

}


void Application_Test_Model::init_kph_qba(QByteArray& qba, QString path)
{
#ifdef USING_KPH
 KPH_Command_Package kcp;
 kcp.parse_from_file(path);
 kcp.supply_data(qba);
 qba.append("<//>");

 QByteArray pre = "<<>>kph@";
 quint64 ms = QDateTime::currentMSecsSinceEpoch();
 pre.append(QByteArray::number(ms));
 pre.append(':');
 qba.prepend(pre);
#endif // USING_KPH
}


void Application_Test_Model::run_kph_test(QString path,
  std::function<void()> okcb, std::function<void()> errcb)
{
 qDebug() << path;

#ifdef USING_KPH

// //  This version seems slower, since it relies on an
 //    extra communication step.  But the QNAM version
 //    relying on a RemoteHostClosedError may be a bit
 //    hackneyed ...
#ifdef USE_SOCKET_WITHOUT_QNAM

 QByteArray* qba = new QByteArray;
 init_kph_qba(*qba, path);

 QTcpSocket* socket = new QTcpSocket;
 int port = 18261; // // r z 1

 socket->connectToHost("Localhost", port);

 QObject::connect(socket, &QNetworkReply::readyRead,
  [socket, qba, okcb, errcb]()
 {
  QString result = QString::fromLatin1( socket->readAll() );
  if(result == "OK")
  {
   socket->write(*qba);
  }
  else if(result == "END")
  {
   qDebug() << "OK\n";
   socket->disconnectFromHost();
   socket->deleteLater();
   delete qba;
   okcb();
  }
  else
  {
   qDebug() << "Unexpected response: " << result << "\n";
   socket->disconnectFromHost();
   socket->deleteLater();
   delete qba;
   errcb();
  }
 });


#else //  USE_SOCKET_WITHOUT_QNAM not defined
 if(!qnam_)
   qnam_ = new QNetworkAccessManager;

 QByteArray qba;

 init_kph_qba(qba, path);

 int port = 18261; // // r z 1
 QString addr = QString("http://localhost:%1/").arg(port);

 QNetworkRequest req;// = new QNetworkRequest;

 req.setUrl( QUrl(addr) );
 req.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

 QNetworkReply* reply = qnam_->post(req, qba);

 QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
  [reply, okcb, errcb](QNetworkReply::NetworkError code)
 {
  if(code != QNetworkReply::RemoteHostClosedError)
  {
   qDebug() << "Unexpected error: " << code << "\n";
   errcb();
  }
  else
  {
   okcb();
   //std::function<void()> pass_cb, std::function<void()> fail_cb
   //qDebug() << "OK\n";
  }
  reply->deleteLater();
 });
#endif // USE_SOCKET_WITHOUT_QNAM

#else
 qDebug() << "This library was built without KPH!";
#endif  //  USING_KPH
}

Application_Test_Model::~Application_Test_Model()
{
 delete qnam_;
}
