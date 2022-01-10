#ifndef COSMO
#include<unistd.h>
#include<sys/mman.h>
#endif

#include"a.h"// read/write mmap/munmap printf/scanf malloc/free
#include"m.h"
#include"h.h"

//S mmap();I open(),close(),fstat(),munmap();J read(),write();V exit();
V w2(S s){write(2,s,sl((char*)s));}ZS r2(S s){ZC b[256];I i;w2(s);i=read(0,b,256);b[i-1]=0;R 13==b[i-2]?b[i-2]=0,b:b;}
K dmp(S s,S x,J n){I d=open((V*)s,O_RDWR|O_CREAT|O_TRUNC,S_IRWXU);Qs(0>d,(S)s)write(d,x,n);R close(d),0;}

//! printf/scanf (almost:)
ZC b[24];ZS ng(S s){R*--s='-',s;}
ZS pu(S s,J i){J j;do*--s='0'+i-10*(j=i/10);W(i=j);R s;}
ZF x(I n){F e=1;N(n,e*=10)R e;} //P(NI==f||0>(j|k),nf)
S pi(J i){R 0>i?ng(pi(-i)):pu(b+23,i);} //!< current state of the art is ryu
S pf(F f){P(0>f,ng(pf(-f)))P(!f,(S)"0.0")I n=6;W(f<1e6)--n,f*=10;W(f>=1e7)++n,f/=10;S p=n?p=pi(n),*--p='e',p:b+23;n=f+.5;W(99<n&&!(n%10))n/=10;R p=pu(p,n),p[-1]=*p,*p--='.',p;}
J ip(S p,I n){P('-'==*p,-ip(p+1,n-1))J j=0;N(n,j=10*j+p[i]-'0')R j;}ZS hh(S s,C c){N(2,C a=i?c&15:c>>4;s[i]="0W"[9<a]+a)R s;}S px(J j){S s=b+23;unsigned long k=j;do hh(s-=2,k);W(k>>=8);R s;}
F fp(S p,I n){P('-'==*p,-fp(p+1,n-1))I l=scn(p,'e',n),m=scn(p,'.',l),f=l<n?ip(p+l+1,n-l-1):0,j=ip(p,m),k;m+=m<l,k=ip(p+m,MN(9,l-=m));k+=j*x(l),f-=l;R 0>f?k/x(-f):k*x(f);} 

//! repl daz ftz \wtfvl: \w wssize \t[:n] timer[ntimes] \f funs \v vars \l loadfile \-var release

V dis(K,I);K es();ZK K0;K k0(){R r1(K0);}
#ifndef SYMS
K GGG[26]; //!< global namespace
K vf(I f){K r=kS(0);N(26,K x=GGG[i];if(NL-x)if(f^!FN(x))r=j2(r,ks(i)))R r;}
#else
HT GT; //!< global namespace
K vf(I f){AB("nyi");}//K vf(I f){K x,r=kS(0);N(26,x=GGG[i];if(NL-x){K y=nm(x);O("vf y %.*s xt %d \n",yn,(S)y,yt);if(f^!FN(*GG(x)))r=j2(r,ks(i));})R r;}
#endif

K Li(K x,I i){R!xt||KS<xt?Xx:KC==xt?kc(Xc):KI==xt?ki(Xi):ks(Xi);} //!< list item x[i]
ZK e1(K(*f)(),K x,K y){K r=kK(xn);N1(rn,Rx=f?f(Li(x,i),y):Li(x,i))R r;} //!< each: r[i]=f(x[i],y)
K sS(I c,K x){I n=c?xn:0;N(xn,K y=Xx;n+=yn)K r=kC(n);if(c)--rn;S s=rC;N(xn,K y=Xx;s=((S)memcpy(s,(V*)y,yn))+yn;if(c)*s++=c)R X0(r);}
ZK c(K x,K pt){N(xn,if(94u<Xc-32){K r=kC(2*xn);N(xn,hh(rC+2*i,Xc))R j2(c2('0'+xu,'x'),r);})
 P(pt&&1<xn,r1(x))C qt='"';if(pt)qt='a'==cl(*xC)?0:'\'';R!qt?r1(x):cj(qt,jc(r1(x),qt));}

