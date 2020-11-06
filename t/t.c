#include"t.h"

UNIT(env,           //<! basic sanity
   WS(0,            "workspace should initally be empty")

   K x=enm(ki(10)), //!< !10
     y=Li(x,5);     //!< list item

   WS(          64, "enm(10) should allocate 64 bytes")

   _(Ax,         0, "x should not be an atom")
   _(xr,         0, "x should have refcount 0")
   _(xt,        KI, "x should be an int vector")
   _(xn,        10, "x should have 10 items")

   _(Ay,        KI, "5th item should be an int")
   _(yi,         5, "5th item should be eq 5")

   r0(x)            //units bail if wss>0
)

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

UNIT(err,
   ERR("\\-f",       "f", "releasing a non-existent global should name-error")
   ERR("\\-A",       "A", "releasing an invalid identifier should name-error")
   ERR("x",          "x", "referencing an non-existent global should name-error")

   _("x:2",         NONE, "declare a test scalar")
   ERR("\\-x",     "nyi", "releasing a scalar should nyi")

   ERR("\\-x",     "nyi", "releasing a scalar should nyi")
)

UNIT(prs,//<! parse trees

   PT("#x",    "('#';x)",          "ptree of basic monadic op")

   PT("2*x",   "('\\';x)",         "2*x should translate to monadic left shift")
   PT("40+2",  "('+';0xa8;0x82)",  "simple inline expression")

   PT("#x",    "('#';x)",          "ptree of monadic op")
   PT("x+y",   "('+';x;y)",        "ptree of dyadic op")

   PT("c[i]$[x;1;2]", "('$';x;0x81;0x82)",          "declare a ctf function (omitted brackets)")
   _("\\-c",        NONE, "release a ctf function")
   WS(                 0, "parsing a bare ctf function shouldn't leak memory")

   PT("c[x]{$[x;1;2]}", "('{';('$';x;0x81;0x82))",  "declare a ctf function (omitted brackets)")
   _("\\-c",        NONE, "release a ctf function")

   PT("l[i]{r:0;N(x){r+:2};r}",  "('{';(':';r;0x80);('N';x;('{';(0xab;r;0x82)));r)", "loop function decl ptree")
   _("\\-l",   NONE, "release of l[] should return memory to the heap")

   //! bracket balancer
   //! TODO add nesting limit tests
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

   //! unit must pass (wss should be zero)
)
#undef pass
#undef fail

UNIT(fio,

   ERR("\\l t/blah.b",   "t/blah.b",      "missing file should report an error")
     _("\\l t/t.fio.b",   NONE,           "successful file compilation shouldn't report")
     _("#x",              100,            "loaded and compiled source should produce result")
     _("\\-x",            NONE,           "releasing the result of compilation should empty the ws")
)

#ifdef SYMS
extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack
K sym(I a),nme(K h);K*GG(K h),ssh(S s,UI n);V del(K h);

UNIT(sym,
   //! api test
   #define SYM "xyz"
   Ss=(S)SYM;       //!< set the parser tape to string SYM
   K b=sym(0),      //!< scan an identifier from the tape and return bucket (KS)
     x=nme(b),      //!< lookup literal symbol name string (KS)
    *v=GG(b);       //!< look up a pointer to the global sym value
   *v=ki(42);       //!< assign a value

   MEM(x,                 SYM,               xn)
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
   //EQ_VAL("prd",         "9",             "prd holds the correct vector value in the slot FIXME")

   W0=ws();                                 //! FIXME variable identifiers should probably be excluded from wssize
)

#include"../h.h"
//#define expmem(n) ((n)*(sizeof(pbkt)+1)+total)
#define expmem(n) ((n)*(sizeof(pbkt)))
UNIT(hsh,

   HT t=hnew("tst",2,10,djb2); //<! 4 slots, 10 split rounds

   I n=6,total=0;B bkts[n];
   S keys[]={"FKTABLE_CAT","cov","bmp","frameset","cos","fmt"},cset=csets[CHARSET_ALNUM]; //<! test vectors

   N(n,I sl;bkts[i]=hget(t,keys[i],sl=strlen(keys[i]));total+=sl;K x=(S)bkts[i]->k;
    MEM(xC,          keys[i],     xn))

   EQ_I(t->cnt,      n,           "htable should contain 6 elements")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_I(hdbg(t,0,0), 1408928309,  "htable checksum must match expected")

   N(n,if(bkts[i]!=hget(t,keys[i],strlen(keys[i])))FAIL("hash table must be stable"))
   EQ_I(t->cnt,      n,           "htable should still remain the same")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(t->mem,      expmem(n),   "htable mem usage should match expected")
   EQ_I(hdbg(t,0,0), 1408928309,  "htable checksum must match expected")

   N(strlen(cset)-1,total+=i+1;hget(t,cset+i,i+1));//uppercase only - cannot be any of keys[]
   EQ_I(t->mem,      expmem(n+strlen(cset)-1), "htable mem usage should match expected")
   EQ_I(hdbg(t,0,1), t->cnt,      "htable counter should match internal check")
   EQ_I(hdbg(t,0,0), 5999325069,  "htable checksum must match expected")

   TRUE(hload(t)     >0.9,        "htable load factor should be above 0.9")

   #ifdef TEST_HT_STRESS
   //! load factor under stress
   N(1000000,I rlen=rand()%100;S s=(S)malloc(rlen+1);total+=rlen;rnd_str(s,rlen,CHARSET_ALNUM);hget(t,s,rlen);free(s))//!< rand load
   EQ_I(hload(t)>0.8,         1,  "htable load factor should be above 0.8")O("HT: keys=%zu slots=%d load=%f\n",t->cnt,hslot(t),hload(t));
   #endif

   hdel(t); //!< release memory
)
#else

UNIT(sym,
   PT("a:42",            "0xaa",            "parse tree of a scalar assignment is its literal value")
   PT("s:2+1",           "('+';0x82;0x81)", "parse tree of a simple expression #1")
   PT("s+s",             "('+';s;s)",       "parse tree of a simple expression #2")

   _("s:2+1",             0,                "scalar expr assignment")
   _("s",                 3,                "parse tree of a simple expression #2")
)

#endif//SYMS

UNIT(nop,TRUE(1,"dummy test"))

TESTS(
   
#ifndef SYMS
   U(env)U(mem)U(err)U(prs)U(fio)
#else
   U(hsh)
   U(sym)
#endif

   X(nop)
)

//:~