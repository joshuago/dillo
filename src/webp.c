/*
 * File: webp.c
 *
 * Copyright (C) 2024 dogma
 * Copyright (C) 2024 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */

#include <config.h>
#ifdef ENABLE_WEBP

#include <stdlib.h> /* For abort() */

#include <webp/decode.h>

#include "msg.h"
#include "image.hh"
#include "cache.h"
#include "dicache.h"

enum prog_state {
    IS_finished, IS_init, IS_nextdata
};

typedef struct {
    DilloImage *Image;           /* Image meta data */
    DilloUrl *url;               /* Primary Key for the dicache */
    int version;                 /* Secondary Key for the dicache */
    int bgcolor;                 /* Parent widget background color */
    int state;
    int y;
    int width;
    WebPIDecoder* idec;
    WebPDecBuffer output_buffer; /* for RGBA */
    uchar_t *linebuf;            /* Reusable line buffer for RGBA->RGB */
} DilloWebp;


/*
 * Free up the resources for this image.
 */
static void Webp_free(DilloWebp *webp)
{
    _MSG("Webp_free: webp=%p\n", webp);

    WebPFreeDecBuffer(&webp->output_buffer);
    if (webp->idec)
        WebPIDelete(webp->idec);
    dFree(webp->linebuf);
    dFree(webp);
}

/*
 * Finish the decoding process (and free the memory)
 */
static void Webp_close(DilloWebp *webp, CacheClient_t *Client)
{
    _MSG("Webp_close\n");
    /* Let dicache know decoding is over */
    a_Dicache_close(webp->url, webp->version, Client);
    Webp_free(webp);
}

/*
 * Op:  Operation to perform.
 *   If (Op == 0)
 *      start or continue processing an image if image data exists.
 *   else
 *       terminate processing, cleanup any allocated memory,
 *       close down the decoding process.
 *
 * Client->CbData  : pointer to previously allocated work area.
 *  This holds the current state of the image processing and is kept
 *  across calls to this routine.
 * Client->Buf     : Pointer to data start.
 * Client->BufSize : the size of the data buffer.
 *
 * You have to keep track of where you are in the image data and
 * how much has been processed.
 *
 * It's entirely possible that you will not see the end of the data.  The
 * user may terminate transfer via a Stop button or there may be a network
 * failure.  This means that you can't just wait for all the data to be
 * presented before starting conversion and display.
 */
void a_Webp_callback(int Op, void *data)
{
    CacheClient_t *Client = data;

    if (Op == CA_Send) {
        uint8_t* output;
        VP8StatusCode ret;

        DilloWebp *webp = (DilloWebp *)Client->CbData;

        if (webp->state == IS_init) {
            WebPBitstreamFeatures features;

            ret = WebPGetFeatures(Client->Buf, Client->BufSize, &features);
            if (ret != VP8_STATUS_OK) {
                MSG("features ret is %d\n", ret);
                return;
            }
            if (features.has_alpha) {
                _MSG("WEBP: Alpha!\n");
            }
            webp->output_buffer.colorspace = features.has_alpha ? MODE_RGBA : MODE_RGB;

            a_Dicache_set_parms(webp->url, webp->version, webp->Image,
                             features.width, features.height,
                             DILLO_IMG_TYPE_RGB, 1 / 2.2);

            webp->width = features.width;
            if (features.has_alpha) {
                webp->linebuf = dNew(uchar_t, features.width * 3);
            }

            webp->idec = WebPINewDecoder(&webp->output_buffer);
            webp->state = IS_nextdata;
        }

        ret = WebPIUpdate(webp->idec, Client->Buf, Client->BufSize);
        /* SUSPENDED is a success state that means you don't have the entire file yet */
        if (ret == VP8_STATUS_SUSPENDED || ret == VP8_STATUS_OK) {
            /* last_y seems 1-based, which would be kind of crazy, but I would expect
          * crazy idiocy from google.
          */
            int last_y, width, height, stride;

            _MSG("webp completed. status: %s\n", ret == VP8_STATUS_SUSPENDED ? "suspended" : "ok (done)");
            output = WebPIDecGetRGB(webp->idec, &last_y, &width, &height, &stride);
            if (!output) {
                _MSG("webp decoding no output\n");
            } else {
                unsigned char *line;
                int row = webp->y;

                if (webp->output_buffer.colorspace == MODE_RGBA)
                    line = webp->linebuf;
                else
                    line = output + row * stride;

                for (; row < last_y; row++) {

                    if (webp->output_buffer.colorspace == MODE_RGBA) {
                        int j = 0;
                        const uint8_t *src = output + row * stride;
                        uint8_t *dst = line;
                        uint_t bg_blue  = (webp->bgcolor) & 0xFF;
                        uint_t bg_green = (webp->bgcolor>>8) & 0xFF;
                        uint_t bg_red   = (webp->bgcolor>>16) & 0xFF;

                        while (j < width) {
                            uint_t alpha = src[3];
                            if (alpha == 255) {
                                memcpy(dst, src, 3);
                                src += 4;
                                dst += 3;
                            } else if (alpha == 0) {
                                dst[0] = bg_red;
                                dst[1] = bg_green;
                                dst[2] = bg_blue;
                                src += 4;
                                dst += 3;
                            } else {
                                uint_t inv_alpha = 255 - alpha;
                                dst[0] = (src[0] * alpha + bg_red * inv_alpha) / 255;
                                dst[1] = (src[1] * alpha + bg_green * inv_alpha) / 255;
                                dst[2] = (src[2] * alpha + bg_blue * inv_alpha) / 255;
                                src += 4;
                                dst += 3;
                            }
                            j++;
                        }
                    } else {
                        line = output + row * stride;
                    }
                    a_Dicache_write(webp->url, webp->version, line, row);
                }
                webp->y = last_y;
            }
        } else {
            MSG("webp WebPIUpdate failed with %d\n", ret);
        }
    } else if (Op == CA_Close) {
        Webp_close(Client->CbData, Client);
    } else if (Op == CA_Abort) {
        Webp_free(data);
    }
}

const char *a_Webp_version(char *buf, int n)
{
    /* Return the decoder's version number, packed in
    * hexadecimal using 8bits for each of major/minor/revision.
    * E.g: v2.5.7 is 0x020507. */
    int ver = WebPGetDecoderVersion();

    int major = (ver >> 16) & 0xff;
    int minor = (ver >>  8) & 0xff;
    int rev   = (ver >>  0) & 0xff;

    int k = snprintf(buf, n, "%d.%d.%d", major, minor, rev);
    if (k >= n)
        return "?";
    return buf;
}

/*
 * Create the image state data that must be kept between calls
 */
void *a_Webp_new(DilloImage *Image, DilloUrl *url, int version)
{
    DilloWebp *webp = dNew0(DilloWebp, 1);
    _MSG("a_Webp_new: webp=%p\n", webp);

    webp->Image = Image;
    webp->url = url;
    webp->version = version;

    webp->bgcolor = Image->bg_color;
    webp->state = IS_init;
    webp->y = 0;
    webp->width = 0;
    webp->idec = NULL;
    webp->linebuf = NULL;
    WebPInitDecBuffer(&webp->output_buffer);

    return webp;
}

#else /* ENABLE_WEBP */

void *a_Webp_new() { return 0; }
void a_Webp_callback() { return; }
const char *a_Webp_version(char *buf, int n) { return 0; }

#endif /* ENABLE_WEBP */
