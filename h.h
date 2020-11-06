//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

typedef size_t SZT;
typedef struct pbkt pbkt;typedef pbkt*B;
typedef struct pbkt{I h,n;B next;C s[];}pbkt;//!< hash,strlen,next,str+nullchar

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

HT hnew(S id,I lvl,I rds);//!< init \p id table identifier \p lvl initial size (power of 2) \p rds rounds of tail split attempts
B hget(HT t,S s,I n);    //!< insert|lookup \p s string \p n length

#ifdef TST
I hslot(HT t);           //<! #occupied slots
F hload(HT t);           //<! table load factor
UJ hchk(HT t,C prt,C s); //<! print and checksums
#endif

//:~
