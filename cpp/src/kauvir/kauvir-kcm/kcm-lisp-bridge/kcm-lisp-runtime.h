
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_LISP_RUNTIME__H
#define KCM_LISP_RUNTIME__H



#include <QObject>
#include <QMap>

#include "kauvir-code-model/kauvir-code-model.h"

#include "kcm-lisp-bridge.h"

USING_KANS(KCM)


KANS_CLASS_DECLARE(Dynamo ,RZ_Dynamo_Generator)

USING_KANS(Dynamo)

class QTextStream;

KANS_(KCL)

class KCM_Lisp_Runtime_Argument;

class KCM_Lisp_Runtime
{
 KCM_Lisp_Bridge bridge_;

 int bridge_type_id_;
 const QMetaObject* bridge_qmo_;

 QMap<QString, QPair<int, QList<QByteArray>>> bridge_qmo_methods_;

 RZ_Dynamo_Generator* rdg_;

 void _init();

public:

 KCM_Lisp_Runtime();
 KCM_Lisp_Runtime(QTextStream& qts);

 ACCESSORS(RZ_Dynamo_Generator* ,rdg)

 ACCESSORS__RGET(KCM_Lisp_Bridge ,bridge)

 void store_key(QString key, quint64 clo);

 void kcm_call(QString method_name, QVector<KCM_Lisp_Runtime_Argument>& klras);

 void kcm_call_void_return(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

 void kcm_call(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

 void kcm_call_0_v(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_0_p(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_0_i(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_0_s(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);


 void kcm_call_1_v(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_1_p(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_1_i(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_1_s(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

 void kcm_call_2_v(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_2_p(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_2_i(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_2_s(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

 void kcm_call_3_v(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_3_p(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_3_i(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_3_s(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

 void kcm_call_4_v(QString method_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_4_p(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_4_i(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);
 void kcm_call_4_s(QString method_name, QString return_type_name,
   QVector<KCM_Lisp_Runtime_Argument>& klras, const QList<QByteArray>& params);

};

_KANS(KCL)

#endif //KCM_LISP_RUNTIME__H
