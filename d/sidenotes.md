## notable changes

compared to the original, available in the initial commit for reference, so far:

1. the original is using a somewhat opinionated superset of ISO C. specifically, it makes prominent use of nested functions, a gcc-specific extension, essentially unportable to any compliant compiler of C language. the modified codebase is free of nested functions and other artefacts, and can be bulit with `gcc9`, `clang12` and `tcc`, albeit with some cosmetic non-pedantic warnings on macos and recent linuces.

2. much of the code is being gradually reformatted to make inline comments possible - this makes source files taller, but makes them more accessible.

3. the inline comments are a mixture of the narrative from the google doc and our own. in former case, the wording is often shortened and makes use of established naming conventions.

4. implementation uses a one-size-fits-all fundamental datatype called `K`, which is basically a `struct` used for *lists* (but not atoms). `K` is an opaque quasi-struct based on relative offsets, members are familiar:

5. undertested / untested / experimental code is fenced by conditional feature flags, e.g. `#ifdef SYMS`.

```
K is mturnnnn:

m memory bucket id
t list data type
u type-specific attributes
r reference count
nnnn list length
```

this signature, referred to as *preamble*, is `1+1+1+1+4` bytes long, and is followed by the actual payload, i.e. a sequence of list elements, if any.

4. an important change compared to the original is that `K`, which is traditionally disguised as `unsigned char*` pointer, is redefined as `unsigned long long`, which doesn't depend on the pointer size of target architecture. For the most part, this change does not impact the code at all.

5. the parser and object code emitter are split into two separate files, `p.c` and `b.c` respectively, to save on scrolling, to better separate concerns and narrow down static globals.

6. since `K` is not a true struct, its members are addressed using so called *accessors*, defined in `a.h` along with more accessors, convenience macros and other sugar designed to keep the code compact:

```
#define xm xC[-8] // membucket
#define xr xC[-7] // refcount
#define xu xC[-6] // attrs
#define xt xC[-5] // type
#define xn xI[-1] // length
#define xx xK[0]  // shortcut to 1st element of a generic list
#define xy xK[1]  // 2nd
#define xz xK[2]  // 3rd
```

`a.h` defines a roughly identical set of accessors for common local variable/argument names - it is very rare to see any other local identifiers other than:

```
x,y,z - typically function arguments
r - usually return value
f - either a function pointer or sometimes a temp variable
```

all of the above are usually of type `K`. we would typically use any of these identifiers that wasn't used earlier in the local scope if we need a temp variable and cannot reuse an identifier declared earlier.

the rationale is that for canonical identifiers there are pre-defined accessors, which keep the code compact.

the actual semantics of `xyzrf` are documented inline where they are not obvious, typically at the site of their declaration.

## malloc

currently, `bcc` doesn't rely on a foreign `malloc`. instead it gradually `mmap`'s  anonymous chunks formatted into buckets of size sufficient to accommodate new lists, with bucket size rounded up to the next power of two relative to the list size. For lists that do not fit in any free memory bucket allocated earlier, an additional `mmap` chunk is requested, of minimal size of 4mb + 8 bytes for the preamble (it would be a viable design to pseudo-allocate all memory addressable by the process in advance, which is very cheap in case of anonymous `mmap`, but is more brittle depending on the mood of the host OS).

for example, a typed list of integers with 80 elements would be of size `80 elements * 4 bytes size of int32 + 8 bytes preamble size`, a total of `328 bytes`, which is not a power of two, and requires a bucket of size that is the closest power of two rounded up, which is a 512-byte bucket.

the smallest possible block size is 64 bytes. the difference between the actual size of the list and the size of its container is initially wasted.  In the above example, the overhead is `184 bytes`, which can potentially be used in case of a list join operation, when the list `y`, that is being appended to `x`, fits in the unused space of a block occupied by `x`. Join and append operations in relatively small increments are therefore assumed to be a sufficiently common operation.

in short, `m.c` defines a static array `M` of 31 pointers to the heads of 31 linked lists. Every element of a list is called a bucket. the id of a bucket is a base two logarithm of its size with a small offset, i.e. sizes of buckets in successive lists start from 64 bytes, 128, 256, ... up to M[31]. buckets above 31 are OOM, a condition that is currently not handled (watchdog of the OS is likely to kill the process earlier)

memory is managed by reference counting using functions `r1/r0`. buckets occupied by lists with no more references are returned to the heap for re-use, no block coalescing, zeroing or `munmap` is performed. *the release of resources is responsibility of a callee*, with a notable exception *when the callee reuses one of the incoming lists as its pass-through return value, possibly mutating it in-place*.

typical idioms seen at the end of a function are `X0(e)/Y0(e)/...` which attempt to release no longer needed `x,y,..` and return some `e`.

for more details, refer to `m.c` which should be adequately documented by now.

## style

further on general coding style and organization:

0. the indent is strictly one `0x20`.

1. Functions are written in a way that can be described as "fail fast". The function body usually starts with declarations of local vars, immediately followed by a set of `P(cond,retval)` macros (a good mnemonic for `P` is `panic`, although the proper expansion is `predicate`). Panics typically test the arguments for sanity, and bail early if something doesn't look right, which flattens the control flow of the main bulk of the function. Since most functions return a `K`, `retval` is presumed to be a `K`. That said, `P()` macro is not limited to early sanity tests and is ubiqutous.

2. It is very common that instead of declaring and assigning an explicit `r` for return value, the tail of a function body would be in form `R expr,expr,expr,...,retval;` where exprs and retval can be fairly complex C expressions, possibly with inline assignments, function calls and other side effects, evaluated left to right as per C spec, where only the final value has anything to do with `R`. i.e. is actually returned.

3. we generally avoid inequality `x!=y`, because it is two chars. instead, we test with `x-y`, which holds true when operands are not the same. this takes time to get used to, especially when used inline, or for example `a-'a'`

4. inequality tests against constants are always backwards, ie `42<x` instead of `x>42`, by convention. pre-increment/decrement `++x/--x` is preferred to their post- counterparts.

5. Loops are strictly implicit and use two macros `W while` and `N for` with some exceptions that are rare enough not to warrant an extra macro, e.g. when the `for` loop goes backwards.

6. `switch/case` and `if/else if/else` are not uncommon, but generally avoided. What is used instead is informally known as `ternary cascades` of the general form `cond0?then0:cond1?then1:...` ad infinitum, very often with side effects in conds and thens, which can be a bit treacherous sometimes.

7. Since explicit parens are avoided where possible to save space, the precedence is sometimes tricky to read, especially in case of ternaries.

8. hard-coded magic numbers are not uncommon, and make assumptions about underlying ISA, e.g. pointer width. These are the priority patients to be turned into proper defines and documented.

9. no part of the code is thread-safe, there is a fair amount of *global state* going on, which is gradually being narrowed down to static globals where possible, and moved closer to functions that use them. Of special care are cases when globals are using names of staple locals (`xyzrf`) which can impair comprehension and result in bugs.


`/:~`
