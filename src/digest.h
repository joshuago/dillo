/*
 * File: digest.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __DIGEST_H__
#define __DIGEST_H__

#include "auth.h"
#include "../dlib/dlib.h"


char *a_Digest_create_cnonce(void);
int a_Digest_compute_digest(AuthRealm_t *realm,
                            const char *username,
                            const char *passwd);
char *a_Digest_authorization_hdr(AuthRealm_t *realm,
                                            const DilloUrl *url,
                                            const char *uri);

#endif /* !__DIGEST_H__ */
