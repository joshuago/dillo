# Dillo Browser Performance Roadmap

This document outlines identified performance improvement opportunities for the Dillo web browser.

## Completed Optimizations

### 1. OOF (Out-Of-Flow) Reference Tracking Optimization
**Status**: Completed

**Files Modified**:
- `dw/textblock.hh`
- `dw/textblock.cc`

**Issue**: The `drawLevel` and `getWidgetAtPointLevel` functions iterated through ALL words to find OOF (float/positioned) widgets, resulting in O(n*m) complexity where n = total words, m = number of OOF managers.

**Solution**: Added a separate `oofWords` vector to track indices of OOF widget references. Now only iterates through OOF words: O(oof*m) where oof << n.

**Impact**: Significant speedup for pages with many words but few floats/positioned elements.


### 2. Image Processing - Alpha Compositing
**Status**: Completed

**Files Modified**:
- `src/png.c`
- `src/webp.c`

**Issue**: Manual per-pixel RGBA→RGB conversion in tight loops was slow. A previous optimization attempt using `memcpy` corrupted colors by mixing alpha channels into RGB data.

**Solution**: Implemented Run-Length Encoding (RLE) loops to process contiguous opaque (`alpha == 255`) and transparent (`alpha == 0`) pixels efficiently, replacing the buggy `memcpy` logic.

**Impact**: Significant reduction in branching overhead and improved image decoding throughput while ensuring correct color rendering.

### 3. URL Handling - String Allocation
**Status**: Completed

**Files Modified**:
- `src/url.c`

**Issue**: `a_Url_dup()` reconstructed the entire URL string and performed a full re-parsing operation for every duplication, wasting CPU cycles and memory allocations.

**Solution**: Introduced reference counting for the internal URL string buffer (`url->buffer`). Duplication is now an `O(1)` operation that safely increments a refcount and copies internal component pointers.

**Impact**: Substantially faster URL duplication and lower memory overhead during page loads, cache lookups, and history navigation.

### 4. Line Buffer Reuse in Image Decoding
**Status**: Completed

**Files Modified**:
- `src/jpeg.c`
- `src/webp.c`

**Issue**: Allocating per-row buffers repeatedly during image decoding.

**Solution**: Allocated line buffers once per image and reused them across rows.

**Impact**: Reduced memory fragmentation and allocation overhead.

---

## Phase 1: Quick Wins (High Impact, Low Risk)

*All viable Phase 1 optimizations have been completed.*

### 1.1 HTTP Server Lookup (Rejected)
**Priority**: Low (Downgraded) | **Est. Impact**: Negligible
**Status**: WontFix

**File**: `src/IO/http.c:1072-1078`

**Issue**: O(n) linear search through server list for every connection.

**Resolution**: The `servers` list only tracks actively connected/queued servers, meaning its size is very small (typically < 20). An O(n) linear search over such a small list requires fewer CPU cycles than computing string hashes and resolving collisions. Furthermore, `dlib` lacks a native Hash Table, making this an unnecessary addition of technical debt for no real-world gain.

---

## Phase 2: Memory & Caching Optimizations

### 2.1 Cache Header Parsing
**Priority**: Medium | **Est. Impact**: Medium

**File**: `src/cache.c:711-734`

**Issue**: Linear search through headers on every HTTP request.

**Fix**: Build indexed header cache for faster lookups.

### 2.2 no_proxy Caching
**Priority**: Medium | **Est. Impact**: Medium

**File**: `src/IO/http.c:680`

**Issue**: `dStrdup(prefs.no_proxy)` called on every request.

**Fix**: Cache parsed no_proxy result.

### 2.3 String Duplicate Pool
**Priority**: Medium | **Est. Impact**: Medium

**File**: `dlib/dlib.c:76-90`

**Issue**: Triple operation (strlen + malloc + memcpy) for every string duplication.

**Fix**: Use `strdup()` or implement string pool allocator.

### 2.4 Dicache Color Optimization
**Priority**: Medium | **Est. Impact**: Low-Medium

**File**: `src/dicache.c:306`

**Issue**: Allocates for max colors regardless of actual count used.

**Fix**: Allocate based on actual color count.

---

## Phase 3: Data Structure Improvements

### 3.1 Hash Table for CachedURLs
**Priority**: Medium | **Est. Impact**: Medium

**File**: `src/cache.c`

**Issue**: Sorted list - O(log n) lookups, O(n) insertions.

**Fix**: Use hash table for O(1) operations.

### 3.2 DNS Cache Optimization
**Priority**: Medium | **Est. Impact**: Medium

**File**: `src/dns.c`

**Issue**: Linear search through DNS cache entries.

**Fix**: Implement hash-based caching.

### 3.3 Server Connection Pool
**Priority**: Medium | **Est. Impact**: Medium

**File**: `src/IO/http.c`

**Issue**: O(n) server lookup for connection reuse.

**Fix**: Hash table implementation.

---

## Phase 4: Rendering & Layout (C++ dw/ Engine)

### 4.1 Textblock Line Breaking
**Priority**: Low | **Est. Impact**: Medium

**Files**: `dw/textblock.cc`, `dw/textblock_linebreaking.cc`

**Note**: OOF optimization completed. Other TODOs in linebreaking algorithm may yield further improvements.

### 4.2 Image Scaling Optimization
**Priority**: Low | **Est. Impact**: Low-Medium

**File**: `dw/fltkimgbuf.cc:311`

**Issue**: TODO noted in code about optimizing scaleRowSimple.

**Fix**: Review and implement suggested optimizations.

---

## Summary by Priority

| Priority | Items | Est. Impact |
|----------|-------|-------------|
| **P0 - Quick** | Alpha compositing, URL dup, line buffers | High |
| **P1 - Memory** | Header caching, no_proxy, string pool | Medium-High |
| **P2 - Core** | Hash tables for lookups | Medium |
| **P3 - Layout** | C++ rendering optimizations | Medium |

---

## Key Files to Modify

1. `src/webp.c` - Alpha compositing fix
2. `src/png.c` - Alpha compositing fix  
3. `src/url.c` - URL duplication optimization
4. `src/gif.c` - Inner loop optimization
5. `src/jpeg.c` - Buffer reuse
6. `src/cache.c` - Header indexing, data structures
7. `src/IO/http.c` - Hash table, caching
8. `dlib/dlib.c` - String allocation improvement
9. `src/dicache.c` - Memory optimization
10. `src/dns.c` - DNS cache optimization

---

## Notes

- Modern library alternatives (e.g., libwebp for image processing) were considered but not chosen per user preference to optimize existing code.
- All optimizations should maintain backward compatibility and pass existing tests.
- Performance testing should be conducted before/after each change.
