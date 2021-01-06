#include"t.h"
#include"../b.h"

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack
//K gset(B b,K v){K x=b->k;P(xr,XXX(&b->v,v))O("gset val %llx\n",b->v);R b->v=v,r1(x);} //!< only used in tests
//#define GSET(k,v) ({ST0(k);B b=tk();K x=gset(b,v);/*K y=nm(x);O("GSET dbg %.*s %d pos=%d=%d %p b=%p xx=%p\n",yn,yC,yn,yu-26,gpos((B)xx),(I*)x,b,(B)xx),*/x;});

UNIT(wip,
#ifdef SYMS

   O("----------- WIP ----------\n");

   _("1|0",                        1,     "or truth table #1")
   _("0|1",                        1,     "or truth table #2")
   _("1|1",                        1,     "or truth table #3")
   _("0|0",                        0,     "or truth table #4")

   O("-----------------------------------------------------\n");

   _("1&0",                        0,     "and truth table #1")
   _("0&1",                        0,     "and truth table #2")
   _("1&1",                        1,     "and truth table #3")
   _("0&0",                        0,     "and truth table #4")

   O("-----------------------------------------------------\n");

   _("1^0",                        1,     "xor truth table #1")
   _("0^1",                        1,     "xor truth table #2")
   _("1^1",                        0,     "xor truth table #3")
   _("0^0",                        0,     "xor truth table #4")

//___

   //GSET("ƒ[]", ki(4))
   //GSET("λ",ki(42))
   //GSET("∀",ki(42))

   //PT("l(i){r:0;N(x){r+:2};r}",  "('{';(':';r;0x80);('N';x;('{';(0xab;r;0x82)));r)", "loop function decl ptree")
   //PT("f[i]{k:42;k+x}",     "('{';(':';k;0xaa);('+';k;x))",     "basic function declaration with unicode identifier")

   //_("f[i]{k:42;k+x}",        NONE,     "basic function declaration with unicode identifier")
   //_("f[2]",                    42,     "basic function declaration with unicode identifier")

   O("----------- WIP ----------\n");

   _("k:42",                    NONE,    "basic function declaration with unicode identifier")
   //_("k+:1",               "FIXME",    "basic function declaration with unicode identifier")
   //_("z-:2",                    41,    "basic function declaration with unicode identifier")
   //_("z%:2",                    20,    "basic function declaration with unicode identifier")

//___

   _("k",                         42,    "basic function declaration with unicode identifier")
   //_("k:k+1",                 NONE,    "basic function declaration with unicode identifier")
   //_("k",                       43,    "basic function declaration with unicode identifier")

   //_("f[5]",                  NONE,    "basic function declaration with unicode identifier")
   //_("f[i]{$[x=(128*1);2;1]}",NONE,    "basic function declaration with unicode identifier")

   O("--------------------------\n");

   //PT("f[]{2}",      "('{';0x82)",     "ptree of a simple function #1")
   //PT("f[i]{x}",        "('{';x)",     "ptree of a simple function #2")
   //PT("λ[i]{λ[i]}",       "FIXME",     "ptree of a basic recursive fn with utf identifier")

   _("-42",                     -42,     "int negation")
   _("-42.5",                 -42.5,     "float negation")
   _("/42",                      21,     "shift")
   _("//42",                     10,     "double shift")
   _("%42",                    42.0,     "cast to float")

   O("--------------------------\n");

   //_("v:!13",                 NONE,    "enlist")
   //_("*v",                 "FIXME",    "first (float)")
   //_("#v",                      13,    "count (float)")
   //ERR("&v",              "nyi sh",    "count (float)")


   //PT("f[i]{$[10>x;f[x+1];x]}",        "asdf",    "basic function declaration with unicode identifier")
   //PT("ƒ[i]{x}",          "('{';x)",   "basic function declaration with unicode identifier")
   //_("f[i]{$[10>x;f[x+1];x]}",            NONE,    "basic function declaration with unicode identifier")
   
   //_("f[2]",                     4,    "basic function call")
   //_("f",                      123,    "disasm")


   //FIXME PT("TEST+NONE","('+';TEST;NONE)",     "addition of non-existent globals hould produce correct parse tree")
   //FIXME ERR("123+NONE",              "NONE",    "sum holds the correct scalar value")

   PT("128+2",    "('+';0x10;0x82)",     "parse tree of a simple repl expr should match expected")
   _("128+2",                   130,     "simple repl expr should be sane")

   O("-------------------------\n");

   _("(2+2)%4",                 1.0,     "precedence sanity #1")
   _("2+2%2",                   3.0,     "precedence sanity #2")
   _("2+(2%4)",                 2.5,     "precedence sanity #3")
   _("(2+2)%0",                   0,     "precedence sanity #4")

   O("-------------------------\n");

   ERR("TEST",               "TEST",     "non-existent global variable should be a name error")
   ERR("TEST",               "TEST",     "non-existent global variable should be a name error (repeat)")
   _("TEST:42",                NONE,     "declaration of a global var shouldn't echo #1")
   _("BLAH:10",                NONE,     "declaration of a global var shouldn't echo #2")
   EQ_SYM("TEST",              "42",     "internal check of assigned global value should pass")
   _("TEST",                     42,     "global identifier should echo correct value")

   PT("TEST+BLAH", "('+';TEST;BLAH)",    "addition of two declared globals should produce correct parse tree")

   _("TEST+BLAH",                52,     "addition of two globals should echo correct value")

   
   O("-------------------------\n");

   _("RIGHT:4",                NONE,    "multiple expressions on a line")
   _("LEFT:3",                 NONE,    "multiple expressions on a line")

   _("RIGHT+LEFT",                7,    "sum of two globals should echo correct value")
   _("RIGHT*LEFT",               12,    "product of two globals should echo correct value")
   _("RIGHT-LEFT",                1,    "subtraction of two globals should echo correct value")
   _("LEFT%RIGHT",             0.75,    "division of two globals should echo correct value")
   _("RIGHT%2",                 2.0,    "division of a global by a constant should echo correct value")


   O("-------------------------\n");

   _("LFT:42",                 NONE,    "(tmp global var #1)")
   _("RGT:58",                 NONE,    "(tmp global var #2)")

   EQ_SYM("LFT",               "42",    "(tmp global var check #1)")
   EQ_SYM("RGT",               "58",    "(tmp global var check #2)")


   O("-------------------------\n");

   _("SUM:2*LFT+RGT",          NONE,    "global assignment (compound expression)")
   _("SUM",                     200,    "global assignment target should hold a correct value")

   O("-------------------------\n");

   _("кен:42",                 NONE,    "unicode identifier #1")
   _("артур:2",                NONE,    "unicode identifier #2")
   _("кен%артур",              21.0,    "an simple expression with unicode identifiers")

   O("-------------------------\n");

   Wstart=ws();

#else

   GGG['l'-'a']=ki(3);
   GGG['r'-'a']=ki(4);

   //PT("a:42",             "0xaa",            "parse tree of a scalar assignment is its literal value")
   //PT("s:2+1",            "('+';0x82;0x81)", "parse tree of a simple expression #1")
   //PT("s+s",              "('+';s;s)",       "parse tree of a simple expression #2")
   //PT("p:s*s",            "('*';s;s)",       "parse tree of a simple expression #3")

   //_("l*r",                 12,                 "evaluate an expression with global references #1")
   _("l:42",                 12,                 "evaluate an expression with global references #1")

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
