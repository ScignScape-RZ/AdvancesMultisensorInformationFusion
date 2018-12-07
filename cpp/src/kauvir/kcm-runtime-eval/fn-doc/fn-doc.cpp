
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "fn-doc.h"

#include "kcm-scopes/kcm-scope-system.h"

#include "kcm-env/kcm-env.h"

#include "kauvir-code-model/kcm-type-object.h"
#include "kauvir-type-system/kauvir-type-object.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kauvir-code-model.h"


#include <QTextStream>

#include <QDebug>

Fn_Doc::Fn_Doc()
  :  scopes_(nullptr), kenv_(nullptr)
{

}

Fn_Doc::Fn_Doc(const Fn_Doc& rhs)
  :  scopes_(rhs.scopes_), kenv_(rhs.kenv_)
{

}

Fn_Doc::~Fn_Doc()
{

}

void Fn_Doc::init(KCM_Env* kenv)
{
 kenv_ = kenv;
 scopes_ = kenv->scopes();
 qDebug() << "init...";
}


QString Fn_Doc::test_summary()
{
 if(kenv_)
   return "Fn_Doc: Initialized.";
 return "?Fn_Doc: Not Initialized.";
}


void Fn_Doc::read(QString fn)
{
 qDebug() << "fn: " << fn;
 const KCM_Type_Object* kto = scopes_->get_type_object_from_symbol_name(fn);
 if(kto)
 {
  if(kenv_)
  {
   kenv_->report_channel_group(kto->channel_group());
  }
 }
}

const KCM_Type_Object* Fn_Doc::get_type_object_from_symbol_name(QString fn)
{
 return scopes_->get_type_object_from_symbol_name(fn);
}

void Fn_Doc::kph_gen(QString subs)
{
 qDebug() << "fn: " << held_fn_;
 const KCM_Type_Object* kto = scopes_->get_type_object_from_symbol_name(held_fn_);
 if(kto)
 {
  if(kenv_)
  {
   kenv_->kph_gen(kto->channel_group(), subs,  held_fn_, nullptr, docus_[held_fn_]);
  }
 }
}

void Fn_Doc::add_documentation(QString key_val)
{
 int index = key_val.indexOf(':');
 if(index != -1)
 {
  docus_[held_fn_][key_val.left(index)] = key_val.mid(index + 1).trimmed();
 }
}

void Fn_Doc::hold_function_name(QString fn)
{
 held_fn_ = fn;
}

void Fn_Doc::kph_gen(const KCM_Type_Object* kto, QString fn, QString& text)
{
 if(kenv_)
 {
  kenv_->kph_gen(kto->channel_group(), fn, &text, docus_[fn]);
 }
}
