//! \file h.c \brief simple hash table with separate chaining
//! \see https://svn.process-one.net/ejabberd/tags/ejabberd-2.0.5/src/tls/tls_drv.c
#include"b.h"
#include"h.h"
#define map(h,rng) (h&((rng)-1)) //!< map hash value onto range (h mod rng-1)
ZJ S1,j;//< alloc,count
ZI RDS,SPL,LVL=2;
static struct bucket**buckets;typedef size_t SZT;
typedef struct bucket{I h,n;struct bucket*next;I usage;C s[];}pbkt;typedef pbkt*B;const static SZT SZB=sizeof(pbkt);

//! djb2 \see www.burtleburtle.net/bob/hash/doobs.html groups.google.com/forum/#!topic/comp.lang.c/lSKWXiuNOAk
Z_ UI hsh(S s,UI n){UI h=5381;N(n,h=(h<<5)+h+*s++)R h;}//Z_ UI djb(S x,UI n){UI h=5381;N(n,h=33*(h^x[i]));R h;}
ZS dsn(V*d,V*s,SZT n){R memcpy(d,s,n)+n;}//!< mcpy+seek
V s0(I l,I r){RDS=r,LVL=l;buckets=(pbkt**)calloc(2*LVL,sizeof(SZT));}
J suse(){R S1;}J scnt(){R j;}

S ssn(S s,I n){
 pbkt*b;I i;UI hash=hsh(s,n),bucket=map(hash,LVL),hi=0;
 $(bucket<SPL,hi=1;bucket=map(hash,LVL<<1));
 b=buckets[bucket];
 W(b){P(b->n==n,N(n,$(b->s[i]!=s[i],goto L0);)b->s)L0:b=b->next;}
 S1+=i=SZB+n+1;
 b=(pbkt*)malloc(i);
 b->h=hash;
 b->n=n;
 b->usage=-1;
 *dsn(b->s,s,n)=0;
 b->next=buckets[bucket];
 buckets[bucket]=b;
 pbkt**bp,*tmp;
 if(b->next){
  N(RDS,
   bp=&buckets[SPL];
   I newBucket=SPL+LVL;
   W(*bp){
    $(map((*bp)->h,LVL<<1)==newBucket,
     tmp=*bp;*bp=(*bp)->next;
     tmp->next=buckets[newBucket];
     buckets[newBucket] = tmp)//else
    bp=&(*bp)->next;}

   $(++SPL==LVL){
    LVL<<=1,SPL=0;
    buckets=(pbkt**)realloc((V*)buckets,sizeof(SZT)*2*LVL);
    N(LVL,buckets[LVL+i]=0)};
  )
 }
 R j++,b->s;}

 //:~