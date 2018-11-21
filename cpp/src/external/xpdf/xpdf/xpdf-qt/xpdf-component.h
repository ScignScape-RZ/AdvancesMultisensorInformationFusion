//  BASED ON (with small modifications) code Copyright 2015 Glyph & Cog, LLC

//  This specific file and project
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef XPDF_COMPONENT__H
#define XPDF_COMPONENT__H

#include <aconf.h>

#include <QApplication>
#include <QColor>
#include "gtypes.h"

class GList;
class XpdfViewer;

//------------------------------------------------------------------------
// Xpdf_Component
//------------------------------------------------------------------------

class Xpdf_Component
{
public:

  Xpdf_Component(int &argc, char **argv);
  virtual ~Xpdf_Component();

  int getNumViewers();

  void newWindow(GBool fullScreen = gFalse);

  GBool openInNewWindow(QString fileName, int page = 1,
   QString dest = QString(),
   QString password = QString(),
   GBool fullScreen = gFalse);

  void closeWindowOrQuit(XpdfViewer *viewer);

  void quit();

  //--- for use by XpdfViewer

  int getErrorEventType() { return errorEventType; }
  const QColor &getPaperColor() { return paperColor; }
  const QColor &getMatteColor() { return matteColor; }
  const QColor &getFullScreenMatteColor() { return fsMatteColor; }
  GBool getReverseVideo() { return reverseVideo; }

  QString state() { return state_; }

private:

  QString state_;


  int errorEventType;
  QColor paperColor;
  QColor matteColor;
  QColor fsMatteColor;
  GBool reverseVideo;

  GList *viewers;		// [XpdfViewer]
};

#endif // XPDF_COMPONENT__H
