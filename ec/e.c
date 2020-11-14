#include"e.h"
typedef void _;typedef unsigned short H;typedef unsigned int V;typedef unsigned char*S,G;typedef int I;typedef struct _pt {FP(x)FP(y)FP(t)FP(z)} PT;typedef PT*pt;ZFP(ONE)={1};
ZFP(EK)={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24};ZFP(XB)={9};
Z_ ecp(pt d,pt s){memcpy(d,s,SZ(*d));}Z_ prp(S x){x[0]&=0xf8;x[31]&=0x7f;x[31]|=0x40;}PT EN={.x={0},.y={1,0},.t={0},.z={1,0}};static S cpy(S x,S a){R memcpy((S)x,(S)a,32);}

Z_ sel(S r,S x,S y,G c){X(Rg=-c&(Yg^Xg)^Xg)}
Z_ nrm(S r){FP(y);H c=(r[31]>>7)*19;CORK;RDc;c=19;N(31,c+=Rg;Yg=c;c>>=8)c+=((H)r[31])-128;y[31]=c;sel(r,y,r,(c>>15)&1);}
Z_ sum(S r,S x,S y){H c=0;X(c>>=8;c+=HX+HY;Rg=c)CORK;RDC}

Z_ mul(S r,S x,S y){V c=0;X(c>>=8;Nj(i+1,c+=Vx(j)*Vy(i-j))Nj(31-i,c+=Vx(i+1+j)*Vy(31-j)*38)Rg=c)RDCC}
Z_ mlc(S r,S x,V y){V c=0;X(c>>=8;c+=y*VX;Rg=c)CORK;c>>=7;c*=19;RDc}
Z_ sub(S r,S x,S y){V c=218;N(31,c+=VX-VY+65280;Rg=c;c>>=8)c+=Vx(31)-Vy(31);RDCC}
Z_ neg(S r,S x){    V c=218;N(31,c+=65280-VX;   Rg=c;c>>=8)c-=Vx(31);       RDCC}
Z_ inv(S r,S x){FP(s)mul(s,x,x);RSX;N(248,SRSX)SRR,RSS,SRX,RSS;N(2,SRSX)}

Z_ smm(pt p,pt p1,pt p2){FPah;sub(c,P1y,P1x),sub(d,P2y,P2x),mul(a,c,d),sum(c,P1y,P1x),sum(d,P2y,P2x),mul(b,c,d),
   mul(d,P1t,P2t),mul(c,d,EK),mul(d,P1z,P2z),sum(d,d,d),sub(e,b,a),sub(f,d,c),sum(g,d,c),sum(h,b,a);XYTZ3}
Z_ dbl(pt p,pt p1){FPah;mul(a,P1x,P1x),mul(b,P1y,P1y),mul(c,P1z,P1z),sum(c,c,c),sum(f,P1x,P1y),mul(e,f,f),
   sub(e,e,a),sub(e,e,b),sub(g,b,a),sub(f,g,c),neg(h,b),sub(h,h,a);XYTZ3}
Z_ mlt(pt out,pt p,S e){PT r,s;ecp(&r,&EN);_N(256,BIT(e);dbl(&r,&r);smm(&s,&r,p);
   SEL(x)SEL(y)SEL(z)SEL(t))ecp(out,&r);}
Z_ xdbl(S x3,S z3,S x1,S z1){FP(x1sq)FP(z1sq)FP(x1z1)FP(a)
   mul(x1sq,x1,x1),mul(z1sq,z1,z1),mul(x1z1,x1,z1),sub(a,x1sq,z1sq),mul(x3,a,a),
   mlc(a,x1z1,486662),sum(a,x1sq,a),sum(a,z1sq,a),mul(x1sq,x1z1,a),mlc(z3,x1sq,4);}
Z_ xadd(S x5,S z5,S x1,S z1,S x2,S z2,S x3,S z3){FP(da)FP(cb)FP(a)FP(b)
   sum(a,x2,z2),sub(b,x3,z3),mul(da,a,b),sub(b,x2,z2),sum(a,x3,z3),mul(cb,a,b),
   sum(a,da,cb),mul(b,a,a),mul(x5,z1,b),sub(a,da,cb),mul(b,a,a),mul(z5,x1,b);}
Z_ xmul(S r,S q,S e){FP(xm)FP(xms)FP(zms)G zm[32]={1},xm1[32]={1},zm1[32]={0};cpy(xm,q);
   _N(254,BIT(e)xadd(xm1,zm1,q,ONE,xm,zm,xm1,zm1),xdbl(xm,zm,xm,zm),xadd(xms,zms,xm1,zm1,xm,zm,q,ONE),
    sel(xm1,xm1,xm,bit),sel(zm1,zm1,zm,bit),sel(xm,xm,xms,bit),sel(zm,zm,zms,bit))
   inv(zm1,zm),mul(r,zm1,xm),nrm(r);}

_ xkeygen(G sec[32],G pub[32],G s[32]){cpy(sec,s),prp(sec),xmul(pub,XB,sec);}
_ xshared(G shr[32],G sec[32],G pub[32]){xmul(shr,pub,sec);}//_ xrandom(S x,V n){N(n,Xk=r8())}

I main(I c,char**v){
  ZG S0[32]={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,
             0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52};
  ZG S1[32]={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,
             0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24};

FP(sec1)FP(pub1)FP(s1)FP(shr1)cpy(s1,S0);//xrandom(s1,2);
FP(sec2)FP(pub2)FP(s2)FP(shr2)cpy(s2,S1);//xrandom(s2,2);

N(32,xkeygen(sec1,pub1,s1);xkeygen(sec2,pub2,s2),
 xshared(shr1,sec1,pub2),xshared(shr2,sec2,pub1);
 P(memcmp(shr1,shr2,32),O("mismatch\n"),-1))
 R O("x25512 ok\n"),0;}

//:~
