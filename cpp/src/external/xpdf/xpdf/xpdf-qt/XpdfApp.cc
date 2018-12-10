//========================================================================
//
// XpdfApp.cc
//
// Copyright 2015 Glyph & Cog, LLC
//
//========================================================================

#include <aconf.h>

#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "parseargs.h"
#include "GString.h"
#include "GList.h"
#include "GlobalParams.h"
#include "XpdfViewer.h"
#include "XpdfApp.h"
#include "gmempp.h"

#include <QTcpServer>
#include <QMessageBox>
#include <QTcpSocket>
#include <QNetworkAccessManager>
#include <QNetworkReply>

//------------------------------------------------------------------------
// command line options
//------------------------------------------------------------------------

static GBool reverseVideoArg = gFalse;
static char paperColorArg[256] = "";
static char matteColorArg[256] = "";
static char fsMatteColorArg[256] = "";
static char initialZoomArg[256] = "";
static char antialiasArg[16] = "";
static char vectorAntialiasArg[16] = "";
static char textEncArg[128] = "";
static char passwordArg[33] = "";
static GBool fullScreen = gFalse;
static char cfgFileArg[256] = "";
static GBool printCommandsArg = gFalse;
static GBool printVersionArg = gFalse;
static GBool printHelpArg = gFalse;

static ArgDesc argDesc[] = {
 {"-rv",           argFlag,   &reverseVideoArg,   0,                          "reverse video"},
 {"-papercolor",   argString, paperColorArg,      sizeof(paperColorArg),      "color of paper background"},
 {"-mattecolor",   argString, matteColorArg,      sizeof(matteColorArg),      "color of matte background"},
 {"-fsmattecolor", argString, fsMatteColorArg,    sizeof(fsMatteColorArg),    "color of matte background in full-screen mode"},
 {"-z",            argString, initialZoomArg,     sizeof(initialZoomArg),     "initial zoom level (percent, 'page', 'width')"},
 {"-aa",           argString, antialiasArg,       sizeof(antialiasArg),       "enable font anti-aliasing: yes, no"},
 {"-aaVector",     argString, vectorAntialiasArg, sizeof(vectorAntialiasArg), "enable vector anti-aliasing: yes, no"},
 {"-enc",          argString, textEncArg,         sizeof(textEncArg),         "output text encoding name"},
 {"-pw",           argString, passwordArg,        sizeof(passwordArg),        "password (for encrypted files)"},
 {"-fullscreen",   argFlag,   &fullScreen,        0,                          "run in full-screen (presentation) mode"},
 {"-cmd",          argFlag,   &printCommandsArg,  0,                          "print commands as they're executed"},
 {"-cfg",          argString, cfgFileArg,         sizeof(cfgFileArg),         "configuration file to use in place of .xpdfrc"},
 {"-v",            argFlag,   &printVersionArg,   0,                          "print copyright and version info"},
 {"-h",            argFlag,   &printHelpArg,      0,                          "print usage information"},
 {"-help",         argFlag,   &printHelpArg,      0,                          "print usage information"},
 {"--help",        argFlag,   &printHelpArg,      0,                          "print usage information"},
 {"-?",            argFlag,   &printHelpArg,      0,                          "print usage information"},
 {NULL}
};

#ifdef HIDE
// //  R/Z Workflow ...

struct RZW
{
 XpdfApp& xpa;
 int peer_port;
 QString current_tcp_msg;
 QNetworkAccessManager& qnam;
};

void send_msg(RZW& rzw, QString msg)
{
 QString addr = QString("http://localhost:%1/").arg(rzw.peer_port);

 QNetworkRequest req;

 req.setUrl( QUrl(addr) );
 req.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

 //int myport = 18262;

 //QString msg = QString("%1##%2").arg(name).arg(page);
 //QString msg = QString("open:%1##%2").arg(name).arg(page);
 //QString msg = QString("hello:%1").arg(myport);


 QByteArray qba = msg.toLatin1();
 qba.append("<//>");
 qba.prepend("<<>>");

 QNetworkReply* reply = rzw.qnam.post(req, qba);
 QObject::connect(reply, &QNetworkReply::finished,
   [reply]()
 {
  reply->deleteLater();
 });
 //QEventLoop qel;

 //QString result;

// QObject::connect(reply, &QNetworkReply::finished,
//  [this, reply]()
// {
//  QString result = QString::fromLatin1( reply->readAll() );
//  if(result.isEmpty())
//  {
//   result = "Process not found.";
//  }
//  qDebug() << "Result: " << result;
//  reply->deleteLater();
//  //qel.exit();
// });
}

