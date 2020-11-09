#include"t.h"
#include"../b.h"

UNIT(TODO,
   //! err
   //ERR("c[x]{$[x;1;2]}",  "x",             "malformed function signature should be an error")
   //ERR("c[x]$[x;1;2]",    "x",             "malformed function signature should be an error")
   //ERR("c[x]{}",          "x",             "malformed function signature should be an error")

   //_("s:4",               0,                "parse tree of a simple expression #2")
   //PT("p:s*s",           "('*';`s;`s)",       "parse tree of a simple expression #2")
#ifdef SYMS
//#if 0
   #define SETSYM(key,val) ({ST0(key);K z,x=tok(0)/*,x=nme(b)*/,*y=GG(x);*y=(val);z=nme(x);O("setsym dbg %.*s %d\n",zn,zC,*zC),x;});

   ST0("kelas");nxt();O("nxt %c %d\n",Pt,Pn);
   SETSYM("LEFT-",ki(3))
   SETSYM("RIGHT+",ki(4))
   SETSYM("ƒ[]",ki(4))
   SETSYM("Кеннет_Айверсон;",ki(42))
   SETSYM("λ",ki(42))
   SETSYM("∀",ki(42))

/*
   Ss=(S)SYM;       //!< set the parser tape to string SYM
   K b=tok(0),      //!< scan an identifier from the tape and return bucket (KS)
     x=nme(b),      //!< lookup literal symbol name string (KS)
    *v=GG(b);       //!< look up a pointer to the global sym value
   *v=ki(16);        //!< assign a value
*/

   SETSYM("LEFT",       ki(3))
   SETSYM("RIGHT",      ki(4))
   EQ_SYM("LEFT",         "3",                "sum holds the correct scalar value")
   EQ_SYM("RIGHT",        "4",                "sum holds the correct scalar value")

   PT("LEFT*RIGHT",        "('*';`LEFT;`RIGHT)",                "parse tree of a simple expression #2")

___
   PT("LEFT*RIGHT",        12,                "parse tree of a simple expression #2")


#endif

   PT("pr:s*s",           "('*';`s;`s)",    "parse tree of a simple expression #2")
   _("p:s*s",             0,                "parse tree of a simple expression #2")
   _("p",                 9,                "p should have expected value")

//   PT("pr:s*s",           "('*';`s;`s)",       "parse tree of a simple expression #2")
//   _("p:s*s",             0,                "parse tree of a simple expression #2")
//   _("p",                 9,                "p should have expected value")

   //PT("prd:sum*sum",        "('*';`sum;`sum)",   "assignment referencing globals should produce correct parse tree")
   //EQ_SYM("prd",           "9",                  "prd holds the correct vector value in the slot FIXME")
)


//:~