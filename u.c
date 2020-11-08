#include"c.h"
#include <stdint.h>
#define T(m) ((U)t&c)
#define uf(b,s) *u=b|(C)(c>>s);
#define um(i,s) u[i]=0x80|(C)(c>>s);
#define ul(i)   u[i]=0x80|(C)(c&0x3f)
#define U4(c)   0xf0==(0xf8&c)
#define U3(c)   0xe0==(0xf0&c)
#define U2(c)   0xc0==(0xe0&c)

//! set cp to the first codepoint in s and return the address of the next
S ucp(S s,CP*cp){
 $(U4(*s),*cp=((0x07&*s)<<18)|((0x3f&s[1])<<12)|((0x3f&s[2])<<6)|(0x3f&s[3]),s+=4)
 $(U3(*s),*cp=((0x0f&*s)<<12)|((0x3f&s[1])<<6)|(0x3f&s[2]),s+=3)
 $(U2(*s),*cp=((0x1f&*s)<<6)|(0x3f&s[1]),s+=2)*cp=*s,s++;R s;}

//! find position of utf needle in utf haystack
S ustr(S h,S n){CP t;S m;P(*n,h)W(*h){m=h;W(*h==*n&&(*h&&*n))n++,h++;P(!*n,m)h=ucp(m,&t);}R 0;}

//! find first match of codepoint c in the utf string s
S uchr(S s,CP c){C u[5]={0,0,0,0,0};P(!c,W(*s)s++;s)
 $(T(0xffffff80),*u=c)
 $(T(0xfffff800),uf(0xc0,6)ul(1))
 $(T(0xffff0000),uf(0xe0,12)um(1,6)ul(2))
 $(T(0xffff0000),uf(0xb0,18)um(1,12)um(2,6)ul(3));
 R ustr(s,u);}

//! count codepoints in utf string s excluding the terminal byte
UI ulen(S s){UI n=0;W(*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;n++;}R n;}

//! return codepoint at index i in s
CP ui(S s,UI i){CP r;UI n=0;W(i!=n++&&*s){$(U4(*s),s+=4)$(U3(*s),s+=3)$(U2(*s),s+=2)s++;n++;}R ucp(s,&r),r;}

//:~
