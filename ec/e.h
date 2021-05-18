#include<string.h>//mcpy
#include<printf.h>//printf

#define dsn memcpy
#define mmv memmove
#define mset memset

#include"sha.h"

typedef void _;typedef unsigned short H;typedef unsigned int V;typedef unsigned char*S,G;typedef int I;typedef unsigned long long UJ;
typedef G fp[32]; typedef struct{fp x;fp y;fp t;fp z;}EP;typedef EP*ep; //!< montgomery / edwards

extern _ xkeygen(fp sec,fp pub,fp rnd),xshared(fp shr,fp sec,fp pub);
extern _ edsign(G sig[64],fp pub,G sec[64],S m,V n);extern G edverify(G sig[64],fp pub,S m,V n);_ edkeygen(G sec[64],fp pub,fp seed);

#define ZEP(x) static const EP x

#ifndef TST
#define ZFP(x) static const fp x
#define ZG     static G
#define ZI     static I
#define ZZ     Z_
#else
#define ZFP(x) fp x
#define ZG     G
#define ZI     I
#define ZZ     _
extern ZG eql(S x,S y);extern ZZ prp(S x),xmul(S r,S q,S e);
#endif

#define W(a...)    while(({a;}))
#define N(n,a...)  {V _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...) {V _n=(n),j=-1;W(++j<_n){a;}}
#define _N(n,a...) {V i=(n);W(i--){a;}}
#define P(b,a...)  if(b)R({a;});

#define R     return
#define SZ    sizeof
#define Z_    static _
#define rG    ((G*)r)
#define yG    ((G*)y)
#define xG    ((G*)x)
#define zG    ((G*)z)
#define Xg    xG[i]
#define Yg    yG[i]
#define Zg    zG[i]
#define Rg    rG[i]
#define Xk    xK[i]
#define X(x)  N(32,x)
#define RD(x) X(c+=x;x=c;c>>=8)
#define RDc   RD(Rg)
#define RDC   c=(c>>7)*19;RDc
#define RDCC  r[31]=c&127;RDC
#define RSX   mul(r,s,x)
#define SRX   mul(s,r,x)
#define SRSX  sq(s,r),RSX
#define HX    ((H)Xg)
#define HY    ((H)Yg)
#define VX    ((V)Xg)
#define VY    ((V)Yg)
#define Vx(i) ((V)x[i])
#define Vy(i) ((V)y[i])

#define SUB(y,yy)  V c=218;N(31,c+=y-VX+0xff00;Rg=c;c>>=8)c+=yy-Vx(31);RDCC
#define BIT(x)     G bit=(x[i>>3]>>(i&7))&1;
#define SEL(f)     sel(r.f,r.f,s.f,bit);
#define rfc(x)     x[31]&=0x7f
#define RFC        rfc(r)
#define sq(r,x)    mul(r,x,x)

#define Px p->x
#define Py p->y
#define Pz p->z
#define Pt p->t
#define P1x p1->x
#define P1y p1->y
#define P1z p1->z
#define P1t p1->t
#define P2x p2->x
#define P2y p2->y
#define P2z p2->z
#define P2t p2->t

//! nolibc
#if 0
unsigned char*dsn(unsigned char*d,unsigned char*s,size_t n)  {W(n--)*d++=*s++;R d;}
unsigned char*mmv(unsigned char*d,unsigned char*s,size_t n)  {P(s<d&&d<s+n,d+=n,s+=n;W(n--)*--d=*--s;d)R dsn(d,s,n);}
unsigned char*mset(unsigned char* s,int c,size_t n)          {N(n,s[n]=c);R s;}
#endif

//:~
