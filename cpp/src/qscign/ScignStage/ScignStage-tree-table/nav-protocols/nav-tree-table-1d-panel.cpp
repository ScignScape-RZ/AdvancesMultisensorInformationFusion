
//          Copyright Nathaniel Christen 2017.
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

USING_QSNS(ScignStage)

NAV_Tree_Table1D_Panel::NAV_Tree_Table1D_Panel(QWidget* parent)
  :  QFrame(parent)
{
 main_layout_ = new QVBoxLayout;
 navigation_layout_ = new QHBoxLayout;

 sample_up_button_ = new QPushButton(this);
 sample_down_button_ = new QPushButton(this);

 sample_first_button_ = new QPushButton(this);

 sample_up_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-up.svg"));
 sample_down_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Gtk-go-down.svg"));

 sample_first_button_->setIcon(QIcon(DEFAULT_ICON_FOLDER "/Arrow-leftup-small.svg"));

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
 first_hlayout_->addStretch();
 first_hlayout_->addWidget(sample_first_label_);
 first_hlayout_->addWidget(sample_first_button_);
 first_hlayout_->addStretch();

 first_vlayout_->addStretch();
 first_vlayout_->addLayout(first_hlayout_);

 first_vlayout_->addStretch();

 navigation_layout_->addLayout(first_vlayout_);

 QSpacerItem* sp = new QSpacerItem(0, 5, QSizePolicy::Maximum, QSizePolicy::Minimum);

 main_layout_->addSpacerItem(sp);
 main_layout_->addLayout(navigation_layout_);

 setLayout(main_layout_);

}

NAV_Tree_Table1D_Panel::~NAV_Tree_Table1D_Panel()
{

}
