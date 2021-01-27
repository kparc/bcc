#pragma GCC diagnostic ignored "-Wempty-body"
#include"b.h"
#include"h.h"

K XXX(K*k,K y){R r0(*k),*k=y,NL;}      //!< release an existing K object under pointer x and replace it with y
C ID(CP p){R!!sc((S)"aNW_",cl(p));}    //!< valid identifier chars
ZS qt(){R sc(";})]",*Ss);}             //!< valid expression terminators

#ifdef SYMS                            //!< global namespace api
K gget(B b){R(&b->k)[-1];}ZC gpos(B x){AB("nyi gpos");}K*GLO(K x){B y=hget(GT,xC,xn);R&y->v;}
CP nxt(ST st){S s=Ss;Ss=cp(Ss,&Pt);R Pn=Ss-s,Pt;}//!< return next cp on tape and paste its length into Pn
B tok(ST st){S r=Ss;W(nxt(st)&&ID(Pt)){};Ss-=Pn;R hget(GT,r,Ss-r);}
#endif

ZK Na(){S r=Ss;W(10u>*++Ss-'0'||'.'==*Ss){};I f=0;N(Ss-r,f|='.'==r[i])R f?kf(fp(r,Ss-r)):ki(ip(r,Ss-r));}//!< parse numbers, int|fp (floats as 1e6 must contain a dot)

// encode integers up to 127 as bytes with the highest bit set
// other numbers are appended at the end of z and return index
// (indices <16 correspond to registers, zn-3 is the index in
// the z is of K vals: z[0] is the source and z[1] is opcodes)
ZK n(K x){R kc(KI==Ax&&129u>1+xi?128+xi:(z=jk(z,x),16+zn-3));}

#define f(x,b) pF(x,b,st)
#define E(a,c) pE(a,c,st)

ZK pF(K x,I b,ST st){       //!< promote rettype to float if needed
  O("pF x %llx b %d Ax %d b %d t(x) %d\n",x,b,Ax,b,t(x));
  R KF-b||KF==t(x)
    ?x
#ifndef SYMS
    :Ax&&126<xi
      ?n(kf(xi-128))
#endif
      :u(KF,k2c('%',x));}

ZK pE(I a,I c,ST st){        //!< parse an expr: c operator, a optional rettype
 K r=k1(kc(c)),x;            //!< store operator as char in K array
 do r=jk(r,x=qt()            //!< append parse trees of subsequent exprs to r
      ?n(ki(0))              //!< null-terminate expr when reached ;})]
      :p());                 //!< parse the next expression
 W(';'==*Ss++);              //!< semicolon is the only expression separator (FIXME multiline)
 R u(a?a:t(x),r);}           //!< force return type, if any, or use type of the last expr

#ifndef SYMS
//! class                   !""#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
I cl(CP c){P(!c,0)R 128>c?"  \"+$++ ()++ + +0000000000+;+++  aaaaaaaaaaaaaNaaaaaaaaWaaa[+]+_`aaaaaaaaaaaaaaaaaaaaaaaaaa{+} "[c-32]:0;}
#else
//! class                   !""#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
I cl(CP c){P(!c,0)R 128>c?"  \"+$++ ()++ + +0000000000+;+++  aaaaaaaaaaaaaNaaaaaaaaWaaa[+]+_`aaaaaaaaaaaaaaaaaaaaaaaaaa{+} "[c-32]:"\0aga++"[UC(c)];}
#endif