K se(K x,K pt){//! string repr of x, pt parse tree printer flag (skips excess quotes)
 P(Ax,
#ifndef SYMS
   KS==Ax?c2('`','a'+xi):
#else
   KS==Ax?pt?(K)xi:se((K)xi,pt):
#endif
   KC==Ax?X0(c(x=c1(xi),pt)):
   kp(KI==Ax?pi(xi):KF==Ax?pf(xf):(S)"+"+!xi))
#ifdef SYMS
 P(KS==xt,O("se xc %s %llx %d\n",xC,x,xn),c(x,pt))
#endif
 P(8==xt,l2(x))//!< fixme nyi
 P(1==xn,cj(',',se(Li(x,0),pt)))
 I t=KS<xt?0:xt;
 P(KC==t,c(x,pt))
 P(!xn,c2("!("[!t],")  0   `"[t]))
 x=sS(";      "[t],e1(se,x,pt));
 R!t?cj('(',jc(x,')')):x;}

K1(o){K y=QQ-Ax?se(x,0):j2(kp((S)"err: "),kp((S)(-1UL>>16&(J)x)));Y0(write(2,(V*)y,yn)),nl();R x;}K1(pr){if(NL-x)r0(o(x));R x;}
ZS1(ld){J n;s=(S)mf(s,&n);Q((K)s)S t=s,u;I a,d=0;W(u=sc(t,10),t<s+n&&d>=0){if(u)*u++=0;a=t[1]?0:(*t=='/')-(*t=='\\');if(!d&&!a&&'/'-*t)Q(pr(es(t)))d+=a,t=u;if(!t)break;}if(n)munmap(s,n);R NL;}
ZS1(tm){S t=sc(s,' ');Qs(!t,s)*t=0;I n=':'-*s++?1:10u>*s-'0'?ip(s,t-s):(J)es(s);K x='\\'-*++t?ps(t):0,r;F a=ms();N(n,Q(r=x?ex(x):ld(t+3))r0(r))if(x)r0(x);R ki(ms()-a);}
ZS1(rg);S1(es){K x;P('\\'-*s,!*s?NL:(x=ps(s))&&NL-x&&QQ-Ax?X0(ex(x)):x)if(!*++s||'\\'==*s)exit(0);R!s[1]?'w'==*s?ki(ws()):sc("vf",*s)?vf('f'==*s):qs(s):'t'==*s?tm(s+1):'-'==*s?rg(s+1):'l'==*s?ld(s+2):qs(s);}

#ifndef SYMS
ZS1(rg){UI i=*s-'a';Qs(26<i,s)K x=GGG[i];Qs((NL==x),s)Qs(Ax,"nyi")P(!xr,GGG[i]=X0(NL))R qs("0<xr");}//!<release global function or vector if refcount is 0
V init(){csr();*(K*)(K0=kK(0))=c0();N(26,GGG[i]=NL)}
#else
ZS1(rg){AB("nyi");} //ZS1(rg){ST0(s);B b=tk();K*y,z,x=gget(b);Qs(NL==x,b->k)Qs((y=GG(x))&&A(z=*y),"nyi")P(!zr,gset(b,NL))R qs("0<xr");}
V init(){csr();*(K*)(K0=kK(0))=c0();GT=hnew((S)"G",2,3);}
#endif

ZV km(S*a){init();if(*++a)pr(ld(*a));os((S)BANNER);W(1)pr(es(r2((S)" ")));}K enm(J x){K r=kI(xi);N(rn,Ri=i)R r;}

#ifdef TST
#define main b_main
#endif
I main(I ac,char**av){R km((S*)av),0;}
#undef main

//:~