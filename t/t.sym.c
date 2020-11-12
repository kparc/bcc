#include"t.h"

#ifdef SYMS

UNIT(sym,
   //! api test
   #define SYM "xyz"
   ST0(SYM);            //!< set the parser tape to string SYM
   B b=tk();            //!< scan an identifier from the tape and return its GT bucket
   K x=gset(b,ki(42)),  //!< assign value v to global symbol b
     y=nm(x);           //!< lookup literal symbol name string (KS)

   MEM(y,                 SYM,               xn)
   EQ_SYM(SYM,           "42",               "assigned variable holds the correct scalar value")

   PT("ccall+go_fn+42",  "('+';`ccall;('+';`go_fn;0xaa))",   "basic multichar identifiers are supported by parser")
   PT("x+Not+Wha",       "('+';`x;('+';`Not;`Wha))",         "special case: if leading N|W is not followed by (, force class to identifier")

   PT("asdf:42",         "0xaa",            "parse tree of a scalar assignment is its literal value")
   PT("sum:2+1",         "('+';0x82;0x81)", "parse tree of a simple expression #1")
   PT("sum+sum",         "('+';`sum;`sum)", "parse tree of a simple expression #2")

   _("til:!3",            0,                "vector expr assignment")
   _("sum:2+1",           0,                "scalar expr assignment")
   _("Not:1",             0,                "global identifier starting with N")
   _("Wha:\\4",           0,                "global identifier starting with W")
   _("woW:/64",           0,                "global identifier ending with W")

   EQ_SYM("sum",        "3",                "sum holds the correct scalar value")
   EQ_SYM("til",    "0 1 2",                "til holds the correct vector value")
   EQ_SYM("Not",        "1",                "Not holds the correct scalar value")
   EQ_SYM("Wha",        "8",                "Wha holds the correct scalar value")
   EQ_SYM("woW",       "32",                "woW holds the correct scalar value")

   //_("fun(i){x+2}",         0,            "function declaration")
   //EQ_SYM("fun",       disasm,            "TODO")

   //_("prd:sum*sum",       0,              "product of two global variables")
   //EQ_SYM("prd",         "9",             "prd holds the correct vector value in the slot FIXME")

   Wstart=ws();                                 //! FIXME variable identifiers should probably be excluded from wssize
)

#else

UNIT(sym,
   GGG['l'-'a']=ki(3);
   GGG['r'-'a']=ki(4);

   PT("a:42",             "0xaa",            "parse tree of a scalar assignment is its literal value")
   PT("s:2+1",            "('+';0x82;0x81)", "parse tree of a simple expression #1")
   PT("s+s",              "('+';s;s)",       "parse tree of a simple expression #2")
   PT("p:s*s",            "('*';s;s)",       "parse tree of a simple expression #3")

   _("s:2+2",             0,                 "scalar expr assignment")
   _("p:s*s",             0,                 "evaluate an expression with global references #1")
   _("l*r",               12,                "evaluate an expression with global references #2")
   _("p",                 16,                "p should have expected value")
)

#endif//SYMS

//:~
