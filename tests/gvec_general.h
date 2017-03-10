#ifndef __GVEC_GENERAL_H__
#define __GVEC_GENERAL_H__

#include "../genvector.h"

#define __GVT_TYPESET_TO_ARGS(template, typeset) \
  template typeset

#define __GVTEST_TYPESET_INTV \
  (int, intv, GVEC_USE_VAL, GVEC_USE_VAL)

#define __GVTEST_TYPESET_INTR \
  (int, intr, GVEC_USE_REF, GVEC_USE_REF)

#endif /*__GVEC_GENERAL_H__*/
