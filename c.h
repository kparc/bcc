#pragma once
#include<string.h>
#include<stdio.h>

#ifndef QUIET
#define O printf
#else
#define O
#endif

#define ptr(x) (*(S*)&x)
#define xC ptr(x)
#define yC ptr(y)
#define zC ptr(z)
#define fC ptr(f)
#define rC ptr(r)

typedef unsigned long long K,UJ;typedef unsigned char C,*S;typedef int I,CP;typedef long long J;typedef double F;typedef void V;typedef unsigned int UI;

enum UCL{UQ,Ul,Ug,Uc,Um,Ua};//!< QQ  Āɏ Ая  Αω  ∀⋿  ⌀⍺  (err, lat, cyr, gre, mth, apl)
#define UR(cp,s,l) (l>cp-s) //!< unicode range: codepoint, range start, range length+1
#define UC(x) (9082<x?0:UR(x,256,336)?Ul:UR(x,913,57)?Ug:UR(x,1040,64)?Uc:UR(x,8704,256)?Um:UR(x,8960,123)?Ua:UQ)
#define R return

#define P(b,a...) if(b)R({a;});
#define W(b...)     while((b))                //while
#define N(n,a...)   {I i=0,_n=(n);W(i<_n){a;++i;}}
#define $(b,a...)   if(b){a;}else             //cond
#define C(i,a...)   case i:{a;}break;         //case
#define S(i,c,a...) switch(i){c default:a;} //switch

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

#ifdef SIGHANDLER
#include<signal.h>
#define AB(s)       (w2((S)"AB: "),w2((S)s),raise(SIGABRT),(K)0L) //abort string
#else
#define AB(s)       (w2((S)"AB: "),w2((S)s),nl(),exit(1),(K)0L)           //abort string
#endif

#define ZV1(f) ZV f(K x)
#define S1(f)   K f(S s)
#define ZS1(f) ZK f(S s)
#define ZK1(f) ZK f(K x)
#define ZK2(f) ZK f(K x,K y)
#define ZK3(f) ZK f(K x,K y,K z)
#define V1(f)   V f(K x)
#define I1(f)   I f(K x)
#define K1(f)   K f(K x)
#define K2(f)   K f(K x,K y)
#define K3(f)   K f(K x,K y,K z)

//#ifndef __APPLE__
#if 0
#define BASE 0x700000
#else
#define BASE 0x70000000L
#endif

#if (__x86_64__||i386)&&!__TINYC__
Z_ I clzl(I n){R 60-__builtin_clzl(n);}Z_ V csr(){R;asm("movl $0x9fc0,-4(%rsp);ldmxcsr -4(%rsp);");}//V csr(){volatile I mxcsr=0x9fc0;asm("ldmxcsr %0":"=m"(mxcsr));}
#else
Z_ I clzl(I n){I i=0;W(n)n/=2,++i;R i-4;}Z_ V csr(){R;}  //<! FIXME tcc ldmxcsr nyi
#endif

Z_ F ms(){J a,d;asm volatile("rdtsc":"=a"(a),"=d"(d));R((d<<32)+a)*.58e-6;}//<! fixme .58e-6

//:~
