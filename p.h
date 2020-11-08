#pragma once

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

extern K p(ST),l1(),u(I,K);extern I U(I i),_t(K x,S sT),c(I c);

#define E(a,c) pE(a,c,st)
#define f(x,b) pF(x,b,st)

//:~