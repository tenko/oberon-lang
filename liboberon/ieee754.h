/* Copyright (C) 1992, 1995, 1996, 1999 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _IEEE754_H

#define _IEEE754_H 1

#if defined(__FreeBSD__) || defined(__APPLE__) || defined(__FreeBSD_kernel__) || defined(__OpenBSD__)
    #include <machine/endian.h>
#endif

#if defined(__linux__) || defined(__CYGWIN__) || defined(__GNU__) || defined(ANDROID)
    #include <endian.h>
#endif

#ifdef __MINGW32__
    #include <sys/param.h>
#endif

#ifdef _MSC_VER
    #define LITTLE_ENDIAN 0x0001
    #define BYTE_ORDER LITTLE_ENDIAN
    #define FLOAT_WORD_ORDER BYTE_ORDER
#endif


union ieee754_float
{
    float f;

    /* This is the IEEE 754 single-precision format.  */
    struct {
#if BYTE_ORDER == BIG_ENDIAN
        unsigned int negative:1;
        unsigned int exponent:8;
        unsigned int mantissa:23;
#endif                                /* Big endian.  */
#if BYTE_ORDER == LITTLE_ENDIAN
        unsigned int mantissa:23;
        unsigned int exponent:8;
        unsigned int negative:1;
#endif                                /* Little endian.  */
    } ieee;

    /* This format makes it easier to see if a NaN is a signalling NaN.  */
    struct {
#if BYTE_ORDER == BIG_ENDIAN
        unsigned int negative:1;
        unsigned int exponent:8;
        unsigned int quiet_nan:1;
        unsigned int mantissa:22;
#endif                                /* Big endian.  */
#if BYTE_ORDER == LITTLE_ENDIAN
        unsigned int mantissa:22;
        unsigned int quiet_nan:1;
        unsigned int exponent:8;
        unsigned int negative:1;
#endif                                /* Little endian.  */
    } ieee_nan;
};

union ieee754_double {
    double d;

    /* This is the IEEE 754 double-precision format.  */
    struct {
#if BYTE_ORDER == BIG_ENDIAN
        unsigned int negative:1;
        unsigned int exponent:11;
        /* Together these comprise the mantissa.  */
        unsigned int mantissa0:20;
        unsigned int mantissa1:32;
#endif                                /* Big endian.  */
#if BYTE_ORDER == LITTLE_ENDIAN
        #if FLOAT_WORD_ORDER == BIG_ENDIAN
            unsigned int mantissa0:20;
            unsigned int exponent:11;
            unsigned int negative:1;
            unsigned int mantissa1:32;
        #else
            /* Together these comprise the mantissa.  */
            unsigned int mantissa1:32;
            unsigned int mantissa0:20;
            unsigned int exponent:11;
            unsigned int negative:1;
        #endif
#endif                                /* Little endian.  */
    } ieee;

    /* This format makes it easier to see if a NaN is a signalling NaN.  */
    struct {
#if BYTE_ORDER == BIG_ENDIAN
        unsigned int negative:1;
        unsigned int exponent:11;
        unsigned int quiet_nan:1;
        /* Together these comprise the mantissa.  */
        unsigned int mantissa0:19;
        unsigned int mantissa1:32;
#else
    #if FLOAT_WORD_ORDER == BIG_ENDIAN
        unsigned int mantissa0:19;
        unsigned int quiet_nan:1;
        unsigned int exponent:11;
        unsigned int negative:1;
        unsigned int mantissa1:32;
    #else
        /* Together these comprise the mantissa.  */
        unsigned int mantissa1:32;
        unsigned int mantissa0:19;
        unsigned int quiet_nan:1;
        unsigned int exponent:11;
        unsigned int negative:1;
    #endif
#endif
    } ieee_nan;
};

#endif //_IEEE754_H
