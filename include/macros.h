#ifndef _MACRO_H
#define _MACRO_H

#include <klib/timer.h>

#define time(code) uint64_t __time = timer_start(); code ; timer_end(__time);

#endif // _MACRO_H