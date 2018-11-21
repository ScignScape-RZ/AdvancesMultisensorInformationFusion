
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-lisp-runtime.h"

#include "kauvir-code-model/kcm-channel-group.h"
#include "kauvir-code-model/kcm-statement.h"
#include "kauvir-code-model/kcm-block.h"
#include "kauvir-code-model/kcm-channel.h"
#include "kauvir-code-model/kcm-expression.h"
#include "kauvir-code-model/kcm-file.h"

#include "kcm-command-package/kcm-command-package.h"

Q_DECLARE_METATYPE(KCM_Command_Package*)

#include "kcm-lisp-runtime-argument.h"

#include "rz-dynamo-generator/rz-dynamo-generator.h"

#include <QMetaMethod>
#include <QDebug>

#include "object.hpp"

USING_KANS(KCL)
USING_KANS(KCM)

Q_DECLARE_METATYPE(KCM_Channel_Group*)
Q_DECLARE_METATYPE(const KCM_Type_Object*)
Q_DECLARE_METATYPE(KCM_Type_Object*)
Q_DECLARE_METATYPE(KCM_Expression*)
Q_DECLARE_METATYPE(KCM_Statement*)
Q_DECLARE_METATYPE(KCM_File*)
Q_DECLARE_METATYPE(KCM_Block*)


KCM_Lisp_Runtime::KCM_Lisp_Runtime(QTextStream& qts)
  :  rdg_(new RZ_Dynamo_Generator(qts))
{
 _init();
}


KCM_Lisp_Runtime::KCM_Lisp_Runtime()
  :  rdg_(nullptr)
{
 _init();
}


void KCM_Lisp_Runtime::_init()
{
 qRegisterMetaType<KA::KCM::KCM_Channel_Group*>();
 qRegisterMetaType<const KA::KCM::KCM_Type_Object*>();
 qRegisterMetaType<KA::KCM::KCM_Type_Object*>();
 qRegisterMetaType<KA::KCM::KCM_Expression*>();
 qRegisterMetaType<KA::KCM::KCM_Statement*>();
 qRegisterMetaType<KA::KCM::KCM_File*>();
 qRegisterMetaType<KA::KCM::KCM_Block*>();
 qRegisterMetaType<KA::CMD::KCM_Command_Package*>();


 bridge_type_id_ = QMetaType::type("KCM_Lisp_Bridge*");
 bridge_qmo_ = QMetaType::metaObjectForType(bridge_type_id_);

 for(int i = bridge_qmo_->methodOffset(); i < bridge_qmo_->methodCount(); ++i)
 {
  QMetaMethod qmm = bridge_qmo_->method(i);
  if(bridge_qmo_methods_.contains(qmm.name()))
  {
   qDebug() << "Warning: KCM Lisp Runtime cannot use overloads; method signature will be overwritten:" << qmm.name();
  }
  bridge_qmo_methods_[QString::fromLatin1(qmm.name())] =
    {qmm.returnType(), bridge_qmo_->method(i).parameterTypes()};
 }

}

void KCM_Lisp_Runtime::kcm_call(QString method_name, QVector<KCM_Lisp_Runtime_Argument>& klras)
{
 if(!bridge_qmo_methods_.contains(method_name))
 {
  qDebug() << "Method not found: " << method_name;
  return;
 }

 int rt = bridge_qmo_methods_[method_name].first;
 if(rt == QMetaType::UnknownType)
 {
  qDebug() << "Unrecognized return type for method: " << method_name;
  return;
 }
 const QList<QByteArray>& params = bridge_qmo_methods_[method_name].second;

 QString rtn = QString::fromLatin1(QMetaType::typeName(rt));

 if(rtn == "void")
 {
  kcm_call_void_return(method_name, klras, params);
  klras[0].set_cl_object((quint64) ECL_NIL);
  return;
 }
 else
 {
  kcm_call(method_name, rtn, klras, params);
  return;
 }
}

void KCM_Lisp_Runtime::kcm_call_void_return(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 switch(klras.size())
 {
 case 1:
  kcm_call_0_v(method_name, klras, params);
  break;

 case 2:
  kcm_call_1_v(method_name, klras, params);
  break;

 case 3:
  kcm_call_2_v(method_name, klras, params);
  break;

 case 4:
  kcm_call_3_v(method_name, klras, params);
  break;

 case 5:
  kcm_call_4_v(method_name, klras, params);
  break;
 }
}

