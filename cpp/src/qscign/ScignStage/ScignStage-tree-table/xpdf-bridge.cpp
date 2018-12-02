
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)




#ifdef USING_XPDF

#include "xpdf-bridge.h"

#include "xpdf/xpdf-qt/xpdf-component.h"

#include <QThread>
#include <QDebug>

extern void xpdf_component_main(int argc, char *argv[], Xpdf_Component** xpc);

XPDF_Bridge::XPDF_Bridge(int argc, char** argv)
  :  argc_(argc), argv_(argv), xpdf_component_(nullptr)
{

}

void XPDF_Bridge::take_message(QString msg)
{
 qDebug() << "msg: " << msg;

 int index = msg.indexOf(':');
 QString key = msg.left(index);

 QString arg = msg.mid(index + 1);

 if(key == "open")
 {
  int index = arg.indexOf(';');
  QString file = arg.left(index);
  int page = arg.mid(index + 1).toInt();
  xpdf_component_->openInNewWindow(file, page);

 }



}

void XPDF_Bridge::init()
{
 xpdf_component_main(argc_, argv_, &xpdf_component_);

 QThread* thr = QThread::create([this]
 {
  while(true)
  {
   if(is_ready())
   {
    Q_EMIT xpdf_is_ready();
//    thr->exit();
//    thr->deleteLater();
    break;
   }
  }
 });

 connect(thr, &QThread::finished, [thr]
 {
  thr->deleteLater();
 });

 thr->start();

}


bool XPDF_Bridge::is_ready()
{
 if(xpdf_component_)
   return !xpdf_component_->state().isEmpty();
 return false;
}

#endif // USING_XPDF

