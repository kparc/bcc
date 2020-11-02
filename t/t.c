#include"t.h"

UNIT(smoke,//<! basic sanity
   _(W0,       0, "workspace should initally be empty")

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   WS(        64, "enm(10) should allocate 64 bytes")

   _(Ax,       0, "x should not be an atom")
   _(xr,       0, "x should have refcount 0")
   _(xt,      KI, "x should be an int vector")
   _(xn,      10, "x should have 10 items")

   _(Ay,      KI, "5th item should be an int")
   _(yi,       5, "5th item should be eq 5")

   _("2+2",    4, "basic ex #1")
   _("2=2",    1, "basic ex #2")

   WS0("non-assigning repl expressions shouldn't leak memory")

   _("f[ii]{x+y}",  NONE, "declare a global function")
   WS(144, "workspace usage should increase to 144 bytes")

   _("f[40;2]",       42, "function call should work as expected")
   WS0("calling a function shouldn't leak memory")

   _("f[ii]{x-y}",  NONE, "reassign an exisiting function")
   WS0("reassigning a global function shouldn't leak memory")

   _("f[40;2]",       38, "reassigned function should work as expected")

   r0(x);WS(80, "r0(x) should return memory to the heap")

   _("\\-f",       NONE,  "release global var should be ok")

   WS(0, "workspace should be empty after global release")

   //_("x", expressioR_VALUE, "basic eval should be sane #3")//!< todo
)

UNIT(parser,//<! parse trees
 PT("#x",    "('#';x)",          "ptree of basic monadic op")

 PT("2*x",   "('\\';x)",         "2*x should translate to monadic left shift")
 PT("40+2",  "('+';0xa8;0x82)",  "simple inline expression")

 PT("#x",    "('#';x)",          "ptree of monadic op")
 PT("x+y",   "('+';x;y)",        "ptree of dyadic op")

 WS0("PT() shouldn't leak memory")

 PT("l[i]{r:0;N(x){r+:2};r}",  "('{';(':';r;0x80);('N';x;('{';(0xab;r;0x82)));r)", "loop function decl ptree")

 W0=ws();  //ignore wssize check FIXME implement global var release

)

TESTS(
 RUN(smoke)
 RUN(parser)
)

//:~