void KCM_Lisp_Runtime::kcm_call(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 switch(klras.size())
 {
 case 1:
  if(return_type_name.endsWith('*'))
   kcm_call_0_p(method_name, return_type_name, klras, params);
  else if(return_type_name == "int")
   kcm_call_0_i(method_name, return_type_name, klras, params);
  else
   kcm_call_0_s(method_name, return_type_name, klras, params);
  break;

 case 2:
  if(return_type_name.endsWith('*'))
   kcm_call_1_p(method_name, return_type_name, klras, params);
  else if(return_type_name == "int")
   kcm_call_1_i(method_name, return_type_name, klras, params);
  else
   kcm_call_1_s(method_name, return_type_name, klras, params);
  break;

 case 3:
  if(return_type_name.endsWith('*'))
   kcm_call_2_p(method_name, return_type_name, klras, params);
  else if(return_type_name == "int")
   kcm_call_2_i(method_name, return_type_name, klras, params);
  else
   kcm_call_2_s(method_name, return_type_name, klras, params);
  break;

 case 4:
  if(return_type_name.endsWith('*'))
   kcm_call_3_p(method_name, return_type_name, klras, params);
  else if(return_type_name == "int")
   kcm_call_3_i(method_name, return_type_name, klras, params);
  else
   kcm_call_3_s(method_name, return_type_name, klras, params);
  break;

 case 5:
  if(return_type_name.endsWith('*'))
   kcm_call_4_p(method_name, return_type_name, klras, params);
  else if(return_type_name == "int")
   kcm_call_4_i(method_name, return_type_name, klras, params);
  else
   kcm_call_4_s(method_name, return_type_name, klras, params);
  break;
 }
}

void KCM_Lisp_Runtime::kcm_call_0_v(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 // //  for examination ...
 if(method_name == "kcm_enter_runtime_scope")
 {
  bridge_.kcm_enter_runtime_scope();
  return;
 }

 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1());
}

void KCM_Lisp_Runtime::kcm_call_0_p(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 void* pv;

 // //  for examination ...
 if(method_name == "new_KCM_Channel_Group")
 {
  pv = bridge_.new_KCM_Channel_Group();
  klras[0].set_pVoid(pv);
  return;
 }

 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<void*>(return_type_name.toLatin1(), pv));
 klras[0].set_pVoid(pv);
}

void KCM_Lisp_Runtime::kcm_call_0_i(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 int i;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<int>(return_type_name.toLatin1(), i));
 klras[0].set_as_fixnum(i);
}

void KCM_Lisp_Runtime::kcm_call_0_s(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QString str;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(), QReturnArgument<QString>("QString", str));
 klras[0].set_string(str);
}


void KCM_Lisp_Runtime::kcm_call_1_v(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QMetaObject::invokeMethod(&bridge_,
   method_name.toLatin1(),
   QArgument<void*>(params[0], *klras[1].pointer_for_qarg()));
}

void KCM_Lisp_Runtime::kcm_call_1_p(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 void* pv;

 // //  for examination ...
 if(method_name == "kcm_dissolve_to_nested_expression")
 {
  KCM_Channel_Group** a1 = (KCM_Channel_Group**) klras[1].pointer_for_qarg();
  pv = bridge_.kcm_dissolve_to_nested_expression(*a1);
  klras[0].set_pVoid(pv);
  return;
 }

 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<void*>(return_type_name.toLatin1(), pv),
   QArgument<void*>(params[0], *klras[1].pointer_for_qarg()));
 klras[0].set_pVoid(pv);
}

void KCM_Lisp_Runtime::kcm_call_1_i(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 int i;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<int>(return_type_name.toLatin1(), i),
   QArgument<void*>(params[0], *klras[1].pointer_for_qarg()));
 klras[0].set_as_fixnum(i);
}

void KCM_Lisp_Runtime::kcm_call_1_s(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QString str;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<QString>("QString", str),
   QArgument<void*>(params[0], *klras[1].pointer_for_qarg()));
 klras[0].set_string(str);
}

