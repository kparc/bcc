#ifdef UNITY
#include<stdio.h>

#define O printf
#define NL O("\n");
#define LEN(x) (sizeof(x)/sizeof(x[0]))

ZS tst[] = {
(S)"\"\"",
(S)"\"abc\"",
(S)"\"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq\"",
(S)"\"abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu\"",
(S)"(_1e6)#\"a\""};

ZV tvec2[] = {
0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b, 0x7852b855,  //""
0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad,  //"abc"
0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1,  //"abcde..."
0xcf5b16a7, 0x78af8380, 0x036ce59e, 0x7b049237, 0x0b249b11, 0xe8f07a51, 0xafac4503, 0x7afee9d1,  //"abcdef.."
0xcdc76e5c ,0x9914fb92, 0x81a1c7e2, 0x84d73e67, 0xf1809a48, 0xa497200e, 0x046d39cc, 0xc7112cd0}; //(_1e6)#"a"

ZU tvec5[] = {
0xcf83e1357eefb8bd, 0xf1542850d66d8007, 0xd620e4050b5715dc, 0x83f4a921d36ce9ce, 0x47d0d13c5d85f2b0, 0xff8318d2877eec2f, 0x63b931bd47417a81, 0xa538327af927da3e,
0xddaf35a193617aba, 0xcc417349ae204131, 0x12e6fa4e89a97ea2, 0x0a9eeee64b55d39a, 0x2192992a274fc1a8, 0x36ba3c23a3feebbd, 0x454d4423643ce80e, 0x2a9ac94fa54ca49f,
0x204a8fc6dda82f0a, 0x0ced7beb8e08a416, 0x57c16ef468b228a8, 0x279be331a703c335, 0x96fd15c13b1b07f9, 0xaa1d3bea57789ca0, 0x31ad85c7a71dd703, 0x54ec631238ca3445,
0x8e959b75dae313da, 0x8cf4f72814fc143f, 0x8f7779c6eb9f7fa1, 0x7299aeadb6889018, 0x501d289e4900f7e4, 0x331b99dec4b5433a, 0xc7d329eeb6dd2654, 0x5e96e55b874be909,
0xe718483d0ce76964, 0x4e2e42c7bc15b463, 0x8e1f98b13b204428, 0x5632a803afa973eb, 0xde0ff244877ea60a, 0x4cb0432ce577c31b, 0xeb009c5c2c49aa2e, 0x4eadb217ad8cc09b};

ZI laps[] = {1e7,1e6,1e5,1e4,1e3};

#define CHK(f,res,seed,slen,hsh,m,rot,tvec) ZI f(I tn){K y=ss((S)tst[tn]);K x=ev(y);\
 U l=xn;mcp(res,seed,8*slen);m(hsh,x);I chk=0;N(8,chk+=res[i]==tvec[tn*8+i]);\
 O("sha%d %10llu chk=%d %s\n",slen*64,l,chk,(8>chk)?"FAIL":"ok");R chk;}

CHK(sha2tst,h2,s2,4,sh2,mV,s4,tvec2) CHK(sha5tst,h5,s5,8,sh5,mU,s8,tvec5)

I sha_tests(){I n=LEN(tst),r=0;NL;N(n,r+=sha2tst(i))NL;N(n,r+=sha5tst(i))NL;R r;}

#if defined(INIT) || defined(RUN)
#include<sys/mman.h>
_ _k(J,_*),t01();_ sha_init(I M){size_t n=1<<M;_k(n,mmap(0,n,PROT_READ|PROT_WRITE,MAP_NORESERVE|MAP_PRIVATE|MAP_ANON,-1,0));t01();}
#endif

#ifdef RUN
#include<stdlib.h>
#include<time.h>
#define main main

ZJ ut(){struct timespec t;R clock_gettime(CLOCK_REALTIME,&t),1E9*(t.tv_sec-19723*86400)+t.tv_nsec;}

