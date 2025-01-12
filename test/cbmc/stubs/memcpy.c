/*
 * SigV4 Library v1.2.0
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
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

/**
 * @file memcpy.c
 * @brief A stub for memcpy so that the proofs for functions that call memcpy
 * run much faster.
 */

#include <string.h>

/* This is a clang macro not available on linux */
#ifndef __has_builtin
    #define __has_builtin( x ) 0
#endif

#if __has_builtin( __builtin___memcpy_chk )
void * __builtin___memcpy_chk( void * dest,
                               const void * src,
                               size_t n,
                               size_t m )
{
    /* Attempting to read or write 0 bytes will make __CPROVER_r/w_ok
     * fail. However, per ANSI C specification, memcpy must be able
     * to handle a copy length of zero. */
    __CPROVER_assert( ( n == 0 ) || __CPROVER_w_ok( dest, n ), "write" );
    __CPROVER_assert( ( n == 0 ) || __CPROVER_r_ok( src, n ), "read" );
    return dest;
}
#else  /* if __has_builtin( __builtin___memcpy_chk ) */
void * memcpy( void * dest, const void * src, size_t n )
{
    /* Per ANSI C specification, memcpy must be able to handle a copy length
     * of zero. */
    __CPROVER_assert( ( n == 0 ) || __CPROVER_w_ok( dest, n ), "write" );
    __CPROVER_assert( ( n == 0 ) || __CPROVER_r_ok( src, n ), "read" );
    return dest;
}
#endif /* if __has_builtin( __builtin___memcpy_chk ) */
