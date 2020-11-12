#include"t.h"

UNIT(utf,
   CP c0,c1,c2;C*t[]={
      "a\0",
      "\xce\x93\0",
      "\xe1\xbd\xb6\0",
      "\xf0\x90\x8d\x88\0",
      "\xf0\x9d\x91\x97\xf0\x9d\x91\x98\xf0\x9d\x91\x99\x20\xd0\x90\xd0\x91\xd0\x92\0"}, //𝑗𝑘𝑙 АБВ
      *gr="αβγδεζηθικλμνξοπρςστυφχψω",
      *cy="Мне отмщение, и аз воздам";
         //0123456789012345678901234

   S ustr0=(S)"\xce\x9e\xce\xb5\xcf\x83\xce\xba\xce\xb5\xcf\x80\xce\xac\xce\xb6"
              "\xcf\x89\x20\xcf\x84\xe1\xbd\xb4\xce\xbd\x20\xcf\x88\xcf\x85\xcf"
              "\x87\xce\xbf\xcf\x86\xce\xb8\xcf\x8c\xcf\x81\xce\xb1\x20\xce\xb2"
              "\xce\xb4\xce\xb5\xce\xbb\xcf\x85\xce\xb3\xce\xbc\xce\xaf\xce\xb1",
              //i uncover the soul-destroying abhorrence

     ustr1=(S)"イロハニホヘト チリヌルヲ ワカヨタレソ ツネナラム ウヰノオクヤマ ケフコエテ アサキユメミシ ヱヒモセスン";

   //! ul()
   EQ_I(ul(t[0]),            1,     "single 1-byte codepoint should have length 1")
   EQ_I(ul(t[1]),            1,     "single 2-byte codepoint should have length 1")
   EQ_I(ul(t[2]),            1,     "single 3-byte codepoint should have length 1")
   EQ_I(ul(t[3]),            1,     "single 4-byte codepoint should have length 1")
   EQ_I(ul(t[4]),            7,     "test vector length should match expected")
   EQ_I(ul(gr),             25,     "test vector length should match expected")
   EQ_I(ul(cy),             25,     "test vector length should match expected")
   EQ_I(ul(ustr0),          33,     "test vector length should match expected")
   EQ_I(ul(ustr1),          55,     "test vector length should match expected")

   //! at()
   EQ_I(at(cy,0),       0x041c,     "utf indexing test #1") // M
   EQ_I(at(cy,7),       0x0449,     "utf indexing test #2") // щ
   EQ_I(at(cy,24),      0x043c,     "utf indexing test #3") // м
   EQ_I(at(gr,15),      0x03c0,     "utf indexing test #4") // π
   EQ_I(at(gr,100),          0,     "utf indexing test #5") // 0
   EQ_I(at(gr,-100),         0,     "utf indexing test #6") // 0

   //! us()
   EQ_I(us(gr,"λ")-gr,      20,     "position of λ must be 20")
   EQ_I(us(cy,"дам")-cy,    39,     "position of 'дам' must be 39")

   //! cp()
   S r=cp(cy,&c0);r=cp(r,&c1);r=cp(r,&c2);
   EQ_I(c0,             0x041c,     "codepoint scan #1")// M
   EQ_I(c1,             0x043d,     "codepoint scan #2")// н
   EQ_I(c2,             0x0435,     "codepoint scan #3")// e

   //! uc()
   EQ_I(uc(gr,0x03c0)-gr,   30,    "position of π should be 30")
   EQ_I(uc(cy,',')-cy,      23,    "position of comma must be 23")

   //! UC()
   char*rng="ΑωАяĀɏ∀⋿⌀⍺𝑗";C rcl[]={Ug,Ug,Uc,Uc,Ul,Ul,Um,Um,Ua,Ua,UQ};
   CP c,i=0;S tp=rng;W((tp=cp(tp,&c))&&c)EQ_I(UC(c),rcl[i++],"unicode range classes should match expected");
)

//:~