#define PRF(f,hfn,label) Z_ f(I tn){I n=laps[tn];F sec,mib;K r,x=ev(ss(tst[tn]));J t0=ut();\
 N(n,r=hfn(r1(x));r0(r))sec=(ut()-t0)/1E9;mib=((1+xn)*n)/(1U<<20);\
 O("sha%d   %7d * %-10d %-10.2fmib/s\n",label,xn,(I)n,mib/sec);r0(x);}

PRF(sha2prf,sha2,256)PRF(sha5prf,sha5,512)
_ sha_bench(){I n=LEN(tst);NL;N(n,sha2prf(i))NL;N(n,sha5prf(i))NL;}
K _ss(S x){R ss(x);}K evl(S x){R ev(ss(x));}S ver(){R(S)__DATE__;}extern I w;I setWW(I r,I c){R w=256*max(24-2,r-2)+min(255,max(80,c));}

#define trc(s,r) ({K x=r;printf("%s %llx xt %d xn %d ax %d\n",s,x,xt,xn,ax);})

I r4(I);U r8();_ SHA5(_*r,S msg,U mn,S sig,U sn);

#define O printf
/*#define _Pp(s,x,n) O("%s ",s);Nj(n,O("%02x",x[j]));NL
#define _Pr(s,x,n) O("\nuint8_t %s[%d]={",s,n);Nj(n,O("0x%02x%s%s",x[j],(j!=n-1)?",":"",((j!=n-1)&&(j%8==7))?"\n\t\t ":""));O("};\n\n");
#define Pp(s,x)  _Pp(s,x,32)
#define PP(s,x)  _Pp(s,x,64)
#define Prr(s,x) _Pr(s,x,32)
#define PRR(s,x) _Pr(s,x,64)
*/

#define SZ sizeof
#define FP(x) G x[32];
#define ZFP(x) static G x[32]
#define X(x) N(32,x)
#define sm(x) r|=r>>x;
#define zG ((G*)z)
#define Zg zG[i]
#define HX ((H)Xg)
#define HY ((H)Yg)
#define VX ((V)Xg)
#define VY ((V)Yg)
#define Vx(i) ((V)x[i])
#define Vy(i) ((V)y[i])

#define RD(x) X(c+=x;x=c;c>>=8)
#define RDc RD(Rg)
#define RDC c=(c>>7)*19;RDc
#define RDCC r[31]=c&127;RDC
#define RSX mul(r,s,x)
#define SRX mul(s,r,x)
#define SRR mul(s,r,r)
#define RSS mul(r,s,s)
#define SRSX SRR,RSX
#define CORK r[31]&=127

#define cpy(x,a) mcp(x,a,32)
#define BIT(x)   const G bit=(x[i>>3]>>(i&7))&1;
#define SEL(f)   sel(r.f,r.f,s.f,bit);
#define Px  p->x
#define Py  p->y
#define Pz  p->z
#define Pt  p->t
#define P1x p1->x
#define P1y p1->y
#define P1z p1->z
#define P1t p1->t
#define P2x p2->x
#define P2y p2->y
#define P2z p2->z
#define P2t p2->t

#define FPah FP(a)FP(b)FP(c)FP(d)FP(e)FP(f)FP(g)FP(h);
#define XYTZ3 mul(Px,e,f),mul(Py,g,h),mul(Pt,e,h),mul(Pz,f,g);
#undef x3
#undef x5
#undef S01
#undef S0
#undef S1

typedef struct _pt {FP(x)FP(y)FP(t)FP(z)} PT;typedef PT*pt;ZFP(ONE)={1};ZFP(XB)={9};PT EN={.x={0},.y={1,0},.t={0},.z={1,0}};

