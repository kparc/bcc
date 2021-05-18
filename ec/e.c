#include"e.h"

#include<stdio.h>
#include<stdlib.h>

ZG min(I x,I y){R x<y?x:y;}

ZFP(ZERO)={0};ZFP(ONE)={1};ZFP(BP)={9};ZEP(EN)={.x={0},.y={1,0},.t={0},.z={1,0}};ZEP(EB)={.z={1,0}, //!< x25519/ed25519 base and neutral points
.x={0x1a,0xd5,0x25,0x8f,0x60,0x2d,0x56,0xc9,0xb2,0xa7,0x25,0x95,0x60,0xc7,0x2c,0x69,0x5c,0xdc,0xd6,0xfd,0x31,0xe2,0xa4,0xc0,0xfe,0x53,0x6e,0xcd,0xd3,0x36,0x69,0x21},
.y={0x58,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66},
.t={0xa3,0xdd,0xb7,0xa5,0xb3,0x8a,0xde,0x6d,0xf5,0x52,0x51,0x77,0x80,0x9f,0xf0,0x20,0x7d,0xe3,0xab,0x64,0x8e,0x4e,0xea,0x66,0x65,0x76,0x8b,0xd7,0x0f,0x5f,0x87,0x67}};
ZFP(ED)={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52}; //!< d
ZFP(EK)={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24}; //!< k=2d
ZFP(EO)={0xed,0xd3,0xf5,0x5c,0x1a,0x63,0x12,0x58,0xd6,0x9c,0xf7,0xa2,0xde,0xf9,0xde,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10}; //!< order

// GF(2^255-19) load, prepare, select, normalize, multiply, mult*const, equal, subtract, negate, add, reciprocate, 2^252-3, sqrt
Z_ loa(S r,V c){X(Rg=0)N(SZ(c),Rg=c;c>>=8)}ZZ prp(S r){*r&=0xf8,RFC,r[31]|=0x40;}Z_ sel(S r,S x,S y,G c){X(Rg=-c&(Yg^Xg)^Xg)}
Z_ nrm(S r){fp y;H c=(r[31]>>7)*19;RFC;RDc;c=19;N(31,c+=Rg;Yg=c;c>>=8)c+=((H)r[31])-128;y[31]=c;sel(r,y,r,(c>>15)&1);}
Z_ mul(S r,S x,S y){V c=0;X(c>>=8;Nj(i+1,c+=Vx(j)*Vy(i-j))Nj(31-i,c+=Vx(i+1+j)*Vy(31-j)*38)Rg=c)RDCC}
Z_ mlc(S r,S x,V y){V c=0;X(c>>=8;c+=y*VX;Rg=c)RFC;c>>=7;c*=19;RDc}
ZG eql(S x,S y){G s=0;X(s|=Xg^Yg)s|=s>>4;s|=s>>2;s|=s>>1;R(s^1)&1;}
Z_ sub(S r,S y,S x){SUB(VY,Vy(31))}Z_ neg(S r,S x){SUB(0,0)}
Z_ add(S r,S x,S y){H c=0;X(c>>=8;c+=HX+HY;Rg=c)RFC;RDC}
Z_ inv(S r,S x){fp s;sq(s,x);RSX;N(248,sq(s,r),RSX)sq(s,r),sq(r,s),SRX,sq(r,s);N(2,sq(s,r),RSX)}
Z_ exp(S r,S x,S s){ sq(r,x);SRX;N(248,sq(r,s),SRX)sq(r,s),sq(s,r),RSX;}
Z_ sqt(S r,S a){fp v,i,x,y;mlc(x,a,2),exp(v,x,y),sq(y,v),mul(i,x,y),loa(y,1),sub(i,i,y),mul(x,v,a),mul(r,x,i);}

