
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef KAUVIR_UNIVERSAL_CLASS__H
#define KAUVIR_UNIVERSAL_CLASS__H


#include "kans.h"

#include "accessors.h"

#include <QVector>

class Kauvir_Universal_Class
{
};


typedef quint64 u64t;
typedef quint32 u32t;


template<int byc>
struct tybc;


#define TYBC_2(bc, a, b) \
template<> \
struct tybc<bc> \
{ \
 typedef u##a##t a0; \
 typedef u##b##t a1; \
 typedef QString(*_sr)(a0, a1); \
 typedef void*(*_r)(a0, a1); \
 typedef void(*_nor)(a0, a1); \
}; \

TYBC_2(944, 32, 32)
TYBC_2(948, 32, 64)
TYBC_2(984, 64, 32)
TYBC_2(988, 64, 64)



#define TYBC_1(bc, a) \
template<> \
struct tybc<bc> \
{ \
 typedef u##a##t a0; \
 typedef QString(*_sr)(a0); \
 typedef void*(*_r)(a0); \
 typedef void(*_nor)(a0); \
}; \

TYBC_1(94, 32)
TYBC_1(98, 64)

typedef void* pvt;
typedef void*& pvrt;

typedef pvt pvft;


typedef void(Kauvir_Universal_Class::*fn0_type)();
typedef void(Kauvir_Universal_Class::*fn1_type)(void*&);
typedef void(Kauvir_Universal_Class::*fn2_type)(quint64&, quint64&);
typedef void(Kauvir_Universal_Class::*fn3_type)(void*&, void*&, void*&);


typedef void(Kauvir_Universal_Class::*s1_fn1_p_type)(pvft);

typedef void(Kauvir_Universal_Class::*fn1_p_type)(pvft);
typedef void(Kauvir_Universal_Class::*fn1_r_type)(quint64&);
typedef void(Kauvir_Universal_Class::*fn1_s_type)(QString);

typedef void*(Kauvir_Universal_Class::*fn1_p_wrtn_type)(pvft);
typedef void*(Kauvir_Universal_Class::*fn1_r_wrtn_type)(quint64&);
typedef void*(Kauvir_Universal_Class::*fn1_s_wrtn_type)(QString);

typedef void(*_s0_fn1_p_type)(pvft);
typedef void(*_s0_fn1_r_type)(quint64&);
typedef void(*_s0_fn1_s_type)(QString);

typedef void*(*s0_fn1_p_type)(pvft);
typedef void*(*s0_fn1_r_type)(quint64&);
typedef void*(*s0_fn1_s_type)(QString);

typedef void*(*s0_fn1_p_p_type)(pvft, pvft);
typedef void(*_s0_fn1_p_p_type)(pvft, pvft);

typedef void(*_s0_fn1_64_64_type)(u64t, u64t);
typedef void(*_s0_fn1_32_32_type)(u32t, u32t);

typedef void*(*s0_fn1_64_64_type)(u64t, u64t);
typedef void*(*s0_fn1_32_32_type)(u32t, u32t);

typedef void(*_s0_fn1_64_32_type)(u64t, u32t);
typedef void(*_s0_fn1_32_64_type)(u32t, u64t);
typedef void*(*s0_fn1_64_32_type)(u64t, u32t);
typedef void*(*s0_fn1_32_64_type)(u32t, u64t);

typedef void*(*s0_fn1_64_type)(u64t);
typedef void*(*s0_fn1_32_type)(u32t);
typedef void(*_s0_fn1_64_type)(u64t);
typedef void(*_s0_fn1_32_type)(u32t);

typedef void*(*s0_fn1_void_type)();
typedef void(*_s0_fn1_void_type)();
typedef QString(*s0_fn1_void__s_type)();


typedef QString(*s0_fn1_p__s_type)(pvft);
typedef QString(*s0_fn1_r__s_type)(quint64&);
typedef QString(*s0_fn1_s__s_type)(QString);

typedef QString(*s0_fn1_p_p__s_type)(pvft, pvft);


typedef void*(*s0_fng_type)();
typedef void(*_s0_fng_type)();

typedef void(Kauvir_Universal_Class::*fn2_pp_type)(pvft, pvft);
typedef void(Kauvir_Universal_Class::*fn2_rp_type)(quint64&, pvft);
typedef void(Kauvir_Universal_Class::*fn2_sp_type)(QString, pvft);

typedef void(Kauvir_Universal_Class::*fn2_pr_type)(pvft, quint64&);
typedef void(Kauvir_Universal_Class::*fn2_rr_type)(quint64&, quint64&);
typedef void(Kauvir_Universal_Class::*fn2_sr_type)(QString, quint64&);

