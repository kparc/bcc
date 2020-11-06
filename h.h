//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

#define hsh(s,n) djb2(s,n) //< default hash fn
#define hval(t,k) (hget(t,k,strlen(k))->v)
#define hset(t,k,v) (hval=(K)v)


typedef size_t SZT;
typedef UI HTYPE; //!< hash width
typedef HTYPE(*HSH_FN)(S s,SZT n); //!< hsh_each function interface

typedef struct pbkt pbkt;typedef pbkt*B;
typedef struct pbkt{HTYPE h;I n;B next;K v;K k;}pbkt;//!< keyhash,keylen,next,value,key

typedef struct ht{
    K       tid;         //< table id
    I       spl;         //< split position
    I       lvl;         //< capacity is 2*lvl
    short   rds;         //< split rounds
    SZT     cnt;         //< bucket count
    SZT     mem;         //< mem usage
    B*      bkt;         //< array of bucket pointers
    HSH_FN  hfn;         //< hash function
    //V*    hea;         //< bucket heap pointer
} pHT;typedef pHT*HT;
const static SZT SZHT=sizeof(pHT); //< hash table header size

HT hnew(S id,I l,I r);   //!< init \p id table identifier \p lvl initial size (power of 2) \p rds rounds of tail split attempts
B hget(HT t,S s,I n);    //!< insert|lookup \p s string \p n length
K hdel(HT t);            //!< destroy table

#ifdef TST
I hslot(HT t);           //<! #occupied slots
F hload(HT t);           //<! table load factor
UJ hdbg(HT t,C prt,C s); //<! print and checksums
#endif

HTYPE hsh(S s,SZT n);       //!< export hash fn

//:~
