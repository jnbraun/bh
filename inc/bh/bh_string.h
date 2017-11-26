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


#ifndef BH_STR_H
#define BH_STR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "bh.h"

static bh_inline char *bh_fgetline(FILE *fp)
{
    int size = 1024, readsize, curr, n;
    char *line = NULL;

    if (feof(fp)) {
        return NULL;
    }	
    
    line = (char *)calloc(size, sizeof(char));
    
    if (!fgets(line, size, fp)) {
        bh_free(line);
        return NULL;
    }

    curr = (int)strlen(line);

    while ((line[curr - 1] != '\n') && !feof(fp)) {
        if (curr == size - 1){
            size *= 2;
            line = (char *)realloc(line, size * sizeof(char));
            if (!line)
                return NULL;
        }
        readsize = size - curr;
        if (readsize > INT_MAX)
            readsize = INT_MAX - 1;
        if (!fgets(&line[curr], readsize, fp)) {
            bh_free(line);
            return NULL;
        }
        curr = (int)strlen(line);
    }
    if (line[curr - 1] == '\n')
        line[curr - 1] = '\0';
        
    return line;
}


static bh_inline int bh_strsplit(char *str, char c, char ***arr)
{
    int cnt = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0') {
        if (*p == c)
            cnt++;
        p++;
    }

    *arr = (char**)calloc(cnt, sizeof(char*));
    if (*arr == NULL)
        return 0;

    p = str;
    while (*p != '\0') {
        if (*p == c) {
            (*arr)[i] = (char*)calloc(token_len, sizeof(char));
            if ((*arr)[i] == NULL)
                return 0;

            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*arr)[i] = (char*)calloc(token_len, sizeof(char));
    if ((*arr)[i] == NULL)
        return 0;

    i = 0;
    p = str;
    t = ((*arr)[i]);
    while (*p != '\0') {
        if (*p != c && *p != '\0') {
            *t = *p;
            t++;
        }
        else {
            *t = '\0';
            i++;
            t = ((*arr)[i]);
        }
        p++;
    }

    return cnt;
}


static bh_inline int bh_strstrip(char *s)
{
    size_t i;
    size_t len = strlen(s);
    size_t offset = 0;
    for (i = 0; i < len; ++i) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\n')
            ++offset;
        else
            s[i - offset] = c;
    }
    s[len - offset] = '\0';

    return 0;
}

static bh_inline int bh_fill_option(char **option, char *argv)
{
    size_t length;
    bh_free(*option);
    length = strlen(argv) + 1;
    *option = (char *)calloc(length, sizeof(char));
    memcpy(*option, argv, length);

    return 0;
}


static bh_inline int bh_fskipline(FILE *f, int nb_lines)
{
    int i;
    char *line = NULL;

    for (i = 0; i < nb_lines; ++i) {
        line = bh_fgetline(f);
        if (line == NULL) {
            rewind(f);
            line = bh_fgetline(f);
        }
        bh_free(line);
    }

    return 0;
}


#ifdef __cplusplus
}
#endif

#endif // BH_STR_H