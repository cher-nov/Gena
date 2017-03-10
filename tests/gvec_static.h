#ifndef __GVEC_STATIC_H__
#define __GVEC_STATIC_H__

#include "gvec_general.h"

GVEC_INSTANTIATE( int, intv, GVEC_USE_VAL, GVEC_USE_VAL );
GVEC_INSTANTIATE( int, intr, GVEC_USE_REF, GVEC_USE_REF );

#endif /*__GVEC_STATIC_H__*/
