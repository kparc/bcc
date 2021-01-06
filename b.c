#include"b.h"

ZK d(I,K,ST),cm(I t,I x,I y);ZI l(S s,I c){S t=sc(s,c);R t?t-s:0;} //!< lookup c in s

S Ss;K z;ZI B5=5,RET=0xc3,A[]={0,7,6,2,1,8,9,10,11,3,12,13,14,15,5,4},//!< x64 abi lol
 //    jmp  jb   jz   jnbe jmp32 jnb  jnz  jbe   jnb32
 JJ[]={0xeb,0x72,0x74,0x77,0xe9, 0x73,0x75,0x76, 0x0f83};
ZK c5(I o,I n){R cj(o,pn((S)&n,4));}  //!< barebone 5-piece struct for longjmps/funcalls/conditionals
ZI m(I a,I b,I c){R 64*a+8*(7&b)+(7&c);}    //!< convert octal abc to int, used to fill mod(2),reg(3),r/m(3) byte
ZK rex(I r,I x,I b,K y){R(r=7<A[r])+(x=7<A[x])+(b=7<A[b])?cj(0x40+4*r+2*x+b,y):y;} //!< use rex prefix to access newer regs
ZK h(I o,I x,I y){//<! opcode o, arguments x y (not rex, x should never be >15)
 R j2(256>o?c1(o):c2(o>>8,o),16>y?c1(m(3,x,y)):c5(m(0,x,5),y));} //!< one- or two-byte opcode
ZK i(I o,I x,I y){R rex(16>x?x:0,0,16>y?y:0,h(o,16>x?A[x]:x-16,16>y?A[y]:y));} //!< opcode o, arguments xy (maybe rex)

ZK jmp(I n){R n<-128||n>127?c5(JJ[4],0>n?n-3:n):c2(*JJ,n);}  //!< c5|c2 long|shortjmp
ZK cc(I o,I x){R j2(i(0x0f20+JJ[o],16,x),i(0x0fb6,x,x));}    //!< conditional
ZK psh(I t,I x){R rex(0,0,x,c1(0x50+(7&A[x])));}
ZK pop(I t,I x){R rex(0,0,x,c1(0x58+(7&A[x])));}
ZK tst(I t,I x){R KF==t?(K)AB("tst"):i(0x85,x,x);}
ZK Jj(K x,I n){R cj(0x0f,c5(16+xC[xn],n-4));}
ZK cll(I c){R c5(0xe8,c);}

ZK o2f(I o,I x,I y){
#ifdef SYMS
 K v=BASE>y?y:0;
#else
 K v = y;
#endif
 R 127>v //    0    1    2     3      4    5    6   7   8   9   10
    //ints:  mov  add  sub  imul         cmp  and              xor
    ?i((I[]){0x8b,0x03,0x2b,0x0faf, 0x0,0x3b,0x23,0x0,0x0,0x0,0x33}[o],x,y)
    :rex(0,0,x,o?c3(0x83,m(3," \0\5  \7\4\1  \6"[o],A[x]),y-128):c5(0xb8+(7&A[x]),y-128));}//!< move to register x
//                            0 1 234 5 6 78910                                            //!< add,sub,cmp,and,or,xor

//!return object code to execute opcode o with arguments x and y and leave the argument of type t in register r
ZK o2(I t,I o,I r,I x,I y){K z; //O("o2: t=%c o=%d r=%d x=%p y=%p\n"," chijefs CHIJEFS"[t],o,r,x,y);
 P(KF==t,8u>y-8?AB("vex"):j2(c2(0xc5,16*(8&~r)+8*(15&~x)+(5-o?3:1)),
  // for fp (with 0f prefix): i2f int to float
  //         0    1    2    3    4    5 6 7    8
  //       mov  add  sub  mul  div  cmp      i2f
  h((C[]){0x10,0x58,0x5c,0x59,0x5e,0x2e,0,0,0x2a}[o],r,y)))
#ifndef SYMS
 I a=126<y,s;
#else
 I a=BASE>y,s;
#endif
 P(0<=o&&r==x&&(!a||3-o),
  4-o?o2f(o,r,y):129-y?AB("/"):i(0xd1,16+7,r))              //!< shl|shr
 P(0<o&&r==y,z=o2f(o,r,x),2-o?z:j2(z,i(0xf7,16+3,r)))       //!< neg
 P((a?3:1)<o,j2(o2f(0,r,x),o2f(o,r,y))) //     mov  mov      lea imul
 R s=0<o?0:3+(o+1)/2,rex(r,a?0:y,x,c3(0>o?1&o?0x8b:0x89:3-o?0x8d:0x6b,m(3-o?a:3,A[r],a?A[x]:4),a?(2-o?y-128:128-y)<<s:m(s,A[y],A[x])));}

