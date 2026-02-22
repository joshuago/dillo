/*
 * File: dwebp.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __WEBP_H__
#define __WEBP_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "url.h"
#include "image.hh"


void *a_Webp_new(DilloImage *Image, DilloUrl *url, int version);
void a_Webp_callback(int Op, void *data);
const char *a_Webp_version(char *buf, int n);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !__WEBP_H__ */
