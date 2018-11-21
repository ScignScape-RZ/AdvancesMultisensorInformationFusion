
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-xml-document.h"

#include "phaon-xml-line.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>


#include "kans.h"
USING_KANS(PhaonXML)

#include "textio.h"
USING_KANS(TextIO)

Phaon_XML_Document::Phaon_XML_Document(QUrl url)
  : url_(url), state_(Stream_States::N_A)
{

}

void Phaon_XML_Document::set_url_from_file(QString f)
{
 set_url(QUrl::fromLocalFile(f));
}


QChar tttochar(const QXmlStreamReader::TokenType& tt)
{
 switch(tt)
 {
 case QXmlStreamReader::StartElement:
  return 's';
 case QXmlStreamReader::EndElement:
  return 'e';
 case QXmlStreamReader::Characters:
  return 't';
 }
 return '_';
}

void Phaon_XML_Document::transpile(QString path)
{
 QFile file(url_.toLocalFile());
 if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
 {
  state_ = Stream_States::No_Data;
  return;
 }
 state_ = Stream_States::Pre;
 QXmlStreamReader qxr;
 qxr.setDevice(&file);
 while(!qxr.atEnd())
 {
  qxr.readNext();
  QChar tt = tttochar(qxr.tokenType());
  if(tt == 't')
  {
   QString qs = "!trm";
   QStringRef txt = qxr.text();
   run_state(tt, qs, qxr.attributes(), txt.toString().trimmed());
  }
  else if(tt != '_')
  {
   QStringRef qs = qxr.name();
   QStringRef txt = qxr.text();
   run_state(tt, qs.toString(), qxr.attributes(), txt.toString());
  }
 }
 QString text = "- Auto generated\n.\n";
 for(Phaon_XML_Line* l : lines_)
 {
  text += l->to_string();
 }
 TextIO::save_file(path, text);
 file.close();
}


void Phaon_XML_Document::transpile()
{
 transpile(url_.toLocalFile() + ".txt");
}


void Phaon_XML_Document::run_state(QChar tt, QString tagn,
  const QXmlStreamAttributes& attributes, QString txt)
{
 static QMap<
   QPair< QPair<Stream_States, QChar>, QString>,
   void(*)(Phaon_XML_Document&, const QXmlStreamAttributes& attributes, QString txt)
   > static_map {{
   {{ {Stream_States::Pre, 's'}, "kauvir-phaon-xml"}, [](Phaon_XML_Document& _this,
      const QXmlStreamAttributes& attributes, QString txt)
 {
  _this.state_ = Stream_States::Entered;
 }  },
   {{ {Stream_States::Entered, 's'}, "ch" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  ch_Line* l = new ch_Line;
  l->code = attributes.value("c").toInt();
  l->name = attributes.value("n").toString();
  _this.lines_.push_back(l);
 }  },
   {{ {Stream_States::Entered, 's'}, "ty" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  ty_Line* l = new ty_Line;
  l->code = attributes.value("c").toInt();
  l->name = attributes.value("n").toString();
  _this.lines_.push_back(l);
 }  },
   {{ {Stream_States::Entered, 's'}, "pkg" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  pkg_Line* l = new pkg_Line;
  l->code = attributes.value("c").toInt();
  _this.lines_.push_back(l);
  _this.state_ = Stream_States::Pkg;
 }  },
   {{ {Stream_States::Pkg, 's'}, "fuxe" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  fuxe_Line* l = new fuxe_Line;
  l->name = attributes.value("n").toString();
  _this.lines_.push_back(l);
 }  },
   {{ {Stream_States::Pkg, 's'}, "arg" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  arg_Line* l = new arg_Line;
  l->code = attributes.value("c").toInt();
  l->ch_code = attributes.value("chc").toInt();
  l->ty_code = attributes.value("tyc").toInt();
  _this.lines_.push_back(l);
  _this.state_ = Stream_States::Arg;
 }  },
   {{ {Stream_States::Arg, 't'}, "!trm" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  arg_Line* l = static_cast<arg_Line*>(_this.lines_.last());
  l->text = txt;
 }  },
   {{ {Stream_States::Arg, 'e'}, "arg" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  _this.state_ = Stream_States::Pkg;
 }  },
   {{ {Stream_States::Pkg, 'e'}, "pkg" }, [](Phaon_XML_Document& _this,
    const QXmlStreamAttributes& attributes, QString txt)
 {
  _this.state_ = Stream_States::Entered;
 }  }


 }};

 auto it = static_map.find({{state_, tt}, tagn});
 if(it != static_map.end())
 {
  (**it)(*this, attributes, txt);
 }
}
