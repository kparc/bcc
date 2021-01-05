#pragma once

#include"c.h"
#include"h.h"

#define NX nt[xt] // chijefs

#define KC 1ULL
#define KH 2ULL
#define KI 3ULL
#define KJ 4ULL
#define KE 5ULL
#define KF 6ULL
#define KS 7ULL

#ifdef SYMS
#define KSSZ 8 //!< symbol contains a ks(1) object with xx pointing to htable bucket B
#else
#define KSSZ 4
#endif

#define NL (K)(X1<<48)
#define X1 11L
#define X2 12L
#define X3 13L
#define QQ 15L

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack
typedef union{V*code;K(*k)();F(*f)();J(*j)();}obj; //!< signatures of compiled funs

extern S cp(S s,CP*cp),us(S h,S n),uc(S s,CP c);UI ul(S s);CP at(S s,UI i);C cw(CP p); //!< utf: cp() scan codepoint, us() strstr, uc() strchr, ul() strlen, at() s[i], cpw() cw byte width

#ifndef SYMS
#define BANNER "kparc/b α x64"
#define ST0(tp) Ss=(S)tp;pst t={  {0},    {0},  0, {1,1},  8,  0};ST st=&t;
extern K GGG[];typedef struct{C L[26];C T[26];I M;C D[2];C N;I A;}pst;typedef pst*ST;
#else
#define BANNER "kparc/b α x64 utf"

// ST   current scope:
// D0   local vars/args, D1 local floats
// L/T  values and types of D
// N    current loop counter (i,j,k,l..)
// M    used register count
// A    target variable (for assignments)
// Pt   current codepoint
// Pn   length of the current cpoint in bytes

#define ST0(tp) Ss=(S)tp;pst t={   {0},    {0},  0, {1,1},  8,   0,   0,   NL};ST st=&t;
extern HT GT;typedef    struct{C L[26];C T[26];I M;C D[2];C N;CP Pt;C Pn;K A;}pst;typedef pst*ST; //<! assignment target (A) must be K to hold KS
extern CP nxt(ST st);extern B tok(ST st);K*GG(K h),nm(K h); //!< syms
K gget(B b),*GLO(K x);C ID(CP x);//C gpos(B x);
#define tk()     tok(st)
#endif//SYMS

I _t(K x,S sT),U(I i);K _p(ST st),XXX(K*k,K y);
#define p()      _p(st)
#define q(x)     _q(x,L)
#define t(x)     _t(x,T)

I clzl(I n);V csr();F ms();//<! s.c
extern J nt[],ip();extern K ex(K),ps(S),r1(K),tn(I,I),k0(),l1(),sS(I,K),enm(J x),o(K);I cl(I c);V exit(I),w2(S),r0(K);S pi(J),pf(F),px(J);J ws();F fp(S,I);K2(j2);
extern K se(K x,K pt),dmp(S,S,J); //!< debug
Z_ I oc(I i){R w2((S)&i),i;}Z_ V nl(){fflush(0),w2((S)"\n");}Z_ S os(S s){R w2(s),nl(),s;}Z_ J oi(J j){R os(pi(j)),j;}Z_ F of(F f){R os(pf(f)),f;}Z_ J ox(J j){R os(px(j)),j;}
Z_ I _scn(S s,I c,I n){N(n,P(c==s[i],i))R n;}//_ K P1(J x){R(K)(X1<<48|x);}_ K P2(J x){R(K)(X2<<48|x);}_ K P3(J x){R(K)(X3<<48|x);}
Z_ S _sc(S s,I c){W(*s-c)P(!*s++,(S)0)R s;}
#define scn(s,c,n) _scn((S)s,c,n)
#define sl(s) strlen((char*)s)
#define sc(s,c) _sc((S)s,c)

