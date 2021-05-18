#include"t.h"

#ifdef TST
#define TEST(s,v) O("%s ",s);N(NVEC(v),tst(&v[i]));
Z_ tst(tvec*v){
  S p,_e,exp;fp e,r;p=hex(v->p);_e=hex(v->e);exp=hex(v->r);
  dsn(e,_e,32),prp(e),rfc(p),xmul(r,p,e);G t=eql(r, exp);
  if(!t){O("  ");dump(r);O(" != ");dump(exp);nl();}
  FR(p)FR(_e)FR(exp)assert(t);}
#endif

I main(I c,char**v){srand(time(0));pcg32 prng={rand(),rand()|1};
#ifdef TST
 TEST("rfc7748",rfc_vectors)
 // rfc7748 alice and bob
 fp ask,bsk,apub,bpub;
 S apri=hex(A_PRI),apub_exp=hex(A_PUB),bpri=hex(B_PRI),bpub_exp=hex(B_PUB),sha_exp=hex(AB_SK);
 prp(apri),prp(bpri),xmul(apub,BP,apri),xmul(bpub,BP,bpri),rfc(apub),rfc(bpub),
 xshared(ask,apri,bpub),xshared(bsk,bpri,apub);
 EQL(apub,apub_exp)EQL(bpub,bpub_exp)EQL(ask,bsk)EQL(ask,sha_exp)
 FR(apri)FR(apub_exp)FR(bpri)FR(bpub_exp)FR(sha_exp)
 O("prng ");
 #define LAPS 32
#else
 #define LAPS 8
 #define EQL(x,y) if(memcmp(x,y,32)){O("mismatch\n");exit(1);}else{dump(x);nl();}
#endif

 fp A,B,a,b,Ab,Ba,S1,S2;
 N(LAPS,seed(S1)seed(S2)xkeygen(A,a,S1),xkeygen(B,b,S2),xshared(Ab,A,b),xshared(Ba,B,a);EQL(Ab,Ba))
 O("ok\n");

 I MSG_SIZE = 128;
 uint8_t*msg = hex("4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e1617424a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e1617424a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e1617424a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742");
 S SEED=hex("4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742");

 fp seed,pub;G sec[64],sig[64];dsn(seed,SEED,32);
 edkeygen(sec,pub,seed);
 edsign(sig,pub,sec,msg,MSG_SIZE);
 P(!edverify(sig,pub,msg,MSG_SIZE),O("failed on good plaintext\n"),-1)
 msg[1]^=0x10;P(edverify(sig,pub,msg,MSG_SIZE),O("failed on bad plaintext\n"),-1)
 O("ed25519 ok\n");
 R 0;}

//:~
