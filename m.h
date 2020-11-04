//! \file m.h memory management exports
#include<unistd.h>
#include<sys/syscall.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
K m1(J n);V1(r0);V1(l0);K3(l1);K1(l2);K tn(I t,I n);K xiy(K x,I i,K y);K2(j2);J ws();K mf(S s,J*n);V csr();

#ifdef USE_AW_MALLOC
V aw_malloc_init(),*aw_malloc(size_t n),*aw_calloc(size_t n,size_t sz),*aw_realloc(V*p,size_t n),aw_free(V*p);//! posix wrappers for benchmarking
#endif

//:~
