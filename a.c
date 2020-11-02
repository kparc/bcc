#include"a.h"// read/write mmap/munmap printf/scanf malloc/free
#include<unistd.h>
#include<sys/syscall.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>

//S mmap();I open(),close(),fstat(),munmap();J read(),write();V exit();
ZF ms(){J a,d;asm volatile("rdtsc":"=a"(a),"=d"(d));R((d<<32)+a)*.58e-6;}//<! fixme .58e-6
V w2(S s){write(2,s,strlen((char*)s));}ZS r2(S s){ZC b[256];R w2(s),b[read(0,b,256)-1]=0,b;}

ZS ma(I d,J n){ZJ p=0x70000000L;p+=d?0:n;V*r=mmap((V*)(d?0:p-n),n,PROT_READ|PROT_WRITE|PROT_EXEC,d?MAP_PRIVATE:(MAP_ANON|MAP_PRIVATE|MAP_FIXED),d-!d,0);P(r==MAP_FAILED,O("%s\n",strerror(errno)),(S)0)R r;}
ZS mf(S s,J*n){struct stat b;I d=open(s,0);Qs(0>d,s)R fstat(d,&b),s=(*n=b.st_size)?ma(d,*n):s,close(d),s;}

//! printf/scanf (almost:)
ZC b[24];ZS ng(S s){R*--s='-',s;}
ZS pu(S s,J i){J j;do*--s='0'+i-10*(j=i/10);W(i=j);R s;}
ZF x(I n){F e=1;N(n,e*=10)R e;}//P(NI==f||0>(j|k),nf)
S pi(J i){R 0>i?ng(pi(-i)):pu(b+23,i);}//! current state of the art is ryu
S pf(F f){P(0>f,ng(pf(-f)))P(!f,"0.0")I n=6;W(f<1e6)--n,f*=10;W(f>=1e7)++n,f/=10;S p=n?p=pi(n),*--p='e',p:b+23;n=f+.5;W(99<n&&!(n%10))n/=10;R p=pu(p,n),p[-1]=*p,*p--='.',p;}
J ip(S p,I n){P('-'==*p,-ip(p+1,n-1))J j=0;N(n,j=10*j+p[i]-'0')R j;}ZS hh(S s,C c){N(2,C a=i?c&15:c>>4;s[i]="0W"[9<a]+a)R s;}S px(J j){S s=b+23;unsigned long k=j;do hh(s-=2,k);W(k>>=8);R s;}
F fp(S p,I n){P('-'==*p,-fp(p+1,n-1))I l=scn(p,'e',n),m=scn(p,'.',l),f=l<n?ip(p+l+1,n-l-1):0,j=ip(p,m),k;m+=m<l,k=ip(p+m,MN(9,l-=m));k+=j*x(l),f-=l;R 0>f?k/x(-f):k*x(f);} 

#if (__x86_64__||i386)&&!__TINYC__
ZI clzl(I n){R 60-__builtin_clzl(n);}V csr(){R;asm("movl $0x9fc0,-4(%rsp);ldmxcsr -4(%rsp);");}//V csr(){volatile I mxcsr=0x9fc0;asm("ldmxcsr %0":"=m"(mxcsr));}
#else
ZI clzl(I n){I i=0;W(n)n/=2,++i;R i-4;}V csr(){R;}//<! \fixme tcc ldmxcsr nyi
#endif

// malloc free:  mturnnnn list join (k[cifs] k[CIFS])
//! K is mturnnnn: membucket, type, flags, refcount, length
ZK M[31];//!< malloc is a classic pow2 buddy allocator w/o coalescing
ZK m1(J n){K x,r;I i=clzl(n+7),j;P(x=M[i],M[i]=xx,x)j=i;
 W(!(x=++j<31?M[j]:8+ma(0,16L<<(j=MX(18,i)))));
 xm=i,M[j]=xx,r=x;W(i<j)x+=16L<<xm,M[*(J*)(x-8)=i++]=x,xx=0;R r;}

//      0 1 2 3 4 5 6 7
//!     K c h i j e f s (arr int8 int16 int32 int64 real double sym)
J nt[]={8,1,2,4,8,4,8,4};ZJ W=-32;J ws(){R W;}ZV l0();V1(r0){if(Ax||!x)R;if(8==xt){l0(x);R;}if(xr){--xr;R;}if(!xt||KS<xt)N1(xn,r0(Xx))W-=16L<<xm,xx=M[xm],M[xm]=x;}K1(r1){P(Ax,x)R++xr?x:AB("r1");}

