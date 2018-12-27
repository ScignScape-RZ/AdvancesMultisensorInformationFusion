
//           Copyright Nathaniel Christen 2019.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KAUVIR_CODE_MODEL__H
#define KAUVIR_CODE_MODEL__H


#include "kans.h"

#include "accessors.h"
#include "flags.h"

#include "kcm-report-syntax.h"

#include "kcm-type-object.h"

#include <QVector>
#include <QMap>
#include <QSet>

#include <QTextStream>
#include <QQueue>
#include <QStack>

#include <functional>


KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_System)
KANS_CLASS_DECLARE(Kauvir ,Kauvir_Type_Object)

KANS_CLASS_DECLARE(CMD ,KCM_Command_Package)
KANS_CLASS_DECLARE(CMD ,KCM_Command_Runtime_Table)
KANS_CLASS_DECLARE(CMD ,KCM_Scope_System)
KANS_CLASS_DECLARE(CMD ,KCM_Runtime_Scope)

KANS_CLASS_DECLARE(Phaon ,KPH_Generator)

USING_KANS(Kauvir)
USING_KANS(CMD)
USING_KANS(Phaon)

class KCM_Lisp_Bridge;

KANS_(KCM)


class KCM_Type_Object;
class KCM_Channel_Group;

class KCM_Channel_Bridge;

class KCM_Lexical_Scope;
class KCM_Proxy_Scope;

class KCM_Expression;
class KCM_Statement;

class KCM_Block;
class KCM_File;
class KCM_Overloadable_Symbol;
class KCM_Callable_Value;

struct Opaque_Lisp_Value
{
 void* value;
};

class Kauvir_Code_Model
{
 typedef std::function<void(Kauvir_Code_Model* kcm,
   KCM_Command_Package* cpkg, KCM_Lisp_Bridge* bridge)> direct_eval_fn_type;

 typedef std::function<KCM_Command_Package*(const KCM_Channel_Group& kcg)>
   make_kcm_command_package_from_channel_group_fn_type;

 make_kcm_command_package_from_channel_group_fn_type make_kcm_command_package_from_channel_group_fn_;

 typedef std::function<KCM_Command_Package*(QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*>& channel_names,
   const KCM_Type_Object* kto,
   QString val, QObject* qob)> make_kcm_command_package_fn_type;

 make_kcm_command_package_fn_type make_kcm_command_package_fn_;


 direct_eval_fn_type direct_eval_fn_;

 KCM_Lexical_Scope* current_lexical_scope_;
 KCM_Proxy_Scope* current_proxy_scope_;

 KCM_Command_Runtime_Table* table_;

 KCM_Scope_System* scope_system_;
 Kauvir_Type_System* type_system_;

 QMap<int, KCM_Expression*> held_expressions_;

 QMap<QString, int> overload_count_;

 QMap<const Kauvir_Type_Object*, QString> type_string_reps_;

 QMap<QString, const KCM_Type_Object*> type_object_string_map_;

 int expression_code_count_;

 KCM_File* current_file_;

 KCM_Report_Syntax lisp_report_synax_;
 KCM_Report_Syntax detailed_report_synax_;

 QMap<const Kauvir_Type_Object*, const KCM_Type_Object*> kcm_type_object_map_;

 QMap<QPair<KCM_Type_Object*, int>, KCM_Type_Object*> kcm_type_object_array_map_;
 QMap<QPair<KCM_Type_Object*,
   KCM_Type_Object::Modifiers>, KCM_Type_Object*> kcm_type_object_modifier_map_;

 // //  stack or queue?
 // // QStack<QPair<QPair<KCM_Expression*, int>, QPair<int, int>>> current_nested_expression_coords_;
 QMap<QPair<int, int>, QQueue<QPair<QPair<KCM_Expression*, int>, QPair<int, int>>>> current_nested_expression_coords_;



 QMap<QString, KCM_Callable_Value*> current_anon_codes_;

