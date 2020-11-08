#pragma GCC diagnostic ignored "-Wunsequenced"
#include"c.h"
#include <stdint.h>

#define ff      (0x3f&*s++)
#define M(m)    (!((CP)m&c))
#define uf(b,s) *u=b|(C)(c>>s);
#define um(i,s) u[i]=0x80|(C)(c>>s);
#define ut(i)   u[i]=0x80|(C)(c&0x3f)
#define U4(c)   0xf0==(0xf8&c)
#define U3(c)   0xe0==(0xf0&c)
#define U2(c)   0xc0==(0xe0&c)

//! set cp to the first codepoint in s and return the address of the next cp
S cp(S s,CP*cp){R*cp=U4(*s)?(0x07&*s++)<<18|ff<<12|ff<<6|ff:U3(*s)?(0x0f&*s++)<<12|ff<<6|ff:U2(*s)?(0x1f&*s++)<<6|ff:*s++,s;}
S us(S h,S n){CP t;S m,s;P(!*n,h)W(*h){m=h;s=n;W(*h==*s&&(*h&&*s))h++,s++;P(!*s,m)h=cp(m,&t);}R 0;}//! position of utf needle in utf haystack
S uc(S s,CP c){C u[5]={0,0,0,0,0};P(!c,W(*s)s++;s)$(M(0xffffff80),*u=(C)c)//! find first match of codepoint c in the utf string s
 $(M(0xfffff800),uf(0xc0,6)ut(1))$(M(0xffff0000),uf(0xe0,12)um(1,6)ut(2))$(M(0xffff0000),uf(0xf0,18)um(1,12)um(2,6)ut(3));R us(s,u);}
UI ul(S s){UI n=0;W(*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;n++;}R n;}//! count codepoints in utf string s excluding terminal
CP at(S s,UI i){CP r=0;UI n=0;W(i-n++&&*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;}R cp(s,&r),r;}//! return codepoint at index i in s

//:~
