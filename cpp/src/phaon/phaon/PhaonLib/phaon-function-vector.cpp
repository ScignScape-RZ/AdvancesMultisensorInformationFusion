
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "phaon-function-vector.h"

#include "kauvir-code-model/kcm-function-package.h"
#include "kauvir-code-model/kcm-type-object.h"

#include "kans.h"

#include <QString>
#include <QDebug>

USING_KANS(KCM)

USING_KANS(PhaonLib)

Phaon_Function_Vector::Phaon_Function_Vector()
 :  QVector<Phaon_Function>()
{

}

void* Phaon_Function_Vector::get_first()
{
 Phaon_Function phf = first();
 KCM_Function_Package* kfp;
 void* fnp = phf.de_augment(kfp);
 return fnp;
}

void* Phaon_Function_Vector::find_argvec_function(int& mc, int& rbc,
  const KCM_Type_Object** pkto)
{
 for(Phaon_Function phf : *this)
 {
  KCM_Function_Package* kfp;
  void* fnp = phf.de_augment(kfp);
  int bc;
  int xbc = kfp->split_byte_code(bc);
  if( (bc % 10) == 9 )
  {
   mc = xbc;
   rbc = bc;
   if(pkto)
   {
    *pkto = kfp->result_type_object();
   }
   return fnp;
  }
 }
 return nullptr;
}

void* Phaon_Function_Vector::match_against_codes(const QSet<int>& codes,
  int& mc, int& rbc, const KCM_Type_Object** pkto)
{
 for(Phaon_Function phf : *this)
 {
  KCM_Function_Package* kfp;
  void* fnp = phf.de_augment(kfp);
  int bc;
  int xbc = kfp->split_byte_code(bc);
  if(codes.contains(xbc))
  {
   mc = xbc;
   rbc = bc;
   if(pkto)
   {
    *pkto = kfp->result_type_object();
   }
   return fnp;
  }
 }
 return nullptr;
}
