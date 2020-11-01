#include"t.h"

UNIT(smoke,//<! basic sanity

   _(ws(),     0, "workspace size should be 0 bytes")

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   _(ws(),    64, "workspace size should be 64 bytes")

   _(Ax,       0, "x should not be an atom")
   _(xr,       0, "x should have refcount 0")
   _(xt,      KI, "x should be an int vector")
   _(xn,      10, "x should have 10 items")

   _(Ay,      KI, "5th item should be an int")
   _(yi,       5, "5th item should be eq 5")

   _("2+2",            4,   "basic ex #1")
   _("2=2",            1,   "basic ex #2")

   _(ws(),            64,   "workspace size should still be 64 bytes")

   _("f[ii]{x+y}",    NONE, "basic ex #3")
   _("f[40;2]",       42,   "basic ex #4")

   _(ws(),           144,   "workspace size should be 144 bytes", r0(x))
   _(ws(),            80,   "r0(x) should return memory to the heap")

   //_("x", ERR_VALUE, "basic eval should be sane #3")//!< todo
)

UNIT(parser,//<! parse trees

 PT("#x",   "(\"#\";\"x\")\x01",        "basic monadic op ptree should be sane FIXME trailing gunk on the first run")
 PT("#x",   "(\"#\";\"x\")",            "trailing gunk only happens once")
 PT("2*x",  "(\"\\\";\"x\")",           "2*x should translate to \\x")
 PT("40+2", "(\"+\";0xa8;0x82)",        "simple inline expression")
 
 PT("#x",   "(\"#\";\"x\")",            "basic monadic op ptree should be sane") 
 PT("x+y",  "(\"+\";\"x\";\"y\")",      "basic dyadic op ptree should be sane") 
 

)

TESTS(
 RUN(smoke)
 RUN(parser)
)

//:~