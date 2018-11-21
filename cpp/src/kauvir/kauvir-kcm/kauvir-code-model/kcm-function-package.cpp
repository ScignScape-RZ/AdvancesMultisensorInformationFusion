
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "kcm-function-package.h"

#include "kcm-channel-group.h"


#include "kans.h"

USING_KANS(KCM)
USING_KANS(Kauvir)

KCM_Function_Package::KCM_Function_Package(KCM_Channel_Group* kcg)
  :  kcg_(kcg), byte_code_(0)
{

}

void KCM_Function_Package::init_byte_code_s1(bool sr)
{
 int head = sr? 601 : 701;
 init_byte_code(head);
}

void KCM_Function_Package::init_byte_code_s0(bool sr)
{
 int head = sr? 600 : 700;
 init_byte_code(head);
}

void KCM_Function_Package::init_byte_code(int head)
{
 quint32 lbc = kcg_->get_sigma_lambda_byte_code();

 quint32 tmp = lbc;

 int len = 0;
 if ( tmp >= 100000000 ) { len += 8; tmp /= 100000000; }
 if ( tmp >= 10000     ) { len += 4; tmp /= 10000; }
 if ( tmp >= 100       ) { len += 2; tmp /= 100; }
 if ( tmp >= 10        ) { len += 1; }

 quint32 bc = lbc;
 bc *= 10;
 bc += len;

 for(int i = 0; i < len + 2; ++i)
 {
  head *= 10;
 }

 bc += head;

 byte_code_ = bc;

}


const KCM_Type_Object* KCM_Function_Package::result_type_object()
{
 if(kcg_)
 {
  KCM_Channel& rch = kcg_->result_ch();
  if(!rch.carriers().isEmpty())
  {
   KCM_Carrier r1;
   rch.get_carrier_at_position(0, r1);
   return r1.type_object();
  }
 }
 return nullptr;
}

int KCM_Function_Package::split_byte_code(int& xbc)
{
 int bc = byte_code_;
 int len = bc % 10;
 bc /= 10;
 int l10 = 1;
 for(int i = 0; i <= len; ++i)
 {
  l10 *= 10;
 }
 xbc = bc % l10;
 bc /= l10;
 return (bc * 10) + len;
}

void KCM_Function_Package::init_byte_code_s10(bool sr)
{
 int head = sr? 610 : 710;
 init_byte_code(head);
}





