typedef struct rl_t {I orig_line_len;I escape_seq;I hist_cur;I cursor_pos;G escape_seq_buf[1];S prompt;} rl_t;
enum {NOP,ESC,ESCBKT,ESCBKT0,ESCO};

_ rl1(),rl2(),rl0(),rlprmt(S p);I rlchar(I c);K rline();//init|destroy|prompt|parse|result

#define LMX   200 //line length
#define HSZ   16  //history buf

#define CTL_A (1)
#define CTL_B (2)
#define CTL_C (3)
#define CTL_D (4)
#define CTL_E (5)
#define CTL_F (6)
#define CTL_K (11)
#define CTL_N (14)
#define CTL_P (16)
#define CTL_U (21)
#define CTL_W (23)

#define xr xI[-3]
#define yr yI[-3]
#define rr rI[-3]
#define xm xG[-16]

#define txn(s,n) stdout_send(s,n)
#define ltx(s) txn(s,strlen(s));
#define cin(l,r) ((l)<=(c)&&(c)<=(r))
#define qes(x) RL.escape_seq_buf[0]==x //is escape
#define BCK(n) redraw_step_back=(n)
#define FWD(n) redraw_step_forward=(n)
#define RFC(n) redraw_from_cursor=(n)
#define POS RL.cursor_pos
#define SETPOS BCK(POS-RL.orig_line_len),FWD(rn-RL.orig_line_len),RFC(1)
#define RESC RL.escape_seq=NOP
#define HOME goto home_key
#define END goto end_key
#define RESET goto reset_esc

#define trc(s,r) ({K x=r;printf("%s %llx xt %d xn %d xr %d ax %d xm %d\n",s,x,xt,xn,xr,ax,xm);})
#define trc(s,r)
