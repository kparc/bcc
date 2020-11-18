#include<string.h>//mcpy

typedef void _;typedef unsigned short H;typedef unsigned int V;typedef unsigned char*S,G;typedef int I;typedef unsigned long long UJ;typedef G fp[32];
#define FP(x) fp x;

extern _ xkeygen(fp sec,fp pub,fp rnd),xshared(fp shr,fp sec,fp pub);

#ifndef TST
#define ZFP(x) static fp x
#define ZG static G
#define ZZ Z_
#else
#define ZFP(x) fp x
#define ZG G
#define ZZ _
extern ZG eql(S x,S y);extern ZZ prp(S x),xmul(S r,S q,S e);
#endif

#define W(a...)   while(({a;}))
#define N(n,a...) {V _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...) {V _n=(n),j=-1;W(++j<_n){a;}}
#define _N(n,a...) {V i=(n);W(i--){a;}}
#define P(b,a...) if(b)R({a;});
#define R return
#define SZ sizeof
#define Z_ static void
#define rG ((G*)r)
#define yG ((G*)y)
#define xG ((G*)x)
#define Xg xG[i]
#define Yg yG[i]
#define Rg rG[i]
#define Xk xK[i]
#define X(x) N(32,x)
#define RD(x) X(c+=x;x=c;c>>=8)
#define RDc RD(Rg)
#define RDC c=(c>>7)*19;RDc
#define RDCC r[31]=c&127;RDC
#define RSX mul(r,s,x)
#define SRX mul(s,r,x)
#define SRR sq(s,r)
#define RSS sq(r,s)
#define SRSX SRR,RSX
#define HX ((H)Xg)
#define HY ((H)Yg)
#define VX ((V)Xg)
#define VY ((V)Yg)
#define Vx(i) ((V)x[i])
#define Vy(i) ((V)y[i])

#define SUB(y,yy)V c=218;N(31,c+=y-VX+0xff00;Rg=c;c>>=8)c+=yy-Vx(31);RDCC
#define BIT(x) G bit=(x[i>>3]>>(i&7))&1;
#define dsn(d,s,n) memcpy((S)d,(S)s,n)
#define rfc(x) x[31]&=0x7f
#define sq(r,x) mul(r,x,x)
#define RFC rfc(r)

//:~
