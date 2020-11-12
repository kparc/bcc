#include"t.h"

UNIT(env,           //<! basic sanity
   WS(0,            "workspace should initally be empty")

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   WS(          64, "enm(10) should allocate 64 bytes")

   EQ_I(Ax,      0, "x should not be an atom")
   EQ_I(xr,      0, "x should have refcount 0")
   EQ_I(xt,     KI, "x should be an int vector")
   EQ_I(xn,     10, "x should have 10 items")

   EQ_I(Ay,     KI, "5th item should be an int")
   EQ_I(yi,      5, "5th item should be eq 5")

   r0(x)            //units bail if wss>0
)

//:~
