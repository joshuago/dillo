/*
 * File: xembed.hh
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __XEMBED_HH__
#define __XEMBED_HH__

#include <FL/Fl_Window.H>

#include "d_size.h"

class Xembed : public Fl_Window {
    private:
        uint32_t xid;
        void createInternal(uint32_t parent);
        void setXembedInfo(unsigned long flags);
        void sendXembedEvent(uint32_t message);

    public:
        Xembed(uint32_t xid, int _w, int _h) : Fl_Window(_w, _h) {
            this->xid = xid;
        };
        void show();
        int handle(int event);
};

#endif
