#pragma once
#include<string.h>
#include<stdio.h>

#define ptr(x) (*(S*)&x)
#define xC ptr(x)
#define yC ptr(y)
#define zC ptr(z)
#define fC ptr(f)
#define rC ptr(r)

typedef unsigned long long K;
typedef unsigned char C,*S;typedef int I;typedef long long J;typedef double F;typedef void V;typedef unsigned int UI;
//V*memcpy();strlen(const char*);//#define P(b,a...)   if(b)return(a);

#define R return

#define P(b,a...) if(b)R({a;});
#define W(b...)     while((b))                //while
#define N(n,a...)   {I i=0,_n=(n);W(i<_n){a;++i;}}
#define $(b,a...)   if(b){a;}else             //cond
#define C(i,a...)   case i:{a;}break  ;       //case
#define S(i,c,a...) switch(i){c default:a;} //switch
#define O printf

#define MN(a,b)    ({typeof(a)_a=(a);typeof(a)_b=(b);_a<_b?_a:_b;})
#define MX(a,b)    ({typeof(a)_a=(a);typeof(a)_b=(b);_a>_b?_a:_b;})

#define ZI static I
#define ZC static C
#define ZS static S
#define ZJ static J
#define ZF static F
#define ZK static K
#define ZV static V

#define Z_ static inline
#define AB(s)       (os((S)s),exit(1),(K)0L) //abort string

//#ifndef __APPLE__
#if 0
#define BASE 0x700000
#else
#define BASE 0x70000000L
#endif

//:~
