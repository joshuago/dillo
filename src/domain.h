/*
 * File: domain.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __DOMAIN_H__
#define __DOMAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "url.h"

void a_Domain_parse(FILE *fp);
void a_Domain_freeall(void);
bool_t a_Domain_permit(const DilloUrl *source, const DilloUrl *dest);

#ifdef __cplusplus
}
#endif

#endif
