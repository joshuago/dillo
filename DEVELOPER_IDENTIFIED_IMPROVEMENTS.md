# Developer-Identified Improvements Roadmap

*Generated from codebase analysis on February 23, 2026*

## Overview

This document catalogs 72+ TODO items identified across the Dillo codebase, categorized by priority and functional area. These items represent technical debt and opportunities for improvement left by previous developers.

## Category 1: Core Browser Functionality (High Priority)

### URL/Public Suffix Handling
- **File**: `src/url.c:748`
  - **TODO**: Consider the old publicsuffix code again. This TLD list has...
- **File**: `dpi/cookies.c`
  - **TODO**: accept the publicsuffix.org list as an optional external file.

### Cookie Management
- **File**: `test/unit/cookies.c`
  - **TODO**: revisit these tests in a few decades

### Security & Process Isolation
- **File**: `dpid/main.c`
  - **TODO**: make dpid work on any directory.
  - **TODO**: call setsid() ??
  - **TODO**: can this cause trouble with umount?

### DPI Protocol
- **File**: `src/IO/dpi.c`
  - **TODO**: define an API and move this function into libDpip.a.
- **File**: `dpi/bookmarks.c`
  - **TODO**: we should send an "Bookmark added" message, but the...
  - **TODO**: this server is not assembling the received packets.

## Category 2: Rendering & Layout Engine (Medium-High Priority)

### Text Layout & Line Breaking
- **File**: `dw/textblock.cc` (12+ TODOs)
  - Line 84: Subtract margin and border (padding box)?
  - Line 233: Some tests would be useful.
  - Line 609: test case?
  - Line 632: For word->flags & Word::TOPLEFT_OF_LINE, make...
  - Line 1105: The width of a text is not the sum...
  - Line 1337: TODO Comment
  - Line 1992: The containing block's line-height property gives a minimum...
  - Line 2332: Actually line1OffsetEff should be used instead of line1Offset, but...
  - Line 2528: Replace (perhaps) later "textblock" by "OOF aware widget".
  - Line 2671: Re-evaluate again.
  - Line 2675: This line does not work: addBreakOption (word, style);
  - Line 2711: lineMustBeBroken should be independent of the penalty

- **File**: `dw/textblock_linebreaking.cc`
  - Multiple TODOs in line breaking algorithm
  - Hyphenation improvements needed
  - Penalty handling clarifications

### Table Rendering
- **File**: `dw/table.cc` (8 TODOs)
  - Column/row spanning improvements
  - Width calculation fixes
  - Documentation updates needed
- **File**: `dw/table.hh`
  - **TODO**: Documentation needs updating

### Image Handling
- **File**: `src/png.c`
  - Line 177: select screen gamma correction for other platforms (currently only works on PCs)
  - Line 253: get the background color from the parent
  - Line 259: maybe change prefs.bg_color to `a_Dw_widget_get_bg_color`
- **File**: `dw/fltkimgbuf.cc`
  - Image scaling optimization opportunities
  - Buffer management improvements

### Out-of-Flow (OOF) Layout
- **File**: `dw/oofawarewidget.cc`
  - **TODO**: The methods isPossibleContainer() and isPossibleContainerParent()...
- **File**: `dw/oofposabslikemgr.cc`
  - Multiple TODOs in positioned element handling
- **File**: `dw/oofpositionedmgr.cc`
  - **TODO**: (empty but marked)

## Category 3: HTML/CSS Support (Medium Priority)

### HTML Parser
- **File**: `src/html.cc` (15+ TODOs)
  - Complete `<div>` support
  - XHTML close tag handling
  - Doctype parsing improvements
  - Language attribute support
  - ALIGN attribute handling
  - usemap URL support
  - media attribute handling (handheld, etc.)
  - TBODY element support
  - MAP with A HREF support
  - video poster attribute
  - Image scaling ratio preservation
  - Percentage and relative length handling

### CSS Properties
- **File**: `dw/widget.cc`
  - min-height/max-height support
  - Percentage height handling
  - Nested layout considerations
  - Inverse drawing handling
- **File**: `dw/textblock.hh`
  - **TODO**: perhaps add a xLeft?

## Category 4: UI & Widget System (Medium Priority)

### FLTK Integration
- **File**: `dw/fltkui.cc`
  - Proper disabling of item groups
  - Code organization improvements
- **File**: `dw/ui.cc`
  - Percentage heights are ignored again
  - Correction should perhaps be left to the resources

### Dialog & Form Handling
- **File**: `src/dialog.cc`
  - Set focus to the *-prefixed alternative
  - Bind down arrow to a search engine selection list