//PT EB={.z={1,0},
//.x={0x1a,0xd5,0x25,0x8f,0x60,0x2d,0x56,0xc9,0xb2,0xa7,0x25,0x95,0x60,0xc7,0x2c,0x69,0x5c,0xdc,0xd6,0xfd,0x31,0xe2,0xa4,0xc0,0xfe,0x53,0x6e,0xcd,0xd3,0x36,0x69,0x21},
//.y={0x58,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66,0x66},
//.t={0xa3,0xdd,0xb7,0xa5,0xb3,0x8a,0xde,0x6d,0xf5,0x52,0x51,0x77,0x80,0x9f,0xf0,0x20,0x7d,0xe3,0xab,0x64,0x8e,0x4e,0xea,0x66,0x65,0x76,0x8b,0xd7,0x0f,0x5f,0x87,0x67}};

ZFP(EK)={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24};
//ZFP(ED)={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52};
//ZFP(EO)={0xed,0xd3,0xf5,0x5c,0x1a,0x63,0x12,0x58,0xd6,0x9c,0xf7,0xa2,0xde,0xf9,0xde,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10};

//mod p=2^255-19 compare,load,select,normalize,add,multiply,constmult,subtract,negate,reciprocal,pow2^252-3,sqrt
/*
G cmp(S x,S y){G r=0;X(r|=Xg^Yg)sm(4)sm(2)sm(1)R(r^1)&1;}*/
_ loa(S r,V c){X(Rg=0)N(SZ(c),Rg=c;c>>=8)}
_ sel(S r,S x,S y,G c){X(Rg=-c&(Yg^Xg)^Xg)}
_ nrm(S r){FP(y);H c=(r[31]>>7)*19;CORK;RDc;c=19;N(31,c+=Rg;Yg=c;c>>=8)c+=((H)r[31])-128;y[31]=c;sel(r,y,r,(c>>15)&1);}
_ sum(S r,S x,S y){H c=0;X(c>>=8;c+=HX+HY;Rg=c)CORK;RDC}
_ mul(S r,S x,S y){V c=0;X(c>>=8;Nj(i+1,c+=Vx(j)*Vy(i-j))Nj(31-i,c+=Vx(i+1+j)*Vy(31-j)*38)Rg=c)RDCC}
_ mlc(S r,S x,V y){V c=0;X(c>>=8;c+=y*VX;Rg=c)CORK;c>>=7;c*=19;RDc}
_ sub(S r,S x,S y){V c=218;N(31,c+=VX-VY+65280;Rg=c;c>>=8)c+=Vx(31)-Vy(31);RDCC}
_ neg(S r,S x){    V c=218;N(31,c+=65280-VX;   Rg=c;c>>=8)c-=Vx(31);       RDCC}
_ inv(S r,S x){FP(s)sq(s,x);RSX;N(248,SRSX)sq(s,r),sq(r,s),SRX,sq(r,s);N(2,SRSX)}
_ exp(S r,S x,S s){ sq(r,x);SRX;N(248,sq(r,s),SRX)sq(r,s),sq(s,r),RSX;}
_ sqt(S r,S a){FP(v)FP(i)FP(x)FP(y)mlc(x,a,2),exp(v,x,y),sq(y,v),mul(i,x,y),loa(y,1),sub(i,i,y),mul(x,v,a),mul(r,x,i);}


I msb(S x){G y;_N(32,if((y=Xg)){i<<=3;W(y){y>>=1;i++;}R--i;})R 0;}
I imn(I x,I y){R x<y?x:y;}
_ shb(S x,I n){H c=0;X(c|=HX<<n;Xg=c;c>>=8)}
_ rad(S x,S y){H c=0;X(c+=HX+HY;Xg=c;c>>=8)}
_ rsb(S x,S y){FP(z);H c=0;X(c=HX-HY-c;Zg=c;c=(c>>8)&1)sel(x,z,x,c);}
_ frb(S r,S x,size_t len,S m){
  I t=imn(msb(m)-1,len<<3),by=t>>3,bi=t&7,rbi=(len<<3)-t;memset(r,0,32);//O("len %d t %d by %d bi %d rbi %d\n",len,t,by,bi,rbi);
  N(by,Rg=x[len-by+i])if(bi){shb(r,bi);r[0]|=x[len-by-1]>>(8-bi);}_N(rbi,BIT(x);shb(r,1);r[0]|=bit;rsb(r,m))}
