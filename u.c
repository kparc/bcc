#pragma GCC diagnostic ignored "-Wunsequenced"
#pragma GCC diagnostic ignored "-Wsequence-point"

#include"a.h"
//extern I clz(I n);
Z_ UI clz(UI x){R __builtin_clz(x);}

#define ff      (0x3f&*s++)
#define M(m)    (!((CP)m&c))
#define uf(b,s) *d=b|(C)(c>>s);
#define um(i,s) d[i]=0x80|(C)(c>>s);
#define ux(i,x) d[i]=0x80|(C)((x)&0x3f)
#define ut(i)   ux(i,c)
#define ue(b,s) case b:ux(w-(b-1),c>>s);
#define U4(c)   0xf0==(0xf8&c)
#define U3(c)   0xe0==(0xf0&c)
#define U2(c)   0xc0==(0xe0&c)

//! set cp to the first codepoint in s and return the address of the next cp
S cp(S s,CP*cp){R*cp=U4(*s)?(0x07&*s++)<<18|ff<<12|ff<<6|ff:U3(*s)?(0x0f&*s++)<<12|ff<<6|ff:U2(*s)?(0x1f&*s++)<<6|ff:*s++,s;}
S us(S h,S n){CP t;S m,s;P(!*n,h)W(*h){m=h;s=n;W(*h==*s&&(*h&&*s))h++,s++;P(!*s,m)h=cp(m,&t);}R 0;}//!< position of utf needle in utf haystack
S uc(S s,CP c){C d[5]={0,0,0,0,0};P(!c,W(*s)s++;s)$(M(0xffffff80),*d=(C)c)//!< find first match of codepoint c in the utf string s
 $(M(0xfffff800),uf(0xc0,6)ut(1))$(M(0xffff0000),uf(0xe0,12)um(1,6)ut(2))$(M(0xffff0000),uf(0xf0,18)um(1,12)um(2,6)ut(3));R us(s,d);}
UI ul(S s){UI n=0;W(*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;n++;}R n;}//!< count codepoints in utf string s excluding terminal
CP at(S s,UI i){CP r=0;UI n=0;W(i-n++&&*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;}R cp(s,&r),r;}//!< return codepoint at index i in s
C cw(CP c){P(!c,1)static const C l[32]={1,1,1,1,1,1,1,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,6,7};R l[31-clz(c)];}//!< codepoint width in bytes
//V uen(CP c,S d){C w;S(w=cw(c),ue(7,30)ue(6,24)ue(5,18)ue(4,12)ue(3,6)ue(2,0)*d=(0xFF00uL>>w)|(c>>(6*w-6));break;C(1,*d=(C)c));R w;}//!< encode cp into buffer d (<=7 bytes)

//:~
