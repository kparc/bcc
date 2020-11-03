#include"t.h"

UNIT(smoke,//<! basic sanity
   WS(0,          "workspace should initally be empty")

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   WS(        64, "enm(10) should allocate 64 bytes")

   _(Ax,       0, "x should not be an atom")
   _(xr,       0, "x should have refcount 0")
   _(xt,      KI, "x should be an int vector")
   _(xn,      10, "x should have 10 items")

   _(Ay,      KI, "5th item should be an int")
   _(yi,       5, "5th item should be eq 5")

   r0(x);    //units bail if wss>0
)

UNIT(malloc,
   _("2+2",    4, "basic ex #1")
   _("2=2",    1, "basic ex #2")

   //_("\\f", "!`", "global function namespace should be empty FIXME")
   //_("\\v", "!`", "global variable namespace should be empty FIXME")

   WS0("non-assigning repl expressions shouldn't leak memory")

   _("f[ii]{x+y}",  NONE, "declare a global function")
   WS(80, "workspace usage should be 80 bytes")

   _("f[40;2]",       42, "function calls should work as expected")
   WS0("calling a function shouldn't leak memory")

   _("f[ii]{x-y}",  NONE, "reassign an exisiting function")
   WS0("reassigning a global function shouldn't leak memory")

   _("f[40;2]",       38, "reassigned function should work as expected")

   _("\\-f",        NONE, "releasing existing global function should be ok")

   _("x:!10",       NONE, "declare a global vector")
   _("\\-x",        NONE, "releasing existing global vector should be ok")

   //_("c[i]$[x;1;2]",NONE, "declare a ctf function (omitted brackets)")
   //_("\\-c",        NONE, "release a bare ctf function")
   //WS(0, "releasing a bare ctf function shouldn't leak memory FIXME")
)

UNIT(errors,
   ERR("\\-f",       "f", "releasing a non-existent global should name-error")
   ERR("\\-A",       "A", "releasing an invalid identifier should name-error")
   ERR("x",          "x", "referencing an non-existent global should name-error")
   _("x:2",         NONE, "declare a test scalar")
   ERR("\\-x",     "nyi", "releasing a scalar should nyi")
)

UNIT(parser,//<! parse trees
   PT("#x",    "('#';x)",          "ptree of basic monadic op")

   PT("2*x",   "('\\';x)",         "2*x should translate to monadic left shift")
   PT("40+2",  "('+';0xa8;0x82)",  "simple inline expression")

   PT("#x",    "('#';x)",          "ptree of monadic op")
   PT("x+y",   "('+';x;y)",        "ptree of dyadic op")

   PT("c[i]$[x;1;2]", "('$';x;0x81;0x82)",          "declare a ctf function (omitted brackets)")
   _("\\-c",        NONE, "release a ctf function")
   WS(0, "parsing a bare ctf function shouldn't leak memory")

   PT("c[x]{$[x;1;2]}", "('{';('$';x;0x81;0x82))",  "declare a ctf function (omitted brackets)")
   _("\\-c",        NONE, "release a ctf function")

   PT("l[i]{r:0;N(x){r+:2};r}",  "('{';(':';r;0x80);('N';x;('{';(0xab;r;0x82)));r)", "loop function decl ptree")
   _("\\-l",   NONE, "release of l[] should return memory to the heap")
)

UNIT(brackets,
   #define pass(s) _(bb(s),0,s)
   #define fail(s,exp) {S b=bb(s);_(exp==(b?(C)*b:(C)b),1,exp)}
   pass("")
   pass("\n")
   pass("[]")
   pass("[]\n")
   pass("[\"asdf]asdf{\"]")
   pass("$[x&1;(\\x)+x+1;/x]")
   fail("[}]",'}')
   fail("[\"]",'\"')
   fail("[\"\"",0)
   //! TODO add nesting limit tests
)
#undef pass
#undef fail

UNIT(disk,
   ERR("\\l t/blah.b",   "t/blah.b",      "missing file should report an error")
     _("\\l t/t.b",       NONE,           "successful file compilation shouldn't report")
     _("#x",              100,            "loaded and compiled source should produce result")
     _("\\-x",            NONE,           "releasing the result of compilation should empty the ws")
)

UNIT(shortsyms,
   PT("a:42",   "0xaa",  "parse tree of a scalar assignment is its literal value")
   PT("s:2+1",           "('+';0x82;0x81)", "parse tree of a simple expression #1")
   PT("s+s",             "('+';s;s)",       "parse tree of a simple expression #2")

   _("s:2+1",             0,                "scalar expr assignment")
   _("s",                 3,                "parse tree of a simple expression #2")

)

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack
K sym(I a),nme(K h);K*GG(K h),hsh(S s,UI n);V del(K h);
UNIT(syms,
   #define SYM "xyz"

   Ss=(S)SYM;       //!< set the parser tape to string SYM
   K h=sym(0),       //!< scan an identifier from the tape and return hash (KS)
     x=nme(h),      //!< lookup literal symbol name string (KC)
    *v=GG(h);       //!< look up a pointer to the global sym value slot
   *v=ki(42);       //!< assign a value

   //K g=*GG(hsh(SYM,strlen(SYM)));os(SYM);o(g);
   r0(x);del(h);    //!< cleanup

   PT("ccall+go_fn+42",  "('+';`ccall;('+';`go_fn;0xaa))",   "basic multichar identifiers are supported by parser")
   PT("x+Not+Wha",       "('+';`x;('+';`Not;`Wha))",         "special case: if leading N|W is not followed by (, force class to identifier")

   PT("asdf:42",         "0xaa",            "parse tree of a scalar assignment is its literal value")
   PT("sum:2+1",         "('+';0x82;0x81)", "parse tree of a simple expression #1")
   PT("sum+sum",         "('+';`sum;`sum)", "parse tree of a simple expression #2")
   //PT("fun[i]{x}",       "asdf",            "function declaration FIXME segv")

   _("til:!3",            0,                "vector expr assignment")
   _("sum:2+1",           0,                "scalar expr assignment")
   _("prd:sum*sum",       0,                "product of two global variables")
   //_("fun[i]{x}",         0,                "function declaration FIXME segv")

   //_("sum",               3,                "get value of a global variable FIXME")

   EQ_SYM("sum",         "3",      "sum holds the correct scalar value in the htable slot")
   EQ_SYM("til",     "0 1 2",      "til holds the correct vector value in the htable slot")

   //EQ_VAL("prd",         "9",      "prd holds the correct vector value in the slot FIXME")

   W0=ws();        //! FIXME variable identifiers should probably be excluded from wssize
)


TESTS(

#ifndef SYMS
   RUN(smoke)RUN(malloc)RUN(errors)RUN(brackets)
   RUN(parser)
   RUN(disk)
   RUN(shortsyms)
#else
   RUN(syms)
#endif
)

//:~