void run_msg(RZW& rzw, QString msg)
{
 rzw.current_tcp_msg = msg;
// Q#messageBox::information(nullptr, "Qt Server",
//                          QString("received: %1")
//                          .arg(msg));
 int index = msg.indexOf(':');
 QString key = msg.left(index);

 QString arg = msg.mid(index + 1);

  Q#messageBox::information(nullptr, "Qt Server",
                           QString("received: %1, %2")
                           .arg(key).arg(arg));

}
#endif


//------------------------------------------------------------------------
// XpdfApp
//------------------------------------------------------------------------

XpdfApp::XpdfApp(int &argc, char **argv):
  QApplication(argc, argv)
{

#ifdef HIDE
 QTcpServer* tcp_server = new QTcpServer();
 QMap<qintptr, QByteArray>* temps = new QMap<qintptr, QByteArray>();

 QString waiting_#message;

 int port = 18262; // // r z 1

 if (!tcp_server->listen(QHostAddress::LocalHost, port))
 {
  Q#messageBox::critical(nullptr, "Qt Server",
                        QString("Unable to start the server: %1.")
                        .arg(tcp_server->errorString()));
 }
 else
 {
  waiting_#message = QString("Server waiting on IP: %1\nport: %2\n\n")
    .arg(tcp_server->serverAddress().toString()).arg(tcp_server->serverPort());

  Q#messageBox::information(nullptr, "Qt Server",
                           QString(waiting_#message));
 }

 RZW* rzw = new RZW{*this, 18261, "", *(new QNetworkAccessManager)};

 QObject::connect(tcp_server, &QTcpServer::newConnection, [this, rzw, tcp_server, temps]
 {
  QTcpSocket* clientConnection = tcp_server->nextPendingConnection();
  Q#messageBox::information(nullptr, "Qt Server ...",
    QString("received: %1, %2")
    .arg(QString::fromLatin1("received")).arg(0));
  QObject::connect(clientConnection, &QTcpSocket::readyRead, [clientConnection, this, rzw, temps]
  {
   qintptr sd = clientConnection->socketDescriptor();
   QByteArray received = clientConnection->readAll();
   Q#messageBox::information(nullptr, "Qt Server",
     QString("received: %1, %2")
     .arg(QString::fromLatin1(received)).arg(sd));

//   while(clientConnection->bytesAvailable())
//   {
//    received.append(clientConnection->readAll());
//       Q#messageBox::information(nullptr, "Qt Server",
//                                QString("received: %1, %2")
//                                .arg(QString::fromLatin1(received)).arg(sd));
//   }
////   Q#messageBox::information(nullptr, "Qt Server",
////                            QString("received: %1, %2")
////                            .arg(QString::fromLatin1(received)).arg(sd));
//   if(received.endsWith("<//>"))
//   {
//    received.chop(4);
//    QByteArray qba = (*temps)[sd];
//    qba.append(received);
//    QByteArray block = "OK";
//    clientConnection->write(block);
//    clientConnection->disconnectFromHost();
//    temps->remove(sd);

//    int index = qba.indexOf("<<>>");

//    if(index != -1)
//    {
//     QString msg = QString::fromLatin1(qba.mid(index + 4));
//     if(msg != rzw->current_tcp_msg)
//       run_msg(*rzw, msg);
//    }
//   }
//   else
//   {
//    (*temps)[sd] += received;
//    clientConnection->disconnectFromHost();
//   }
  });
 });

#endif

 const char *fileName, *dest;
 GString *color;
 GBool ok;
 int pg, i;

 setApplicationName("XpdfReader");
 setApplicationVersion(xpdfVersion);

 ok = parseArgs(argDesc, &argc, argv);
 if (!ok || printVersionArg || printHelpArg) {
  fprintf(stderr, "xpdf version %s\n", xpdfVersion);
  fprintf(stderr, "%s\n", xpdfCopyright);
  if (!printVersionArg) {
   printUsage("xpdf", "[<PDF-file> [:<page> | +<dest>]] ...", argDesc);
  }
  ::exit(99);
 }

 //--- set up GlobalParams; handle command line arguments
 globalParams = new GlobalParams(cfgFileArg);
