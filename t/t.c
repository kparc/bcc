#include"t.h"

UNIT(smoke,//<! basic sanity

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   _(Ax,       0, "x should not be an atom")
   _(xr,       0, "x should have refcount 0")
   _(xt,      KI, "x should be an int vector")
   _(xn,      10, "x should have 10 items")

   _(Ay,      KI, "5th item should be an int")
   _(yi,       5, "5th item should be eq 5")

   _("2+2",           4,    "basic ex #1")
   _("2=2",           1,    "basic ex #2")
   _("f[ii]{x+y}",    NONE, "basic ex #3")
   _("f[40;2]",       42,   "basic ex #4")

   //_("x", ERR_VALUE, "basic eval should be sane #3")//!< todo

   r0(x))

UNIT(parser,//<! parse trees

 PT("40+2", "(\"+\";0xa8;0x82)", "inline expression")

)

TESTS(
 RUN(smoke)
 RUN(parser)
)

//:~