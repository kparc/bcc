#include"t.h"

UNIT(fio,

   ERR("\\l t/dat/blah.b",   "t/blah.b",      "missing file should report an error")
     _("\\l t/dat/t.fio.b",   NONE,           "successful file compilation shouldn't report")
     _("#x",                  100,            "loaded and compiled source should produce result")
     _("\\-x",                NONE,           "resulteleasing the result of compilation should empty the ws")
)

//:~
