//#define UNITY_INCLUDE_DOUBLE
#include"lib/unity.h"
#include"../a.h"
#include<stdlib.h>//rand

//#define TEST_HT_STRESS

#define NONE 0
#define ES(x) ((S)(-1UL>>16&(J)x))

ZJ W0=0,Wprev;//!< wssize

extern V init();K1(enm);K1(pr);K Li(K x,I i),sS(I c,K x);S1(es);K pcle(S tp,I dbg);K se(K x,K pt);K bb(S x);//!< NB never forget signatures

C xQ(K x){R QQ==A(x);}ZS str(K x){R(S)es(x);}ZK ptree(S s){K x=pcle(s,1);/*os("PTREE"),o(x);*/R X0(jc(se(x,1),0));}
//ZK out(S x){R pr(es(x));}
V setUp(V){}V tearDown(V){}//!< before/after each test

#define TYPE(expr) (_Generic((expr), \
  char: 'C', short: 'H', int: 'I', long: 'L', \
  long long: 'J', unsigned char*: 'K', \
  float: 'E', double: 'F', \
  void*: '_', char*: 'S', default: '?'))

#define EQ_I(act,exp,msg) TEST_ASSERT_EQUAL_INT_MESSAGE(exp,act,msg);
#define EQ_F(act,exp,msg) TEST_ASSERT_EQUAL_FLOAT_MESSAGE(exp,act,msg);
#define EQ_S(act,exp,msg) TEST_ASSERT_EQUAL_STRING_MESSAGE(exp,str(act),msg);
//#define STR(act,exp,msg) TEST_ASSERT_EQUAL_STRING_MESSAGE(exp,act,msg);

#define SYMVAL(s) (S)se(hget(GT,s,strlen(s))->v,0)
#define EQ_SYM(act,exp,msg) {S x=SYMVAL(act);\
 TEST_ASSERT_MESSAGE(!memcmp(x,exp,MN(strlen(exp),xn)), "variable value should match expected");}

#define FAIL(msg) TEST_ASSERT_MESSAGE(0,msg)
#define TRUE(cnd,msg) TEST_ASSERT_MESSAGE((cnd),msg);
#define MEM(act,exp,n) TEST_ASSERT_EQUAL_MEMORY(act,exp,n);

//#define EQ_NL(act,msg)    TEST_ASSERT_MESSAGE(out(act)==NL,msg);

#define ASSERT(act,exp,msg) S(TYPE(exp),\
  C('S',EQ_S(act,exp,msg))    \
  C('I',EQ_I(I(act),exp,msg)) \
  C('L',EQ_I(I(act),exp,msg)) \
  ,TEST_ASSERT_MESSAGE(0,"unknown type"))

#define _(act,exp,msg,cleanup...) Wprev=ws();if(TYPE(act)=='S'){K x=str((S)(J)(act));\
  if(xQ(x)){TEST_ASSERT_EQUAL_STRING_MESSAGE("ok",ES(x),"unexpected error");r0(x);}\
  else{ASSERT(X0(x),exp,msg)}}else{ASSERT(act,exp,msg)};cleanup;

#define ERR(act,exp,msg,cleanup...) Wprev=ws();{K x=str((S)(J)(act));\
  if(!xQ(x)){TEST_ASSERT_EQUAL_STRING_MESSAGE(exp,"ok","expected an error");r0(x);}\
  else{TEST_ASSERT_EQUAL_STRING_MESSAGE(exp,ES(x),msg);r0(0);}cleanup;}


#define PT(act,exp,msg) {Wprev=ws();K x=ptree(act);TEST_ASSERT_EQUAL_STRING_MESSAGE(exp,(S)x,msg);r0(x);}
#define WS0(msg)           {TEST_ASSERT_EQUAL_INT_MESSAGE(0,ws(),msg);}
#define WSSAME(msg)        {TEST_ASSERT_EQUAL_INT_MESSAGE(0,ws()-Wprev,msg);}
#define WS(exp,msg)        {TEST_ASSERT_EQUAL_INT_MESSAGE(exp,ws(),msg);}

#define ___  TEST_ASSERT_MESSAGE(0,"STOP");

