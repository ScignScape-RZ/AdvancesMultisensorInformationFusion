
//          Copyright Nathaniel Christen 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SCIGNSTAGE_TREE_TABLE_DIALOG__H
#define SCIGNSTAGE_TREE_TABLE_DIALOG__H

#include <QObject>

#include <QMetaType>

#include <QList>

#include <QPoint>

#include <QDialog>
#include <QTableWidget>

#include <functional>

#include "accessors.h"
#include "qsns.h"

#include "nav-protocols/nav-tree-table-1d-panel.h"

#include <functional>

#include "kans.h"

KANS_CLASS_DECLARE(DSM ,Test_Sample)


USING_KANS(DSM)

class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QTabWidget;
class QTextEdit;
class QFrame;
class QHBoxLayout;
class QVBoxLayout;
class QSlider;
class QPlainTextEdit;
class QBoxLayout;
class QButtonGroup;
class QGroupBox;
class QScrollArea;
class QGridLayout;
class QMediaPlayer;
class QProcess;
class QTcpServer;
class QTreeWidget;
class QTreeWidgetItem;

class ScignStage_Clickable_Label;

class XPDF_Bridge;

KANS_CLASS_DECLARE(PhaonLib ,Phaon_Runner)
USING_KANS(PhaonLib)

QSNS_(ScignStage)
_QSNS(ScignStage)
//?namespace QScign { namespace ScignStage {



class ScignStage_Tree_Table_Dialog : public QDialog
{

 Q_OBJECT

 QDialogButtonBox* button_box_;
 QPushButton* button_ok_;
 QPushButton* button_cancel_;
 QPushButton* button_proceed_;


 QHBoxLayout* middle_layout_;
 QVBoxLayout* main_layout_;

 // //  "Pseudo" Toolbar ...
 QHBoxLayout* top_buttons_layout_;

 QPushButton* activate_tcp_button_;

 QPushButton* take_screenshot_button_;

 QTreeWidget* main_tree_widget_;

 NAV_Tree_Table1D_Panel* nav_panel_;

 XPDF_Bridge* xpdf_bridge_;

 QVector<Test_Sample*>* samples_;

 QTcpServer* tcp_server_;

 QString held_xpdf_msg_;

 Phaon_Runner* phr_;

 std::function<void(Phaon_Runner&)> phr_init_function_;
 std::function<void()> screenshot_function_;

 Test_Sample* current_sample_;

 bool xpdf_is_ready();
 void check_phr();

 void run_msg(QString msg, QByteArray qba);
 void run_kph(const QByteArray& qba);

 void play_file_at_current_index();

 void open_pdf_file(QString name, int page);

 void check_launch_xpdf(std::function<void()> fn,
   std::function<void()> waitfn);
 void send_xpdf_msg(QString msg);

 QString load_about_file(QString name);

 bool ask_pdf_proceed(QString name);

 void highlight(QTreeWidgetItem* twi);
 void unhighlight(QTreeWidgetItem* twi);

 void highlight(Test_Sample* samp);
 void unhighlight(Test_Sample* samp);

 void highlight_scroll_to_sample(Test_Sample* samp);


 void run_tree_context_menu(const QPoint& qp, int col, int row = 0);
 void run_tree_context_menu(const QPoint& qp, int page, int col,
   std::function<void(int)> pdf_fn, std::function<void(int)> copyc_fn,
   int row = 0, std::function<void(int)> copyr_fn = nullptr,
   std::function<void(int)> highlight_fn = nullptr);


public:



 ScignStage_Tree_Table_Dialog(XPDF_Bridge* xpdf_bridge,
   QVector<Test_Sample*>* samples, QWidget* parent = nullptr);

 ~ScignStage_Tree_Table_Dialog();

 ACCESSORS__SET(std::function<void(Phaon_Runner&)>, phr_init_function)
 ACCESSORS__SET(std::function<void()> ,screenshot_function)

 // //  Kernel Application Interface
 void test_msgbox(QString msg);

 void emit_highlight();


Q_SIGNALS:
 void canceled(QDialog*);
 void accepted(QDialog*);
 void take_screenshot_requested();
 void sample_highlighted(Test_Sample* samp);

public Q_SLOTS:

 void browse_to_selected_sample(Test_Sample* samp);

 void handle_xpdf_is_ready();
 void handle_take_screenshot_requested();

 void handle_sample_down();
 void handle_sample_up();

 void handle_sample_first();

 void handle_peer_down();
 void handle_peer_up();

 void accept();
 void cancel();

 void activate_tcp_requested();


};

//_QSNS(ScignStage)


#endif  // SCIGNSTAGE_AUDIO_DIALOG__H