typedef void(Kauvir_Universal_Class::*fn2_ps_type)(pvft, QString);
typedef void(Kauvir_Universal_Class::*fn2_rs_type)(quint64&, QString);
typedef void(Kauvir_Universal_Class::*fn2_ss_type)(QString, QString);


typedef void*(Kauvir_Universal_Class::*fn2_pp_wrtn_type)(pvft, pvft);
typedef void*(Kauvir_Universal_Class::*fn2_rp_wrtn_type)(quint64&, pvft);
typedef void*(Kauvir_Universal_Class::*fn2_sp_wrtn_type)(QString, pvft);

typedef void*(Kauvir_Universal_Class::*fn2_pr_wrtn_type)(pvft, quint64&);
typedef void*(Kauvir_Universal_Class::*fn2_rr_wrtn_type)(quint64&, quint64&);
typedef void*(Kauvir_Universal_Class::*fn2_sr_wrtn_type)(QString, quint64&);

typedef void*(Kauvir_Universal_Class::*fn2_ps_wrtn_type)(pvft, QString);
typedef void*(Kauvir_Universal_Class::*fn2_rs_wrtn_type)(quint64&, QString);
typedef void*(Kauvir_Universal_Class::*fn2_ss_wrtn_type)(QString, QString);

//typedef void(Kauvir_Universal_Class::*fng_type)();

typedef void(Kauvir_Universal_Class::*_s1_fng_type)();
typedef void*(Kauvir_Universal_Class::*s1_fng_type)();

template<typename T, int Index>
struct ARG_Type
{

};

#define TEMP_MACRO(ty, index, Typ) \
 template<> \
 struct ARG_Type<fn2_##ty##_type, index> \
 { \
  typedef Typ Type; \
 }; \


TEMP_MACRO(pp, 1, pvft)
TEMP_MACRO(pp, 2, pvft)

TEMP_MACRO(ps, 1, pvft)
TEMP_MACRO(ps, 2, QString)

TEMP_MACRO(rp, 1, quint64&)
TEMP_MACRO(rp, 2, pvft)

TEMP_MACRO(rr, 1, quint64&)
TEMP_MACRO(rr, 2, quint64&)

TEMP_MACRO(rs, 1, quint64&)
TEMP_MACRO(rs, 2, QString)

TEMP_MACRO(ss, 1, QString)
TEMP_MACRO(ss, 2, QString)

TEMP_MACRO(pr, 1, pvft)
TEMP_MACRO(pr, 2, quint64&)

TEMP_MACRO(sp, 1, QString)
TEMP_MACRO(sp, 2, pvft)

TEMP_MACRO(sr, 1, QString)
TEMP_MACRO(sr, 2, quint64&)

#undef TEMP_MACRO

#define TEMP_MACRO(ty, index, Typ) \
 template<> \
 struct ARG_Type<fn1_##ty##_type, index> \
 { \
  typedef Typ Type; \
 }; \


TEMP_MACRO(p, 1, pvft)
TEMP_MACRO(r, 1, quint64&)
TEMP_MACRO(s, 1, QString)

#undef TEMP_MACRO




struct FN_Type_Interchange_Argument__Pointer
{
};

struct FN_Type_Interchange_Argument__Reference
{
};

struct FN_Type_Interchange_Argument__QString
{
};

template<int ARG_Count>
struct FN_Type_Arg_Count
{

};


template<>
struct FN_Type_Arg_Count<2>
{
 typedef fn2_pp_type Type;
};

template<>
struct FN_Type_Arg_Count<1>
{
 typedef fn1_p_type Type;
};

template<>
struct FN_Type_Arg_Count<0>
{
 typedef fn0_type Type;
};

template<typename T, typename AA, int Interchange_Position>
struct FN_Type_Interchange
{
 //?typedef fng_type Type;
};

