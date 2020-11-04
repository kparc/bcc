#pragma once
//#include <stddef.h>
//#include <stdint.h>
#include"../c.h"

#define SZ size_t
#define SZT sizeof(size_t)
#define ALGN(x) x=(x+heap_alignment-1)&-heap_alignment;

#ifndef TA_NO_COMPACT
#define INSERT(b) insert_block(b);compact();
#else
#define INSERT(b) insert_block(b);
#endif

V ta_init(S base,S max,SZ heap_blocks,SZ split_thresh,SZ alignment);
V*ta_alloc(SZ num),*ta_calloc(SZ num,SZ size);
C ta_free(V*ptr),ta_check();

#define CNT(f,x) SZ f(){R ta_count(hp->x);}
SZ ta_avail(),ta_used(),ta_fresh();

#ifdef TA_MAIN
#define TA_TEST
#endif

#ifdef TA_TEST
SZ phy();S ma(SZ n);
#endif

//:~
