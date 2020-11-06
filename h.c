//! \file h.c \brief simple hash table with separate chaining
//! \see https://svn.process-one.net/ejabberd/tags/ejabberd-2.0.5/src/tls/tls_drv.c
#include"b.h"
#include"h.h"

#define SZ sizeof
#define rea realloc
#define hmap(h,rng) (h&((rng)-1)) //!< map hash value onto given range (h mod rng-1)

static B*ht;    //<! hash table
ZI rds;         //<! balancer rounds
ZI lvl,spl;     //<! current size of the table divided by 2, split position (initially 0)
ZJ S1,j;        //!< memory usage, bucket count

//! djb2 \see www.burtleburtle.net/bob/hash/doobs.html groups.google.com/forum/#!topic/comp.lang.c/lSKWXiuNOAk
Z_ UI djb(S s,SZT n){UI h=5381;N(n,h=(h<<5)+h+*s++)R h;}//Z_ UI djb(S x,UI n){UI h=5381;N(n,h=33*(h^x[i]));R h;}
ZV hcpy(V*d,V*s,SZT n){*((S)memcpy(d,s,n)+n)=0;}//!< copy and terminate
B*hnew(I l,I r){rds=r,lvl=l;ht=(B*)calloc(2*lvl,SZ(B*));R ht;}
J hmem(){R S1;}J hcnt(){R j;}ZV hbal();

S hget(S s,I n){                      //!< lookup or insert string s of length n
 B b;UI h=djb(s,n),hi=0,              //!< b bucket, h hash, hi use full range (dbg)
 idx=hmap(h,lvl);                     //!< first, try to map hash value to the 1st half of table
 $(idx<spl,hi=1,idx=hmap(h,lvl<<1));  //!< if idx is above split position, remap to the entire table
 b=ht[idx];                           //!< retrieve the bucket from the slot idx
 W(b){                                //!< traverse its linked list, if any:
  P(b->n==n,                          //!< if length matches..
   N(n,$(b->s[i]!=s[i],goto L0);)     //!< compare strings char by char
   b->s)                              //!< if they match, return the existing string
  L0:b=b->next;}                      //!< otherwise keep traversing the list.
 I m=SZ(pbkt)+n+1;b=(B)malloc(m);     //!< allocate memory for a new bucket (header size + strlen + terminator)
 S1+=m;b->h=h;b->n=n;                 //!< increment mem usage and initialize bucket header
 hcpy(b->s,s,n);                      //!< copy string to the bucket and terminate it
 b->next=ht[idx];ht[idx]=b;           //!< push the new bucket to the head of the slot
 if(b->next)hbal();                   //!< if slot has a tail, try to split it
 R j++,b->s;}

ZV hbal(){B*bp,mov;                   //!< balance hash table load
  N(rds,                              //!< perform rds balancing attempts:
   bp=&ht[spl];                       //!< retrieve the head bucket at spl
   I topidx=lvl+spl;                  //!< index of a slot in the upper part
   W(*bp){                            //!< while the slot at spl is not empty
    $(hmap((*bp)->h,lvl<<1)==topidx,  //!< if the bucket's hash maps to topidx
     mov=*bp;*bp=(*bp)->next;         //!< remove it from the list at spl
     mov->next=ht[topidx];            //!< link the head bucket at newidx to it
     ht[topidx]=mov)//else            //!< and make it the new head
     bp=&(*bp)->next;}                //!< keep traversing the list.
   $(++spl==lvl,                      //!< if ++spl+lvl reaches the size of the table
    lvl<<=1;spl=0;                    //!< then double lvl and reset spl to zero
    ht=(B*)rea((V*)ht,SZ(B*)*2*lvl);  //!< double the size of the table
    N(lvl,ht[lvl+i]=0));              //!< zero out the upper part.
  )}

#ifdef TST
I hslot(){I r=0;N(lvl<<1,r+=!!ht[i])R r;}//<! count occupied slots
F hload(){R(F)hslot()/j;}

UJ hchk(C o,C st){B b;I n,len,LEN=0,CNT=0;UJ csum,CSUM=0;
  N(lvl<<1,
    b=ht[i];n=len=csum=0;
    if(o)O("ht[%d]: ",i);
    W(b){
      if(o)O("(%s) -> ",b->s);
      n++,len+=b->n,csum+=b->h;
      b=b->next;
    }
    if(n)csum+=len+n+i;
    if(o)$(n,O("[cnt=%d,len=%d,sum=%llu]\n",n,len,csum))O("()\n");
    CSUM+=csum;LEN+=len;CNT+=n
  )
  if(o)O("HT: keys=%d len=%d\n",CNT,LEN);
  R st?CNT:(CSUM+(lvl<<1));
}
#endif

 //:~
