//! \file h.h hash table cfg/api
#include<stdlib.h>
#include"c.h"

V s0(I lvl,I rds); //!< init \p lvl initial size (power of 2) \p rds rounds of tail split attempts
S ssn(S s,I n);    //!< insert|lookup \p s string \p n length
J suse(),scnt();   //!< ram usage, count

//:~
