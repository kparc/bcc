//! \file h.h hash table cfg/api
#pragma once
#include<stdlib.h>
#include"c.h"

typedef size_t SZT;
typedef struct pbkt pbkt;typedef pbkt*B;  //!< fwd decl for recursion
typedef struct pbkt{I h,n;B next;C s[];}pbkt;

B*hnew(I lvl,I rds);  //!< init \p lvl initial size (power of 2) \p rds rounds of tail split attempts
S hget(S s,I n);    //!< insert|lookup \p s string \p n length
J hmem(),hcnt();    //!< ram usage, count

//:~
