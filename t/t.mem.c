#include"t.h"
#include"../m.h"

UNIT(mem,
   _("2+2",    4, "basic ex #1")
   _("2=2",    1, "basic ex #2")

   //_("\\f", "!`", "global function namespace should be empty FIXME")
   //_("\\v", "!`", "global variable namespace should be empty FIXME")

   WS0("non-assigning repl expressions shouldn't leak memory")

   _("f[ii]{x+y}",  NONE, "declare a global function")
   WS(                80, "workspace usage should be 80 bytes")

   _("f[40;2]",       42, "function calls should work as expected")
   WSSAME(                "calling a function shouldn't leak memory")

   _("f[ii]{x-y}",  NONE, "reassign an exisiting function")
   WSSAME(                "reassigning a global function shouldn't leak memory")

   _("f[40;2]",       38, "reassigned function should work as expected")

   _("\\-f",        NONE, "releasing existing global function should work")

   _("x:!10",       NONE, "declare a global vector")
   _("\\-x",        NONE, "releasing existing global vector should be ok")

   WS0(                   "releasing a global vector shouldn't leak memory")

   //_("c[i]$[x;1;2]",NONE, "declare a ctf function (omitted brackets)")
   //_("\\-c",        NONE, "release a bare ctf function")
   //WS(0, "releasing a bare ctf function shouldn't leak memory FIXME")

   //! aw_malloc|calloc|realloc|free
   //! TODO test calloc, add more posix compliance tests
   N(16,K x=(K)aw_malloc(i+1);//O("x %d = %p xn %d %d\n",i,x,xm,xr);N(xn,O("%d ",((C*)x)[i]))O("\n");
      aw_free((V*)x))

   N(16,K x=(K)aw_calloc(i+1,2);//O("x %d = %p xn %d %d\n",i,x,xm,xr);N(xn,O("%d ",((C*)x)[i]))O("\n");
      aw_free((V*)x))

   //! unit must pass (wss should be zero, no leaked refs)
)

//:~
