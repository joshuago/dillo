/*
 * File: decode.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __DECODE_H__
#define __DECODE_H__

#include "../dlib/dlib.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct Decode {
    char *buffer;
    Dstr *leftover;
    void *state;
    Dstr *(*decode) (struct Decode *dc, const char *instr, int inlen);
    void (*free) (struct Decode *dc);
} Decode;

/* I'm not going to shoehorn the decoders into the same form anymore. They
 * can evolve independently.
 */
typedef struct DecodeTransfer {
    Dstr *leftover;
    void *state;
    bool_t finished;    /**< has the terminating chunk been seen? */
} DecodeTransfer;

DecodeTransfer *a_Decode_transfer_init(const char *format);
Dstr *a_Decode_transfer_process(DecodeTransfer *dc, const char *instr,
                                int inlen);
bool_t a_Decode_transfer_finished(DecodeTransfer *dc);
void a_Decode_transfer_free(DecodeTransfer *dc);

Decode *a_Decode_content_init(const char *format);
Decode *a_Decode_charset_init(const char *format);
Dstr *a_Decode_process(Decode *dc, const char *instr, int inlen);
void a_Decode_free(Decode *dc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __DECODE_H__ */
