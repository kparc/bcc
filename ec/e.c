#include"e.h"
typedef struct _pt {FP(x)FP(y)FP(t)FP(z)} PT;typedef PT*pt;ZFP(ONE)={1};ZFP(BP)={9};//!< base point
PT NP={.x={0},.y={1,0},.t={0},.z={1,0}};Z_ prp(S x){x[0]&=0xf8;x[31]&=0x7f;x[31]|=0x40;}Z_ ecp(pt d,pt s){dsn(d,s,SZ(PT))}

// mod 2^255-19 primitives
Z_ sel(S r,S x,S y,G c){X(Rg=-c&(Yg^Xg)^Xg)}//!< select, normalize, product, constmult, subtract, negate, inverse. sum
Z_ nrm(S r){FP(y);H c=(r[31]>>7)*19;CORK;RDc;c=19;N(31,c+=Rg;Yg=c;c>>=8)c+=((H)r[31])-128;y[31]=c;sel(r,y,r,(c>>15)&1);}
Z_ prd(S r,S x,S y){V c=0;X(c>>=8;Nj(i+1,c+=Vx(j)*Vy(i-j))Nj(31-i,c+=Vx(i+1+j)*Vy(31-j)*38)Rg=c)RDCC}
Z_ sub(S r,S x,S y){V c=218;N(31,c+=VX-VY+65280;Rg=c;c>>=8)c+=Vx(31)-Vy(31);RDCC}
Z_ neg(S r,S x){    V c=218;N(31,c+=65280-VX;   Rg=c;c>>=8)c-=Vx(31);       RDCC}
Z_ inv(S r,S x){FP(s)prd(s,x,x);RSX;N(248,SRSX)SRR,RSS,SRX,RSS;N(2,SRSX)}
Z_ prc(S r,S x,V y){V c=0;X(c>>=8;c+=y*VX;Rg=c)CORK;c>>=7;c*=19;RDc}
Z_ sum(S r,S x,S y){H c=0;X(c>>=8;c+=HX+HY;Rg=c)CORK;RDC}

// group law
Z_ xadd(S x5,S z5,S x1,S z1,S x2,S z2,S x3,S z3){FP(da)FP(cb)FP(a)FP(b)
   sum(a,x2,z2),sub(b,x3,z3),prd(da,a,b),sub(b,x2,z2),sum(a,x3,z3),prd(cb,a,b),
   sum(a,da,cb),prd(b,a,a),prd(x5,z1,b),sub(a,da,cb),prd(b,a,a),prd(z5,x1,b);}
Z_ xdbl(S x3,S z3,S x1,S z1){FP(x1sq)FP(z1sq)FP(x1z1)FP(a)
   prd(x1sq,x1,x1),prd(z1sq,z1,z1),prd(x1z1,x1,z1),sub(a,x1sq,z1sq),prd(x3,a,a),
   prc(a,x1z1,486662),sum(a,x1sq,a),sum(a,z1sq,a),prd(x1sq,x1z1,a),prc(z3,x1sq,4);}

// scalar multiplication
Z_ xmul(S r,S q,S e){FP(xm)FP(xms)FP(zms)G zm[32]={1},xm1[32]={1},zm1[32]={0};dsn(xm,q,32);
   _N(254,BIT(e)xadd(xm1,zm1,q,ONE,xm,zm,xm1,zm1),xdbl(xm,zm,xm,zm),xadd(xms,zms,xm1,zm1,xm,zm,q,ONE),
    sel(xm1,xm1,xm,bit),sel(zm1,zm1,zm,bit),sel(xm,xm,xms,bit),sel(zm,zm,zms,bit))
   inv(zm1,zm),prd(r,zm1,xm),nrm(r);}

// x25519 ecdh
_ xkeygen(G sec[32],G pub[32],G s[32]){dsn(sec,s,32)prp(sec),xmul(pub,BP,sec);}
_ xshared(G shr[32],G sec[32],G pub[32]){xmul(shr,pub,sec);}//_ xrandom(S x,V n){N(n,Xk=r8())}

I main(I c,char**v){
  ZG S0[32]={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,
             0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52};
  ZG S1[32]={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,
             0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24};

 FP(sec1)FP(pub1)FP(s1)FP(shr1)dsn(s1,S0,32);//xrandom(s1,2);
 FP(sec2)FP(pub2)FP(s2)FP(shr2)dsn(s2,S1,32);//xrandom(s2,2);

 N(32,xkeygen(sec1,pub1,s1),xkeygen(sec2,pub2,s2),
  xshared(shr1,sec1,pub2),xshared(shr2,sec2,pub1);
  P(memcmp(shr1,shr2,32),O("mismatch\n"),-1))
  R O("x25519 ok\n"),0;}

//:~
