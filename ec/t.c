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
 edkeygen(sec,pub,seed);edsign(sig,pub,sec,msg,MSG_SIZE);
 P(!edverify(sig,pub,msg,MSG_SIZE),O("failed on good plaintext\n"),-1)
 msg[1]^=0x10;P(edverify(sig,pub,msg,MSG_SIZE),O("failed on bad plaintext\n"),-1)
 O("ed25519 smoke test ok\n");

 /* rfc8072 7.1 */

 G TESTSIG[64];

 S PRI = hex("f5e5767cf153319517630f226876b86c"
             "8160cc583bc013744c6bf255f5cc0ee5");
 S PUB = hex("278117fc144c72340f67d0f2316e8386"
             "ceffbf2b2428c9c51fef7c597f1d426e");
 S SIG = hex("0aab4c900501b3e24d7cdf4663326a3a"
             "87df5e4843b2cbdb67cbf6e460fec350"
             "aa5371b1508f9f4528ecea23c436d94b"
             "5e8fcd4f681e30a6ac00a9704a188a03");
 V LEN =     1023;
 S MSG = hex("08b8b2b733424243760fe426a4b54908"
             "632110a66c2f6591eabd3345e3e4eb98"
             "fa6e264bf09efe12ee50f8f54e9f77b1"
             "e355f6c50544e23fb1433ddf73be84d8"
             "79de7c0046dc4996d9e773f4bc9efe57"
             "38829adb26c81b37c93a1b270b20329d"
             "658675fc6ea534e0810a4432826bf58c"
             "941efb65d57a338bbd2e26640f89ffbc"
             "1a858efcb8550ee3a5e1998bd177e93a"
             "7363c344fe6b199ee5d02e82d522c4fe"
             "ba15452f80288a821a579116ec6dad2b"
             "3b310da903401aa62100ab5d1a36553e"
             "06203b33890cc9b832f79ef80560ccb9"
             "a39ce767967ed628c6ad573cb116dbef"
             "efd75499da96bd68a8a97b928a8bbc10"
             "3b6621fcde2beca1231d206be6cd9ec7"
             "aff6f6c94fcd7204ed3455c68c83f4a4"
             "1da4af2b74ef5c53f1d8ac70bdcb7ed1"
             "85ce81bd84359d44254d95629e9855a9"
             "4a7c1958d1f8ada5d0532ed8a5aa3fb2"
             "d17ba70eb6248e594e1a2297acbbb39d"
             "502f1a8c6eb6f1ce22b3de1a1f40cc24"
             "554119a831a9aad6079cad88425de6bd"
             "e1a9187ebb6092cf67bf2b13fd65f270"
             "88d78b7e883c8759d2c4f5c65adb7553"
             "878ad575f9fad878e80a0c9ba63bcbcc"
             "2732e69485bbc9c90bfbd62481d9089b"
             "eccf80cfe2df16a2cf65bd92dd597b07"
             "07e0917af48bbb75fed413d238f5555a"
             "7a569d80c3414a8d0859dc65a46128ba"
             "b27af87a71314f318c782b23ebfe808b"
             "82b0ce26401d2e22f04d83d1255dc51a"
             "ddd3b75a2b1ae0784504df543af8969b"
             "e3ea7082ff7fc9888c144da2af58429e"
             "c96031dbcad3dad9af0dcbaaaf268cb8"
             "fcffead94f3c7ca495e056a9b47acdb7"
             "51fb73e666c6c655ade8297297d07ad1"
             "ba5e43f1bca32301651339e22904cc8c"
             "42f58c30c04aafdb038dda0847dd988d"
             "cda6f3bfd15c4b4c4525004aa06eeff8"
             "ca61783aacec57fb3d1f92b0fe2fd1a8"
             "5f6724517b65e614ad6808d6f6ee34df"
             "f7310fdc82aebfd904b01e1dc54b2927"
             "094b2db68d6f903b68401adebf5a7e08"
             "d78ff4ef5d63653a65040cf9bfd4aca7"
             "984a74d37145986780fc0b16ac451649"
             "de6188a7dbdf191f64b5fc5e2ab47b57"
             "f7f7276cd419c17a3ca8e1b939ae49e4"
             "88acba6b965610b5480109c8b17b80e1"
             "b7b750dfc7598d5d5011fd2dcc5600a3"
             "2ef5b52a1ecc820e308aa342721aac09"
             "43bf6686b64b2579376504ccc493d97e"
             "6aed3fb0f9cd71a43dd497f01f17c0e2"
             "cb3797aa2a2f256656168e6c496afc5f"
             "b93246f6b1116398a346f1a641f3b041"
             "e989f7914f90cc2c7fff357876e506b5"
             "0d334ba77c225bc307ba537152f3f161"
             "0e4eafe595f6d9d90d11faa933a15ef1"
             "369546868a7f3a45a96768d40fd9d034"
             "12c091c6315cf4fde7cb68606937380d"
             "b2eaaa707b4c4185c32eddcdd306705e"
             "4dc1ffc872eeee475a64dfac86aba41c"
             "0618983f8741c5ef68d3a101e8a3b8ca"
             "c60c905c15fc910840b94c00a0b9d0");

 O("rfc8032_test1024_verify: %s\n",edverify(SIG,PUB,MSG,LEN)?"ok":"FAIL");
 edsign(TESTSIG,PUB,PRI,MSG,LEN);
 O("rfc8032_test1024_sign: %s\n", memcmp(TESTSIG,SIG,64)?"FAIL":"ok");

 PRI = hex("833fe62409237b9d62ec77587520911e"
           "9a759cec1d19755b7da901b96dca3d42");
 PUB = hex("ec172b93ad5e563bf4932c70e1245034"
           "c35467ef2efd4d64ebf819683467e2bf");
 SIG = hex("dc2a4459e7369633a52b1bf277839a00"
           "201009a3efbf3ecb69bea2186c26b589"
           "09351fc9ac90b3ecfdfbc7c66431e030"
           "3dca179c138ac17ad9bef1177331a704");
 LEN = 64;
 MSG = hex("ddaf35a193617abacc417349ae204131"
           "12e6fa4e89a97ea20a9eeee64b55d39a"
           "2192992a274fc1a836ba3c23a3feebbd"
           "454d4423643ce80e2a9ac94fa54ca49f");

 O("rfc8032_testABC_verify: %s\n",edverify(SIG,PUB,MSG,LEN)?"ok":"FAIL");
 edsign(TESTSIG,PUB,PRI,MSG,LEN);
 O("rfc8032_testABC_sign: %s\n", memcmp(TESTSIG,SIG,64)?"FAIL":"ok");

 PRI = hex("c5aa8df43f9f837bedb7442f31dcb7b1"
           "66d38535076f094b85ce3a2e0b4458f7");
 PUB = hex("fc51cd8e6218a1a38da47ed00230f058"
           "0816ed13ba3303ac5deb911548908025");
 SIG = hex("6291d657deec24024827e69c3abe01a3"
           "0ce548a284743a445e3680d7db5ac3ac"
           "18ff9b538d16f290ae67f760984dc659"
           "4a7c15e9716ed28dc027beceea1ec40a");
 LEN = 2;
 MSG = hex("af82");

 O("rfc8032_test3_verify: %s\n",edverify(SIG,PUB,MSG,LEN)?"ok":"FAIL");
 edsign(TESTSIG,PUB,PRI,MSG,LEN);
 O("rfc8032_test3_sign: %s\n", memcmp(TESTSIG,SIG,64)?"FAIL":"ok");

 PRI = hex("4ccd089b28ff96da9db6c346ec114e0f"
           "5b8a319f35aba624da8cf6ed4fb8a6fb");
 PUB = hex("3d4017c3e843895a92b70aa74d1b7ebc"
           "9c982ccf2ec4968cc0cd55f12af4660c");
 SIG = hex("92a009a9f0d4cab8720e820b5f642540"
           "a2b27b5416503f8fb3762223ebdb69da"
           "085ac1e43e15996e458f3613d0f11d8c"
           "387b2eaeb4302aeeb00d291612bb0c00");
 LEN = 1;
 MSG = hex("72");

 O("rfc8032_test2_verify: %s\n",edverify(SIG,PUB,MSG,LEN)?"ok":"FAIL");
 edsign(TESTSIG,PUB,PRI,MSG,LEN);
 O("rfc8032_test2_sign: %s\n", memcmp(TESTSIG,SIG,64)?"FAIL":"ok");

 PRI = hex("9d61b19deffd5a60ba844af492ec2cc4"
           "4449c5697b326919703bac031cae7f60");
 PUB = hex("d75a980182b10ab7d54bfed3c964073a"
           "0ee172f3daa62325af021a68f707511a");
 SIG = hex("e5564300c360ac729086e2cc806e828a"
           "84877f1eb8e5d974d873e06522490155"
           "5fb8821590a33bacc61e39701cf9b46b"
           "d25bf5f0595bbe24655141438e7a100b");
 LEN = 0;MSG = hex("");

 O("rfc8032_test1_verify: %s\n",edverify(SIG,PUB,MSG,LEN)?"ok":"FAIL");
 edsign(TESTSIG,PUB,PRI,MSG,LEN);
 O("rfc8032_test1_sign: %s\n", memcmp(TESTSIG,SIG,64)?"FAIL":"ok");


 R 0;}

//:~
