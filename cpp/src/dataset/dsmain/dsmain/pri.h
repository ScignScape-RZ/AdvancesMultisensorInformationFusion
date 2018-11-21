
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef PRI__H
#define PRI__H


#define with_(type ,method ,name) method##__do([&](type name){

#define _with })

#define pri__ [&](){

#define pri_(x) static auto __##x = pri__

#define _pri(x) return x;}

#define __pri(x) __##x()

#define pri(x) __pri(x)


#endif // PRI__H
