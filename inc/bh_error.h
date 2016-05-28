/*
* Copyright (c) 2016 Jean-Noël Braun.
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


#ifndef BH_ERROR_H
#define BH_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>

#define bh_info(msg) { fprintf(stderr, "[INFO] %s\n", (msg)); fflush(stderr); }
#define bh_warning(msg) { fprintf(stderr, "[WARNING] %s\n", (msg)); }
#define bh_error(msg, err) { fprintf(stderr, "[ERROR] %s\n", (msg)); return err; }
#define bh_assert(cond, msg, err) { if (cond) { (void)0; }else { fprintf(stderr, "[ERROR] %s\n", (msg)); return err; }}

#define bh_assert(exp, msg, err) { if (exp) { (void)0; }else { fprintf(stderr, "[ERROR] %s\n", (msg)); return err; }}
#define bh_assert_valid_ptr(p, err)  if (((void*)p) == ((void*)NULL)) { fprintf(stderr, "[ERROR] Invalid pointer\n"); return err;}
#define bh_assert_valid_size(size, err) { if (size <= 0) { return err;} }

#ifdef __cplusplus

}
#endif

#endif