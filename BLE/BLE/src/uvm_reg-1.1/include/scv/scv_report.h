//  -*- C++ -*- <this line is for emacs to recognize it as C++ code>
/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2002 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.3 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  scv_report.h --  The public interface for error messages.

  Original Authors (Cadence Design Systems, Inc):
  Norris Ip, Dean Shea, John Rose, Jasvinder Singh, William Paulsen,
  John Pierce, Rachida Kebichi, Ted Elkind, David Bailey
  2002-09-23

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

#ifndef _SCV_REPORT_H
#define _SCV_REPORT_H

#include "scv_config.h"


// BEGIN MODELSIM MODIFICATIONS

// Use sc_report instead of scv_report

typedef sc_actions scv_actions;
typedef sc_report scv_report;
typedef sc_report_handler scv_report_handler;
typedef sc_severity scv_severity;
typedef const char *scv_msg_type;

#define SCV_INFO SC_INFO
#define SCV_WARNING SC_WARNING
#define SCV_ERROR SC_ERROR
#define SCV_FATAL SC_FATAL

#define SCV_UNSPECIFIED SC_UNSPECIFIED
#define SCV_DO_NOTHING SC_DO_NOTHING
#define SCV_THROW SC_THROW
#define SCV_LOG SC_LOG
#define SCV_DISPLAY SC_DISPLAY
#define SCV_CACHE_REPORT SC_CACHE_REPORT
#define SCV_INTERRUPT SC_INTERRUPT
#define SCV_STOP SC_STOP
#define SCV_ABORT SC_ABORT

#define SCV_DEFAULT_INFO_ACTIONS SC_DEFAULT_INFO_ACTIONS
#define SCV_DEFAULT_WARNING_ACTIONS SC_DEFAULT_WARNING_ACTIONS
#define SCV_DEFAULT_ERROR_ACTIONS SC_DEFAULT_ERROR_ACTIONS
#define SCV_DEFAULT_FATAL_ACTIONS SC_DEFAULT_FATAL_ACTIONS

#define SCV_REPORT_INFO SC_REPORT_INFO
#define SCV_REPORT_WARNING SC_REPORT_WARNING
#define SCV_REPORT_ERROR SC_REPORT_ERROR
#define SCV_REPORT_FATAL SC_REPORT_FATAL

// END MODELSIM MODIFICATIONS

#if defined(_MSC_VER) || (defined(__GNUC__) && defined(WIN32))
#ifdef DELETE
#undef DELETE
#endif
#ifdef ERROR
#undef ERROR
#endif
#endif

//
// Translation layer for _scv_message messages
//


class _scv_message_desc {
public:
  _scv_message_desc(
    string tag, string format, scv_severity severity, scv_actions actions
  ) : _tag(tag), _format(format), _severity(severity), _actions(actions) {}
  const char *get_tag() const { return _tag.c_str(); }
  const char *get_format() const { return _format.c_str(); }
  scv_severity get_severity() const { return _severity; }
  unsigned get_actions() const { return _actions; }
private:
  string _tag;
  string _format;
  scv_severity _severity;
  scv_actions _actions;
};


class _scv_message {
friend class scv_report_core;
public:

  enum severity_level { INFO, WARNING, ERROR, FATAL };

  enum response_level {
    NONE_SPECIFIED, ENABLE_MESSAGE, SUPPRESS_MESSAGE
  };

// Message types are actually pointers to descriptors
#define _SCV_DEFERR(code, number, string, severity, actions) \
  static _scv_message_desc *code##_base; \
  static _scv_message_desc **code;
#include "scv_messages.h"
#undef _SCV_DEFERR

  // Used internally by the SystemC Verification Standard to report exceptions
  static void message(_scv_message_desc **desc_pp, ... );
  static scv_severity xlat_severity(severity_level severity);

private:
  static void setup();
};


#endif // ! _SCV_REPORT_H 