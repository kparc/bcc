#include"t.h"
#define pass(s) _(bb(s),0,s)
#define fail(s,exp) {S b=bb(s);_(exp==(b?(C)*b:(C)b),1,exp)}

//! bracket balancer
//! TODO add nesting limit tests

UNIT(prs,//<! parse trees

   PT("#x",    "('#';x)",          "ptree of basic monadic op")

   PT("2*x",   "('\\';x)",         "2*x should translate to monadic left shift")
   PT("40+2",  "('+';0xa8;0x82)",  "simple inline expression")

   PT("#x",    "('#';x)",          "ptree of monadic op")
   PT("x+y",   "('+';x;y)",        "ptree of dyadic op")

   PT("c[i]$[x;1;2]", "('$';x;0x81;0x82)",          "declare a ctf function (omitted brackets)")
   _("\\-c",        NONE, "release a ctf function")
   WS(                 0, "parsing a bare ctf function shouldn't leak memory")

   PT("l[i]{r:0;N(x){r+:2};r}",  "('{';(':';r;0x80);('N';x;('{';(0xab;r;0x82)));r)", "loop function decl ptree")
   _("\\-l",        NONE, "release of l[] should return memory to the heap")


   pass("")
   pass("\n")
   pass("[]")
   pass("[]\n")
   pass("[\"asdf]asdf{\"]")
   pass("$[x&1;(\\x)+x+1;/x]")
   fail("[}]",'}')
   fail("[\"]",'\"')
   fail("[\"\"",0)

   //! unit must pass (wss should be zero)
)

//:~
