# Automated Testing in Dillo

## Overview

Dillo uses GNU Automake's test framework for automated testing. Tests are organized into several categories based on their scope and requirements.

## Test Types & Organization

| Type | Location | Headless? | Description |
|------|----------|-----------|-------------|
| **Unit** | `test/unit/` | Yes | Standalone C/C++ binaries testing individual components |
| **DW Widget** | `test/dw/` | Mixed | Tests for the Dw (Document Widget) library |
| **HTML Render** | `test/html/` | Yes (via Xvfb) | Visual rendering comparison tests |
| **Dilloc** | `test/dilloc/` | Yes (via Xvfb) | Command/control tests for Dillo's IPC |

## Running Tests

```bash
make check        # Run all test suites
make recheck      # Re-run failed tests only
```

To run a specific test suite:

```bash
cd test/unit && make check
cd test/html && make check
cd test/dilloc && make check
cd test/dw && make check
```

## Unit Tests (`test/unit/`)

Standalone C/C++ executables that test individual library components. These do not require a graphical display.

### Active Tests

| Test | Description |
|------|-------------|
| `containers` | Hash and vector container tests |
| `disposition` | Content-Disposition header parsing |
| `identity` | Object identity tests |
| `liang` | Liang hyphenation algorithm |
| `notsosimplevector` | Vector implementation tests |
| `shapes` | Drawing shape tests |
| `unicode_test` | Unicode handling tests |

### Adding a Unit Test

1. Create a `.c` or `.cc` file in `test/unit/`
2. Add to `TESTS` in `test/unit/Makefile.am`
3. Define `<testname>_SOURCES` and `<testname>_LDADD` variables
4. Run `autoreconf` to regenerate Makefile

## DW Widget Tests (`test/dw/`)

Tests for the Document Widget library. Some tests require FLTK and a display, others can run headlessly.

### Tests

| Test | Display Required | Description |
|------|------------------|-------------|
| `dw-imgbuf-mem-test` | Yes | Image buffer memory management |
| `widgets` | Yes | Widget rendering tests |

## HTML Render Tests (`test/html/`)

Visual regression tests that compare rendered HTML pages against reference images. These tests use Xvfb for headless operation.

### How They Work

1. Start Xvfb virtual display server
2. Launch Dillo with test HTML file
3. Capture screenshot using `xwd`
4. Compare against reference image using ImageMagick `compare`
5. Test passes if images are pixel-identical

### Test Structure

Each test consists of:
- `<name>.html` - The test HTML file
- `<name>.ref.html` - Reference HTML for comparison

### Categories

Tests cover various CSS and layout features:
- Image aspect ratios
- Margin and width calculations
- Table rendering
- Float layouts
- Text alignment

### Known Issues (XFAIL)

Some tests are marked as expected failures (`XFAIL_TESTS`):
- `div-100-percent-with-padding.html`
- `float-img-justify.html`
- `margin-auto.html`
- `margin-rounding.html`
- `max-width-html.html`
- `min-width-html.html`
- `multiple-floats.html`
- `span-padding.html`
- `table-td-width-percent.html`

## Dilloc Tests (`test/dilloc/`)

Tests for Dillo's command/control IPC mechanism. Uses `dilloc` binary to control Dillo programmatically.

### Tests

| Test | Description |
|------|-------------|
| `cmd-load.sh` | Page loading commands |
| `cmd-load-multi.sh` | Multiple page loads |
| `cmd-load-deadlock.sh` | Deadlock prevention |
| `cmd-title.sh` | Title retrieval |

## Headless Execution

### Xvfb Virtual Display

The test suite uses Xvfb (X Virtual Framebuffer) for headless execution:

```bash
# How tests start Xvfb (from test/lib/xorg.sh)
Xvfb -screen 5 1024x768x24 -displayfd 6 &
```

### Using an Existing Display

For debugging, you can use an existing display:

```bash
export DILLO_DISPLAY=:0
make check
```

### Required Tools

For full test suite execution:
- `Xvfb` - Virtual X server
- `xwd` - X window dump utility
- `xwininfo` - Window information utility
- ImageMagick (`compare`, `convert` or `magick`) - Image comparison

## Test Infrastructure Files

### Library Scripts (`test/lib/`)

| File | Purpose |
|------|---------|
| `xorg.sh` | Xvfb start/stop functions |
| `dilloc.sh` | Dillo/dilloc setup and control |
| `workdir.sh` | Temporary directory management |

### Driver Scripts

Each test directory has a `driver.sh` that:
- Sets up the test environment
- Runs the test
- Reports results
- Cleans up

## Memory Leak Detection

The test suite includes leak filtering via `test/html/leakfilter.awk` to catch memory leaks during test execution. When building with AddressSanitizer (ASAN), leaks are detected automatically.

## Adding New Tests

### Unit Test Example

```c
// test/unit/mytest.c
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Test code here
    if (success) {
        return 0;
    } else {
        fprintf(stderr, "Test failed\n");
        return 1;
    }
}
```

### HTML Render Test Example

1. Create `test/html/render/mytest.html`
2. Create `test/html/render/mytest.ref.html` with expected rendering
3. Add `render/mytest.html` to `TESTS` in `test/html/Makefile.am`
4. Run `autoreconf`

## Continuous Integration

The test suite is designed to run in CI environments:

- All tests can run without physical display
- Tests clean up after themselves
- Exit codes indicate pass/fail
- Log files generated for debugging (`test-suite.log`)