// dbl-1987-m3: a=x2+z2, b=x2-z2, c=x3+z3, d=x3-z3, da=d a, cb=c b, x5=z1(da+cb)^2, z5=x1(da-cb)^2
Z_ xadd(S x5,S z5,S x1,S z1,S x2,S z2,S x3,S z3){fp da,cb,a,b;add(a,x2,z2),sub(b,x3,z3),mul(da,a,b),sub(b,x2,z2),add(a,x3,z3),mul(cb,a,b),add(a,da,cb),sq(b,a),mul(x5,z1,b),sub(a,da,cb),sq(b,a),mul(z5,x1,b);}
// dbl-1987-m: x3=(x1^2-z1^2)^2, z3=4 x1 z1 (x1^2+(a x1 z1)+z1^2)
Z_ xdbl(S x3,S z3,S x1,S z1){fp x1sq,z1sq,x1z1,a;sq(x1sq,x1),sq(z1sq,z1),mul(x1z1,x1,z1),sub(a,x1sq,z1sq),sq(x3,a),mlc(a,x1z1,486662),add(a,x1sq,a),add(a,z1sq,a),mul(x1sq,x1z1,a),mlc(z3,x1sq,4);}
// scalar mult
ZZ xmul(S r,S q,S e){fp xm,xms,zms,zm={1},xm1={1},zm1={0};dsn(xm,q,32); //!< p(m),p(m-1)
   _N(254,BIT(e)xadd(xm1,zm1,q,ONE,xm,zm,xm1,zm1),xdbl(xm,zm,xm,zm),xadd(xms,zms,xm1,zm1,xm,zm,q,ONE); //!< p(2m),p(2m-1)
    sel(xm1,xm1,xm,bit),sel(zm1,zm1,zm,bit),sel(xm,xm,xms,bit),sel(zm,zm,zms,bit))//!< bit?(p(2m+1),p(2m)):(p(2m),p(2m-1))
   inv(zm1,zm),mul(r,zm1,xm),nrm(r);}//!< freeze out projective coords

// x25519 ecdh
_ xkeygen(fp sec,fp pub,fp rnd){dsn(sec,rnd,32),prp(sec),xmul(pub,BP,sec),rfc(pub);}
_ xshared(fp shr,fp sec,fp pub){xmul(shr,pub,sec);}//_ xrandom(S x,V n){N(n,Xk=r8())}

// generic finite fields
Z_ shft(S x,I n){H c=0;X(c|=HX<<n;Xg=c;c>>=8)}Z_ copy(S x,S a){dsn(x,a,32);}ZI pmsb(S x){G y;_N(32,if((y=Xg)){i<<=3;W(y){y>>=1;i++;}R--i;})R 0;}
Z_ radd(S x,S y){H c=0;X(c+=HX+HY;Xg=c;c>>=8)}Z_ rsub(S x,S y){fp z;H c=0;X(c=HX-HY-c;Zg=c;c=(c>>8)&1)sel(x,z,x,c);}Z_ fadd(S r,S a,S m){radd(r,a),rsub(r,m);}
Z_ pfrb(S r,S x,size_t len,S m){I t=min(pmsb(m)-1,len<<3),by=t>>3,bi=t&7,rbi=(len<<3)-t;memset(r,0,32);//O("len %d t %d by %d bi %d rbi %d\n",len,t,by,bi,rbi);
   N(by,Rg=x[len-by+i])if(bi){shft(r,bi);r[0]|=x[len-by-1]>>(8-bi);}_N(rbi,BIT(x);shft(r,1);*r|=bit;rsub(r,m))}
Z_ fmul(S r,S a,S b,S m){memset(r,0,32);_N(pmsb(m),BIT(b);fp plusa;shft(r,1),rsub(r,m),copy(plusa,r),fadd(plusa,a,m),sel(r,r,plusa,bit))}

#define SHA(s) struct sha_state s;sha_ini(&s);
Z_ sha5(S out_fp,S init_block,V prfx,S msg,V len){SHA(s);
 if(len<128&&len+prfx<128){dsn(init_block+prfx,msg,len);sha_end(&s,init_block,len+prfx);
 }else{dsn(init_block+prfx,msg,128-prfx);sha_add(&s,init_block);
  size_t i;for(i=128-prfx;i+128<=len;i+=128)sha_add(&s,msg+i);sha_end(&s,msg+i,len+prfx);}
 sha_get(&s,init_block,0,64);pfrb(out_fp,init_block,64,EO);}

