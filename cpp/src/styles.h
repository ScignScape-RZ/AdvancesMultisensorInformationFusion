

//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STYLES__H
#define STYLES__H



#include <QString>
inline QString basic_button_style_sheet_()
{
 return
 "QPushButton:default {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E4FA,"
 "stop:0.04 #F5E6FA,"
 "stop:1 #F5E8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 1px ridge #3AFFAB;"
 "border-right: 1px ridge #3AFFAB;"
 "border-top: 2px solid #618281;"
 "border-bottom: 2px solid #618281;"
 "}"

 "QPushButton {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #F5E0FA,"
 "stop:0.04 #F5E8FA,"
 "stop:1 #F5E8BE"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border-radius: 6px;"
 "border-left: 2px ridge #3AFFAB;"
 "border-right: 2px ridge #3AFFAB;"
 "border-top: 2px ridge #C5D8FA;"
 "border-bottom: 2px ridge #C5D8FA;"
 "}"

 "QPushButton:disabled {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.01 #618281,"
 "stop:0.02 #EDEDED,"
 "stop:0.07 #EDEDED,"
 "stop:0.09 #445A82,"
 "stop:1 #616161"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:pressed {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #445A82,"
 "stop:0.03 #6182BD,"
 "stop:0.04 #6182BD,"
 "stop:1 #C5D8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:hover {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"
 ;
}


inline QString colorful_toggle_button_quiet_style_sheet_()
{
 return

   "QPushButton {"
   "background-color: qlineargradient("
   "x1:0, y1:0, x2:0, y2:1,"
   "stop:0 #C5D8FA,"
   "stop:0.03 #F5E0FA,"
   "stop:0.04 #F5E8FA,"
   "stop:1 #F5E8BE"
   ");"
   "background-image: none;"
   "border-image: none;"
   "border-radius: 6px;"
   "border-left: 2px ridge #3AFFAB;"
   "border-right: 2px ridge #3AFFAB;"
   "border-top: 2px ridge #C5D8FA;"
   "border-bottom: 2px ridge #C5D8FA;"
   "}"


 "QPushButton:disabled {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.01 #618281,"
 "stop:0.02 #EDEDED,"
 "stop:0.07 #EDEDED,"
 "stop:0.09 #445A82,"
 "stop:1 #616161"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:hover {"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #445A82,"
 "stop:0.03 #6182BD,"
 "stop:0.04 #6182BD,"
 "stop:1 #C5D8FA"
 ");"
 "background-image: none;"
 "border-image: none;"
 "border: 1px solid #364767;"
 "}"

 "QPushButton:checked {"
 "border:1px solid #EFE7F7;"
 "background-color: qlineargradient("
 "x1:0, y1:0, x2:0, y2:1,"
 "stop:0 #C5D8FA,"
 "stop:0.03 #E95289,"
 "stop:0.04 #E95289,"
 "stop:1 #A64166"
 ");"
 "}"
 ;
}

//?QPushButton:hover,
//"QPushButton[checked=true] { background:#B13240; }"
//"QPushButton[checked=false] { background:white; }"

//"QPushButton[checked=false] {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.03 #F5E0FA,"
//"stop:0.04 #F5E8FA,"
//"stop:1 #F5E8BE"
//");"
//"background-image: none;"
//"border-image: none;"
//"border-radius: 6px;"
//"border-left: 2px ridge #3AFFAB;"
//"border-right: 2px ridge #3AFFAB;"
//"border-top: 2px ridge #C5D8FA;"
//"border-bottom: 2px ridge #C5D8FA;"
//"}"

// "QPushButton:default {"
//"background-color: qlineargradient("
//"x1:0, y1:0, x2:0, y2:1,"
//"stop:0 #C5D8FA,"
//"stop:0.03 #F5E4FA,"
//"stop:0.04 #F5E6FA,"
//"stop:1 #F5E8FA"
//");"
//"background-image: none;"
//"border-image: none;"
//"border-radius: 6px;"
//"border-left: 1px ridge #3AFFAB;"
//"border-right: 1px ridge #3AFFAB;"
//"border-top: 2px solid #618281;"
//"border-bottom: 2px solid #618281;"
//"}"




inline QString tab_style_sheet_()
{
 return "QTabBar::tab {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
        "                            stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
        "border: 2px solid #C4C4C3;"
        "border-bottom-color: #C2C7CB; /* same as the pane color */"
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
        "min-width: 8ex;"
        "padding: 2px;"
        "color:rgb(85,10,10)"
        "}"

        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                            stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
        "                            stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
        "border-color: #5BAB9B;"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:hover { border-color: #ABABCB; }"

        "QTabBar::tab:selected {"
        "border-color: #1B9B9B;"
        "border-bottom-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:!selected {"
        "margin-top: 2px; /* make non-selected tabs look smaller */"
        "}"

        "QTabBar::tab::disabled {"
        "width: 0; height: 0; margin: 0; padding: 0; border: none;"
        "}"

        "QTabWidget{border:solid white 3px; background:white}"

   ;

}


inline QString colorful_button_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(240,190,150);"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n"
   "QPushButton{color:black;  padding:1px;  border: 2px solid rgb(240,190,150); "
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 6px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #CC"
   "C6BC, stop: 0.8 #ECCFA0, stop: 0.9 darkred,  stop: 1 brown"
   "); min-width: 80px; }";
}

inline QString colorful_button_style_sheet_down_()
{
 return
   "QPushButton {background:rgb(190,190,230);padding-left:20;padding-right:20;padding-top:0;padding-bottom:0;"
   " border-left: 4px groove rgb(240,190,150); "
   " border-right: 4px ridge rgb(240,190,150); "
   "}\n";
}

inline QString make_basic_style_sheet_()
{
 QString result = "QMainWindow{background:coral}"
               "QWidget{background:none;color:black}"
               "QMenu::item{color:black}"
               "QMenu::item:selected{ "
               " background-color: rgb(66, 206, 244); "
               " } "
               ;

 result += basic_button_style_sheet_();
 result += tab_style_sheet_();

 return result;

}

inline QString basic_style_sheet_()
{
 static QString result = make_basic_style_sheet_();
 return result;
}

inline QString button_close_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(150,240,190);"
   " border-left: 4px groove rgb(150,240,190); "
   " border-right: 4px ridge rgb(150,240,190); "
   "}\n"

     "QPushButton {background:rgb(160,190,230);padding-left:20;padding-right:20;padding-top:0;padding-bottom:0;"
     " border-left: 4px groove rgb(240,190,150); "
     " border-right: 4px ridge rgb(240,190,150); "
     "}\n"


   "QPushButton:pressed{ color:black; padding:1px;  border: 1px solid rgb(150,240,190);"
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 0px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
   "  stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
   "); min-width: 80px; }";
}

inline  QString colorful_toggle_button_style_sheet_()
{
 return
   "QPushButton:hover {background:rgb(150,240,190);"
   " border-left: 4px groove rgb(150,240,190); "
   " border-right: 4px ridge rgb(150,240,190); "
   "}\n"
   "QPushButton:checked {color:black; background:rgb(200,10,100);"
   " border-left: 4px groove rgb(200,10,100); "
   " border-right: 4px ridge rgb(200,10,100); "
   "}\n"
   "QPushButton{ color:black; padding:1px;  border: 1px solid rgb(150,240,190);"
   "  border-bottom: 1px solid #CEF51D; "
   " border-radius: 0px; "
   " background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
   "  stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
   "  stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
   "); min-width: 80px; }";
}


inline  QString tight_button_style_sheet_()
{
 return


" QPushButton:hover {background:rgb(150,240,190);"
"  border-left: 4px groove rgb(150,240,190); "
"  border-right: 4px ridge rgb(150,240,190); "
" }\n "

" QPushButton { background:rgb(220,220,230); "
"  border: 2px groove rgb(0,90,50); "
"  font-family:\"Comic Sans MS\", cursive, sans-serif; "
"  border-bottom: 2px groove rgb(240,190,150); "
"  border-top: 2px groove rgb(240,90,150); "
"  border-radius: 10px; font-weight:600; color:rgb(0, 90, 105); "
"  padding-left:16px;padding-right:16px;padding-top:2px;padding-bottom:2px; "

//   " border-left: 4px groove rgb(0,190,150);   "
//   " border-right: 4px ridge rgb(240,190,150); "

" }\n"

" QPushButton[enabled=false] { color:grey; } "



" QPushButton:pressed{ color:black; padding:1px; "
"  border: 1px solid rgb(150,240,190); "
"  border-bottom: 1px solid #CEF51D; "
"  border-radius: 0px; "
"  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
"   stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
"   stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
"  ); min-width: 80px; } ";

}


inline  QString toggle_button_style_sheet_()
{
 return


" QPushButton:hover {background:rgb(150,240,190);"
"  border-left: 4px groove rgb(150,240,190); "
"  border-right: 4px ridge rgb(150,240,190); "
" }\n "

 " QPushButton{ background:rgb(220,220,230); "
 "  border: 2px groove rgb(0,90,50); "
 "  font-family:\"Comic Sans MS\", cursive, sans-serif; "
 "  border-bottom: 2px groove rgb(240,190,150); "
 "  border-top: 2px groove rgb(240,90,150); "
 "  border-radius: 3px; font-weight:600; color:rgb(0, 90, 105); "
 "  padding-left:16px;padding-right:16px;padding-top:2px;padding-bottom:2px; "
 " }\n"


 " QPushButton[checked=false] {background:rgb(250,250,190);"
 "  border-left: 4px groove rgb(150,240,190); "
 "  border-right: 4px ridge rgb(150,240,190); "
 " }\n "

 " QPushButton[checked=true] { background:#B13240; " //background:rgb(10,10,190);"
 "  color:rgb(210,220,190); "
 "  border-left: 4px groove rgb(150,240,190); "
 "  border-right: 4px ridge rgb(150,240,190); "
 " }\n "


//   " border-left: 4px groove rgb(0,190,150);   "
//   " border-right: 4px ridge rgb(240,190,150); "
//" }\n"

" QPushButton[enabled=false] { color:grey; } "



" QPushButton:pressed{ color:black; padding:1px; "
"  border: 1px solid rgb(150,240,190); "
"  border-bottom: 1px solid #CEF51D; "
"  border-radius: 0px; "
"  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, "
"   stop: 0 white, stop: 0.1 #C0C0C0, stop: 0.6 #C6CCBC "
"   stop: 0.8 #A0ECCF, stop: 0.9 darkseagreen,  stop: 1 blue"
"  ); min-width: 80px; } ";

}

#endif
