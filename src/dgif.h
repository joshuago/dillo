/*
 * File: dgif.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __GIF_H__
#define __GIF_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "url.h"
#include "image.hh"


void *a_Gif_new(DilloImage *Image, DilloUrl *url, int version);
void a_Gif_callback(int Op, void *data);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !__GIF_H__ */