//! parse next codepoint on tape
K _p(ST st){K x,y;CP a;I b;  //!< a operator, x/y operands, b return type
 C qn='0'-cl('-'==(a=*Ss++)?Ss['.'==*Ss]:'.'==a?*Ss:a); //!< special case: if expr starts with a minus, dot or a minus-dot, it may be a number
 C cls=qn?cl(a):'0';

#ifdef SYMS
 cls=LP(cls)&&'('-Ss[1]?'a':cls; //!< special case: if N|W is not followed by (, force class to identifier
#endif

 switch(cls){                //!< current char class:
  case'N':T[sN++]=KI;        //!< 'for' loop, declare a loop variable and fallthrough to W
  C('W',R                    //!< W|N(cnd){body}
   ++Ss,x=p(),++Ss,          //!< parse cnd expr into x
   x=k3(kc(a),x,p()),        //!< x is (W|N,cnd,body)
   sN-='N'==a,x)             //!< undeclare loop var for N
  case'$':++Ss;              //!< $[ctf], fallthrough
  C('{',R E(0,a))            //!< inner scope, parse enclosed expressions
  C('+',R x=p(),             //!< operator: parse right operand and store rettype in xu:
   u('#'==a?KI:              //!< count #x is int
     '%'==a?KF:              //!< division x%y is float
      t(x)-8*('*'==a),       //!< dereference *x is list type
      k2c(a,x)))             //!< other ops inherit type of right operand
  C('[',R E(X2,a))           //!< parse a dyadic expression inside square brackets
  C('(',x=p(),++Ss)          //!< parse fenced expression
  C('0',                     //!< number:
    P('2'==a&&'*'==*Ss,      //!< translate 2*x into bitwise left shift (\x)
     ++Ss,x=p(),             //!< skip 2* and parse the right operand
     u(t(x),k2c('\\',x))     //!< inherit type of x and return monadic tuple
    )--Ss;x=n(Na()))         //!< parse a number
  case'a':                   //!< identifier:
#ifdef SYMS
    {--Ss;B t=tk();K y=gget(t); //!< tk() scans an identifier and stores it in the hash table
#endif
    x='['==*Ss?++Ss,E(       //!< a) if followed by [expr], it is an array indexing or a function call:
#ifndef SYMS
     T[b=a-'a']?T[b]-8:      //!< if varname has no type, it is a func call; for arrays, unset high bit
      (x=GGG[b],x=xy,        //!< xx is the string, xy is the code
#else
     T[b=gpos(t)]?T[b]-8:    //!< if varname has no type, it is a func call; for arrays, unset high bit
      (x=y,x=xy,             //!< xx is the string, xy is the code
#endif
       D0=MX(D0,xC[xn-2]),   //!< D[0] and D[1] are stored after RET
       D1=MX(D1,xC[xn-1]),xu),
#ifdef SYMS
     y                       //!< op is the array|function name.
    ):ks(t->k);};break;      //!< b) it is a variable reference.
#else
     a                       //!< op is the array|function name.
    ):ks(a);break;           //!< b) it is a variable reference.
#endif
  default:R AB(Ss-1);}       //!< bail on unmapped class or whitespace

 P(qt(),x)                   //!< if reached expr end, return the parse tree
 P('+'-cl(a=*Ss++),AB(Ss-1)) //!< otherwise next char should be an operator, bail if not
 if(':'==*Ss)++Ss,a+=128;    //!< for assignment, set high bit of op char byte
 y=p();b=t(y);               //!< parse right operand into y and get its type into b
#ifndef SYMS
 $(':'==a&&Ax,T[xi-'a']=b)   //!< for assignment, set result type to the type of the right operand
#else
 $(':'==a&&Ax,T[(*(I*)x)-'a']=b)  //!< for assignment, set result type to the type of the right operand
#endif
 b='%'-a?MX(b,t(x)):KF;      //!< for div, force it to float, for the rest, use the widest one (KF>KJ>KI>KC)
 O("END p() b %d\n",b);

 R u(U('<')<=U(a)?KI:b,      //!< if operator is a comparison (<=>), force return type to int
 k3(kc(a),f(x,b),f(y,b)));}  //!< return (op,left,right)

//S('0'-c('-'==(a=*s++)?s['.'==*s]:'.'==a?*s:a)?c(a):'0',case'N':T[sN++]=KI;
// C('W',R++s,x=p(st),++s,x=k3(kc(a),x,p(st)),sN-='N'==a,x)case'$':++s;C('{',R Ee(0,a,st))
// C('+',R x=p(st),u('#'==a?KI:'%'==a?KF:t(x)-8*('*'==a),k2(kc(a),x)))C('[',R Ee(12,a,st))C('(',x=p(st),++s)C('0',P('2'==a&&'*'==*s,++s,x=p(st),u(t(x),k2(kc('\\'),x)))--s;x=n(Na()))
// C('a',x='['==*s?++s,Ee(T[b=a-'a']?T[b]-8:(x=G[b],x=xy,D0=MX(D0,x[xn-2]),D1=MX(D1,x[xn-1]),xu),a,st):kc(a)),AB(s-1))

//:~
