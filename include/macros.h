#ifndef _MACRO_H
#define _MACRO_H

#include <klib/timer.h>

extern uint64_t __time;

#define time(code) __time = timer_start(); code ; timer_end(__time);

#endif // _MACRO_H
