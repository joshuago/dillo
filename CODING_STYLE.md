# Dillo Coding Style Guide

This document describes the coding conventions used in the Dillo web browser project.

## Basic Formatting

### Indentation

- Use **4 spaces** for indentation
- **Never use tabs**
- Maximum line length: 80-100 characters (soft limit)

### Braces

- **Functions**: Opening brace on a new line (Allman style)
- **Control structures**: Opening brace on the same line (K&R style)

```c
void my_function(int arg)
{
    if (condition) {
        do_something();
    } else {
        do_other();
    }
}
```

### Whitespace

- Space after keywords: `if (`, `while (`, `for (`, `switch (`
- Space around operators: `a = b + c`
- No trailing whitespace on lines
- No CRLF line endings (use LF only)

## Comments

### C Files (.c, .h)

Use traditional C-style comments only:

```c
/* Single-line comment */

/*
 * Multi-line comment
 * Second line
 */

/** 
 * Doxygen documentation comment
 * @param name Description
 */
```

**Do not use** C++ style `//` comments in C files.

### C++ Files (.cc, .hh)

Both styles are acceptable:

```cpp
// C++ style comment

/* C style comment */
```

### Doxygen Style

Use `\brief` for Doxygen documentation:

```c
/**
 * \brief Short description of the function.
 *
 * Longer description if needed.
 *
 * \param arg1 Description of first argument
 * \return Description of return value
 */
```

## Naming Conventions

### Functions

| Type | Convention | Example |
|------|------------|---------|
| Public API (src/) | `a_CamelCase` | `a_Url_new()`, `a_Cache_init()` |
| Public API (dlib/) | `dCamelCase` | `dMalloc()`, `dStrdup()` |
| Internal/static | `CamelCase` | `Url_object_new()` |

### Types

- **Classes/Structs**: `PascalCase` - `DilloUrl`, `CacheEntry_t`
- **Typedefs**: `PascalCase` with optional `_t` suffix

### Variables

- **Local variables**: `snake_case` or `camelCase`
- **Struct members**: `snake_case`
- **Constants/Macros**: `UPPER_SNAKE_CASE`

```c
#define MAX_BUFFER_SIZE 1024
#define URL_HTTP_PORT 80

static const char *HEX = "0123456789ABCDEF";
```

## File Organization

### Header Guards

Use the `__FILENAME_H__` pattern:

```c
#ifndef __URL_H__
#define __URL_H__

/* content */

#endif /* __URL_H__ */
```

For C++ headers:

```cpp
#ifndef __DIALOG_HH__
#define __DIALOG_HH__

/* content */

#endif /* __DIALOG_HH__ */
```

### C++ Compatibility in C Headers

All C headers should include `extern "C"` guards:

```c
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* function declarations */

#ifdef __cplusplus
}
#endif /* __cplusplus */
```

### File Header

Every source file should begin with a copyright header:

```c
/*
 * File: filename.c
 *
 * Copyright (C) YEAR Author Name <email@example.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 */
```

## External Libraries

Files from external libraries (md5.c, nanosvg.h, etc.) are exempt from these
style guidelines. They should have an exemption notice at the top:

```c
/*
 * External library - formatting exempt from project style guidelines.
 * Original source: https://example.com/library
 */
```

## Memory Management

Use Dillo's wrapper functions instead of standard allocation:

- `dMalloc()`, `dNew()`, `dNew0()` instead of `malloc()`
- `dFree()` instead of `free()`
- `dStr_*` functions for string operations

## Error Handling

Use the validation macros at function entry:

```c
void my_function(DilloUrl *url)
{
    dReturn_if_fail(url != NULL);
    /* ... */
}

int my_other_function(void *ptr)
{
    dReturn_val_if_fail(ptr != NULL, -1);
    /* ... */
}
```

## Directory Structure

| Directory | Language | Purpose |
|-----------|----------|---------|
| `src/` | C/C++ | Main application |
| `dw/` | C++ | Widget library |
| `lout/` | C++ | Utility library |
| `dlib/` | C | C utility library |
| `dpi/` | C | DPI plugins |
| `dpid/` | C | DPI daemon |
| `dpip/` | C | DPI protocol |

## File Extensions

| Extension | Usage |
|-----------|-------|
| `.c` | C source files |
| `.h` | C header files |
| `.cc` | C++ source files |
| `.hh` | C++ header files |