#include"a.h"

typedef union{V*code;K(*k)();F(*f)();J(*j)();}obj; //!<signatures of compiled funs

// local scope:
// D0 local vars/args, D1 local floats
// L/T values and types of D
// N loop counter var name (i,j,k,l..) 
// M used register count
typedef struct{C L[26];C T[26];I M;C D[2];C N;I A;}pst;typedef pst*ST;

//! shortcuts for scope:
#define L  st->L
#define D  st->D
#define T  st->T
#define M  st->M
#define sN st->N
#define sA st->A
#define D0  D[0]
#define D1  D[1]
#define Di  D[i]
#define Li  L[i]
#define Ti  T[i]
#define q(x) _q(x,L)
#define t(x) _t(x,T)

K p(ST),l1(),u(I,K),Na();I U(I i),_t(K x,S sT),c(I c);

//:~