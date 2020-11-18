#include"e.h"
typedef struct _pt {FP(x)FP(y)FP(t)FP(z)} PT;typedef PT*pt;ZFP(ONE)={1};ZFP(BP)={9};//!< base point
Z_ prp(S x){x[0]&=0xf8;x[31]&=0x7f;x[31]|=0x40;}Z_ ecp(pt d,pt s){dsn(d,s,SZ(PT));}

// mod 2^255-19 primitives
Z_ sel(S r,S x,S y,G c){X(Rg=-c&(Yg^Xg)^Xg)}//!< select, normalize, multiply, subtract, negate, inverse, xint, equal, add
Z_ nrm(S r){FP(y);H c=(r[31]>>7)*19;CORK;RDc;c=19;N(31,c+=Rg;Yg=c;c>>=8)c+=((H)r[31])-128;y[31]=c;sel(r,y,r,(c>>15)&1);}
Z_ mul(S r,S x,S y){V c=0;X(c>>=8;Nj(i+1,c+=Vx(j)*Vy(i-j))Nj(31-i,c+=Vx(i+1+j)*Vy(31-j)*38)Rg=c)RDCC}
Z_ sub(S r,S x,S y){V c=218;N(31,c+=VX-VY+65280;Rg=c;c>>=8)c+=Vx(31)-Vy(31);RDCC}
Z_ neg(S r,S x){    V c=218;N(31,c+=  -VX+65280;Rg=c;c>>=8)c-=Vx(31);       RDCC}
Z_ inv(S r,S x){FP(s)sq(s,x);RSX;N(248,SRSX)SRR,RSS,SRX,RSS;N(2,SRSX)}
Z_ mlc(S r,S x,V y){V c=0;X(c>>=8;c+=y*VX;Rg=c)CORK;c>>=7;c*=19;RDc}
ZG eql(S x,S y){G s=0;X(s|=Xg^Yg)s|=s>>4;s|=s>>2;s|=s>>1;R(s^1)&1;}
Z_ add(S r,S x,S y){H c=0;X(c>>=8;c+=HX+HY;Rg=c)CORK;RDC}

// dbl-1987-m3: a=x2+z2, b=x2-z2, c=x3+z3, d=x3-z3, da=d a, cb=c b, x5=z1(da+cb)^2, z5=x1(da-cb)^2
Z_ xadd(S x5,S z5,S x1,S z1,S x2,S z2,S x3,S z3){FP(da)FP(cb)FP(a)FP(b)
   add(a,x2,z2),sub(b,x3,z3),mul(da,a,b),sub(b,x2,z2),add(a,x3,z3),mul(cb,a,b),
   add(a,da,cb),sq(b,a),mul(x5,z1,b),sub(a,da,cb),sq(b,a),mul(z5,x1,b);}

// dbl-1987-m: x3=(x1^2-z1^2)^2, z3=4 x1 z1 (x1^2+(a x1 z1)+z1^2)
Z_ xdbl(S x3,S z3,S x1,S z1){FP(x1sq)FP(z1sq)FP(x1z1)FP(a)
   sq(x1sq,x1),sq(z1sq,z1),mul(x1z1,x1,z1),sub(a,x1sq,z1sq),sq(x3,a),
   mlc(a,x1z1,486662),add(a,x1sq,a),add(a,z1sq,a),mul(x1sq,x1z1,a),mlc(z3,x1sq,4);}

// scalar multiplication
Z_ xmul(S r,S q,S e){FP(xm)FP(xms)FP(zms)G zm[32]={1},xm1[32]={1},zm1[32]={0};dsn(xm,q,32);// p(m), p(m-1)
   _N(254,BIT(e)xadd(xm1,zm1,q,ONE,xm,zm,xm1,zm1),xdbl(xm,zm,xm,zm),xadd(xms,zms,xm1,zm1,xm,zm,q,ONE);// p(2m), p(2m-1)
   sel(xm1,xm1,xm,bit),sel(zm1,zm1,zm,bit),sel(xm,xm,xms,bit),sel(zm,zm,zms,bit))// bit?(p(2m+1),p(2m)):(p(2m),p(2m-1))
   inv(zm1,zm),mul(r,zm1,xm),nrm(r);}// freeze out projective coords

// x25519 ecdh
_ xkeygen(G sec[32],G pub[32],G rnd[32]){dsn(sec,rnd,32),prp(sec),xmul(pub,BP,sec),rfc(pub);}
_ xshared(G shr[32],G sec[32],G pub[32]){xmul(shr,pub,sec);}//_ xrandom(S x,V n){N(n,Xk=r8())}


#ifdef TST
#define TEST(s,v) O("%s ",s);N(NVEC(v),tst(&v[i]));
Z_ tst(tvec*v){
  S p,_e,exp;FP(e)FP(r)p=hex(v->p);_e=hex(v->e);exp=hex(v->r);
  dsn(e,_e,32),prp(e),rfc(p),xmul(r,p,e);G t=eql(r, exp);
  if(!t){O("  ");X(O("%02x",r[i]))O(" != ");X(O("%02x",exp[i]))O("\n");}
  FR(p)FR(_e)FR(exp)assert(t);}

I main(I c,char**v){
 TEST("rfc7748",rfc_vectors)

 // rfc7748 alice and bob
 FP(ask)FP(bsk)FP(apub)FP(bpub)
 S apri=hex(A_PRI),apub_exp=hex(A_PUB),bpri=hex(B_PRI),bpub_exp=hex(B_PUB),sha_exp=hex(AB_SK);
 prp(apri),prp(bpri),xmul(apub,BP,apri),xmul(bpub,BP,bpri),rfc(apub),rfc(bpub),
 xshared(ask,apri,bpub),xshared(bsk,bpri,apub);
 EQL(apub,apub_exp)EQL(bpub,bpub_exp)EQL(ask,bsk)EQL(ask,sha_exp)
 FR(apri)FR(apub_exp)FR(bpri)FR(bpub_exp)FR(sha_exp)

 srand(time(0));pcg32 prng={rand(),rand()|1}; FP(A)FP(B)FP(a)FP(b)FP(Ab)FP(Ba)FP(S1)FP(S2)
 O("prng");N(32,seed(S1)seed(S2)xkeygen(A,a,S1),xkeygen(B,b,S2),xshared(Ab,A,b),xshared(Ba,B,a);EQL(Ab,Ba))R O(" ok\n"),0;}

#endif

//:~
