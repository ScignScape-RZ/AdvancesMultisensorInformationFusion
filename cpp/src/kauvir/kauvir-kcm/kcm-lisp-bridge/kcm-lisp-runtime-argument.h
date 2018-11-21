
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LISP_RUNTIME_ARGUMENT__H
#define KCM_LISP_RUNTIME_ARGUMENT__H



#include <QObject>
#include <QMap>

#include "kauvir-code-model/kauvir-code-model.h"

#include "kcm-lisp-bridge.h"

USING_KANS(KCM)

KANS_(KCL)

class KCM_Lisp_Runtime_Argument
{
public:

 enum class Kinds {

  N_A, String, Cl_Object, PVoid, Opaque_Lisp_Value

 };

 QString string_;
 quint64 cl_object_;
 void* pVoid_;

public:

 KCM_Lisp_Runtime_Argument(QString string);
 KCM_Lisp_Runtime_Argument(quint64 cl_object);
 KCM_Lisp_Runtime_Argument(void* pVoid = nullptr);

 ACCESSORS__GET(QString ,string)
 ACCESSORS__GET(quint64 ,cl_object)
 ACCESSORS(void* ,pVoid)

 ACCESSORS__SDECLARE(QString ,string)
 ACCESSORS__SDECLARE(quint64 ,cl_object)

 void set_as_fixnum(int i);
 void set_opaque_lisp_value(quint64 cl_object);

 Kinds get_kind() const;

 void** pointer_for_qarg();
};

_KANS(KCL)


#endif //KCM_LISP_RUNTIME_ARGUMENT__H
