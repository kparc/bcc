//! \file h.h hash table cfg/api
#pragma once

#ifndef COSMO
#include<stdlib.h>
#endif

#include"c.h"

//#define HFN sdbm
#define HFN djb2

#define hval(t,k) (hget(t,k,sl(k))->v)
#define hset(t,k,v) (hval=(K)v)

typedef size_t SZT;typedef UI HTYPE;//typedef HTYPE(*HFN)(S s,SZT n); //!< //!< hash value type, hshfn function interface
typedef struct pbkt pbkt;typedef pbkt*B;typedef struct pbkt{HTYPE h;SZT n;B next;K v;K k;}pbkt;//!< keyhash,keylen,next,value,key

typedef struct ht{
    K       tid;         //< table id (KS)
    SZT     spl;         //< split position
    SZT     lvl;         //< capacity is 2*lvl
    short   rds;         //< split rounds
    SZT     cnt;         //< bucket count
    SZT     mem;         //< mem usage
    B*      bkt;         //< array of bucket pointers
    //V*    hea;         //< bucket heap pointer TODO packing
} pHT;typedef pHT*HT;
const static SZT SZHT=sizeof(pHT); //< hash table header size

HT hnew(S id,I l,I r);   //!< init \p id table identifier \p lvl initial size \p rds rounds of tail split attempts
B hget(HT t,S s,SZT n);  //!< insert|lookup \p s string \p n length
K hdel(HT t);            //!< destroy table

#ifdef TST
I hslot(HT t);           //<! #occupied slots
F hload(HT t);           //<! table load factor
UJ hdbg(HT t,C prt,C s); //<! print and checksums
#endif

HTYPE HFN(S s,SZT n);    //!< export hash fn

//:~