void KCM_Lisp_Runtime::kcm_call_2_v(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 // //  for examination ...
 if(method_name == "_kcm_hold_opaque_lisp_value")
 {
  QString* a1 = (QString*) klras[1].pointer_for_qarg();
  Opaque_Lisp_Value* a2 = (Opaque_Lisp_Value*) klras[2].pointer_for_qarg();
  bridge_._kcm_hold_opaque_lisp_value(*a1, *a2);
  return;
 }

 if(method_name == "_kcm_load_bridge")
 {
  QString* a1 = (QString*) klras[1].pointer_for_qarg();
  Opaque_Lisp_Value* a2 = (Opaque_Lisp_Value*) klras[2].pointer_for_qarg();
  bridge_._kcm_load_bridge(*a1, *a2);
  return;
 }


 QMetaObject::invokeMethod(&bridge_,
   method_name.toLatin1(),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()));
}


void KCM_Lisp_Runtime::kcm_call_2_p(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 void* pv;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<void*>(return_type_name.toLatin1(), pv),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()));
 klras[0].set_pVoid(pv);
}

void KCM_Lisp_Runtime::kcm_call_2_i(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 int i;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<int>(return_type_name.toLatin1(), i),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()));
 klras[0].set_as_fixnum(i);
}

void KCM_Lisp_Runtime::kcm_call_2_s(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QString str;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<QString>("QString", str),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()));
 klras[0].set_string(str);
}




void KCM_Lisp_Runtime::kcm_call_3_v(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 // for examination ...
 if(method_name == "kcm_kcg_add_fuxe_carrier")
 {
  KCM_Channel_Group** a1 = (KCM_Channel_Group**) klras[1].pointer_for_qarg();
  const KCM_Type_Object** a2 = (const KCM_Type_Object**) klras[2].pointer_for_qarg();
  QString* a3 = (QString*) klras[3].pointer_for_qarg();
  bridge_.kcm_kcg_add_fuxe_carrier(*a1, *a2, *a3);
  return;
 }
 if(method_name == "kcg_lambda_carrier_from_result_channel")
 {
  KCM_Channel_Group** a1 = (KCM_Channel_Group**) klras[1].pointer_for_qarg();
  int* a2 = (int*) klras[2].pointer_for_qarg();
  int* a3 = (int*) klras[3].pointer_for_qarg();
  bridge_.kcg_lambda_carrier_from_result_channel(*a1, *a2, *a3);
  return;
 }

 QMetaObject::invokeMethod(&bridge_,
   method_name.toLatin1(),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()));
}

void KCM_Lisp_Runtime::kcm_call_3_p(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 void* pv;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<void*>(return_type_name.toLatin1(), pv),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()));
 klras[0].set_pVoid(pv);
}

void KCM_Lisp_Runtime::kcm_call_3_i(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 int i;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<int>(return_type_name.toLatin1(), i),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()));
 klras[0].set_as_fixnum(i);
}

void KCM_Lisp_Runtime::kcm_call_3_s(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QString str;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<QString>("QString", str),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()));
 klras[0].set_string(str);
}




void KCM_Lisp_Runtime::kcm_call_4_v(QString method_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QMetaObject::invokeMethod(&bridge_,
   method_name.toLatin1(),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()),
   QArgument<void*>(params[3],
     *klras[4].pointer_for_qarg()));
}

void KCM_Lisp_Runtime::kcm_call_4_p(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 void* pv;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<void*>(return_type_name.toLatin1(), pv),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()),
   QArgument<void*>(params[3],
     *klras[4].pointer_for_qarg()));
 klras[0].set_pVoid(pv);
}

void KCM_Lisp_Runtime::kcm_call_4_i(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 int i;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<int>(return_type_name.toLatin1(), i),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()),
   QArgument<void*>(params[3],
     *klras[4].pointer_for_qarg()));
 klras[0].set_as_fixnum(i);
}

void KCM_Lisp_Runtime::kcm_call_4_s(QString method_name, QString return_type_name,
  QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params)
{
 QString str;
 QMetaObject::invokeMethod(&bridge_, method_name.toLatin1(),
   QReturnArgument<QString>("QString", str),
   QArgument<void*>(params[0],
     *klras[1].pointer_for_qarg()),
   QArgument<void*>(params[1],
     *klras[2].pointer_for_qarg()),
   QArgument<void*>(params[2],
     *klras[3].pointer_for_qarg()),
   QArgument<void*>(params[3],
     *klras[4].pointer_for_qarg())
   );
 klras[0].set_string(str);
}
