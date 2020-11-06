//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

typedef size_t SZT;
typedef struct pbkt pbkt;typedef pbkt*B;
typedef struct pbkt{I h,n;B next;C s[];}pbkt;//!< hash,strlen,next,str+nullchar

B*hnew(I lvl,I rds);     //!< init \p lvl initial size (power of 2) \p rds rounds of tail split attempts
S hget(S s,I n);         //!< insert|lookup \p s string \p n length
J hmem(),hcnt();         //!< ram usage, count

#ifdef TST
I hslot();               //<! #occupied slots
F hload();               //<! table load factor
UJ hchk(C prt,C stat);   //<! print and checksums
#endif

//:~
