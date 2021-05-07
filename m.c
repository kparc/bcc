//! \file memory manager
#include"a.h"
#include"m.h"
//! malloc/free:  mturnnnn list join (k[cifs] k[CIFS])
//! K is mturnnnn: membucket, type, flags, refcount, length
ZI clzl(I n);ZK M[31];ZJ W=W0;//!< M memory buckets, W wssize (W0 initial offset for GT header and seed alloc c0() \see init()
S ma(I d,size_t n){ZJ p=BASE;p+=d?0:n;V*r=mmap((V*)(d?0:p-n),n,PROT_READ|PROT_WRITE|PROT_EXEC,d?MAP_PRIVATE:(MAP_ANON|MAP_PRIVATE|MAP_FIXED),d-!d,0);P(r==MAP_FAILED,O("%s\n",strerror(errno)),(S)0)R r;}
K mf(S s,J*n){struct stat b;I d=open((V*)s,0);Qs(0>d,(S)s)R(K)(fstat(d,&b),s=(*n=b.st_size)?ma(d,*n):s,close(d),s);}

K m1(J n){K x,r;             //!< allocate a memory block
    I i=clzl(n+7),j=i;       //!< i is the bucket id, log2((I)n)
    P((x=M[i]),M[i]=xx,x);   //!< if there is a free block on top of the list M[i], pop and return
    W(!(x=++j<31             //!< otherwise, scan for a free block of a larger size
      ?M[j]:                 //!< if one exists, use it, otherwise..
      8+(K)ma(0,16L<<(j=MX(18,i))))); //!< ..mmap additional ram, at least 4mb + 8 bytes for mturnnnn
    xm=i,M[j]=xx,r=x;        //!< assign bucket id to the new block and push it on top of the list M[j]
    //! assign  fill the smaller empty buckets as follows:
    W(i<j)                   //!< j-i are the empty memory slots
     x+=16L<<xm,             //!< the next available memory region x..
     M[*(J*)(x-8)=i++]=x,    //!< ..is assigned to a bucket in a corresponding slot with 8-byte preamble.
     xx=0;R r;}

V1(l0){if((J)xy)l0(xy),l0(xz);xx=M[xm],M[xm]=x;}K3(l1){K r=m1(24);R rt=8,rn=3,rx=x,ry=y,rz=z,r;}K1(l2){R kp((S)"[]");}//!< struct/fixedarray experiment

//      0 1 2 3 4 5 6 7
//!     K c h i j e f s ()
J nt[]={8,1,2,4,8,4,8,KSSZ};//!< list int8 int16 int32 int64 real double sym
J ws(){R W;}K1(r1){P(Ax,x)R++xr?x:(O("r1\n"),exit(1),(K)0L);/*AB("r1");*/}
V1(r0){//O("r0 %llx Ax %d xn %d\n",x,Ax,!Ax?xn:0);
 if(Ax||!x||KS==xt)R;if(8==xt){l0(x);R;}if(xr){--xr;R;}if(!xt||KS<xt)N1(xn,r0(Xx))W-=16L<<xm,xx=M[xm],M[xm]=x;}
K tn(I t,I n){K x=m1(MX(1,n)*nt[KS<t?0:t]);R W+=16L<<xm,xu=0,xt=t,xn=n,x;}

//! append items of y after the i-th element of x
K xiy(K x,I i,K y){
 memcpy(xC+NX*i,(V*)y,NX*yn);   //!< NX is the (N)ative byte width of a single item in the list x
 if(!yt)N(yn,r1(Yx))            //!< if y is a mixed list, increase refcounts of items in y
 R Y0(x);}                      //!< recursively decrease refcounts of y and return x.

//! join two lists x and y, or append an atom y to list x
K2(j2){I m=xn,n=m+(Ay?1:yn);    //!< m is the old size of x, n is the new one (inc n by 1 if y is an atom)
    P(!m&&!xt,X0(y))            //!< if x is empty, decrease refcount of x and return y
    if(xr||8+NX*n>16L<<xm)      //!< if x has references, or there is not enough space left in the x's membucket...
      x=xiy(tn(xt,n),0,x);      //!< ..copy x to a new array of size n
    else xu=0,xn=n;             //!< otherwise, set the size of x to the new size, then:
    Ay?(K)memcpy(xC+NX*m,&y,NX) //<! for atoms, append the new item via memcpy
      :xiy(x,m,y);R x;}         //<! for lists, use xiy to append y items to the x's tail.

//! posix wrappers for benchmarking
#ifdef USE_AW_MALLOC
V aw_malloc_init(){c0();O("aw_malloc_init ok\n");}    //!< seed alloc
V*aw_malloc(size_t n){P(!n,(V*)0)R(V*)tn(KC,(I)n);}   //!< allocate a list of n bytes
V*aw_realloc(V*p,size_t n){K x=(K)p;
    P(!x||!n,$(x,aw_free(p));aw_malloc(n?n:1))        //!< if ptr is null, realloc() is same as malloc(n), if size is 0 and ptr is not, ptr is freed and a new byte-sized object is allocated
    P(KC-xt,O("`nyi"),(V*)0)                          //!< realloc only supports char-typed lists
    P(xn<=(I)n||(!xr&&8+NX*(J)n<16L<<xm),xu=0,xn=n,p) //!< if new size is less than current, or x has no refs and there is enough space in the block, set xn to requested length and return x
    R(V*)xiy(tn(xt,n),0,x);}                          //!< otherwise, copy contents of x into to a fresh list of requested size and release the old one.
V*aw_calloc(size_t n,size_t sz){                      //!< allocate n*sz bytes and fill with zero
    I nn=MX(1,n)*MX(1,sz);K x=tn(KC,nn);              //!< calculate new length and allocate a new list
    //N(nn/8,xJ[i]=0LL)N(nn%8,((C*)x)[nn-i]=0)R x;}   //<! zero out first with 8-byte stride, then byte-wise
    R memset((V*)x,0,nn);}                            //<! zero out using memset(3)
V aw_free(V*p){r0((K)p);}J aw_malloc_used(){R ws();}
#endif

//:~
