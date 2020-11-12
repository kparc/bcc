#include"t.h"
#include"../h.h"

#define TEST_HT_STRESS
#include<stdlib.h>//rand
enum charsets { CHARSET_ALNUM, CHARSET_AZaz, CHARSET_AZ, CHARSET_az};
ZS csets[4]={
 (S)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
 (S)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
 (S)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
 (S)"abcdefghijklmnopqrstuvwxyz"
};ZS rnd_str(S,SZT,C);

//#define expmem(n) ((n)*(sizeof(pbkt)+1)+total)
#define expmem(n) ((n)*(sizeof(pbkt)))
UNIT(hsh,

   HT t=hnew("tst",2,10,0); //<! 4 slots, 10 split rounds, default hashfn
   I n=7,total=0;B bkts[n];
   S keys[]={"sin","cos","til","𝑗𝑘𝑙","π", //<! test vectors
             "αβγδεζηθικλμνξοπρςστυφχψω",
             "Мне отмщение, и аз воздам"},
             charset=csets[CHARSET_ALNUM]; 

   N(n,I sl;bkts[i]=hget(t,keys[i],sl=sl(keys[i]));total+=sl;K x=(S)bkts[i]->k;
   MEM(xC,           keys[i],     xn))

   EQ_I(t->cnt,      n,           "htable should contain 6 elements")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_I(hdbg(t,0,0), 0x1968B7A76, "htable checksum must match expected")

   N(n,if(bkts[i]!=hget(t,keys[i],sl(keys[i])))FAIL("hash table must be stable"))
   EQ_I(t->cnt,      n,           "htable should still remain the same")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_I(hdbg(t,0,0), 0x1968B7A76, "htable checksum must match expected")

   hdbg(t,1,0);

   N(sl(charset)-1,total+=i+1;hget(t,charset+i,i+1));//uppercase only - cannot be any of keys[]
   EQ_I(t->mem,      expmem(n+sl(charset)-1), "htable mem usage should match expected")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(hdbg(t,0,0), 0x1ED3F6001E,"htable checksum must match expected")

   TRUE(hload(t)     >0.9,        "htable load factor should be above 0.9")

   #ifdef TEST_HT_STRESS
   //! load factor under stress
   N(1000000,I rlen=rand()%100;S s=(S)malloc(rlen+1);total+=rlen;rnd_str(s,rlen,CHARSET_ALNUM);hget(t,s,rlen);free(s))//!< rand load
   EQ_I(hload(t)>0.8,         1,  "htable load factor should be above 0.8")

   hdbg(t,1,0);

   #endif
   
   hdel(t); //!< release memory
)

#ifdef TEST_HT_STRESS
ZS rnd_str(S dest,size_t size,C cs){
  P(4<cs,(S)0)S dict=csets[cs];size_t dictlen=strlen(dict);
  N(size,size_t key=rand()%(dictlen-1);dest[i]=dict[key])
  dest[size]=0;R dest;}
#endif


//:~