_ fadd(S r,S a,S m){rad(r,a),rsb(r,m);}
_ fmul(S r,S a,S b,S m){memset(r,0,32);_N(msb(m),BIT(b);FP(plusa);shb(r,1),rsb(r,m),cpy(plusa,r),fadd(plusa,a,m),sel(r,r,plusa,bit))}

*/
static inline _ ecp(pt d,pt s){mcp(d,s,SZ(*d));}
static inline _ prp(S x){x[0]&=0xf8;x[31]&=0x7f;x[31]|=0x40;}
/*
*/

_ smm(pt p,pt p1,pt p2){FPah;sub(c,P1y,P1x),sub(d,P2y,P2x),mul(a,c,d),sum(c,P1y,P1x),sum(d,P2y,P2x),mul(b,c,d),
  mul(d,P1t,P2t),mul(c,d,EK),mul(d,P1z,P2z),sum(d,d,d),sub(e,b,a),sub(f,d,c),sum(g,d,c),sum(h,b,a);XYTZ3}

_ dbl(pt p,pt p1){FPah;mul(a,P1x,P1x),mul(b,P1y,P1y),mul(c,P1z,P1z),sum(c,c,c),sum(f,P1x,P1y),mul(e,f,f),
  sub(e,e,a),sub(e,e,b),sub(g,b,a),sub(f,g,c),neg(h,b),sub(h,h,a);XYTZ3}

_ mlt(pt out,pt p,S e){PT r,s;ecp(&r,&EN);_N(256,BIT(e);dbl(&r,&r);smm(&s,&r,p);
  SEL(x)SEL(y)SEL(z)SEL(t))ecp(out,&r);}

_ xdbl(S x3,S z3,S x1,S z1){FP(x1sq)FP(z1sq)FP(x1z1)FP(a)
  mul(x1sq,x1,x1),mul(z1sq,z1,z1),mul(x1z1,x1,z1),sub(a,x1sq,z1sq),mul(x3,a,a),
  mlc(a,x1z1,486662),sum(a,x1sq,a),sum(a,z1sq,a),mul(x1sq,x1z1,a),mlc(z3,x1sq,4);}

_ xadd(S x5,S z5,S x1,S z1,S x2,S z2,S x3,S z3){FP(da)FP(cb)FP(a)FP(b)
  sum(a,x2,z2),sub(b,x3,z3),mul(da,a,b),sub(b,x2,z2),sum(a,x3,z3),mul(cb,a,b),
  sum(a,da,cb),mul(b,a,a),mul(x5,z1,b),sub(a,da,cb),mul(b,a,a),mul(z5,x1,b);}

_ xmul(S r,S q,S e){FP(xm)FP(xms)FP(zms)G zm[32]={1},xm1[32]={1},zm1[32]={0};cpy(xm,q);
  _N(254,
  //int i;for (i = 253; i >= 0; i--) {
  	BIT(e)

  	// from P_m and P_(m-1), compute P_(2m) and P_(2m-1)
  	xadd(xm1,zm1,q,ONE,xm,zm,xm1,zm1),xdbl(xm,zm,xm,zm),

  	// compute P_(2m+1)
  	xadd(xms,zms,xm1,zm1,xm,zm,q,ONE),

	/* select:
	 *   bit = 1 --> (P_(2m+1), P_(2m))
	 *   bit = 0 --> (P_(2m), P_(2m-1))
	 */
    sel(xm1,xm1,xm,bit),sel(zm1,zm1,zm,bit),sel(xm,xm,xms,bit),sel(zm,zm,zms,bit);
  )
  //}
  // freeze out of projective coordinates
  inv(zm1,zm),mul(r,zm1,xm),nrm(r);}

