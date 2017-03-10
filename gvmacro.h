#ifndef __GVMACRO_H__
#define __GVMACRO_H__

#define __impl_GV_MACRO_CONCAT(x, y) x##y
#define __GV_MACRO_CONCAT(x, y) __impl_GV_MACRO_CONCAT(x, y)

#define __GV_REQUIRE_SEMICOLON_INDOOR \
  (void)0

#define __GV_REQUIRE_SEMICOLON_OUTDOOR \
  extern void __GV_MACRO_CONCAT(__THIS_REQUIRES_A_SEMICOLON_, __LINE__) (void)

#endif /*__GVMACRO_H__*/
