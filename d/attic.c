//#define PW2(x) (x&&!(x&x-1)) //!< is integer n x power of 2
//I main(){asm("movl $0x9fc0,-4(%rsp);ldmxcsr -4(%rsp);lea 8(%rsp),%rdi;jmp _km");}
//V csr(){R;asm("movl $0x9fc0,-4(%rsp);ldmxcsr -4(%rsp);");}

//K qi(I i){R qs((S[]){"nyi","rank","length","type","domain","value"}[i]);} //!< \fixme humans prefer this to segv

//! \todo format c:
//ZK1(rd1){QC(x)x=jc(x,0);I d=open(x,0);Qs(0>d,x)J b[16];fstat(d,b);R x=X0(511+ma(0,0,0,b[6]+4096)),xm=-1,xt=KC,ma(0,d,x,xn=b[6]),W+=xn,x;}(W-=xn,mu(x-511,xn+4096))
//ZK2(wr1){QC(x)x=jc(x,0);QC(y)unlink(x);I d=open(x,0102,0666);Qs(0>d,x)ftruncate(d,yn);R x=X0(ma(1,d,0,yn)),dsn(x,y,yn),mu(x,yn),Y0(NL);}
//K1(rd0){R Ss(0,rd1(x));} //{-1_'(0,1+&x=y)_y} K2(wr0){R wr1(x,sS(0,y));} //{,/x,'y}
//ZI rand(){ZJ j0=-314159;R j0=4294957665L*j0+(j0>>32);}

//! b.c prototype code
//asm("push %rbp;push %rbx");asm("pop %rbx;pop %rbp");MIN(y^(x^y)&x-y>>63)I low()__builtin_ctz(~i&-2);}V qq(I o,I r,I x,I y){oc(":+-*%?  c"[o]),oc('0'+r),oc('0'+x),oi(y);}
/* K1(ev){S s=xy;ZF M[16];ZJ A[999],*a=A+999,L[16],c,f;I b(){f&=7;R!f||(4>f?c==f-2:c!=f-6);}
#define G(n,T,t) C(n,((t*)L[15&r])[l(*s++)]=T[r>>4])C(n+1,T[r>>4]=((t*)L[15&r])[l(*s++)])
J l(I c){R 16>c?L[c]:32>c?(I)xJ[2+c-16]:124>c?(J)G[c-'a']:c-128;} J j2(I i,J x,J y){R!i?y:1==i?x+y:2==i?x-y:3==i?x*y:4==i?x>>y:5==i?x<<y:x&y;}
F m(I c){R 16>c?M[c]:32>c?   xF[2+c-16]:*(F*)(G+c-'a');}          F f2(I i,F x,F y){R!i?y:1==i?x+y:2==i?x-y:3==i?x*y:x/y;}
W(*s){f=*s++;I r=*s++;$(1==f,$(25<r,*L=(J)l1((K)L[1],(K)L[2],(K)L[3]))ev(G[r]))$(16>f,L[r]=b())$(24>f,s+=b()?(signed char)r:0)$(32>f,s+=3;s+=b()?*((I*)s-1):0)$(64>f,
S(31&f,C(0,*--a=L[r])C(1,L[r]=*a++)C(2,c=L[r]?1:0)C(3,oi(L[r]))                  C(6,J j=l(*s++);c=L[r]<j?-1:L[r]>j)G(12,L,I)G(14,L,J),L[r>>4]=j2(f-48,L[15&r],l(*s++))))
S(31&f,C(0,*--a=M[r])C(1,M[r]=*a++)C(2,c=M[r]?1:0)C(3,of(M[r])) C(4,M[r]=L[*s++])C(6,F f=m(*s++);c=M[r]<f?-1:M[r]>f)                  ,M[r>>4]=f2(f-80,M[15&r],m(*s++)))}
R x=xy,KS<xu?(K)*L:KF==xu?kf(*M):ki((I)*L);}V1(lnk){}K ps(S s){K z;I a=0;I ln(S s){I c=*s&31;R!*s?1:32>*s||4>c?2:15>*s?5:3;}I j(I t){R KF==t?32:0;}C B=2,RET=0,JJ[]={16,17,18,19,24,21,22,23};
K cc(I o,I r){R c2(8+o,r);}K Jj(K x,I n){R c5(8+x[xn],n-3);}K cll(I c){R c2(1,c);}K psh(I t,I r){R c2(32+j(t),r);}K pop(I t,I r){R c2(33+j(t),r);}K tst(I t,I r){R c2(34+j(t),r);}
K sh(I t,I r){R c2(35+j(t),r);}K cv(I x,I y){R c3(36+32,x,y);}K cm(I t,I x,I y){R c3(38+j(t),x,y);}K o2(I t,I o,I r,I x,I y){R c3(48+o+j(t),16*r+x,y);}*/

//! original x64 spec
// :+-*% ^&|<=>  x64 JJ Jj o2 cc tst RET cll psh pop acdbsbsd89..  o[m[s|d]] c3 eb+1 e8+4 e9+4 [f2/66/4*][0f] 5* 7*+1 b*+4 0f8*+4  03 23 2b 3b (6b 83) 89 8b ..