//!opmap         01234567890123
I U(I i){R l((S)" +-*% &|  ^<=>",i);}           //!< TODO cst mod neq not flr ...

//!comparison|operator|funcall dispatch
ZK O2(I t,I f,I r,K x,K y){I i=Ay?yi:yu;       //!< y is either value or function name
 R u(r,j3(Ay?c0():y,x,
    U('<')>f?o2(t,f,r,xu,i)                     //!< operator
   :j2(cm(t,xu,i),16>r?cc(f-U('^'),r):c1(f-U('^')))));}  //!< comparison or function call (^ is ops|conds boundary in U())

//!compare, convert to float, sh nyi
ZK cm(I t,I x,I y){R o2(t,5,x,x,y);}ZK cv(I x,I y){R o2(KF,8,x,x,A[y]);}ZK sh(I t,I r){R AB("sh");}

//!opcode length
ZI ln(S s){I o=*s++,h=o/16,p=0xc5==o?2:0x0f==o;R 4==h?1+ln(s):RET==o||5==h?1:*JJ==o||7==h?2:0xe==h||0xb==h?5:p&&8==*s/16?6:p+(3==s[p]/64?2+(0x83==o||0x6b==o):5==(0xc7&s[p])?6:3);}

//!fix relative addresses
ZV lnk(K x,K z,K a){S s=xC;W(s<xC+xn){
  I n=ln(s+=4==*s/16),p=0xc5==*s?2:0x0f==*s;S r=s+n-4; //!< 4==*s/16 => *s is a rex instruction, skip it
  //O("lnk RRR %llx\n",*(I*)r);
  if(0xe8==*s|| //!< function call
   ((p?8-s[1]/16:4>*s/16||8==*s/16)&&(5==(0xc7&s[1+p])))){ //!< check if instruction uses relative address argument:
#ifndef SYMS
  *(I*)r=(0xe8==*s?a-'a'==*r?x:26==*r?(K)l1:((K*)GGG[*r])[1]:32>*r?(K)&zF[2+*r-16]:(K)(GGG+*r-'a'))-(K)r-4;}
#else
  I t=*(I*)r;
  //O("lnk r=%llx *r %d (I)r %d s %llx r-s %d n %d p %d 32>*r %d t %d x %llx 0xe8==*s %d\n",r,*r,*(I*)r,s,r-s,n,p,32>*r,t,x,0xe8==*s);
  *(I*)r=(
    0xe8==*s
      ?a-'a'==*r
        ?x
        :26==*r
          ?(K)l1
          :((K*)GLO(*(I*)r))[1]  //!< FIXME
      :32>t
         ?(K)&zF[2+*r-16]
         :(K)(GLO(*(I*)r))
    )-(I)r-4;}
#endif
  s+=n;}}

//!pretty print function opcodes and its return type
V dis(K x){S s=xC;W(s<xC+xn-2){N(ln(s),w2(px(*s++)))oc(' ');}N(2,w2(px(*s++)))oc(' ');oc(KS<xu?'K':KF==xu?'f':'j');nl();}

ZK SH(I t,K y){R u(yu,j2(y,sh(t,yu)));}      //!< nyi
ZK ZR(I t,C r){R u(r,o2(t,2,r,r,r));}        //!< set register r of type t to zero (2 is subtract, i.e. r-r=0)
ZK MV(I t,I r,K y){R O2(t,0,r,u(r,c0()),y);} //!< move value y with type t to register r (0 is mov, the first arg is empty array)

