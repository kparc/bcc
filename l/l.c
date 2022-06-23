#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include"b.h"
#include"l.h"

_ stdout_send(S s,I n){N(n,putchar(s[i]))}

B2(MA);i2(p2);ZK r=0,lH[HSZ]={0};static rl_t RL;K rl(){R r;}ZK1(r00){P(x&&x!=c0,xr=0,r0(x))}K an(K f,I n,K*x);A2(a2);
ZK _sp,_ct;ZK take(I x,K y){R r1(Y0(p2(14,ki(x),y)));}ZK drop(I x,K y){R r1(Y0(p2(15,ki(x),y)));}
ZK splice(I i,I c,K x){R r1(X0(an(_sp,3,(K*)(K[]){ki(i),kc(c),x})));}ZK cutout(I i,K x){R r1(X0(a2(_ct,ki(i),x)));}
_ rlinit(){_sp=_sp?_sp:p9(",/@[(0,2#x)^z;1;y]");_ct=_ct?_ct:p9(",/((0,x,x+1)^y)0 2");}

ZI last_line_len,redraw_step_back,redraw_step_forward,redraw_from_cursor;

_ rlprmt(S p){r=ss(""),RL.orig_line_len=POS=rn;RESC;RL.escape_seq_buf[0]=0;RL.hist_cur=-1;trc("rl_",r);RL.prompt=p;ltx(p);}
Z_ rlback(I n){P(n<=4,txn("\b\b\b\b",n))G VT[6];n=snprintf(&VT[0],sizeof(VT),"\x1b[%u",n);P(n>0,VT[n]='D';txn(VT,n+1))}
Z_ rlsave(K y){if(!yn||*lH&&MA(*lH,y)){if(y==c0)r0(c0);R;}r00(lH[HSZ-1]);I j;N(j=HSZ-1,lH[j-i]=lH[j-i-1])*lH=y;trc("save3",*lH);}
Z_ rlkill(U n){(_)n;ltx("\x1b[K");}_ rl1(){memset(lH,0,HSZ*sizeof(K));}_ rl0(){"nyi";}

ZI rldraw(){
    if(RL.hist_cur>=0){lH[RL.hist_cur]=r;}//update pointer
    if(redraw_step_back>0){rlback(redraw_step_back);POS -= redraw_step_back;}
    Z(redraw_from_cursor,
        if(rn < last_line_len)rlkill(last_line_len - POS);//erase old chars            
        txn(rG + POS, rn - POS);//draw new chars
        //move cursor forward if needed (already moved forward by length of line, so move it back)
        rlback(rn - (POS + redraw_step_forward));POS += redraw_step_forward)
    Z(redraw_step_forward>0,//draw over old chars to move cursor forwards
        txn(rG + POS, redraw_step_forward);POS += redraw_step_forward);R-1;}

I rlchar(I c){BCK(0),FWD(0),RFC(0),last_line_len=rn;SW(RL.escape_seq,
    C(NOP,
        P(c=='\n',txn("\r\n",2),rlsave(r),0)//commit line
        P(c==CTL_C||cin(CTL_A,CTL_E)&&!rn,-1)//^c or ctrl char on empty line
        Z(c==CTL_W,r=drop(POS,r),BCK(POS-RL.orig_line_len),RFC(1))//^w kill from caret to line start
        Z(c==CTL_K,r=take(POS,r),RFC(1))//^k kill from caret to line end
        Z((c==8||c==127)&&POS>RL.orig_line_len,r=cutout(POS-1,r),BCK(1),RFC(1))//del|bksp
        Z(cin(32,126),r=splice(POS,c,r),FWD(1),RFC(1))//ascii
        Z(c==CTL_A,HOME)Z(c==CTL_E,END)Z(c==27,RL.escape_seq=ESC);)//esc seq start
    C(ESC,RL.escape_seq=c=='['?ESCBKT:c=='O'?ESCO:NOP)
    C(ESCO,SW(c,C('H',HOME)C('F',END),RESET))
    C(ESCBKT,
        Z(cin('0','9'),RL.escape_seq=ESCBKT0,RL.escape_seq_buf[0]=c){RESC;
            Z(c=='A'&&RL.hist_cur+1<HSZ&&lH[RL.hist_cur+1],lH[RL.hist_cur]=r,r=lH[++RL.hist_cur],SETPOS;)//u
            Z(c=='B'&&RL.hist_cur>=0,lH[RL.hist_cur]=r;if(RL.hist_cur-->=0)r=lH[RL.hist_cur],SETPOS;)//d
            Z(c=='C'&&POS<rn,FWD(1))Z(c=='D'&&POS>RL.orig_line_len,BCK(1))//rl
            Z(c=='H',HOME)Z(c=='F',END);})
    C(ESCBKT0,
        Z(c=='~',
            Z(qes('1')||qes('7'),home_key:BCK(POS-RL.orig_line_len))
            Z(qes('4')||qes('8'),end_key:FWD(rn-POS))
            Z(qes('3')&&POS<rn,r=cutout(POS,r),RFC(1));
        );RESET),
    reset_esc:RESC)
    R rldraw();}

//:~