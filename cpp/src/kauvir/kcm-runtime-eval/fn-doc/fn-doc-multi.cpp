
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "fn-doc-multi.h"

#include "kcm-scopes/kcm-scope-system.h"

#include "kcm-env/kcm-env.h"

#include "kauvir-code-model/kcm-type-object.h"
#include "kauvir-type-system/kauvir-type-object.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kauvir-code-model.h"

#include "fn-doc.h"

#include "textio.h"

#include <QTextStream>
#include <QDebug>

USING_KANS(TextIO)


Fn_Doc_Multi::Fn_Doc_Multi()
  :  fnd_(nullptr)
{

}

Fn_Doc_Multi::Fn_Doc_Multi(const Fn_Doc_Multi& rhs)
  :  fnd_(rhs.fnd_)
{

}

Fn_Doc_Multi::~Fn_Doc_Multi()
{
 // // should be unnecessary
 // // delete fnd_;
}

void Fn_Doc_Multi::init(KCM_Env* kenv)
{
 fnd_ = new Fn_Doc;
 fnd_->init(kenv);
}


void Fn_Doc_Multi::read(QString fn)
{
 const KCM_Type_Object* kto = fnd_->get_type_object_from_symbol_name(fn);
 if(kto)
 {
  fns_.push_back({fn, kto});
 }
}

void Fn_Doc_Multi::kph_gen_multi(QString path)
{
 QString text;
 QListIterator<QPair<QString, const KCM_Type_Object*>> it(fns_);
 while(it.hasNext())
 {
  const QPair<QString, const KCM_Type_Object*>& pr = it.next();
  QString txt;
  QString fn = pr.first;
  const KCM_Type_Object* kto = pr.second;
  fnd_->kph_gen(kto, fn, txt);
  if(it.hasNext())
  {
   if(txt.endsWith('-'))
   {
    txt.chop(1);
    txt += "##\n.\n";
   }
  }
  text += txt;
 }
 if(path.startsWith('@'))
 {
  path = path.mid(1);
  path.prepend(AR_ROOT_DIR);
 }
 save_file(path, text);
}
