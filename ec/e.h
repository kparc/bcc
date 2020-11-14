#include<string.h>//mcpy
#include<stdio.h>//printf
#define W(a...)   while(({a;}))
#define N(n,a...) {V _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...) {V _n=(n),j=-1;W(++j<_n){a;}}
#define _N(n,a...) {V i=(n);W(i--){a;}}
#define P(b,a...) if(b)R({a;});
#define O printf
#define R return
#define Z_ static void
#define ZG static G
#define SZ sizeof
#define P1x p1->x
#define P1y p1->y
#define P1z p1->z
#define P1t p1->t
#define P2x p2->x
#define P2y p2->y
#define P2z p2->z
#define P2t p2->t
#define Px p->x
#define Py p->y
#define Pz p->z
#define Pt p->t
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
#define SRR mul(s,r,r)
#define RSS mul(r,s,s)
#define SRSX SRR,RSX
#define HX ((H)Xg)
#define HY ((H)Yg)
#define VX ((V)Xg)
#define VY ((V)Yg)
#define Vx(i) ((V)x[i])
#define Vy(i) ((V)y[i])
#define FP(x) G x[32];
#define ZFP(x) static G x[32]
#define CORK r[31]&=127
#define BIT(x) const G bit=(x[i>>3]>>(i&7))&1;
#define SEL(f) sel(r.f,r.f,s.f,bit);
#define FPah FP(a)FP(b)FP(c)FP(d)FP(e)FP(f)FP(g)FP(h);
#define XYTZ3 mul(Px,e,f),mul(Py,g,h),mul(Pt,e,h),mul(Pz,f,g);

//:~