#ifdef _WIN32
 QString dir = applicationDirPath();
 globalParams->setBaseDir(dir.toLocal8Bit().constData());
 dir += "/t1fonts";
 globalParams->setupBaseFonts(dir.toLocal8Bit().constData());
#else
 globalParams->setupBaseFonts(NULL);
#endif
 if (initialZoomArg[0]) {
  globalParams->setInitialZoom(initialZoomArg);
 }
 reverseVideo = reverseVideoArg;
 if (paperColorArg[0]) {
  paperColor = QColor(paperColorArg);
 } else {
  color = globalParams->getPaperColor();
  paperColor = QColor(color->getCString());
  delete color;
 }
 if (reverseVideo) {
  paperColor = QColor(255 - paperColor.red(),
                      255 - paperColor.green(),
                      255 - paperColor.blue());
 }
 if (matteColorArg[0]) {
  matteColor = QColor(matteColorArg);
 } else {
  color = globalParams->getMatteColor();
  matteColor = QColor(color->getCString());
  delete color;
 }
 if (fsMatteColorArg[0]) {
  fsMatteColor = QColor(fsMatteColorArg);
 } else {
  color = globalParams->getFullScreenMatteColor();
  fsMatteColor = QColor(color->getCString());
  delete color;
 }
 if (antialiasArg[0]) {
  if (!globalParams->setAntialias(antialiasArg)) {
   fprintf(stderr, "Bad '-aa' value on command line\n");
  }
 }
 if (vectorAntialiasArg[0]) {
  if (!globalParams->setVectorAntialias(vectorAntialiasArg)) {
   fprintf(stderr, "Bad '-aaVector' value on command line\n");
  }
 }
 if (textEncArg[0]) {
  globalParams->setTextEncoding(textEncArg);
 }
 if (printCommandsArg) {
  globalParams->setPrintCommands(gTrue);
 }

 errorEventType = QEvent::registerEventType();

 viewers = new GList();

// // // rz
// connect(this, &XpdfApp::window_ready, [rzw, port]
// {
//  Q#messageBox::information(nullptr, "Qt Server",
//                           QString("hello:xpdf;%1")
//                           .arg(port));
//  send_msg(*rzw, QString("hello:xpdf;%1").arg(port));
// });

 //--- load PDF file(s) requested on the command line
 if (argc >= 2) {
  i = 1;
  while (i < argc) {
   pg = 1;
   dest = "";
   if (i+1 < argc && argv[i+1][0] == ':') {
    fileName = argv[i];
    pg = atoi(argv[i+1] + 1);
    i += 2;
   } else if (i+1 < argc && argv[i+1][0] == '+') {
    fileName = argv[i];
    dest = argv[i+1] + 1;
    i += 2;
   } else {
    fileName = argv[i];
    ++i;
   }
   if (viewers->getLength() > 0) {
    ok = ((XpdfViewer *)viewers->get(0))->openInNewTab(fileName, pg, dest,
                                                       passwordArg,
                                                       gFalse);
   } else {
    ok = openInNewWindow(fileName, pg, dest, passwordArg, fullScreen);
   }
  }
 } else {
  newWindow(fullScreen);
 }
}

XpdfApp::~XpdfApp() {
 delete viewers;
 delete globalParams;
}

int XpdfApp::getNumViewers() {
 return viewers->getLength();
}

void XpdfApp::newWindow(GBool fullScreen) {
 XpdfViewer *viewer = new XpdfViewer(this, fullScreen);
 viewers->append(viewer);
 viewer->show();
 //emit window_ready();
}

GBool XpdfApp::openInNewWindow(QString fileName, int page, QString dest,
                               QString password, GBool fullScreen) {
 XpdfViewer *viewer;

 viewer = XpdfViewer::create(this, fileName, page, dest, password, fullScreen);
 if (!viewer) {
  return gFalse;
 }
 viewers->append(viewer);
 viewer->tweakSize();
 viewer->show();
 return gTrue;
}

void XpdfApp::closeWindowOrQuit(XpdfViewer *viewer) {
 int i;

 viewer->close();
 for (i = 0; i < viewers->getLength(); ++i) {
  if ((XpdfViewer *)viewers->get(i) == viewer) {
   viewers->del(i);
   break;
  }
 }
}

void XpdfApp::quit() {
 XpdfViewer *viewer;

 while (viewers->getLength()) {
  viewer = (XpdfViewer *)viewers->del(0);
  viewer->close();
 }
 QApplication::quit();
}
