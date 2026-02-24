# AGENTS.md - Dillo Web Browser Codebase Guide

Guidance for AI agents working in the Dillo codebase - a lightweight web browser built with FLTK 1.3/1.4 in C (`.c`, `.h`) and C++ (`.cc`, `.hh`).

## Build Commands

```bash
./autogen.sh           # Generate configure script (first time only)
./configure            # Configure build
make                   # Build the project
make install           # Install to prefix

# Configuration options
./configure --enable-html-tests     # Enable HTML rendering tests
./configure --enable-tls            # Enable TLS/HTTPS (default)
./configure --enable-control-socket # Enable IPC socket
```

## Test Commands

```bash
make check            # Run all test suites
make recheck          # Re-run failed tests only
cd test/unit && make check     # Unit tests (headless)
cd test/dw && make check       # Widget tests
cd test/html && make check     # HTML rendering tests
```

### Running a Single Unit Test

```bash
cd test/unit
make containers         # Build the test
./containers            # Run it directly
```

### Debugging & Sanitizers

```bash
export DILLO_DISPLAY=:0   # Use existing display
./configure CFLAGS="-fsanitize=address" CXXFLAGS="-fsanitize=address"
make check
```

## Code Style

### Formatting

- **4 spaces** for indentation (never tabs)
- Line length: 80-100 characters soft limit
- **No trailing whitespace**, **LF line endings only**
- **Functions**: Opening brace on new line (Allman)
- **Control structures**: Opening brace on same line (K&R)

```c
void my_function(int arg)
{
    if (condition) {
        do_something();
    }
}
```

### Comments

**C files (.c, .h)**: Traditional C-style only (`/* */`). **No `//` comments.**

**C++ files (.cc, `.hh`)**: Both styles acceptable.

### Naming Conventions

| Type | Convention | Example |
|------|------------|---------|
| Public API (src/) | `a_CamelCase` | `a_Url_new()` |
| Public API (dlib/) | `dCamelCase` | `dMalloc()` |
| Internal/static | `CamelCase` | `Url_object_new()` |
| Classes/Structs | `PascalCase` | `DilloUrl` |
| Local variables | `snake_case` | `buffer_size` |
| Constants/Macros | `UPPER_SNAKE_CASE` | `MAX_BUFFER_SIZE` |

### Include Order

**C files**: Standard library → project headers → dlib

```c
#include <stdlib.h>
#include <string.h>
#include "url.h"
#include "dlib/dlib.h"
```

**C++ files**: Standard library → project headers → dlib → dw/FLTK

```cpp
#include <stdlib.h>
#include "bw.h"
#include "dlib/dlib.h"
#include "dw/textblock.hh"
using namespace lout;
using namespace dw;
```

### Header Guards

```c
#ifndef __URL_H__
#define __URL_H__
#ifdef __cplusplus
extern "C" {
#endif
/* declarations */
#ifdef __cplusplus
}
#endif
#endif /* __URL_H__ */
```

## Error Handling

Use validation macros at function entry:

```c
void my_function(DilloUrl *url)
{
    dReturn_if_fail(url != NULL);
}

int my_other_function(void *ptr)
{
    dReturn_val_if_fail(ptr != NULL, -1);
}
```

## Memory Management

Use Dillo's wrappers instead of standard allocation:

```c
dNew(Type, count)   /* malloc */
dNew0(Type, count)  /* calloc */
dFree(ptr)          /* free */
dStr_new(s)         /* dynamic string */
```

## Directory Structure

| Directory | Language | Purpose |
|-----------|----------|---------|
| `src/` | C/C++ | Main application |
| `dw/` | C++ | Widget library |
| `lout/` | C++ | Utility library |
| `dlib/` | C | C utility library |
| `dpi/`, `dpid/`, `dpip/` | C | DPI plugins/daemon/protocol |
| `test/unit/` | C/C++ | Unit tests |

## Adding a Unit Test

1. Create `test/unit/mytest.c` (or `.cc`)
2. Add to `TESTS` in `test/unit/Makefile.am`
3. Define `mytest_SOURCES` and `mytest_LDADD`
4. Run `autoreconf`

## Key Files

- `CODING_STYLE.md` - Full style guide
- `AUTOMATED_TESTING.md` - Testing docs
- `devdoc/` - Architecture docs
