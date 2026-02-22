/*
 * File: bookmark.h
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __BOOKMARK_H__
#define __BOOKMARK_H__

#include "bw.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void a_Bookmarks_add(BrowserWindow *bw, const DilloUrl *url);

/* TODO: this is for testing purposes */
void a_Bookmarks_chat_add(BrowserWindow *Bw, char *Cmd, char *answer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BOOKMARK_H__ */
