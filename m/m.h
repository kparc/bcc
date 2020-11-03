//#include <stddef.h>
//#include <stdint.h>
#include"../c.h"

#define SZ size_t
#define SZT sizeof(size_t)
#define ALGN(x) x=(x+heap_alignment-1)&-heap_alignment;

#ifndef TA_NO_COMPACT
#define INSERT(b) insert_block(b),compact();
#else
#define INSERT(b) insert_block(b);
#endif

V ta_init(S base,S max,SZ heap_blocks,SZ split_thresh,SZ alignment);
S ta_alloc(SZ num),ta_calloc(SZ num,SZ size);
C ta_free(S ptr),ta_check();

#define CNT(f,x) SZ f(){R ta_count(hp->x);}
SZ ta_avail(),ta_used(),ta_fresh();

#ifdef TA_TEST
#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysctl.h>
#include<sys/mman.h>
#include<errno.h>

#define GB(n) (n>>30)

SZ phy(){SZ m=0;
#if defined(__EMSCRIPTEN__)
 m=__builtin_wasm_memory_size(0)*64*1024;
#elif defined(__linux__) || defined(__OpenBSD__)
 m=sysconf(_SC_PHYS_PAGES))*sysconf(_SC_PAGE_SIZE);
#elif defined(__APPLE__)
 SZ ln=sizeof(m);sysctlbyname("hw.memsize",&m,&ln, NULL, 0);
#endif
 R m;}

S ma(SZ n){S r=mmap(0,n,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,0,0);$(r==MAP_FAILED,O("%s (n=%zu)\n",strerror(errno),n),exit(1))R r;}

#endif

//:~