#define TESTS(units...) V hsegv();I main(I a,char**c){hsegv(),init();UNITY_BEGIN();units;R UNITY_END();}

//#define UNIT(name,tests...) V test##_##name(V){W0=ws();tests;WS(0,"test unit shouldn't leak memory")};
//#define RUN(unit) RUN_TEST(test##_##unit);

#define UNIT(name,tests...) V skip##_##name(V){TEST_IGNORE();};V unit##_##name(V){W0=ws();tests;WS(W0,"test unit shouldn't leak memory")};

#define U(name) extern V unit##_##name(V);RUN_TEST(unit##_##name);
#define X(name) extern V skip##_##name(V);RUN_TEST(skip##_##name);


enum charsets { CHARSET_ALNUM, CHARSET_AZaz, CHARSET_AZ, CHARSET_az};
ZS csets[4]={
 (S)"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
 (S)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
 (S)"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
 (S)"abcdefghijklmnopqrstuvwxyz"
};

#ifdef TEST_HT_STRESS
ZS rnd_str(S dest,size_t size,C cs){
  P(4<cs,(S)0)S dict=csets[cs];size_t dictlen=strlen(dict);
  N(size,size_t key=rand()%(dictlen-1);dest[i]=dict[key])
  dest[size]=0;R dest;}
#endif

#define _GNU_SOURCE 1 //!<REG_RIP
#define _XOPEN_SOURCE //!< macos
#include<execinfo.h>
#include<signal.h>
#include<string.h>
#include<ucontext.h>
#ifdef __APPLE__
#define osg(s) psignal(si->si_signo,s)
#define RIP ((ucontext_t*)c)->uc_mcontext->__ss.__rip
#else
#define osg(s) psiginfo(si,s)
//#define RIP ((ucontext_t *)c)->uc_mcontext->__ss.__rip
#define RIP 0x0
#endif
V stack(I d,I o){V*arr[d];I sz=backtrace(arr, d);char**frames=backtrace_symbols(arr,sz);N(sz-o,os(frames[i+o]));nl();free(frames);}//!< depth+offset
V handler(I sig,siginfo_t*si,V*c){nl();if(si->si_signo-SIGABRT){nl(),O("rip 0x%llx",RIP),osg(""),nl();}osg("");stack(10,0),exit(1);}
V hsegv(){struct sigaction a;memset(&a,0,sizeof(struct sigaction));a.sa_flags=SA_SIGINFO;a.sa_sigaction=handler;sigaction(SIGSEGV,&a,0);sigaction(SIGABRT,&a,0);}

//!attic

//V __llvm_profile_enable_continuous_mode(V);I __llvm_profile_is_continuous_mode_enabled(V),__llvm_profile_write_file(V);
//        0        1         2         3        4         5       6         7          8        9          10        11
//enum kerr{ERR_ZERO,ERR_CARET,ERR_PARSE,ERR_RANK,ERR_VALUE,ERR_NYI,ERR_CLASS,ERR_LENGTH,ERR_TYPE,ERR_DOMAIN,ERR_STACK,ERR_LIMIT};
//char* err[]={"zero",  "caret",  "parse",  "rank",  "value",  "nyi",  "class",  "length",  "type",  "domain",  "stack",  "limit"};
//unsigned long: "unsigned long",unsigned int: "unsigned int",signed char: "signed char",long: "long",long double: "long double"
//I k_init(I n,char**a);K1 e0,w_,ev;ZS str(K x){R(S)vc(wv(0,x),0);}long xT(K x){R(I)xt;}J xA(K x){R Ax;}
//ZI WS(){I r=_i(w_(0));R 0>r?0:r;}ZS se(I e){R(S)err[e];}ZK out(S s){K x;U(x=p9(s));R X0(e0(x));}
//#define $(act,msg) _(act,act,msg)
//printf("cont mode enabled: %d\n", __llvm_profile_is_continuous_mode_enabled());\
//__llvm_profile_enable_continuous_mode();
//ZC arg[32]={0};init(0,(char**)(S[]){(S)"b"});
//if(a==2){strncpy(arg,c[1],31);arg[31]='\0';memset(c[1],0,32);c=0;}

//:~