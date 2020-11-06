//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

#define hval(t,k) (hget(t,k,strlen(k)->v)
#define hset(t,k,v) (hval=(K)v)

typedef size_t SZT;
typedef struct pbkt pbkt;typedef pbkt*B;
typedef struct pbkt{I h,n;B next;K v;C s[];}pbkt;//!< keyhash,keylen,next,value,keyname+nullchar

typedef struct ht{
    S       id;          //< table id
    I       spl;         //< split position
    I       lvl;         //< capacity is 2*lvl
    short   rds;         //< split rounds
    SZT     cnt;         //< bucket count
    SZT     mem;         //< mem usage
    B*      bkt;         //< array of bucket pointers
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

UI hsh(S s,SZT n);       //!< export hash fn

//:~
