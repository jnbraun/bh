/*
* Copyright (c) 2016 Jean-No�l Braun.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/


#ifndef BH_TIMER_H
#define BH_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(_WIN32) || defined(_WIN64))
#include <windows.h>
#elif defined (__linux__)
#include <time.h>
#include <sys/time.h>
#endif

#include "bh.h"

/**
 * \brief Timer structure
 */
typedef struct {
    uint64_t	start;
    uint64_t	stop;
    uint64_t	freq;
} bh_timer; 


static bh_inline int bh_timer_start(bh_timer *t) 
{
#if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceFrequency((LARGE_INTEGER*)(&(t->freq)));
    QueryPerformanceCounter((LARGE_INTEGER*)(&(t->start)));
#elif defined(__linux__)
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t->start = ((uint64_t)ts.tv_sec) * 1000000L + (uint64_t)(ts.tv_nsec / 1000);
    }
#else
    fprintf(stderr, "[ERROR] OS not supported\n");
#endif
    return 0;
}

static bh_inline int bh_timer_stop(bh_timer *t) 
{
#if defined(_WIN32) || defined(_WIN64)
    QueryPerformanceCounter((LARGE_INTEGER*)(&(t->stop)));
#elif defined(__linux__)
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        t->stop = ((uint64_t)ts.tv_sec) * 1000000L + (uint64_t)(ts.tv_nsec / 1000);
    }
#else
    fprintf(stderr, "[ERROR] OS not supported\n");
#endif
    return 0;
}

static bh_inline double bh_timer_get_msec(bh_timer *t)
{
    uint64_t diff = t->stop - t->start;
#if defined(_WIN32) || defined(_WIN64)
    return (1000 * (double)(diff) / ((double)(t->freq)));
#elif defined(__linux__)
    return ((double)(diff) / 1000);
#else
    fprintf(stderr, "[ERROR] OS not supported\n");
#endif
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // BH_TIMER_H