
//          Copyright Nathaniel Christen 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "nav-tree-table-1d-panel.h"

#include "styles.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>
#include <QButtonGroup>
#include <QGroupBox>
#include <QCheckBox>

USING_QSNS(ScignStage)

NAV_Tree_Table1D_Panel::NAV_Tree_Table1D_Panel(QWidget* parent)
  :  QFrame(parent)
{
 main_layout_ = new QVBoxLayout;
 navigation_layout_ = new QHBoxLayout;

 sample_up_button_ = new QPushButton(this);
 sample_down_button_ = new QPushButton(this);

 sample_first_button_ = new QPushButton(this);
 peer_first_button_ = new QPushButton(this);

 sample_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 sample_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 sample_first_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Arrow-leftup-small.svg"));
 peer_first_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Arrow-leftup-small.svg"));

 peer_up_button_ = new QPushButton(this);
 peer_down_button_ = new QPushButton(this);

 peer_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 peer_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 connect(peer_up_button_, SIGNAL(clicked()),
   this, SIGNAL(peer_up_requested()));

 connect(peer_down_button_, SIGNAL(clicked()),
   this, SIGNAL(peer_down_requested()));


 connect(sample_up_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_up_requested()));

 connect(sample_down_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_down_requested()));

 connect(sample_first_button_, SIGNAL(clicked()),
   this, SIGNAL(sample_first_requested()));

 connect(peer_first_button_, SIGNAL(clicked()),
   this, SIGNAL(peer_first_requested()));

 sample_up_down_layout_ = new QVBoxLayout;

 sample_up_down_layout_->addWidget(sample_up_button_);
 sample_up_down_layout_->addWidget(sample_down_button_);
 sample_up_down_layout_->addStretch(2);

 sample_up_down_group_box_ = new QGroupBox("Sample Up/Down", this);
 sample_up_down_button_group_ = new QButtonGroup(this);

 sample_up_down_button_group_->addButton(sample_up_button_);
 sample_up_down_button_group_->addButton(sample_down_button_);

 sample_up_down_group_box_->setLayout(sample_up_down_layout_);

 navigation_layout_->addWidget(sample_up_down_group_box_);

 peer_up_down_layout_ = new QVBoxLayout;

 peer_up_down_layout_->addWidget(peer_up_button_);
 peer_up_down_layout_->addWidget(peer_down_button_);
 peer_up_down_layout_->addStretch(2);

 peer_up_down_group_box_ = new QGroupBox("Peer Up/Down", this);
 peer_up_down_button_group_ = new QButtonGroup(this);


 peer_up_down_button_group_->addButton(peer_up_button_);
 peer_up_down_button_group_->addButton(peer_down_button_);

 peer_up_down_group_box_->setLayout(peer_up_down_layout_);

 navigation_layout_->addWidget(peer_up_down_group_box_);

 first_hlayout_ = new QHBoxLayout;
 first_vlayout_ = new QVBoxLayout;

 sample_first_label_ = new QLabel("First", this);

 first_hlayout_->addWidget(sample_first_label_);
 first_hlayout_->addWidget(sample_first_button_);
 first_hlayout_->addStretch();

 first_vlayout_->addLayout(first_hlayout_);

 peer_first_hlayout_ = new QHBoxLayout;
 peer_first_label_ = new QLabel("Peer First", this);

 peer_first_hlayout_->addWidget(peer_first_label_);
 peer_first_hlayout_->addWidget(peer_first_button_);
 peer_first_hlayout_->addStretch();

 first_vlayout_->addLayout(peer_first_hlayout_);

 deco_button_ = new QPushButton("DECO", this);
 deco_button_->setCheckable(true);
 deco_button_->setChecked(false);
 deco_button_->setStyleSheet(colorful_toggle_button_style_sheet_());

 deco_hlayout_ = new QHBoxLayout;
 QSpacerItem* sp00 = new QSpacerItem(10, 0, QSizePolicy::Maximum, QSizePolicy::Fixed);
 deco_hlayout_->addSpacerItem(sp00);
 deco_hlayout_->addStretch();
 deco_hlayout_->addWidget(deco_button_);

 QSpacerItem* sp0 = new QSpacerItem(0, 35, QSizePolicy::Fixed, QSizePolicy::Maximum);
 first_vlayout_->addSpacerItem(sp0);
 first_vlayout_->addLayout(deco_hlayout_);
 first_vlayout_->addStretch();

 ckb_layout_ = new QGridLayout;

 QStringList qsl {
   "2:25x25", "2:12x12", "2:3x3", "2:37x75",
   "3:25x25", "3:12x12", "3:3x3", "3:37x75"
 };

 int count = 0;
 int col_count = qsl.size() / 2;

 for(QString qs : qsl)
 {
  int d = qs.left(1).toInt();
  QString qs1 = qs.mid(2);
  int index = qs1.indexOf('x');
  int r = qs1.left(index).toInt();
  int c = qs1.mid(index + 1).toInt();
  QCheckBox* ckb = new QCheckBox(QString("%1D %2").arg(d).arg(qs1), this);
  ckb_layout_->addWidget(ckb, d - 2, count % col_count);
  ckbs_[qs] = ckb;

  connect(ckb, &QCheckBox::toggled,
    [this, d, r, c](bool checked)
  {
   if(checked)
     Q_EMIT( graphic_open_requested(d, r, c, deco_button_->isChecked()) );
   else
     Q_EMIT( graphic_close_requested(d, r, c) );
  });

  ++count;
 }

 ckb_layout_->setColumnStretch(col_count, 1);
 ckb_layout_->setRowStretch(2, 1);

 ckbs_group_box_ = new QGroupBox("Graphics", this);
 ckbs_group_box_->setLayout(ckb_layout_);

 QSpacerItem* sp1 = new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
 QSpacerItem* sp2 = new QSpacerItem(5, 0, QSizePolicy::Fixed, QSizePolicy::Fixed);
 QSpacerItem* sp3 = new QSpacerItem(25, 0, QSizePolicy::Maximum, QSizePolicy::Fixed);

 navigation_layout_->addSpacerItem(sp1);
 navigation_layout_->addLayout(first_vlayout_);
 navigation_layout_->addSpacerItem(sp2);
 navigation_layout_->addSpacerItem(sp3);

 navigation_layout_->addWidget(ckbs_group_box_);
 navigation_layout_->addStretch();

 QSpacerItem* sp = new QSpacerItem(0, 2, QSizePolicy::Fixed, QSizePolicy::Maximum);

 main_layout_->addSpacerItem(sp);
 main_layout_->addLayout(navigation_layout_);

 setLayout(main_layout_);

}

void NAV_Tree_Table1D_Panel::uncheck_graphic(QString code)
{
 QCheckBox* ckb = ckbs_.value(code);

 if(ckb)
 {
  ckb->setChecked(false);
 }
}


NAV_Tree_Table1D_Panel::~NAV_Tree_Table1D_Panel()
{

}