 const KCM_Type_Object* generic_anon_callable_value_type_object_;
 const KCM_Type_Object* callable_lisp_deferred_value_type_object_;
 const KCM_Type_Object* argument_vector_type_object_;

 QStack<QPair<KCM_Expression*, QPair<int, int>>> current_held_deferred_coords_;

 QSet<QString*> channel_names_set_;
 QMap<KCM_Channel::Kinds, QString*> channel_names_map_;

 QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*> channel_names_;

 QStack<QPair<int, int>> runtime_scope_ids_;

 int runtime_scope_id_count_;

 typedef void*(*envv_fn_type)(void*);
 envv_fn_type envv_fn_;

 KPH_Generator* kph_generator_;

 QPair<int, int> get_current_runtime_scope_id();


 typedef QPair<QSet<QString*>*, QMap<KCM_Channel::Kinds, QString*>*> channel_names_type;

public:

 Kauvir_Code_Model();

 ACCESSORS(Kauvir_Type_System* ,type_system)
 ACCESSORS(KCM_Command_Runtime_Table* ,table)
 ACCESSORS(KCM_Scope_System* ,scope_system)

 ACCESSORS(KCM_Proxy_Scope* ,current_proxy_scope)

 ACCESSORS(direct_eval_fn_type ,direct_eval_fn)
 ACCESSORS(envv_fn_type ,envv_fn)

 ACCESSORS(KPH_Generator* ,kph_generator)

 ACCESSORS(make_kcm_command_package_from_channel_group_fn_type
           ,make_kcm_command_package_from_channel_group_fn)

 ACCESSORS(make_kcm_command_package_fn_type ,make_kcm_command_package_fn)

 ACCESSORS__RGET(KCM_Report_Syntax ,detailed_report_synax)

 ACCESSORS__RGET(channel_names_type, channel_names)

 void init_scope_system();
 void prepare_nested_expression(KCM_Expression* kcx, int level, int index);
 void prepare_nested_defer_expression(KCM_Expression* kcx, int hdcode, int level, int index);

 KCM_Statement* promote_type_binding_to_statement_with_nested_block(QString symbol_name, const KCM_Type_Object* kto);

 KCM_Statement* promote_overloadable_function_type_binding_to_statement(QString symbol_name, const KCM_Type_Object* kto);

 KCM_Runtime_Scope* get_current_runtime_scope();

 void hold_runtime_list(QString key, quint64 clo);
 void hold_deferred(int hdcode, quint64 clo);


 const KCM_Type_Object* get_kcm_type_by_kauvir_type_object(const Kauvir_Type_Object*);
 const KCM_Type_Object* get_or_add_kcm_type(QString type_name);

 const KCM_Type_Object* get_kcm_type_by_type_name(QString type_name);

 KCM_Type_Object* create_type_object(QString name);
 KCM_Type_Object* create_and_register_type_object(QString name);
 KCM_Type_Object* create_and_register_type_object(QString name, int bc);

 QString make_kcm_code();
 void kcg_add_fuxe_carrier(KCM_Channel_Group* kcg, const KCM_Type_Object* kto, QString symbol_name);

 void enter_plebod();

 void hold_runtime_value(QString key, const KCM_Type_Object* kto, QString value_encoding);

 QString get_key_for_storing(quint64 clo);


 const KCM_Type_Object* type_object_from_channel_group(KCM_Channel_Group& kcg);

 void add_type_binding(QString symbol_name, const KCM_Type_Object* kto);

 const KCM_Type_Object* retrieve_type_binding(QString symbol_name);


 int add_overloadable_type_binding(QString symbol_name, KCM_Type_Object* kto);

 void add_default_type_assignment_statement(QString symbol_name);

 void hold_dissolve(int code, KCM_Channel_Group& kcg);
 KCM_Expression* dissolve_to_expression(KCM_Channel_Group& kcg);

