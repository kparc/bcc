#include"t.h"

UNIT(err,
   ERR("\\-f",       "f", "releasing a non-existent global should name-error")
   ERR("\\-A",       "A", "releasing an invalid identifier should name-error")
   ERR("x",          "x", "referencing an non-existent global should name-error")

   _("x:2",         NONE, "declare a test scalar")
   ERR("\\-x",     "nyi", "releasing a scalar should nyi")

   ERR("\\-x",     "nyi", "releasing a scalar should nyi")
)

//:~