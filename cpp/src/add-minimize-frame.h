
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef ADD_MINIMIZE_FRAME__H
#define ADD_MINIMIZE_FRAME__H


class QHBoxLayout;
class QDialogButtonBox;

#include <functional>

extern QHBoxLayout* add_minimize_frame(QDialogButtonBox* bb, std::function<void()> fn);

#endif // ADD_MINIMIZE_FRAME__H
