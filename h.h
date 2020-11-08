//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

#define DFLT_HFN djb2

#define hval(t,k) (hget(t,k,strlen(k))->v)
#define hset(t,k,v) (hval=(K)v)

typedef size_t SZT;typedef UI HTYPE;typedef HTYPE(*HFN)(S s,SZT n); //!< //!< hash value type, hshfn function interface
typedef struct pbkt pbkt;typedef pbkt*B;typedef struct pbkt{I h;I n;B next;K v;K k;}pbkt;//!< keyhash,keylen,next,value,key

typedef struct ht{
    K       tid;         //< table id (KS)
    I       spl;         //< split position
    I       lvl;         //< capacity is 2*lvl
    short   rds;         //< split rounds
    SZT     cnt;         //< bucket count
    SZT     mem;         //< mem usage
    B*      bkt;         //< array of bucket pointers
    HFN     hfn;         //< hash function
    //V*    hea;         //< bucket heap pointer TODO packing
} pHT;typedef pHT*HT;
const static SZT SZHT=sizeof(pHT); //< hash table header size

HT hnew(S id,I l,I r,HFN f); //!< init \p id table identifier \p lvl initial size \p rds rounds of tail split attempts, hashfn or 0 for default
B hget(HT t,S s,I n);    //!< insert|lookup \p s string \p n length
K hdel(HT t);            //!< destroy table

#ifdef TST
I hslot(HT t);           //<! #occupied slots
F hload(HT t);           //<! table load factor
UJ hdbg(HT t,C prt,C s); //<! print and checksums
#endif

HTYPE DFLT_HFN(S s,SZT n);       //!< export hash fn

//:~
