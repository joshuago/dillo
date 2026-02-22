/*
 * File: bitvec.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __BITVEC_H__
#define __BITVEC_H__

#include "d_size.h"

#define BVEC_TYPE uchar_t
#define BVEC_SIZE sizeof(BVEC_TYPE)

typedef struct {
    BVEC_TYPE *vec;
    int len;       /* number of bits [1 based] */
} bitvec_t;


/*
 * Function prototypes
 */
bitvec_t *a_Bitvec_new(int bits);
void a_Bitvec_free(bitvec_t *bvec);
int a_Bitvec_get_bit(bitvec_t *bvec, int pos);
void a_Bitvec_set_bit(bitvec_t *bvec, int pos);
void a_Bitvec_clear(bitvec_t *bvec);

/*
#define a_Bitvec_get_bit(bvec,pos) \
    ((bvec)->vec[(pos)/BVEC_SIZE] & 1 << (pos) % BVEC_SIZE)

#define a_Bitvec_set_bit(bvec,pos) \
    ((bvec)->vec[(pos)/BVEC_SIZE] |= 1 << (pos) % BVEC_SIZE)
*/
#define a_Bitvec_clear_bit(bvec,pos) \
    ((bvec)->vec[(pos)/BVEC_SIZE] &= ~(1 << (pos) % BVEC_SIZE))


#endif /* __BITVEC_H__ */
