/*
 * File: hsts.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __HSTS_H__
#define __HSTS_H__

#include "d_size.h"
#include "url.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void  a_Hsts_init(FILE *fp);
void  a_Hsts_set(const char *header, const DilloUrl *url);
bool_t a_Hsts_require_https(const char *host);
void  a_Hsts_freeall( void );

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !__HSTS_H__ */