_ xrandom(S x,V n){N(n,Xk=r8())}
_ xkeygen(G sec[32],G pub[32],G s[32]){cpy(sec,s),prp(sec),xmul(pub,XB,sec);}
_ xshared(G shr[32],G sec[32],G pub[32]){xmul(shr,pub,sec);}


/*
#define PTRND(x) FP(x);lod(x,r4(r8()));nrm(x);
_ prfx(S r,S hdr,V hn,S m,V mn){G t[64];SHA5(t,m,mn,hdr,hn);
	printf("\n");
	PP("SHA5(hdr) <<",hdr);
	PP("SHA5(msg) <<",m);
	PP("SHA5      >>",t);
	printf("\n");
	frb(r,t,64,EO);
}
_ pp(S r,pt p){FP(x)FP(y)upj(x,y,p);pck(r,x,y);}
_ pack(S r,S k){PT p;mlt(&p,&EB,k);pp(r,&p);}
_ xpnd(S e,S seed){SHA5(e,seed,32,(S)"",0),prp(e);}
_ pubk(S pub,S seed){G e[64];xpnd(e,seed);pack(pub,e);}
_ kgen(G sec[64],G pub[32],G seed[32]){pubk(pub,seed);cpy(sec,seed);cpy(sec+32,pub);}//FIXME wipe seed
_ getk(S k,S key,S m,V n){G blk[128]={0};cpy(blk,key);prfx(k,blk,32,m,n);}
_ hash(S z,S r,S a,S m,V n){G blk[128]={0};cpy(blk,r);cpy(blk+32,a);prfx(z,blk,64,m,n);}

_ sign(G sig[64],G pub[32],G sec[64],S m,V n){G expd[64];FP(e)FP(s)FP(k)FP(z)
	xpnd(expd,sec),getk(k,expd+32,m,n),pack(sig,k),hash(z,sig,pub,m,n),
	frb(e,expd,32,EO),fmul(s,z,e,EO),fadd(s,k,EO),cpy(sig+32,s);}

G vrfy(G sig[64],G pub[32],S m,V n){PT p,q;FP(lhs)FP(rhs)FP(z)G ok=1;
	hash(z,sig,pub,m,n),pack(lhs,sig+32),ok&=upk(&p,pub),mlt(&p,&p,z),ok&=upk(&q,sig),smm(&p,&p,&q),pp(rhs,&p);
	Pp("\nverify lhs", lhs);Pp("verify rhs", rhs);printf("\n");
	R(ok&cmp(lhs,rhs))!=0;}
*/

