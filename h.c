//! \file h.c \brief simple hash table with separate chaining
//! \see https://svn.process-one.net/ejabberd/tags/ejabberd-2.0.5/src/tls/tls_drv.c
#include"a.h"
#include"h.h"

#define SZ sizeof
#define rea brealloc
#define F(p) bfree(p)
#define hmap(h,rng) (h&((rng)-1)) //!< map hash value onto given range (h mod rng-1)
#define tid t->tid
#define spl t->spl
#define hfn t->hfn
#define lvl t->lvl
#define rds t->rds
#define mem t->mem
#define cnt t->cnt
#define bkt t->bkt

//! djb2 \see www.burtleburtle.net/bob/hash/doobs.html groups.google.com/forum/#!topic/comp.lang.c/lSKWXiuNOAk
inline HTYPE djb2(S s,SZT n){HTYPE h=5381;N(n,h=(h<<5)+h+*s++)R h;}//Z_ UI djb(S x,UI n){UI h=5381;N(n,h=33*(h^x[i]));R h;}
inline HTYPE sdbm(S s,SZT n){HTYPE h=0;I c;W(c=*s++)h=c+(h<<6)+(h<<16)-h;R h;}//<! sdbm \see berkeleydb \see sleepycat
//ZV hcpy(V*d,V*s,SZT n){*((S)memcpy(d,s,n)+n)=0;}//!< copy and terminate
ZK hcpy(S s,SZT n){K x=kS(n+1);*((S)memcpy((V*)x,s,n)+n)=0;R x;}//!< copy and terminate
HT hnew(S id,I l,I r,HFN f){HT t=(HT)bcalloc(1,SZHT);tid=hcpy(id,strlen(id));hfn=f?f:DFLT_HFN;rds=r,lvl=l,bkt=(B*)bcalloc(2*l,SZ(B*));R t;}//tid=(S)bmalloc((n=strlen(id))+1);hcpy(t->id,id,n);
ZV hbal(HT t);

B hget(HT t,S s,I n){                 //!< lookup or insert string s of length n
 K x;B b;HTYPE h=hfn(s,n),hi=0,       //!< b bucket, h hash, hi use full range (dbg)
 idx=hmap(h,lvl);                     //!< first, try to map hash value to the 1st half of table
 $(idx<spl,hi=1,idx=hmap(h,lvl<<1));  //!< if idx is above split position, remap to the entire table
 b=bkt[idx];                          //!< retrieve the bucket from the slot idx
 W(b){                                //!< traverse its linked list, if any:
  P(b->n==n,x=b->k;                   //!< if length matches..
   N(n,$(xC[i]!=s[i],goto L0);)       //!< compare strings char by char
   b)                                 //!< if they match, return the bucket
  L0:b=b->next;}                      //!< otherwise keep traversing the list.
 I m=SZ(pbkt)/*+n+1*/;b=(B)bmalloc(m);//!< allocate memory for a new bucket (header size //+ strlen + terminator)
 mem+=m;b->h=h;b->n=n;b->v=NL;        //!< increment mem usage and initialize bucket header
 //hcpy(b->k,s,n);                    //!< copy string to the bucket and terminate it
 x=b->k=pn(s,n);xt=KS;                //!< internalize the string
 b->next=bkt[idx];bkt[idx]=b;         //!< push the new bucket to the head of the slot
 if(b->next)hbal(t);                  //!< if slot has a tail, try to split it
 R cnt++,b;}                          //!< increment bucket count and return new bucket

ZV hbal(HT t){B*bp,mov;               //!< balance hash table load
  N(rds,                              //!< perform rds balancing attempts:
   bp=&bkt[spl];                      //!< retrieve the head bucket at spl
   I topidx=lvl+spl;                  //!< index of a slot in the upper part
   W(*bp){                            //!< while the slot at spl is not empty
    $(hmap((*bp)->h,lvl<<1)==topidx,  //!< if the bucket's hash maps to topidx
     mov=*bp;*bp=(*bp)->next;         //!< remove it from the list at spl
     mov->next=bkt[topidx];           //!< link the head bucket at newidx to it
     bkt[topidx]=mov)//else           //!< and make it the new head
     bp=&(*bp)->next;}                //!< keep traversing the list.
   $(++spl==lvl,                      //!< if ++spl+lvl reaches the size of the table
    lvl<<=1;spl=0;                    //!< then double lvl and reset spl to zero
    bkt=(B*)rea((V*)bkt,SZ(B*)*2*lvl);//!< double the size of the table
    N(lvl,bkt[lvl+i]=0));             //!< zero out the upper part.
  )}

#define S0(ks) {K x=ks;xt=KC;r0(x);}; //!< release symbol (downcast to KC)
K hdel(HT t){B b,n;                   //!< destroy table
 N(lvl<<1,b=bkt[i];
  W(b){n=b->next,cnt--;S0(b->k)F(b),b=n;})
  K r=cnt?AB("cnt"):(K)(spl=lvl=rds=mem=0);S0(tid)
  R F(bkt),F(t),r;}

#ifdef TST
I hslot(HT t){I r=0;N(lvl<<1,r+=!!bkt[i])R r;}F hload(HT t){R(F)hslot(t)/cnt;}//<! slot count, load factor
UJ hdbg(HT t,C o,C st){B b;I n,len,LEN=0,CNT=0;UJ csum,CSUM=0;
  N(lvl<<1,b=bkt[i];n=len=csum=0;$(o,O("%s[%d]: ",(S)tid,i))
    W(b){$(o,O("(%s) -> ",(S)b->k));n++,len+=b->n,csum+=b->h;b=b->next;}
    $(n,csum+=len+n+i);$(o,$(n,O("[cnt=%d,len=%d,sum=%llu]\n",n,len,csum))O("()\n"););
    CSUM+=csum;LEN+=len;CNT+=n)
  $(o,O("HT[%s]: keys=%d len=%d\n",(S)tid,CNT,LEN));
  R st?CNT:(CSUM+(lvl<<1));}
#endif

//:~