- **File**: `src/form.cc`
  - Form list handling improvements
  - Current form setting access
  - "enter" event support for text fields

### Menu System
- **File**: `src/menu.cc`
  - Hook popdown event with delete or similar

## Category 5: Performance Optimizations

*Note: Detailed in `PERFORMANCE_ROADMAP.md`*

### High Impact (P0)
1. **Alpha compositing** - `src/webp.c`, `src/png.c`
2. **URL duplication** - `src/url.c`
3. **Line buffers** - Various files

### Medium-High Impact (P1)
1. **Header caching** - `src/cache.c`
2. **no_proxy handling** - `src/IO/http.c`
3. **String pool** - `dlib/dlib.c`

### Medium Impact (P2)
1. **Hash tables for lookups** - `src/IO/http.c`

### Medium Impact (P3)
1. **C++ rendering optimizations** - Various layout files

## Category 6: Internationalization & Text (Low-Medium Priority)

### Hyphenation
- **File**: `dw/hyphenator.cc` (6 TODOs)
  - UTF-8 support needed
  - Multi-language support (currently English/German only)
  - Error handling improvements
  - Encoding considerations
  - Multi-digit number handling

### String Handling
- **File**: `dlib/dlib.c`
  - **TODO**: vsnprintf() is in C99, maybe a simple replacement if necessary.

### Font Configuration
- **File**: `src/prefs.c`
  - **TODO**: find good default for PREFS_FONT_FANTASY (currently "DejaVu Sans")

## Category 7: External Protocol Support (Low Priority)

### FTP Client
- **File**: `dpi/ftp.c`
  - **TODO**: (incomplete)
  - **TODO**: could use dStr ADT!

### XEmbed Support
- **File**: `src/xembed.cc`
  - **TODO**: Implement more XEMBED support

### SVG Rendering
- **File**: `src/nanosvg.h`, `src/nanosvgrast.h`
  - Multiple TODOs in SVG parser and rasterizer
  - Inherit value handling
  - Spread modes implementation
  - Optimization opportunities

## Category 8: Memory & Resource Management

### Cache System
- **File**: `src/cache.c`
  - Resource Type not handled
  - Implement CA_Abort Op in client callback
  - Notify dicache and upper layers

### Image Management
- **File**: `src/bw.c`
  - **TODO**: Make NumImages count different images

### File Operations
- **File**: `src/misc.c`
  - Filesize threshold implementation
  - String handling improvements

## Category 9: API & Architecture

### C API
- **File**: `src/capi.c`
  - Clean up ad-hoc bindings with proper API
  - Cache entry removal when connection is done

### Iterator System
- **File**: `dw/oofawarewidget_iterator.cc`
  - Consider start and end positions
  - OOF widget handling

### Container Classes
- **File**: `lout/container.cc`
  - HashTable value removal
- **File**: `lout/object.cc`
  - Equality operator verification

## Category 10: Navigation & History

- **File**: `src/nav.c`
  - Keep track of clients
  - Function removal or relocation considerations

## Execution Recommendations

### Phase 1: Foundation (Weeks 1-2)
1. Address Category 5 performance optimizations (already documented)
2. Fix critical security issues in Category 1
3. Implement basic test improvements

### Phase 2: Core Rendering (Weeks 3-4)
1. Tackle text layout TODOs in `dw/textblock.cc`
2. Improve table rendering
3. Fix image handling issues

### Phase 3: HTML/CSS Compliance (Weeks 5-6)
1. Complete HTML parser improvements
2. Implement missing CSS properties
3. Add test coverage

### Phase 4: UI Polish (Weeks 7-8)
1. Improve dialog and form handling
2. Enhance FLTK integration
3. Fix menu system issues

### Phase 5: Internationalization & Protocols (Weeks 9-10)
1. Implement UTF-8 and multi-language support
2. Improve external protocol handling
3. Complete SVG rendering improvements

## Testing Strategy

For each category, developers should:
1. Write tests before implementing changes
2. Verify backward compatibility
3. Test performance impact
4. Validate cross-platform behavior

## Contribution Guidelines

When addressing these TODOs:
1. Follow the coding style in `CODING_STYLE.md`
2. Update documentation as needed
3. Add appropriate test cases
4. Consider performance implications
5. Maintain backward compatibility

## Notes

- Many TODOs are in the layout engine (`dw/` directory), indicating complex rendering logic
- The HTML parser has numerous compliance issues to address
- Performance optimizations are well-documented in `PERFORMANCE_ROADMAP.md`
- Internationalization support needs significant work for non-English languages

---

*This document will be updated as TODOs are addressed and new ones are identified.*