//! projective prims: copy, project, unproject, pack, try to unpack
Z_ ecpy(ep d,const ep s){dsn(d,s,SZ(EP));}
Z_ proj(ep p,S x,S y){copy(Px,x),copy(Py,y);loa(Pz,1),mul(Pt,x,y);}
Z_ uprj(S x,S y,ep p){fp z;inv(z,Pz),mul(x,Px,z),mul(y,Py,z),nrm(x),nrm(y);}
Z_ pack(S c,S x,S y){fp t;G p;copy(t,x),nrm(t);copy(c,y),nrm(c);c[31]|=(t[0]&1)<<7;}
ZG unpk(S x,S y,S comp){I p=comp[31]>>7;fp a,b,c;copy(y,comp);y[31]&=127;
	sq(c,y);mul(b,c,ED);add(a,b,ONE);inv(b,a);sub(a,c,ONE);
	mul(c,a,b),sqt(a,c),neg(b,a),sel(x,a,b,(a[0]^p)&1),sq(a,x),nrm(a),nrm(c);R eql(a,c);}

// point addition (add-2008-hwcd-3)
Z_ eadd(ep p,ep p1,ep p2){fp a,b,c,d,e,f,g,h;sub(c,P1y,P1x),sub(d,P2y,P2x),mul(a,c,d),add(c,P1y,P1x),add(d,P2y,P2x),mul(b,c,d),mul(d,P1t,P2t),mul(c,d,EK),
   mul(d,P1z,P2z),add(d,d,d),sub(e,b,a),sub(f,d,c),add(g,d,c),add(h,b,a);mul(Px,e,f),mul(Py,g,h),mul(Pt,e,h),mul(Pz,f,g);}

// point doubling (dbl-2008-hwcd)
Z_ edbl(ep p,ep p1){fp a,b,c,d,e,f,g,h;sq(a,P1x),sq(b,P1y),sq(c,P1z),add(c,c,c),add(f,P1x,P1y),sq(e,f),sub(e,e,a),sub(e,e,b),sub(g,b,a),sub(f,g,c),neg(h,b),sub(h,h,a);
   mul(Px,e,f),mul(Py,g,h),mul(Pt,e,h),mul(Pz,f,g);}

// edwards scalar multiplication
Z_ emul(ep out,ep p,S e){EP r,s;ecpy(&r,&EN);_N(256,BIT(e);edbl(&r,&r);eadd(&s,&r,p);SEL(x)SEL(y)SEL(z)SEL(t))ecpy(out,&r);}

Z_ pck(S r,ep p){fp x,y;uprj(x,y,p);pack(r,x,y);}
ZG upk(ep p,S pckd){fp x,y;G ok=unpk(x,y,pckd);R proj(p,x,y),ok;}
Z_ epck(S r,S k){EP p;emul(&p,&EB,k);pck(r,&p);}
Z_ xpnd(S r,S sec){SHA(s);sha_end(&s,sec,32),sha_get(&s,r,0,64),prp(r);}
Z_ pubk(S pub,S sec){G e[64];xpnd(e,sec);epck(pub,e);}

Z_ getk(S k,S key,S m,V n){G blk[128]={0};copy(blk,key);sha5(k,blk,32,m,n);}
Z_ getm(S z,S r,S a,S m,V n){G blk[128]={0};copy(blk,r);copy(blk+32,a);sha5(z,blk,64,m,n);}

//! ed25519 ecdsa
_ edkeygen(G sec[64],fp pub,fp seed){pubk(pub,seed);copy(sec,seed);copy(sec+32,pub);}//FIXME wipe seed

_ edsign(G sig[64],fp pub,G sec[64],S m,V n){
	G expd[64];fp e,s,k,z;xpnd(expd,sec);
	getk(k,expd+32,m,n),epck(sig,k),getm(z,sig,pub,m,n),
	pfrb(e,expd,32,EO),fmul(s,z,e,EO),fadd(s,k,EO),copy(sig+32,s);}

G edverify(G sig[64],fp pub,S m,V n){EP p,q;fp lhs,rhs,z;G ok=1;
	getm(z,sig,pub,m,n),epck(lhs,sig+32);
	ok&=upk(&p,pub);emul(&p,&p,z);
	ok&=upk(&q,sig);eadd(&p,&p,&q),
	pck(rhs,&p);R(ok&eql(lhs,rhs))!=0;}

//:~