I main(I c,char**v){

//sha_init(30);
//P(sha_tests()<LEN(tst)*8*2,1)
//G ttt[112]="abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";
/*
G tt2[112]={0x60,0x33,0x45,0x7f,0xc0,0xbd,0xbb,0xcc,0x5e,0xbc,0xd4,0xd1,0xf5,0x4f,0x22,0x3e,0x41,0xf0,0x07,0x0f,0x55,0x11,0xf6,0x7f,0x38,0xfc,0x6d,0x22,0x1a,0x3e,0x22,0x16,0x9b,0xfe,0x33,0xcc,0xda,0x93,0x07,0x4f,0x66,0x1c,0x47,0xc9,0x4f,0x66,0x98,0xc0,0x40,0x97,0x67,0x3e,0x99,0x6f,0x62,0x6b,0x8a,0x75,0xb2,0x0f,0x0a,0xf5,0x31,0x0a,0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52,0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00};
G shA[64]={0};
SHA5(shA,(S)"",0,tt2,112);PP("TESTSHA",shA);
SHA5(shA,tt2,112,(S)"",0);PP("TESTSHA",shA);
//exit(0);
*/
I MSG_SIZE=48;

G S0[32]={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52};
G S1[32]={0x59,0xf1,0xb2,0x26,0x94,0x9b,0xd6,0xeb,0x56,0xb1,0x83,0x82,0x9a,0x14,0xe0,0x00,0x30,0xd1,0xf3,0xee,0xf2,0x80,0x8e,0x19,0xe7,0xfc,0xdf,0x56,0xdc,0xd9,0x06,0x24};
G msg[64]={0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52,
           0xa3,0x78,0x59,0x13,0xca,0x4d,0xeb,0x75,0xab,0xd8,0x41,0x41,0x4d,0x0a,0x70,0x00,0x98,0xe8,0x79,0x77,0x79,0x40,0xc7,0x8c,0x73,0xfe,0x6f,0x2b,0xee,0x6c,0x03,0x52};


FP(sec1)FP(pub1)FP(s1)FP(shr1)cpy(s1,S0);
FP(sec2)FP(pub2)FP(s2)FP(shr2)cpy(s2,S1);
//xrandom(s1,2),xrandom(s2,2);
N(1024,
 xkeygen(sec1,pub1,s1),xkeygen(sec2,pub2,s2),
 xshared(shr1,sec1,pub2),xshared(shr2,sec2,pub1);
 P(memcmp(shr1,shr2,32),O("shared secret mismatch\n");-1)
 O("%d x25512 ok\n",i)
)

exit(0);

/*
FP(seed);FP(pub);G sec[64],sig[64];cpy(seed,S1);
kgen(sec,pub,seed);Pp("PUB",pub);PP("SEC",sec);
sign(sig,pub,sec,msg,MSG_SIZE);
P(!vrfy(sig,pub,msg,MSG_SIZE),printf("failed on good plaintext\n"),-1)
//msg[1]^=0x10;P(vrfy(sig,pub,msg,MSG_SIZE),printf("failed on bad plaintext\n"),-1)

exit(0);
*/
/*
PTRND(x)PTRND(y)V r=r4(r8());FP(p0)FP(p1)

f25519_load(p0,r);lod(p1,r);
O("cmp(p0,p1)==f25519_eq(p0,p1) => %d\n",cmp(p0,p1)==f25519_eq(p0,p1));

       f25519_select(p0,x,y,0);Pp(" select",p0);
                 sel(p0,x,y,0);Pp("    sel",p0);
       f25519_select(p0,x,y,1);Pp(" select",p0);
                 sel(p0,x,y,1);Pp("    sel",p0);

    f25519_normalize(p0);      Pp("normlze",p0);
                 nrm(p0);      Pp("    nrm",p0);

          f25519_add(p0,x,y);  Pp("    add",p0);
                 sum(p0,x,y);  Pp("    sum",p0);
          f25519_add(p0,y,x);  Pp("    add",p0);
                 sum(p0,y,x);  Pp("    sum",p0);

          f25519_sub(p0,x,y);  Pp("sbtract",p0);
                 sub(p0,x,y);  Pp("    sub",p0);
          f25519_sub(p0,y,x);  Pp("sbtract",p0);
                 sub(p0,y,x);  Pp("    sub",p0);

            f25519_neg(p0,x);  Pp(" negate",p0);
                   neg(p0,x);  Pp("    neg",p0);
            f25519_neg(p0,y);  Pp(" negate",p0);
                   neg(p0,y);  Pp("    neg",p0);
            f25519_neg(p0,x);  Pp(" negate",p0);
                   neg(p0,x);  Pp("    neg",p0);
           f25519_neg(p1,p0);  Pp(" negate",p1);
                  neg(p1,p0);  Pp("    neg",p1);

f25519_mul__distinct(p0,x,y);  Pp("muldist",p0);
                 mul(p0,x,y);  Pp("    mul",p0);

        f25519_mul_c(p0,x,r);  Pp("  mul_c",p0);
                 mlc(p0,x,r);  Pp("    mlc",p0);

  f25519_inv__distinct(p0,x);  Pp("inverse",p0);
                   inv(p0,x);  Pp("    inv",p0);

             exp2523(p0,x,y);  Pp("exp2523",p0);
                 xpn(p0,x,y);  Pp("    xpn",p0);

         f25519_sqrt(p1, p0);  Pp("   sqrt",p1);
                 sqr(p1, p0);  Pp("    sqr",p1);
*/

exit(0);

#ifndef WSM
sha_bench();
#endif
R 0;}
#endif

