/*****************************************************************************
 *
 * MTI Wrapper class for ac_fixed.h 
 *
 * Copyright 1991-2011 Mentor Graphics Corporation
 *
 * All Rights Reserved.
 *
 * THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY INFORMATION WHICH IS THE PROPERTY OF 
 * MENTOR GRAPHICS CORPORATION OR ITS LICENSORS AND IS SUBJECT TO LICENSE TERMS.
 * $Revision: #1 $
 * $Id: //dvt/mti/rel/10.0b/src/systemc/ac_fixed.h#1 $
 *
 *****************************************************************************/

#ifndef __AC_FIXED_MTI_H
#define __AC_FIXED_MTI_H

//
// if SC_INCLUDE_MTI_AC is defined, wrapper the actual ac_fixed.h to add 
// the extra base class otherwise just include the actual ac_fixed.h
//
#ifdef SC_INCLUDE_MTI_AC
#include "sc_mti_access.h"

#ifndef __AC_INT_MTI_H
#define __AC_INT_MTI_H
//
// ac_int type that has additional base class is placed in namespace so that it is not
// seen as having the same type as plain ac_int (without extra base class). This would 
// happen if different modules are compiled differently
//
#define __AC_NAMESPACE mti_ac

namespace __AC_NAMESPACE {
  template<int W, bool S> class ac_int;

  template<int W, bool S>
  class mti_ac_int_base : public sc_mti_access { 
    public:
    inline void* mti_get_value() {
      ac_int<W,S> *t = (ac_int<W,S> *) this;
      for (unsigned int i = 0; i < W; i++)
        m_mti_value[W-i-1] = t->operator[](i);
      return (void*)m_mti_value;
    }

    void mti_set_value(void* value) {
    }
    protected:
      unsigned char m_mti_value[W];
  };
}

#define __AC_INT_UTILITY_BASE , public mti_ac_int_base<W,S>

// GCC feature to include ac_int.h in the next include search path (to include actual ac_int.h)
#include_next "ac_int.h"

#ifndef AC_VERSION
#error Version 1.2 or more recent of ac types is required for native support 
#endif

#endif

//
// ac_fixed type that has additional base class is placed in namespace so that it is not
//  seen as having the same type as plain ac_fixed (without extra base class). This would
//  happen if different modules are compiled differently
//
namespace __AC_NAMESPACE {

  template<int W, int I, bool S, ac_q_mode Q, ac_o_mode O> class ac_fixed;
  template<int W, int I, bool S, ac_q_mode Q, ac_o_mode O>
  class mti_ac_fixed_base : public sc_mti_access {
    public:
    void* mti_get_value() {
      ac_fixed<W,I,S,Q,O> *t = (ac_fixed<W,I,S,Q,O> *) this;
      for (unsigned int i = 0; i < W; i++)
        m_mti_value[W-i-1] = t->operator[](i);
      return (void*)m_mti_value;
    }
                                                                                                                   
    void mti_set_value(void* value) {
    }
    protected:
      unsigned char m_mti_value[W];
  };

}

#define __AC_FIXED_UTILITY_BASE , public mti_ac_fixed_base<W,I,S,Q,O>

// GCC feature to include ac_fixed.h in the next include search path (include actual ac_fixed.h)
#include_next "ac_fixed.h"

#ifndef AC_VERSION
#error Version 1.2 or more recent of AC types is required for native debug support
#endif

using namespace __AC_NAMESPACE;

#else

#ifndef __AC_INT_MTI_H
//
// SC_INCLUDE_MTI_AC not defined, include the actual ac_int.h without adding the extra base class 
// GCC feature to include ac_int.h in the next include search path (to include actual ac_int.h)
//
#include_next "ac_int.h"
#endif

#warning The native debug support for the AC types is not enabled as SC_INCLUDE_MTI_AC is not defined. This will cause the AC types to be treated as regular C++ classes. Define this variable to see the native debug view for these types in the simulator.
//
// SC_INCLUDE_MTI_AC not defined, include the actual ac_fixed.h without adding the extra base class
// GCC feature to include ac_fixed.h in the next include search path (include actual ac_fixed.h)
//
#include_next "ac_fixed.h"

#endif

namespace sc_core {
	class sc_trace_file;
};
template<int W, int I, bool S, ac_q_mode Q, ac_o_mode O>
inline void sc_trace(sc_core::sc_trace_file *, const ac_fixed<W,I,S,Q,O>&, const std::string&) {}

#endif
