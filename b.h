#include"a.h"

#ifdef ISOMORPH
#define ARGOPN '('
#define ARGCLS ')'
#else
#define ARGOPN '['
#define ARGCLS ']'
#endif

//! scope accessors
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

K p(ST),l1(),u(I,K),Na();I U(I i),_t(K x,S sT);

//:~