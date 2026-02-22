/*
 * File: auth.h
 *
 * Copyright (C) 2024 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef __AUTH_H__
#define __AUTH_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "url.h"

enum AuthParseHTTPAuthType_t { TYPENOTSET, BASIC, DIGEST };
enum AuthParseDigestAlgorithm_t { ALGORITHMNOTSET, MD5, MD5SESS };
enum AuthParseDigestQOP_t { QOPNOTSET, AUTH, AUTHINT };

typedef struct {
    enum AuthParseHTTPAuthType_t type;
    char *name;
    Dlist *paths; /* stripped of any trailing '/', so the root path is "" */
    char *authorization; /* BASIC: the authorization request header */
                                /* DIGEST: the hexdigest of A1             */
    /* digest state ahead */
    char *username;
    char *cnonce;
    unsigned int nonce_count;
    char *nonce;
    char *opaque;
    enum AuthParseDigestAlgorithm_t algorithm;
    char *domain; /* NOT USED */
    enum AuthParseDigestQOP_t qop;
} AuthRealm_t;


char *a_Auth_get_auth_str(const DilloUrl *url, const char *request_uri);
int a_Auth_do_auth(Dlist *auth_string, const DilloUrl *url);
void a_Auth_init(void);


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* !__AUTH_H__ */
