/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2007 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/* $Id$ */

#ifndef __TLM_ANALYSIS_PORT_H__
#define __TLM_ANALYSIS_PORT_H__

#include "tlm_analysis_if.h"
#include <deque>

namespace tlm {


template < typename T>
class tlm_analysis_port :
  public sc_core::sc_object ,
  public virtual tlm_analysis_if< T >
{
 public:
  tlm_analysis_port() : sc_core::sc_object() {}
  tlm_analysis_port( const char *nm ) : sc_core::sc_object( nm ) {}

  // bind and () work for both interfaces and analysis ports, since 
  // analysis ports implement the analysis interface

  void bind( tlm_analysis_if<T> &_if ) {
    m_interfaces.push_back( &_if );
  }

  void operator() ( tlm_analysis_if<T> &_if ) { bind( _if ); }

  bool unbind( tlm_analysis_if<T> &_if ) {

    typename std::deque< tlm_analysis_if<T> *>::iterator i;

    for( i = m_interfaces.begin(); 
	 i != m_interfaces.end();
	 i++ ) {

      if( *i == &_if ) {

	m_interfaces.erase( i );
	return 1;

      }

    }

    return 0;

  }

  void write( const T &t ) {
    typename std::deque< tlm_analysis_if<T> * >::iterator i;
 
    for( i = m_interfaces.begin(); 
	 i != m_interfaces.end();
	 i++ ) {

      (*i)->write( t );

    }

  }

 private:
  std::deque< tlm_analysis_if<T> * > m_interfaces;

};

} // namespace tlm

#endif
 

