
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef ACCESSORS__H
#define ACCESSORS__H

#include <functional>

#ifndef ACCESSORS__GET
#define ACCESSORS__GET(type, name) \
 type name() const { return name##_; }
#endif

#ifndef ACCESSORS__IMPL_GET
#define ACCESSORS__IMPL_GET(type, name) \
 type name() const { return impl_.name(); }
#endif

#ifndef ACCESSORS__IMPL_SET
#define ACCESSORS__IMPL_SET(type, name) \
 void set_##name(type t) { impl_.set_##name(t); }
#endif


#ifndef ACCESSORS__IMPL
#define ACCESSORS__IMPL(type, name) \
 ACCESSORS__IMPL_GET(type, name) \
 ACCESSORS__IMPL_SET(type, name)
#endif


#ifndef RZ_CALL_IMPL
#define RZ_CALL_IMPL(type, name) \
 type name() const { return impl_.name(); }
#endif

#ifndef RZ_CALL_IMPL_VOID
#define RZ_CALL_IMPL_VOID(type, name) \
 void name(type arg) { impl_.name(arg); }
#endif


#ifndef ACCESSORS__CGET
#define ACCESSORS__CGET(type, name) \
 const type name() const { return name##_; }
#endif


#ifndef ACCESSORS__STATIC_GET
#define ACCESSORS__STATIC_GET(type, name) \
 static type name() { return name##_; }
#endif


#ifndef ACCESSORS__RGET
#define ACCESSORS__RGET(type, name) \
 type& name() { return name##_; }
#endif


#ifndef ACCESSORS__CONST_RGET
#define ACCESSORS__CONST_RGET(type, name) \
 const type& name() const { return name##_; }
#endif

#ifndef ACCESSORS__RGET_DEREF
#define ACCESSORS__RGET_DEREF(type, name) \
 type& name() { return *name##_; }
#endif


#ifndef ACCESSORS__STATIC_RGET
#define ACCESSORS__STATIC_RGET(type, name) \
 static type& name() { return name##_; }
#endif


#ifndef ACCESSORS__SET
#define ACCESSORS__SET(type, name) \
 void set_##name(type _arg_) { name##_ = _arg_; }
#endif


#ifndef Q_INVOKABLE__ACCESSORS__SET
#define Q_INVOKABLE__ACCESSORS__SET(type, name) \
 void Q_INVOKABLE set_##name(type _arg_) { name##_ = _arg_; }
#endif



#ifndef ACCESSORS__SDECLARE
#define ACCESSORS__SDECLARE(type, name) \
 void set_##name(type name);
#endif

#ifndef ACCESSORS__SET__IMPL
#define ACCESSORS__SET__IMPL(type, name) \
 void set_##name(type name)
#endif


#ifndef ACCESSORS__GDECLARE
#define ACCESSORS__GDECLARE(type, name) \
 type name() const;
#endif


#ifndef ACCESSORS__DECLARE
#define ACCESSORS__DECLARE(type, name) \
 ACCESSORS__GDECLARE(type, name) \
 ACCESSORS__SDECLARE(type, name)
#endif


#ifndef ACCESSORS
#define ACCESSORS(type, name) \
 ACCESSORS__GET(type, name) \
 ACCESSORS__SET(type, name)
#endif


#ifndef Q_INVOKABLE__ACCESSORS
#define Q_INVOKABLE__ACCESSORS(type, name) \
 ACCESSORS__GET(type, name) \
 Q_INVOKABLE__ACCESSORS__SET(type, name)
#endif


#ifndef ACCESSORS__SET__CONST
#define ACCESSORS__SET__CONST(type, name) \
 void set_##name(type _arg_) const { name##_ = _arg_; }
#endif

#ifndef ACCESSORS__CONST
#define ACCESSORS__CONST(type, name) \
 ACCESSORS__GET(type, name) \
 ACCESSORS__SET__CONST(type, name)
#endif


#ifndef ACCESSORS__DO
#define ACCESSORS__DO(type, name) \
 void name##__do(std::function<void(type)> fn) const { fn(name()); }
#endif


#ifndef ACCESSORS__GDECLARE__DO
#define ACCESSORS__GDECLARE__DO(type, name) \
  ACCESSORS__GDECLARE(type, name) \
  ACCESSORS__DO(type, name)
#endif


#ifndef ACCESSORS__DECLARE__DO
#define ACCESSORS__DECLARE__DO(type, name) \
  ACCESSORS__DECLARE(type, name) \
  ACCESSORS__DO(type, name)
#endif


#endif //ACCESSORS__H