#endif

//:~



//#define trc(s,r) ({K x=r;printf("%s %llx xt %d xn %d ax %d\n",s,x,xt,xn,ax);})
//extern K1*m[20];I ip(I);
//K seed(I n){K x=m[ip('?')](ki(n));R x;}
//K x = seed(16);N(2*xn,O("%i ",xI[i]))
//trc("rnd",seed);}


/*
#include<stdio.h>
#ifdef SO
#include <string.h>
#include"k.h"
#define K1(f) K f(K x)
#define K2(f) K f(K x,K y)
#define K3(f) K f(K x,K y,K z)
#define i1(f) K f(I i,K x)
#define X0(e) ({typeof(e)_e=(e);r0(x);_e;})
#define Y0(e) ({typeof(e)_e=(e);r0(y);_e;})
#else
#include"b.h"
#endif

#define O printf
#define NL O("\n");
#define Z_ static _
typedef void _;typedef unsigned int V;typedef unsigned long long U;
#define Z_ static _
#define ZU static U
#define ZV static V
#define xV ((V*)x)
#define xU ((U*)x)
#define LEN(x) (sizeof(x)/sizeof(x[0]))
#define nC(n,s) sr((S)s,(S)(s+n))
#define XY0(e) X0(Y0(e))
#define init(M) n=1<<M;_k(n,mmap(0,n,PROT_READ|PROT_WRITE,MAP_NORESERVE|MAP_PRIVATE|MAP_ANON,-1,0));

K1(r0);K2(vv);K3(k3);i1(na);K vc(K,I),kc(I),ss(S),sr(S,S),_k(J,_*);S mcp(_*s,_*t,U n);K1(w_);

#define s4(x) __builtin_bswap32(x)
#define s8(x) __builtin_bswap64(x)
#define shr(a,x)  (x>>a|x<<(32-a))
#define shR(a,x)  (x>>a|x<<(64-a))

#define ini(n,x,s) w[n],a=x[0],b=x[1],c=x[2],d=x[3],e=x[4],f=x[5],g=x[6],h=x[7],t,u;N(16,w[i]=s(q[i]))
#define sch(n,sh,s00,s01,s02,s10,s11,s12) N(n,t=w[14+i],u=w[1+i],w[16+i]=(sh(s10,t)^sh(s11,t)^t>>s12)+w[9+i]+(sh(s00,u)^sh(s01,u)^u>>s02)+w[i])
#define zip(n,sh,S00,S01,S02,S10,S11,S12) N(n,t=h+(sh(S10,e)^sh(S11,e)^sh(S12,e))+(e&f^~e&g)+k[i]+w[i],h=g,g=f,f=e,e=d+t,d=c,c=b,b=a,a=t+(sh(S00,b)^sh(S01,b)^sh(S02,b))+(b&c^b&d^c&d))
#define add(x) x[0]+=a,x[1]+=b,x[2]+=c,x[3]+=d,x[4]+=e,x[5]+=f,x[6]+=g,x[7]+=h;

#ifndef FFI
#define sha(f,res,seed,hsh,m,rot,slen) K1(f){Q(Ax||!Cx)mcp(res,seed,8*slen);m(hsh,x);N(8,res[i]=rot(res[i]))R nC(8,res);}
#else
#define sha(f,res,seed,hsh,m,rot,slen) S f(S x){mcp(res,seed,8*slen);m(hsh,x);N(8,res[i]=rot(res[i]))R nC(8,res);}
#endif



*/