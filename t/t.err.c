#include"t.h"

#ifndef SYMS
UNIT(err,
   ERR("\\-f",       "f", "releasing a non-existent global should name-error")
   ERR("\\-A",       "A", "releasing an invalid identifier should name-error")
   ERR("x",          "x", "referencing an non-existent global should name-error")

   _("x:2",        NONE,  "declare a test scalar")
   ERR("\\-x",     "nyi", "releasing a scalar should nyi")
)
#else
UNIT(err,
   ERR("\\-f",       "f", "releasing a non-existent global should name-error (lcase)")
   ERR("\\-A",       "A", "releasing a non-existent global should name-error (ucase)")
   ERR("\\-кен",   "кен", "releasing a non-existent global should name-error (utf)")
   ERR("\\-123",   "123", "releasing an invalid global should name-error")

   ERR("x",          "x", "referencing an non-existent global should name-error")
___
   _("x:2",        NONE,  "declare a test scalar")
   ERR("\\-x",     "nyi", "releasing a scalar should nyi")
)
#endif
//:~