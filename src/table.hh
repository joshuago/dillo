/*
 * File: table.hh
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __TABLE_HH__
#define __TABLE_HH__

/*
 * Classes
 */

class DilloHtml;

/*
 * Table parsing functions
 */

void Html_tag_open_table(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_content_table(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_tr(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_content_tr(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_td(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_content_td(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_tbody(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_content_tbody(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_tfoot(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_thead(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_open_th(DilloHtml *html, const char *tag, int tagsize);
void Html_tag_content_th(DilloHtml *html, const char *tag, int tagsize);

#endif /* __TABLE_HH__ */