template<int Interchange_Position>
struct FN_Type_Interchange<fn2_pp_type,
  FN_Type_Interchange_Argument__Pointer, Interchange_Position>
{
 typedef fn2_pp_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_pp_type,
  FN_Type_Interchange_Argument__Reference, 0>
{
 typedef fn2_rp_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_pp_type,
  FN_Type_Interchange_Argument__Reference, 1>
{
 typedef fn2_pr_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_pp_type,
  FN_Type_Interchange_Argument__QString, 0>
{
 typedef fn2_sp_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_pp_type,
  FN_Type_Interchange_Argument__QString, 1>
{
 typedef fn2_ps_type Type;
 //?typedef fng_type Type;
};


template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__Pointer, 0>
{
 typedef fn2_pp_type Type;
 //?typedef fng_type Type;
};


template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__Reference, 0>
{
 typedef fn2_rp_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__QString, 0>
{
 typedef fn2_sp_type Type;
 //?typedef fng_type Type;
};

template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__QString, 1>
{
 typedef fn2_rs_type Type;
 //?typedef fng_type Type;
};


template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__Reference, 1>
{
 typedef fn2_rr_type Type;
 //?typedef fng_type Type;
};


template<>
struct FN_Type_Interchange<fn2_rp_type,
  FN_Type_Interchange_Argument__Pointer, 1>
{
 typedef fn2_pp_type Type;
 //?typedef fng_type Type;
};

#define TEMP_MACRO(SPR, Variant, Index, New_SPR) \
 template<> \
 struct FN_Type_Interchange<fn2_##SPR##_type, \
   FN_Type_Interchange_Argument__##Variant, Index> \
 { \
  typedef fn2_##New_SPR##_type Type; \
 }; \


TEMP_MACRO(pr, Pointer, 1, pp)
TEMP_MACRO(pr, Reference, 0, rp)
TEMP_MACRO(pr, Reference, 1, pr)
TEMP_MACRO(pr, QString, 0, sr)
TEMP_MACRO(pr, QString, 1, ps)
TEMP_MACRO(sp, Pointer, 0, pp)
TEMP_MACRO(sp, Pointer, 1, sp)
TEMP_MACRO(sp, Reference, 0, rp)
TEMP_MACRO(sp, Reference, 1, sr)
TEMP_MACRO(sp, QString, 0, sp)
TEMP_MACRO(sp, QString, 1, ss)

TEMP_MACRO(ps, Pointer, 0, ps)
TEMP_MACRO(ps, Pointer, 1, pp)
TEMP_MACRO(ps, Reference, 0, rs)
TEMP_MACRO(ps, Reference, 1, pr)
TEMP_MACRO(ps, QString, 0, ss)
TEMP_MACRO(ps, QString, 1, ps)

TEMP_MACRO(rr, Pointer, 0, pr)
TEMP_MACRO(rr, Pointer, 1, rp)
TEMP_MACRO(rr, Reference, 0, rr)
TEMP_MACRO(rr, Reference, 1, rr)
TEMP_MACRO(rr, QString, 0, sr)
TEMP_MACRO(rr, QString, 1, rs)

TEMP_MACRO(rs, Pointer, 0, ps)
TEMP_MACRO(rs, Pointer, 1, rp)
TEMP_MACRO(rs, Reference, 0, rs)
TEMP_MACRO(rs, Reference, 1, rr)
TEMP_MACRO(rs, QString, 0, ss)
TEMP_MACRO(rs, QString, 1, rs)

TEMP_MACRO(sr, Pointer, 0, pr)
TEMP_MACRO(sr, Pointer, 1, sp)
TEMP_MACRO(sr, Reference, 0, rr)
TEMP_MACRO(sr, Reference, 1, sr)
TEMP_MACRO(sr, QString, 0, sr)
TEMP_MACRO(sr, QString, 1, ss)

TEMP_MACRO(ss, Pointer, 0, ps)
TEMP_MACRO(ss, Pointer, 1, sp)
TEMP_MACRO(ss, Reference, 0, rs)
TEMP_MACRO(ss, Reference, 1, sr)
TEMP_MACRO(ss, QString, 0, ss)
TEMP_MACRO(ss, QString, 1, ss)

#undef TEMP_MACRO


template<>
struct FN_Type_Interchange<fn2_pr_type,
  FN_Type_Interchange_Argument__Pointer, 0>
{
 typedef fn2_pr_type Type;
 //?typedef fng_type Type;
};


#define TEMP_MACRO(SPR, Variant, Index, New_SPR) \
 template<> \
 struct FN_Type_Interchange<fn1_##SPR##_type, \
   FN_Type_Interchange_Argument__##Variant, Index> \
 { \
  typedef fn1_##New_SPR##_type Type; \
 }; \


TEMP_MACRO(p, Pointer, 0, p)
TEMP_MACRO(p, Reference, 0, r)
TEMP_MACRO(p, QString, 0, s)
TEMP_MACRO(r, Pointer, 0, p)
TEMP_MACRO(r, Reference, 0, r)
TEMP_MACRO(r, QString, 0, s)
TEMP_MACRO(s, Pointer, 0, p)
TEMP_MACRO(s, Reference, 0, r)
TEMP_MACRO(s, QString, 0, s)

#undef TEMP_MACRO


#endif //KAUVIR_UNIVERSAL_CLASS__H

