/*
 * File: dpng.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __PNG_H__
#define __PNG_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "url.h"
#include "image.hh"
#include "cache.h"


void *a_Png_new(DilloImage *Image, DilloUrl *url, int version);
void a_Png_callback(int Op, CacheClient_t *Client);
const char *a_Png_version(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !__PNG_H__ */
