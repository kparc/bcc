#include"a.h"
#include"b.h"

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xtype:opcodes:stack
K u(I,K),Na();I U(I i),_t(K x,S sT);K p(ST);

I l(S s,I c){S t=sc(s,c);R t?t-s:0;}
ZS qt(){R sc(";})]",*Ss);}I U(I i){R l(" +-*% &|  <=>",i);}
ZK n(K x){R kc(KI==Ax&&129u>1+xi?128+xi:(z=jk(z,x),16+zn-3));}
ZK Ee(I a,I c,ST st){K r=k1(kc(c)),x;do r=jk(r,x=qt()?n(ki(0)):p(st));W(';'==*Ss++);R u(a?a:t(x),r);}
ZK pF(K x,I b,ST st){R KF-b||KF==t(x)?x:Ax&&126<xi?n(kf(xi-128)):u(KF,k2(kc('%'),x));}

//! class          !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
I c(I c){R 128>c?"   +$++ ()++ + +0000000000+;+++  aaaaaaaaaaaaaNaaaaaaaaWaaa[+]  `aaaaaaaaaaaaaaaaaaaaaaaaaa{+} "[c-32]:0;}
// !til #cnt %div     *mul|frst +sum|inc -sub|dec     &and |or /shr \shl   <=>leg    ;sep      $[c;t;f] N(times){} W(true){}

//! \todo cst xor mod neq not flr ...

//! parse
K p(ST st){K x,y;I a,b;
 switch('0'-c('-'==(a=*Ss++)?Ss['.'==*Ss]:'.'==a?*Ss:a)?c(a):'0'){
  case'N':T[sN++]=KI;
  C('W',R++Ss,x=p(st),++Ss,x=k3(kc(a),x,p(st)),sN-='N'==a,x)
  case'$':++Ss;
  C('{',R Ee(0,a,st))
  C('+',R x=p(st),u('#'==a?KI:'%'==a?KF:t(x)-8*('*'==a),k2(kc(a),x)))
  C('[',R Ee(12,a,st))
  C('(',x=p(st),++Ss)
  C('0',P('2'==a&&'*'==*Ss,++Ss,x=p(st),u(t(x),k2(kc('\\'),x)))--Ss;x=n(Na()))
  case'a':x='['==*Ss?++Ss,Ee(T[b=a-'a']?T[b]-8:(x=G[b],x=xy,D0=MX(D0,x[xn-2]),D1=MX(D1,x[xn-1]),xu),a,st):kc(a);break;
  default:AB(Ss-1);}
 P(qt(),x)if('+'-c(a=*Ss++))AB(Ss-1);if(':'==*Ss)++Ss,a+=128;
 y=p(st);b=t(y);
 $(':'==a&&Ax,T[xi-'a']=b)b='%'-a?MX(b,t(x)):KF;
 R u(9<U(a)?KI:b,k3(kc(a),pF(x,b,st),pF(y,b,st)));}

//S('0'-c('-'==(a=*s++)?s['.'==*s]:'.'==a?*s:a)?c(a):'0',case'N':T[sN++]=KI;
// C('W',R++s,x=p(st),++s,x=k3(kc(a),x,p(st)),sN-='N'==a,x)case'$':++s;C('{',R Ee(0,a,st))
// C('+',R x=p(st),u('#'==a?KI:'%'==a?KF:t(x)-8*('*'==a),k2(kc(a),x)))C('[',R Ee(12,a,st))C('(',x=p(st),++s)C('0',P('2'==a&&'*'==*s,++s,x=p(st),u(t(x),k2(kc('\\'),x)))--s;x=n(Na()))
// C('a',x='['==*s?++s,Ee(T[b=a-'a']?T[b]-8:(x=G[b],x=xy,D0=MX(D0,x[xn-2]),D1=MX(D1,x[xn-1]),xu),a,st):kc(a)),AB(s-1))