ZI _q(K x,S sL){I i=xi-'a';R Ax?26u>i&&sL[i]?sL[i]:0:':'==*xC?I(xy):0;}
I  _t(K x,S sT){I a=xi-'a';  //!< determine type of x
  //O("****** t(x) a %d x=%llx Ax=%d\n",a,x,Ax);
  I r=!Ax?xu:                //!< not an atom is a function: xu holds rettype
   126<xi?KI:                //!< small integer atom encoded in a single byte
   26u>a&&sT[a]?sT[a]:       //!< local variable
#ifndef SYMS
   A(x=26u>a?GGG[a]:         //!< global variable
#else
   A(x=26u>a?*GLO(*(I*)x):   //!< global variable
#endif
    zK[2+xi-16])?Ax:         //!< function argument (additional element of z)
    xt+8;                    //!< array (element type + 4th bit)
    //O("****** t r=%d\n",r);
    R r;}

ZK e(I r,K x,ST st){K y=d(r,x,st);if(Ay){ //!< expr x to register r
    I qz=128==yi||(32>yi&&!zK[2+yi-16]);  //!< if y is zero, either coded as a small int(128), or in the z array
    R qz?ZR(t(x),r)                       //!< set register to zero
        :MV(t(x),r,y);                    //!< otherwise move value to register
  }else R y;}                             //!< for arrays and functions, pass y.

//!branch out
ZK b(I f,K x,ST st){K y=d(16,x,st);R(K)(Ay?AB("b"):16==yu?yC[yn-1]=JJ[yC[yn-1]+f*4],y:j3(y,tst(t(x),yu),c1(JJ[f?2:6])));}

// force: transform values and other expressions into object code,
// except conditional expressions, and move result to register r
ZK f(I r,K x,ST st){K y=e(r,x,st);//O("f y %llx\n",y);os("f y=");o(y);O("f t(x) %d\n",t(x));o(z);
  R r-yu?MV(t(x),r,y):y;} //<! if not a function, move value y to register r

ZK E(I r,K x,ST st){I i=xn-1;K z=e(r,Xx,st),y=kK(i--);r=zu,Yx=z;W(i--)Yx=e(0,xK[i+1],st);R u(r,sS(0,y));}

//!ctf
ZK vh(K x,I n,I r,ST st){R++Ss,1<n?e(0,x,st):f(r,x,st);}
ZK v(I r,K x,I n,ST st){
 K y=xz,z;I c=!n&&!Ay&&sA==*yC,l=M; //!< fixme
 z=vh(xK[3],n,r,st),M=l,y=vh(y,n,r,st),x=b(1,xy,st);
 //yn-=c*B5;I jj=1-n?n-xn-yn-3:zn;K j=jmp(jj);y=j2(y,n||c?yn,j:c1(RET));R j3(jc(x,yn),y,z);}
 y=j2(y,n||c?yn-=c*B5,jmp(1-n?n-xn-yn-3:zn):c1(RET));R j3(jc(x,yn),y,z);}

//!while|for
ZV mm(K x,ST st){I i;$(Ax,if(26u>xi-'a'&&L[i=xi-'a'])M|=1<<L[i])$(':'==*xC&&A(xy),i=I(xy)-'a',M&=~(1<<L[i]),mm(xz,st))N(xn,mm(sc("{WNC",*xC)?xK[xn-1-i]:Xx,st))}
ZK w(K x,ST st){I i='N'==*xC?L[sN++]:0,j=0;mm(x,st);K y=xy,z=xz;I jj;
 P(!i&&!Az&&'$'==*zC,x=b(1,y,st),z=v(0,z,-xn-1,st),jj=-xn-1-zn-2,j3(jc(x,zn+2),z,jmp(jj)))
 x=i?M|=1<<i,jc(cm(0,i,j=(j=q(y))?j:D0),JJ[1]):b(0,y,st),z=i?j2(e(0,z,st),o2(0,1,i,i,129)):e(0,z,st);
 I n=-zn-xn-1;z=j3(jmp(zn),z,n<-128?--xn,j2(x,Jj(x,n)):jc(x,n));R i?--sN,M&=~(1<<i),j3(f(j,y,st),ZR(0,i),z):z;}

ZK g(I c,K x,ST st){K y=c0(),z,r=c0();I i=0,l=sA?M:0;//O("g() c=%d x %llx xn %d\n",c,x,xn);
 W(++i<xn){
  z=Xx;I l=M&1<<i;//O("g() z %llx\n",z);
  I b=Az||(128>*zC&&':'-*zC)||i-L[I(zy)-'a'],h=2-i||Az||26>c;
  z=f(i,z,st);
  if(!h)z=j3(psh(0,3),z,pop(0,3));
  if(l)z=j2(b?psh(0,i):z,b?z:psh(0,i)),r=j2(r,pop(0,i));
  y=j2(z,y);}
 z=cll(c);
 W(i<16){if(l&1<<i)z=j3(psh(0,i),z,pop(0,i));++i;}
 R j3(y,z,r);}

ZI dh(K x,ST st){I t=T[xi-'a'];R 14==t?-2:13==t?-4:2*t-26;}

ZK d(I r,K x,ST st){
  //O("d x %llx\n",x);o(x);
 P(Ax,(r=q(x))?M|=1<<r,u(r,c0()):x)
 I s=15&r,a;K y,z;
 y=xy;switch(cl(a=*xC)){
  case'N':C('W',R w(x,st))
  C('$',R u(r,v(r,x,1,st)))
  C('{',R E(r,x,st))
  C('[',R g(26,x,st))
  C('a',R T[a-'a']?O2(0,1+dh(xx,st),s,d(0,xx,st),d(0,y,st)):g(a-'a',x,st))
  C(0,R y=d(0,y,st),O2(t(x),U(a-128),yu,y,d(s,xz,st)))
  default:
  if(':'==a){
    P(Ay,r=L[yi-'a'],M&=~(1<<r),f(r,xz,st))y=d(0,yy,st),z=e(s,xz,st),x=xy;R r=zu,u(r,j2(z,O2(0,dh(xx,st),r,d(0,xx,st),y)));}
  I m,b=t(y);
  P(3>xn, //!< monadic ops
    '&'==a?SH(b,e(0,y,st)):
    '%'==a?y=e(0,y,st),u(s,j2(y,cv(s,yu))):
    '\\'==a?y=e(s,y,st),O2(b,1,s,u(yu,c0()),y):
    O2(0,
      '#'==a?-3:
      '*'==a?1+dh(y,st):
      '/'==a?4:U(a),
      s,
      e(s,y,st),
      kc(128+('#'==a?-1:'*'!=a))))
  z=xz;a=U(a),r=U('<')<a||16-r?r:0;
  P(!Ay&&!q(y)&&!Az&&!q(y),
    M|=1<<(m=D[KF==b]++),y=e(0,y,st),M&=~(1<<m),z=O2(b,a,r,y,f(m,z,st)),--D[KF==b],z)
  R Ay&&!q(y)&&2-a&&4-a //!< dyadic ops
      ?O2(b,U('<')<=a?11-a+11:a,r,e(s,z,st),y)
      :O2(b,a,r,e(s,y,st),d(s,z,st));}}

//!bracket balancer
Z_ I m2(S s,S t){R*s==*t&&s[1]==t[1];}ZS bq(S x){W((x=sc(++x,'"'))&&!({I i=0;W('\\'==x[--i]);1&i;})){};R x;}//!< parse quoted string with esc sequences
S bb(S x){C b[BLIM];I n=0,a;S s;x-=1;W(*++x){$(m2((S)" /",x),s=sc(x,'\n');P(!s,n?x:0)x=s)$('"'==(a=cl(*x)),s=bq(x);P(!s,x)x=s)$(sc("{[(",a),P(BLIM==++n,x)b[n]=*x)if(sc("}])",a))P(!n||b[n--]!=*x-1-*x/64,x)}R n?x:0;}//!< bracket balancer

//! parse[->compile->link->exec]
K pcle(S tp,I dbg){ST0(tp);//pst t;ST st=&t;sA=M=0;sN=8;D0=D1=1;N(26,L[i]=T[i]=0)N(26,O("%d %d\n",L[i],T[i]))
 S b=bb(tp);P(b,qs(*b?b:(S)"bal")) //<! scan the whole tape and bail on unbalanced "{[( or excessive nesting

#ifndef SYMS
 if(!tp[1]){if(26u>*tp-'a'){K x=GGG[*tp-'a'];Qs(NL==x,tp)P(FN(x),os((S)xx),dis(xy),NL)}R qs(tp);}//!< KPC FIXME quick temporary hack to pretty print-opcodes by referencing function name
#else
 S tmp=Ss;B Tk=tk();
 if(ID(*tmp)&&ARGOPN-*Ss){
  $(':'-*Ss,
   Ss-=Ss-tmp;
   P(!*Ss,o(Tk->v),NL)//$(FN(x),os((S)xx),dis(xy)) FIXME
   Qs(NL==Tk->v,Tk->k));
 }
#endif

#ifndef SYMS
 S r=!LP(*Ss)&&ARGOPN==Ss[1]&&(r=sc(Ss,ARGCLS))&&*++r?r:0; //!< FIXME function assignment is a lookahead hack
 K*kkk=(r||':'==Ss[1])?sA=*Ss,Ss+=2,GGG+sA-'a':0;
#else
 S r=!LP(*Ss)&&ARGOPN==*Ss&&(r=sc(Ss,ARGCLS))&&*++r?r:0;   //!< FIXME function assignment is a lookahead hack
 K*kkk=(r||':'==*Ss)?sA=*Ss,Ss++,&Tk->v:0; // FIXME
#endif

 P('!'==*Ss,++Ss,XXX(kkk,enm(ki(ip(Ss,sl((V*)Ss))))))     //!< parse and assign a global vector x:!int FIXME generalize
 z=k2(kp(Ss-!!kkk),NL);                                   //!< (src;shellcode)

#ifndef SYMS
 if(!Ss[1]&&26u>*Ss-'a')r1(GGG[*Ss-'a']);                 //!< inc xr of the referenced global var
#else
 if(!Ss[1]&&26u>*Ss-'a')r1(Tk->k);                        //!< inc xr of the referenced global var
#endif

 if(r){                                                   //!< function definition
  XXX(kkk,k2(r1(zx),u(KI,c2(1,1))));                      //!< parse arguments
  N(r-Ss-1,
    L[23+i]=D0++,
    T[23+i]=l((S)" chijefs CHIJEFS",Ss[i])
  )Ss=r;}                                                 //!< FIXME increase argcount limit, more than 3 args segfaults

 K x=p();
 P(dbg,r0(z),x);                                          //!< dump parse tree
 N(23,if(Ti)Li=D[KF==Ti]++)                               //!< set addresses of local vars (i>23 is xyz)

 I qfv=Ax||'$'-*xC;                                       //!< f/v function or value
 zy=j2(X0(qfv?f(0,x,st):v(0,x,0,st)),c3(RET,D0,D1));
 zy=u(t(x),zy);x=zy;

 //dis(x);
 dmp((S)"raw.bin",(S)x,xn-2);                             //!< disasm and dump
 lnk(x,z,sA);
 //dis(x);
 dmp((S)"lnk.bin",(S)x,xn-2);

 // kkk!=0 is an assignment: function values are (src;bin) tuples,
 // everything else gets assigned with the evaluation result.
 // non-assignining expressions return their value to the printer.
#ifndef SYMS
 R kkk?XXX(kkk,r?z:Z0(ex(z))):z;
#else
 O("ASSIGN kkk %llx z %llx r %d\n",kkk,z,r);
 R kkk?XXX(&Tk->v,r?z:Z0(ex(z))):z;
#endif
}

K ps(S tp){R pcle(tp,0);} //!< p->c->l->e

//!< ("[i]{source}";0xrtype0xopcodes0xconsts) xyu is return type k|f|j
K1(ex){obj o;R o.code=(V*)xy,KS<xyu?o.k():KF==xyu?kf(o.f()):ki(o.j());}

//:~
