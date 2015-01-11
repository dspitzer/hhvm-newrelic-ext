/*
+----------------------------------------------------------------------+
| HipHop for PHP                                                       |
+----------------------------------------------------------------------+
| Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
| Copyright (c) 1997-2010 The PHP Group                                |
+----------------------------------------------------------------------+
| This source file is subject to version 3.01 of the PHP license,      |
| that is bundled with this package in the file LICENSE, and is        |
| available through the world-wide-web at the following url:           |
| http://www.php.net/license/3_01.txt                                  |
| If you did not receive a copy of the PHP license and are unable to   |
| obtain it through the world-wide-web, please send a note to          |
| license@php.net so we can mail you a copy immediately.               |
+----------------------------------------------------------------------+
*/

#include "newrelic_profiler.h"
#include "hphp/runtime/ext/ext_hotprofiler.h"

namespace HPHP {
    void NewRelicProfiler::beginFrameEx(const char *symbol) {
        if (m_stack->m_parent) {
            Frame *p = m_stack->m_parent;
            m_stack->m_recursion = p->m_recursion + 1;
        } else {
            m_stack->m_recursion  = 0;
        }
        m_stack->m_hash_code = 0;
        if (m_stack->m_recursion < max_depth) {
            m_stack->m_hash_code = newrelic_segment_generic_begin(NEWRELIC_AUTOSCOPE, NEWRELIC_AUTOSCOPE, m_stack->m_name);
        }

    }

    void NewRelicProfiler::endFrameEx(const TypedValue *retval,
    const char *given_symbol) {

        if ( m_stack->m_hash_code != 0) {
            newrelic_segment_end(NEWRELIC_AUTOSCOPE, m_stack->m_hash_code);
            m_stack->m_hash_code = 0;
        }
    }

}