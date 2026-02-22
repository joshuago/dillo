/*
 * File: doctree.hh
 *
 * Copyright (C) 2024-2025 Rodrigo Arias Mallo <rodarima@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
#ifndef __DOCTREE_HH__
#define __DOCTREE_HH__

#include "lout/misc.hh"

class DoctreeNode {
    public:
        DoctreeNode *parent;
        DoctreeNode *sibling;
        DoctreeNode *lastChild;
        int num; // unique ascending id
        int element;
        lout::misc::SimpleVector<char*> *klass;
        const char *pseudo;
        const char *id;

        DoctreeNode () {
            parent = NULL;
            sibling = NULL;
            lastChild = NULL;
            klass = NULL;
            pseudo = NULL;
            id = NULL;
            element = 0;
        };

        ~DoctreeNode () {
            dFree ((void*) id);
            while (lastChild) {
                DoctreeNode *n = lastChild;
                lastChild = lastChild->sibling;
                delete n;
            }
            if (klass) {
                for (int i = 0; i < klass->size (); i++)
                    dFree (klass->get(i));
                delete klass;
            }
        }
};

/**
 * \brief HTML document tree interface.
 *
 * The Doctree class defines the interface to the parsed HTML document tree
 * as it is used for CSS selector matching.
 */
class Doctree {
    private:
        DoctreeNode *topNode;
        DoctreeNode *rootNode;
        int num;

    public:
        Doctree () {
            rootNode = new DoctreeNode;
            topNode = rootNode;
            num = 0;
        };

        ~Doctree () {
            delete rootNode;
        };

        DoctreeNode *push () {
            DoctreeNode *dn = new DoctreeNode ();
            dn->parent = topNode;
            dn->sibling = dn->parent->lastChild;
            dn->parent->lastChild = dn;
            dn->num = num++;
            topNode = dn;
            return dn;
        };

        void pop () {
            assert (topNode != rootNode); // never pop the root node
            topNode = topNode->parent;
        };

        inline DoctreeNode *top () {
            if (topNode != rootNode)
                return topNode;
            else
                return NULL;
        };

        inline DoctreeNode *parent (const DoctreeNode *node) {
            if (node->parent != rootNode)
                return node->parent;
            else
                return NULL;
        };

        inline DoctreeNode *sibling (const DoctreeNode *node) {
            return node->sibling;
        };
};

#endif
