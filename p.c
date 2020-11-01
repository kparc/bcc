#include"b.h"
// !til #cnt %div  *mul|frst  +sum|inc -sub|dec &and |or /shr \shl   <=>leg  ;sep    $[c;t;f] N(times){} W(true){}
// \todo xor cst mod neq not flr ...

extern S Ss;extern K z;//!< \Ss tape \z zx source zy 0xrtype:opcodes:stack

// encode integers up to 127 as bytes with the highest bit set,
// other numbers are appended at the end of z and return index
// (indices <16 correspond to registers, zn-3 is the index in
// the z is of K vals: z[0] is the source and z[1] is opcodes)
ZK n(K x){R kc(KI==Ax&&129u>1+xi?128+xi:(z=jk(z,x),16+zn-3));}
ZS qt(){R sc(";})]",*Ss);}//<! test whether current char is an expression terminator
ZK pE(I a,I c,ST st){K r=k1(kc(c)),x;do r=jk(r,x=qt()?n(ki(0)):p(st));W(';'==*Ss++);R u(a?a:t(x),r);}//!< expr \c cmd \a optional type or 0
ZK pF(K x,I b,ST st){R KF-b||KF==t(x)?x:Ax&&126<xi?n(kf(xi-128)):u(KF,k2(kc('%'),x));}
#include"p.h"//pE->E,pF->f

//! class          !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
I c(I c){R 128>c?"   +$++ ()++ + +0000000000+;+++  aaaaaaaaaaaaaNaaaaaaaaWaaa[+]+ `aaaaaaaaaaaaaaaaaaaaaaaaaa{+} "[c-32]:0;}

//! parse an expression
K p(ST st){K x,y;I a,b;    //!< a operator, x/y operands, b return type
 C qn='0'-c('-'==(a=*Ss++)?Ss['.'==*Ss]:'.'==a?*Ss:a);//<!special case: if expr starts with a minus, dot or a minus-dot, it may be a number
 switch(qn?c(a):'0'){      //!< current char class:
  case'N':T[sN++]=KI;      //!< 'for' loop, declare a loop variable and fallthrough to W
  C('W',R                  //!< W|N(cnd){body}
   ++Ss,x=p(st),++Ss,      //<! parse cnd expr into x
   x=k3(kc(a),x,p(st)),    //<! x is (W|N,cnd,body) 
   sN-='N'==a,x)           //<! undeclare loop var for N
  case'$':++Ss;            //!< $[ctf], fallthrough
  C('{',R E(0,a))          //!< inner scope, return enclosed expression
  C('+',R x=p(st),         //!< operator
   //!rettype: #x is int (count), x%y is float (div), *x is list type (first), others retain right operand type
   u('#'==a?KI:'%'==a?KF:t(x)-8*('*'==a),k2(kc(a),x)))
  C('[',R E(12,a))
  C('(',x=p(st),++Ss)      //!< parse fenced expression
  C('0',                   //!< number
    P('2'==a&&'*'==*Ss,++Ss,x=p(st),u(t(x),k2(kc('\\'),x)))//!< override 2*x as right shift /x and return
    --Ss;x=n(Na()))        //<! parse number
  C('a',                   //<! identifier:
    x='['==*Ss?++Ss,E(     //<! a) if followed by [exp], it is an array indexing or a function call:
     T[b=a-'a']?T[b]-8:    //<! if varname has no type, it is a func call; for arrays, unset high bit
      (x=G[b],x=xy,        //<! xx is the string, xy the code
       D0=MX(D0,x[xn-2]),  //<! D[0] and D[1] are stored after RET
       D1=MX(D1,x[xn-1]),xu),
     a                     //<! op is the array|function name
    ):kc(a))               //<! b) it is variable reference
  ,AB(Ss-1);}              //<! default: bail on unmapped class or whitespace

 P(qt(),x)                  //<! if reached expr end, return the parse tree
 if('+'-c(a=*Ss++))AB(Ss-1);//<! otherwise next char should be an operator, bail if not
 if(':'==*Ss)++Ss,a+=128;   //<! for assignment, set high bit of op char byte
 y=p(st);b=t(y);            //<! parse right argument into y and get its type into b
 $(':'==a&&Ax,T[xi-'a']=b)  //<! for assignment, set result type to the type of the right operand
 b='%'-a?MX(b,t(x)):KF;     //<! for div force it to float, for the rest take the widest (KF>KJ>KI>KC)

 R u(9<U(a)?KI:b,           //<! if U(a)>9 (<=> comparison) force rettype to int
  k3(kc(a),f(x,b),f(y,b)));}//<! return (op,left,right)

//S('0'-c('-'==(a=*s++)?s['.'==*s]:'.'==a?*s:a)?c(a):'0',case'N':T[sN++]=KI;
// C('W',R++s,x=p(st),++s,x=k3(kc(a),x,p(st)),sN-='N'==a,x)case'$':++s;C('{',R Ee(0,a,st))
// C('+',R x=p(st),u('#'==a?KI:'%'==a?KF:t(x)-8*('*'==a),k2(kc(a),x)))C('[',R Ee(12,a,st))C('(',x=p(st),++s)C('0',P('2'==a&&'*'==*s,++s,x=p(st),u(t(x),k2(kc('\\'),x)))--s;x=n(Na()))
// C('a',x='['==*s?++s,Ee(T[b=a-'a']?T[b]-8:(x=G[b],x=xy,D0=MX(D0,x[xn-2]),D1=MX(D1,x[xn-1]),xu),a,st):kc(a)),AB(s-1))
