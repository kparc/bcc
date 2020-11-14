#include"t.h"
#include"../b.h"

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack
#define GSET(k,v) ({ST0(k);B b=tk();K x=gset(b,v);/*K y=nm(x);O("GSET dbg %.*s %d pos=%d=%d %p b=%p xx=%p\n",yn,yC,yn,yu-26,gpos((B)xx),(I*)x,b,(B)xx),*/x;});

UNIT(wip,
#ifdef SYMS
   //! err
   //ERR("c[x]{$[x;1;2]}",  "x",             "malformed function signature should be an error")
   //ERR("c[x]$[x;1;2]",    "x",             "malformed function signature should be an error")
   //ERR("c[x]{}",          "x",             "malformed function signature should be an error")

   //_("s:4",               0,                "parse tree of a simple expression #2")
   //PT("p:s*s",           "('*';`s;`s)",       "parse tree of a simple expression #2")

   GSET("LEFT-", ki(3))
   GSET("LEFT+", ki(4))
   GSET("LEFT",  ki(4))
   GSET("RIGHT+",ki(4))
   //GSET("ƒ[]", ki(4))
   GSET("Кеннет_Айверсон;",ki(42))
   //GSET("λ",ki(42))
   //GSET("∀",ki(42))
   
/*
   Ss=(S)SYM;       //!< set the parser tape to string SYM
   K b=tok(0),      //!< scan an identifier from the tape and return bucket (KS)
     x=nme(b),      //!< lookup literal symbol name string (KS)
    *v=GG(b);       //!< look up a pointer to the global sym value
   *v=ki(16);        //!< assign a value
*/

   GSET("LEFT",        ki(3))
   GSET("RIGHT",       ki(4))
   EQ_SYM("LEFT",         "3",                "sum holds the correct scalar value")
   EQ_SYM("RIGHT",        "4",                "sum holds the correct scalar value")
   PT("LEFT*RIGHT",   "('*';`LEFT;`RIGHT)",   "a dyadic expression referencing ascii globals should produce a correct parse tree")

   _("LEFT*RIGHT",        12,                 "a dyadic expression referencing globals should evaluate to an expected value")


   GSET("кен",         ki(42))
   GSET("артур",       ki(58))
   EQ_SYM("кен",         "42",                "sum holds the correct scalar value")
   EQ_SYM("артур",       "58",                "sum holds the correct scalar value")

   PT("кен+артур",   "('+';`кен;`артур)",     "a dyadic expression referencing ascii globals should produce a correct parse tree")

   _("кен+артур",        100,                 "a dyadic expression referencing globals should evaluate to an expected value")

___

   //extern K vf(I f);o(vf(0));

   //_("\\v",              "`LEFT`RIGHT",       "a dyadic expression referencing globals should evaluate to an expected value")

   //PT("кен(i)",        "(`кен;1;2)",     "a dyadic expression referencing ascii globals should produce a correct parse tree")
   //ERR("asdf",        0,     "a dyadic expression referencing ascii globals should produce a correct parse tree")

   //extern HT GT;hdel(GT);

   Wstart=ws();

#else

   GGG['l'-'a']=ki(3);
   GGG['r'-'a']=ki(4);

   //PT("a:42",             "0xaa",            "parse tree of a scalar assignment is its literal value")
   //PT("s:2+1",            "('+';0x82;0x81)", "parse tree of a simple expression #1")
   //PT("s+s",              "('+';s;s)",       "parse tree of a simple expression #2")
   //PT("p:s*s",            "('*';s;s)",       "parse tree of a simple expression #3")

   _("l*r",                 12,                 "evaluate an expression with global references #1")

   //_("s:2+2",             0,                 "scalar expr assignment")
   //_("p:s*s",             0,                 "evaluate an expression with global references #1")
   //_("l*r",               12,                "evaluate an expression with global references #2")
   //_("p",                 16,                "p should have expected value")

#endif

#if 0
   PT("pr:s*s",           "('*';`s;`s)",     "parse tree of a simple expression #2")
   _("p:s*s",              0,                "parse tree of a simple expression #2")
   _("p",                  9,                "p should have expected value")
#endif


//   PT("pr:s*s",           "('*';`s;`s)",    "parse tree of a simple expression #2")
//   _("p:s*s",             0,                "parse tree of a simple expression #2")
//   _("p",                 9,                "p should have expected value")

   //PT("prd:sum*sum",    "('*';`sum;`sum)",  "assignment referencing globals should produce correct parse tree")
   //EQ_SYM("prd",           "9",             "prd holds the correct vector value in the slot FIXME")

)

//:~
