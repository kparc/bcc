//! \file memory manager
#include"a.h"
#include"m.h"
//! malloc/free:  mturnnnn list join (k[cifs] k[CIFS])
//! K is mturnnnn: membucket, type, flags, refcount, length
ZK M[31];ZI clzl(I n);V csr();//!< malloc is a classic pow2 buddy allocator w/o coalescing
S ma(I d,J n){ZJ p=BASE;p+=d?0:n;V*r=mmap((V*)(d?0:p-n),n,PROT_READ|PROT_WRITE|PROT_EXEC,d?MAP_PRIVATE:(MAP_ANON|MAP_PRIVATE|MAP_FIXED),d-!d,0);P(r==MAP_FAILED,O("%s\n",strerror(errno)),(S)0)R r;}
S mf(S s,J*n){struct stat b;I d=open(s,0);Qs(0>d,s)R fstat(d,&b),s=(*n=b.st_size)?ma(d,*n):s,close(d),s;}
K m1(J n){K x,r;I i=clzl(n+7),j;P((x=M[i]),M[i]=xx,x)j=i;W(!(x=++j<31?M[j]:8+ma(0,16L<<(j=MX(18,i))))){};xm=i,M[j]=xx,r=x;W(i<j)x+=16L<<xm,M[*(J*)(x-8)=i++]=x,xx=0;R r;}
V1(l0){if((J)xy)l0(xy),l0(xz);xx=M[xm],M[xm]=x;}K3(l1){K r=m1(24);R rt=8,rn=3,rx=x,ry=y,rz=z,r;}K1(l2){R kp("[]");}//!< struct/fixedarray experiment

//      0 1 2 3 4 5 6 7
//!     K c h i j e f s (arr int8 int16 int32 int64 real double sym)
J nt[]={8,1,2,4,8,4,8,KSSZ};ZJ W=-32;
J ws(){R W;}K1(r1){P(Ax,x)R++xr?x:AB("r1");}
V1(r0){if(Ax||!x)R;if(8==xt){l0(x);R;}if(xr){--xr;R;}if(!xt||KS<xt)N1(xn,r0(Xx))W-=16L<<xm,xx=M[xm],M[xm]=x;}
K tn(I t,I n){K x=m1(MX(1,n)*nt[KS<t?0:t]);R W+=16L<<xm,xu=0,xt=t,xn=n,x;}
K xiy(K x,I i,K y){memcpy(x+NX*i,y,NX*yn);if(!yt)N(yn,r1(Yx))R Y0(x);}
K2(j2){I m=xn,n=m+(Ay?1:yn);P(!m&&!xt,X0(y))$(xr||8+NX*n>16L<<xm,x=xiy(tn(xt,n),0,x))xu=0,xn=n;Ay?memcpy(x+NX*m,&y,NX):xiy(x,m,y);R x;}

//! arch|sys
#if (__x86_64__||i386)&&!__TINYC__
ZI clzl(I n){R 60-__builtin_clzl(n);}V csr(){R;asm("movl $0x9fc0,-4(%rsp);ldmxcsr -4(%rsp);");}//V csr(){volatile I mxcsr=0x9fc0;asm("ldmxcsr %0":"=m"(mxcsr));}
#else
ZI clzl(I n){I i=0;W(n)n/=2,++i;R i-4;}V csr(){R;}//<! FIXME tcc ldmxcsr nyi
#endif

//:~