K tn(I t,I n){K x=m1(MX(1,n)*nt[KS<t?0:t]);R W+=16L<<xm,xu=0,xt=t,xn=n,x;}
ZK xiy(K x,I i,K y){memcpy(x+NX*i,y,NX*yn);if(!yt)N(yn,r1(Yx))R Y0(x);}
K2(j2){I m=xn,n=m+(Ay?1:yn);P(!m&&!xt,X0(y))$(xr||8+NX*n>16L<<xm,x=xiy(tn(xt,n),0,x))xu=0,xn=n;Ay?memcpy(x+NX*m,&y,NX):xiy(x,m,y);R x;}

ZK1(l2){R kp("[]");}//!< struct/fixedarray experiment
ZV1(l0){if((J)xy)l0(xy),l0(xz);xx=M[xm],M[xm]=x;}
K3(l1){K r=m1(24);R rt=8,rn=3,rx=x,ry=y,rz=z,r;}

//! repl daz ftz \wtfvl: \w wssize \t[:n] timer[ntimes] \f funs \v vars \l loadfile \-var release
//! \G global namespace \fixme 1char literals are tough on the ego
K G[26];V dis(K,I);K es();ZK K0;K k0(){R r1(K0);}ZK vf(I f){K r=kS(0);N(26,K x=G[i];if(NL-x)if(f^(Ax||xt))r=j2(r,ks(i)))R r;}
K Li(K x,I i){R!xt||KS<xt?Xx:KC==xt?kc(Xc):KI==xt?ki(Xi):ks(Xi);}ZK e1(K(*f)(),K x,K y){K r=kK(xn);N1(rn,Rx=f?f(Li(x,i),y):Li(x,i))R r;}
K sS(I c,K x){I n=c?xn:0;N(xn,K y=Xx;n+=yn)K r=kC(n);if(c)--rn;S s=r;N(xn,K y=Xx;s=memcpy(s,y,yn)+yn;if(c)*s++=c)R X0(r);}

ZK c(K x,K pt){N(xn,if(94u<Xc-32){K r=kC(2*xn);N(xn,hh(r+2*i,Xc))R j2(c2('0'+xu,'x'),r);})
C qt='"';if(pt)qt=2>xn&&'a'==cl(*x)?0:'\'';R!qt?r1(x):cj(qt,jc(r1(x),qt));}
K se(K x,K pt){//! string repr of a K object, pt - parse tree mode (don't use "", skip '' for identifiers)
 P(Ax,
   KS==Ax?c2('`','a'+xi):
   KC==Ax?X0(c(x=c1(xi),pt)):
   kp(
    KI==Ax?pi(xi):
    KF==Ax?pf(xf):
    (S)"+"+!xi)
 )
 P(8==xt,l2(x))//< fixme nyi
 P(1==xn,cj(',',se(Li(x,0),pt)))
 I t=KS<xt?0:xt;
 P(KC==t,c(x,pt))
 P(!xn,c2("!("[!t],")  0   `"[t]))
 x=sS(";      "[t],e1(se,x,pt));
 R!t?cj('(',jc(x,')')):x;}

K1(o){K y=QQ-Ax?se(x,0):j2(kp((K)"err: "),kp((S)(-1UL>>16&(J)x)));Y0(write(2,y,yn)),nl();R x;}K1(pr){if(NL-x)r0(o(x));R x;}
ZS1(ld){J n;Q(s=mf(s,&n))S t=s,u;I a,d=0;W(u=sc(t,10),t<s+n&&d>=0){if(u)*u++=0;a=t[1]?0:(*t=='/')-(*t=='\\');if(!d&&!a&&'/'-*t)Q(pr(es(t)))d+=a,t=u;if(!t)break;}if(n)munmap(s,n);R NL;}
ZS1(tm){S t=sc(s,' ');Qs(!t,s)*t=0;I n=':'-*s++?1:10u>*s-'0'?ip(s,t-s):(J)es(s);K x='\\'-*++t?ps(t):0,r;F a=ms();N(n,Q(r=x?ex(x):ld(t+3))r0(r))if(x)r0(x);R ki(ms()-a);}
ZS1(rg){I i=*s-'a';K x;P(26u<i,NL)P((x=G[i])&&!xr,G[i]=X0(NL))R NL;}//!<release global var
S1(es){K x;P('\\'-*s,!*s?NL:(x=ps(s))&&NL-x?X0(ex(x)):x)if(!*++s||'\\'==*s)exit(0);R!s[1]?'w'==*s?ki(W):sc("vf",*s)?vf('f'==*s):qs(s):'t'==*s?tm(s+1):'-'==*s?rg(s+1):'l'==*s?ld(s+2):qs(s);}
V init(){csr();N(26,G[i]=NL)*(K*)(K0=kK(0))=c0();}K enm(J x){K r=kI(xi);N(rn,Ri=i)R r;}
ZV km(S*a){init();if(*++a)pr(ld(*a));os("kparc/b x64");W(1)pr(es(r2(" ")));}

#ifdef TST
#define main b_main
#endif
I main(I ac,char**av){R km((S*)av),0;}
#undef main

//:~