Z_ K kK(I n){R tn( 0,n);}
Z_ K kC(I n){R tn(KC,n);}
Z_ K kI(I n){R tn(KI,n);}
Z_ K kJ(I n){R tn(KJ,n);}
Z_ K kS(I n){R tn(KS,n);}
Z_ K pn(S s,I n){R(K)memcpy((V*)kC(n),s,n);}Z_ K kp(S s){R pn(s,sl(s));}
Z_ K kc(J x){R(K)(KC<<48|x);}
Z_ K ki(unsigned x){R(K)(KI<<48|(J)x);}
Z_ K kf(F f){R*(K*)&f;}
Z_ K ks(J x){R(K)(KS<<48|x);}
Z_ K _qs(S s){R(K)(QQ<<48|(J)s);}
#define qs(s) _qs((S)(s))
Z_ K c0(){R kC(0);}
Z_ K c1(C x){K r=kC(1);R*rC=x,r;}
Z_ K c2(C x,C y){K r=kC(2);R*rC=x,rC[1]=y,r;}
Z_ K c3(C x,C y,C z){K r=kC(3);R*rC=x,rC[1]=y,rC[2]=z,r;}
Z_ K jc(K x,C c){R j2(x,kc(c));}

#define A(x) ({J _j=(J)(x);!_j||_j>>52?KF:15&_j>>48;})
#define FN(x) (!Ax&&!xt)
#define I(x) (I)(J)(x) //(-1UL>>16&(J)(x))
#define Q(x)        P(QQ==A(x),x) //#define Q(c,i)      P(c,qi(i))  //error index(nyi,rank,length,type,..)
#define Qs(c,s)     P(c,qs((S)s))  //error string
#define N1(n,a...)  {I i=0,_n=(n);do{a;}while(++i<_n);}

// access x y z r
#define Ax A(x)
#define xi I(x)
#define xj (J)(x)
#define xf *(F*)&x
#define xm xC[-8] //mem
#define xr xC[-7] //ref
#define xu xC[-6]
#define xt xC[-5]
#define xn xI[-1]
#define xx xK[0]
#define xy xK[1]
#define xz xK[2]
#define xxu ptr(xx)[-6]
#define xyu ptr(xy)[-6]
#define xI ((I*)x)
#define xF ((F*)x)
#define xK ((K*)x)
#define Xc ((S)x)[i]
#define Xi xI[i]
#define Xj xJ[i]
#define Xx xK[i]
#define X0(e)  ({typeof(e)_e=(e);r0(x);_e;})
#define Ay A(y)
#define yi I(y)
#define yj (J)(y)
#define yr yC[-7] //ref
#define yu yC[-6]
#define yt yC[-5]
#define yn yI[-1]
#define yx yK[0]
#define yy yK[1]
#define yI ((I*)y)
#define yK ((K*)y)
#define Yc ((S)y)[i]
#define Yi yI[i]
#define Yx yK[i]
#define Y0(e)  ({typeof(e)_e=(e);r0(y);_e;})
#define Az A(z)
#define zi I(z)
#define zr zC[-7] //ref
#define zu zC[-6]
#define zt zC[-5]
#define zn zI[-1]
#define zx zK[0]
#define zy zK[1]
#define zI ((I*)z)
#define zF ((F*)z)
#define zK ((K*)z)
#define Zc ((S)z)[i]
#define Zi zI[i]
#define Zx zK[i]
#define Z0(e)  ({typeof(e)_e=(e);r0(z);_e;})
#define Ar T(r)
#define ri I(r)
#define rr rC[-7]
#define rt rC[-5]
#define rn rI[-1]
#define rI ((I*)r)
#define rK ((K*)r)
#define rx rK[0]
#define ry rK[1]
#define rz rK[2]
#define Rc ((S)r)[i]
#define Ri rI[i]
#define Rx rK[i]
#define R0(e)  ({typeof(e)_e=(e);r0(r);_e;})

#define xJ ((J*)x)
#define zJ ((J*)z)

Z_ K1(k1){K r=kK(1);R rx=x,r;}Z_ K2(k2){K r=kK(2);R rx=x,ry=y,r;}Z_ K3(k3){K r=kK(3);R rx=x,ry=y,rz=z,r;}Z_ K3(j3){R j2(j2(x,y),z);}Z_ K2(jk){R j2(x,k1(y));}Z_ K cj(C c,K y){R j2(c1(c),y);}Z_ K u(I u,K x){R xu=u,x;}

#if 0
//! TODO malloc override
#include"m.h"
#define bmalloc  aw_malloc
#define bcalloc  aw_calloc
#define brealloc aw_realloc
#define bfree    aw_free
#else
/*
#define bmalloc  malloc
#define bcalloc  calloc
#define brealloc realloc
#define bfree    free
*/
#endif


//:~
