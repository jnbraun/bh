/*
* Copyright (c) 2016 Jean-Noel Braun.
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


#ifndef BH_H
#define BH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <assert.h>
#include <limits.h>


#if defined(_MSC_VER) && (_MSC_VER > 1000) 
#pragma once
#endif

#if defined(_MSC_VER)
#	define bh_inline __inline
#elif defined(__GNUC__)
#	define bh_inline __inline__
#else
#	error Unknwown compiler
#endif 

#if defined(__GNUC__) || (defined(_MSC_VER) && (_MSC_VER >= 1600))
#include <stdint.h>
#else
#  if (_MSC_VER < 1300)
typedef signed char       int8_t;
typedef signed short      int16_t;
typedef signed int        int32_t;
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned int      uint32_t;
#  else
typedef signed __int8     int8_t;
typedef signed __int16    int16_t;
typedef signed __int32    int32_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
#  endif
typedef signed __int64    int64_t;
typedef unsigned __int64  uint64_t;
#endif



#define bh_clamp(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))
#define bh_min(a, b) (((a) < (b)) ? (a) : (b))
#define bh_max(a, b) (((a) > (b)) ? (a) : (b))
#define bh_swap(a, b, type) { type t = (a); (a) = (b); (b) = t; }
#define bh_abs(a) (((a) < (0)) ? -(a) : (a))

#define bh_free(buf) { if (buf) {free(buf); (buf) = NULL; }}


#ifdef __cplusplus

}
#endif

#endif