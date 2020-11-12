#include"t.h"
#include"../h.h"

#define TEST_HT_STRESS

#include<stdlib.h>//rand
enum charsets { CHARSET_ALNUM, CHARSET_AZaz, CHARSET_AZ, CHARSET_az};
char*csets[]={
 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
 "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
 "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
 "abcdefghijklmnopqrstuvwxyz"
};ZS rnd_str(S,SZT,C);

UJ csums[]={1435,13992,5376450523,107282683043};//sdbm|djb2
UJ CSM(I i){R csums[2*(HFN((S)"",0)==5381)+i];}

//#define expmem(n) ((n)*(sizeof(pbkt)+1)+total)
#define expmem(n) ((n)*(sizeof(pbkt)))
UNIT(hsh,

   HT t=hnew((S)"tst",2,10); //<! 4 slots, 10 split rounds, default hashfn

   I n=7,total=0;B bkts[n];
   char*keys[]={"sin","cos","til","𝑗𝑘𝑙","π", //<! test vectors
             "αβγδεζηθικλμνξοπρςστυφχψω",
             "Мне отмщение, и аз воздам"},
             *charset=csets[CHARSET_ALNUM]; 

   N(n,I sl;bkts[i]=hget(t,(S)keys[i],sl=sl(keys[i]));total+=sl;K x=bkts[i]->k;
   MEM(xC,           keys[i],     xn))

   EQ_I(t->cnt,      n,           "htable should contain 6 elements")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_K(hdbg(t,0,0), CSM(0),      "htable checksum must match expected")

   N(n,if(bkts[i]!=hget(t,(S)keys[i],sl(keys[i])))FAIL("hash table must be stable"))
   EQ_I(t->cnt,      n,           "htable counter should stay the same")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_K(hdbg(t,0,0), CSM(0),      "htable checksum must match expected")
   //hdbg(t,0,0);
   TRUE(hload(t)     >0.85,       "htable load factor should be above 0.85")

   I c;N(c=sl(charset),total+=i+1;hget(t,(S)charset+i,c-i));//uppercase only - cannot be any of keys[]
   EQ_I(t->mem,      expmem(n+sl(charset)), "htable mem usage should match expected")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_K(hdbg(t,0,0), CSM(1),      "htable checksum must match expected")
   //hdbg(t,1,0);
   TRUE(hload(t)     >0.85,       "htable load factor should be above 0.85")

   #ifdef TEST_HT_STRESS
   //! load factor under stress
   N(10000,I rlen=rand()%100;S s=(S)calloc(1,rlen+1);total+=rlen;rnd_str(s,rlen,CHARSET_ALNUM);hget(t,s,rlen);free(s))//!< rand load
   //hdbg(t,1,0);
   TRUE(hload(t)     >0.8,       "htable load factor should be above 0.8")
   #endif
   
   hdel(t); //!< release memory
)

#ifdef TEST_HT_STRESS
ZS rnd_str(S dest,size_t size,C cs){
  P(4<cs,(S)0)char*dict=csets[cs];size_t dictlen=sl(dict);
  N(size,size_t key=rand()%(dictlen-1);dest[i]=dict[key])
  dest[size]=0;R dest;}
#endif


//:~