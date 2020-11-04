#ifdef TA_TEST
//#define DBG(a...) O(a)
#define DBG(a...)

#ifndef TA_CHECK
#define CHK(fn)
#else
#define CHK(fn) if(!ta_check())O("ta_check() fail %s\n",fn),exit(1);
#endif

#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysctl.h>
#include<sys/mman.h>
#include<errno.h>
#include<ctype.h>

#define GB(n) (n>>30)

SZ phy(){SZ m=0;
#if defined(__EMSCRIPTEN__)
 m=__builtin_wasm_memory_size(0)*64*1024;
#elif defined(__linux__) || defined(__OpenBSD__)
#include<unistd.h>
 m=sysconf(_SC_PHYS_PAGES)*sysconf(_SC_PAGE_SIZE);
#elif defined(__APPLE__)
 SZ ln=sizeof(m);sysctlbyname("hw.memsize",&m,&ln, NULL, 0);
#endif
 R m;}

static C ge(char*name,char*result,SZ sz){// cannot call getenv() when still initializing the C runtime.
  char*s=getenv(name);
  if(!s){
    C buf[64+1];// we check the upper case name too.
    SZ len=strlen(name);
    if(len>=sizeof(buf))len=sizeof(buf)-1;
    N(len,buf[i]=toupper(name[i]))buf[len]=0;
    s=getenv((char*)buf);}
  P(s&&strlen(s)<sz,strncpy(result,s,sz),1)
  R 0;} 

V*ma(SZ n){V*r=mmap(0,n,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_NORESERVE|MAP_ANON|MAP_SHARED,0,0);$(r==MAP_FAILED,O("%s (n=%zu)\n",strerror(errno),n),exit(1))R r;}

V ta_test_init(){
  char nb[16];C r=ge("TA_NBLK",(char*)nb,16);J n=0;
  if(r)n=strtol((char*)&nb,0,10);DBG("ge %d %s %lld\n",r,r?nb:"(null)",n);
  V*base;SZ
    phys=phy(),
    heap=phys>>2,
    nblk=n?n:256,
    splt=16,
    algn=sizeof(S);
    base=ma(heap);

 ta_init(base,(S)base+heap,nblk,splt,algn);
 O("ta_test_init blk %zu heap %zug phys %zug\n",nblk,GB(heap),GB(phys));}

#else
#define DBG(a...)
#define CHK(fn)
#endif

#ifdef TA_MAIN

I main(I c,char**v){R ta_test_init(),0;}
#endif
