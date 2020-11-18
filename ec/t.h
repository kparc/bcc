#include<stdlib.h>//malloc free srand rand
#include<stdio.h>//printf
#include<assert.h>//assert
#include<time.h>//time
#include"e.h"

#define O printf
#define nl() O("\n")
#define dump(x) X(O("%02x",x[i]))
#define seed(x) N(8,((V*)x)[i]=pcg(&prng))
typedef struct{UJ state;UJ inc;}pcg32;
static V pcg(pcg32*r){ //<! do not use in prod
    UJ old=r->state;r->state=old*6364136223846793005ULL+(r->inc|1);//!< advance
    V xorsh=((old>>18u)^old)>>27u,rot=old>>59u;//!< XSH RR, uses old state for max ILP
    R(xorsh>>rot)|(xorsh<<((-rot)&31));}

#ifdef TST
extern fp ONE,BP;//base point
#define FR(x) free(x);
#define EQL(x,y) assert(eql(x,y));
#define NVEC(x) (SZ(x)/SZ(x[0]))
#define XI(p) (*(p) <= '9'? (*(p)- '0'): *(p) <= 'F'? (*(p)-'A'+10):(*(p)-'a'+10))
#define xtoi(p) ((XI(p)*16)+XI((p)+1))
static S hex(char*x){char*s;S b=malloc(strlen((char*)x)/2+1);I l=0;for(s=x;*s;s+=2){((S)b)[l++]=xtoi(s);}R b;}

#define BASE_POINT "0900000000000000000000000000000000000000000000000000000000000000"
#define ZERO_POINT "0000000000000000000000000000000000000000000000000000000000000000"

typedef struct{char*p;char*e;char*r;}tvec;
static tvec
 rfc_vectors[] = {//rfc7748
 { BASE_POINT                                                       , BASE_POINT                                                       ,"422c8e7a6227d7bca1350b3e2bb7279f7897b87bb6854b783c60e80311ae3079"},
 { BASE_POINT                                                       ,"a8abababababababababababababababababababababababababababababab6b","e3712d851a0e5d79b831c5e34ab22b41a198171de209b8b8faca23a11c624859"},
 { BASE_POINT                                                       ,"c8cdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcdcd4d","b5bea823d9c9ff576091c54b7c596c0ae296884f0e150290e88455d7fba6126f"},
 {"e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552"},
 {"e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493","4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d","95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957"},
 {"e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a413","4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d","95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957"},
 {"cdeb7a7c3b41b8ae1656e3faf19fc46ada098deb9c32b1fd866205165f49b880","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","7ce548bc4919008436244d2da7a9906528fe3a6d278047654bd32d8acde9707b"},
 {"4c9c95bca3508c24b1d0b1559c83ef5b04445cc4581c8e86d8224eddd09f11d7","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","e17902e989a034acdf7248260e2c94cdaf2fe1e72aaac7024a128058b6189939"},
 {"d9ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","ea6e6ddf0685c31e152d5818441ac9ac8db1a01f3d6cb5041b07443a901e7145"},
 {"daffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","845ddce7b3a9b3ee01a2f1fd4282ad293310f7a232cbc5459fb35d94bccc9d05"},
 {"dbffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4","6989e2cb1cea159acf121b0af6bf77493189c9bd32c2dac71669b540f9488247"},
 { ZERO_POINT                                                       ,"a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"0100000000000000000000000000000000000000000000000000000000000000","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"e0eb7a7c3b41b8ae1656e3faf19fc46ada098deb9c32b1fd866205165f49b800","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"5f9c95bca3508c24b1d0b1559c83ef5b04445cc4581c8e86d8224eddd09f1157","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"ecffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff7f","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"edffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff7f","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       },
 {"eeffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff7f","a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4", ZERO_POINT                                                       }};

// rfc7748
char*A_PRI="77076d0a7318a57d3c16c17251b26645df4c2f87ebc0992ab177fba51db92c2a",//alice
    *A_PUB="8520f0098930a754748b7ddcb43ef75a0dbf3a0d26381af4eba4a98eaa9b4e6a",
    *B_PRI="5dab087e624a8a4b79e17f8b83800ee66f3bb1292618b6fd1c2f8b27ff88e0eb",//bob
    *B_PUB="de9edb7d7b7dc1b4d35b61c2ece435373f8343c85b78674dadfc7e146f882b4f",
    *AB_SK="4a5d9d5ba4ce2de1728e3bf480350f25e07e21c947d19e3376f09b3c1e161742";//shared

#endif

//:~
