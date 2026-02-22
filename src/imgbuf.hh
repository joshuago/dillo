/*
 * File: imgbuf.hh
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __IMGBUF_HH__
#define __IMGBUF_HH__

// Imgbuf wrappers


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "image.hh"

/*
 * Function prototypes
 */
void a_Imgbuf_ref(void *v_imgbuf);
void a_Imgbuf_unref(void *v_imgbuf);
void *a_Imgbuf_new(void *v_ir, int img_type, uint_t width, uint_t height,
                   double gamma);
int a_Imgbuf_last_reference(void *v_imgbuf);
void a_Imgbuf_update(void *v_imgbuf, const uchar_t *buf, DilloImgType type,
                            uchar_t *cmap, uint_t width, uint_t height, uint_t y);
void a_Imgbuf_new_scan(void *v_imgbuf);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IMGBUF_HH__ */