 KCM_Expression* dissolve_to_nested_expression(KCM_Channel_Group& kcg);
 KCM_Expression* dissolve_to_nested_expression(KCM_Channel_Group& kcg, QString kcm_code);

 void direct_eval(KCM_Command_Package* cpkg, KCM_Lisp_Bridge* bridge);

 void enter_runtime_scope(KCM_Lisp_Bridge& bridge);
 void leave_runtime_scope(KCM_Lisp_Bridge& bridge);

 KCM_Statement* promote_expression_to_statement(KCM_Expression* kcx);

 KCM_Command_Package* statement_to_command_package(KCM_Statement* kcs);

 KCM_Statement* promote_type_binding_to_statement(QString symbol_name, int index);
 KCM_Statement* promote_type_binding_to_statement(QString symbol_name);

 KCM_Statement* promote_type_binding_to_statement(QString symbol_name, KCM_Expression* kcx);
 KCM_Statement* promote_type_binding_to_statement_with_token(QString symbol_name,
   const KCM_Type_Object* kto, QString val);

 KCM_Statement* promote_type_binding_to_statement_with_qobject(QString symbol_name,
   const KCM_Type_Object* kto, QObject* qob);


 KCM_Block* create_and_enter_block();
 KCM_File* create_and_enter_file(QString file_path);

 void prepare_anon_fdef_expression(const KCM_Type_Object* kto, QString anon_code);
 void kcg_add_lambda_carrier_of_anon_fdef(KCM_Channel_Group* kcg, QString anon_code);


 void load_bridge(KCM_Channel_Bridge* bridge);

 void add_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb);

 void leave_block(KCM_Block* kcb);

 void join_statement_to_block(KCM_Statement* kcs, KCM_Block* kcb);
 void finalize_fdef(quint64 clo, QString symbol_name);
 void finalize_anon_fdef(quint64 clo, QString symbol_name);


 void add_statement_to_file(KCM_Statement* kcs, KCM_File* kcf);

 KCM_Expression* promote_type_binding_to_statement_via_type_default_literal__let(KCM_Channel_Group* kcg, QString symbol_name);

 QString string_rep(const Kauvir_Type_Object* kauvir_type_object);

 QString get_type_expression_for_overloadable_symbol(
   const KCM_Overloadable_Symbol& kcos, KCM_Lexical_Scope* scope);

 void report_type_expression_for_overloadable_symbol(QTextStream& qts,
   KCM_Report_Syntax& kcrs, const KCM_Overloadable_Symbol& kcos,
   KCM_Channel::Code_Environments cenv,
   KCM_Lexical_Scope* scope);

 QString get_function_type_keyword_for_overloadable_symbol(const KCM_Overloadable_Symbol& kcos,
   KCM_Lexical_Scope* scope);

 const KCM_Type_Object* get_type_object_for_overloadable_symbol(const KCM_Overloadable_Symbol& kcos,
   KCM_Lexical_Scope* scope);

 const KCM_Type_Object* type_object_by_qobject_type_name(QString tn);
 const KCM_Type_Object* type_object_by_qregistered_type_name(QString tn);

 KCM_Type_Object* type_with_array_length(KCM_Type_Object* kto, int array_length);
 KCM_Type_Object* type_with_modifiers(KCM_Type_Object* kto, KCM_Type_Object::Modifiers modifier);

 QString get_ouput_type_name(KCM_Report_Syntax& kcrs, const KCM_Type_Object* kto);


 QString get_type_expression_for_type_object(const KCM_Type_Object* kto);

 QString get_function_type_keyword_for_type_object(const KCM_Type_Object* kto);

 void prepare_proxy_symbol(QString symbol_name, const KCM_Type_Object* kto);
 void init_proxy_symbol(QString symbol_name, QString proxy_coords_code);

 void report_expression_from_code(QTextStream& qts, QString code, KCM_Report_Syntax& kcrs);
};


_KANS(KCM)


#endif //KAUVIR_CODE_MODEL__H

