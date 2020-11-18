#include<string.h>//mcpy

typedef void _;typedef unsigned short H;typedef unsigned int V;typedef unsigned char*S,G;typedef int I;typedef unsigned long long UJ;

#define ZFP(x) static G x[32]
ZFP(ONE)={1};ZFP(BP)={9};//!< base point
extern _ xkeygen(G sec[32],G pub[32],G rnd[32]),xshared(G shr[32],G sec[32],G pub[32]);

#ifndef TST
#define ZG static G
#define ZZ Z_
#else
#define ZG G
#define ZZ _
extern ZG eql(S x,S y);extern ZZ prp(S x),xmul(S r,S q,S e);
#endif

#define W(a...)   while(({a;}))
#define N(n,a...) {V _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...) {V _n=(n),j=-1;W(++j<_n){a;}}
#define _N(n,a...) {V i=(n);W(i--){a;}}
#define P(b,a...) if(b)R({a;});
#define O printf
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
#define FP(x) G x[32];
#define CORK r[31]&=127
#define BIT(x) G bit=(x[i>>3]>>(i&7))&1;
#define FPah FP(a)FP(b)FP(c)FP(d)FP(e)FP(f)FP(g)FP(h);
#define sq(r,x) mul(r,x,x)
#define dsn(d,s,n) memcpy((S)d,(S)s,n)
#define rfc(x) x[31]&=0x7f

//:~
