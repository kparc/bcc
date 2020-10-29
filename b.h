typedef struct{C L[26];C T[26];I M;C D[2];C N;I A;}pst;typedef pst*ST;ZK d(I,K,ST);
typedef union{V*code;K(*k)();F(*f)();J(*j)();}ret;//!<signatures of compiled code
#define L st->L
#define D st->D
#define T st->T
#define M st->M
#define sN st->N
#define sA st->A
#define D0 D[0]
#define D1 D[1]
#define Di D[i]
#define Li L[i]
#define Ti T[i]
#define q(x) _q(x,L)
#define t(x) _t(x,T)
