#include"t.h"

UNIT(utf,
   CP c0,c1,c2;C*t[]={
  /*0*/(S)"a\0",
  /*1*/(S)"\xce\x93\0",
  /*2*/(S)"\xe1\xbd\xb6\0",
  /*3*/(S)"\xf0\x90\x8d\x88\0",
  /*4*/(S)"\xf0\x9d\x91\x97\xf0\x9d\x91\x98\xf0\x9d\x91\x99\x20\xd0\x90\xd0\x91\xd0\x92\0"}, //𝑗𝑘𝑙 АБВ
       *gr=(S)"αβγδεζηθικλμνξοπρςστυφχψω",
       *cy=(S)"Мне отмщение, и аз воздам";
         //0123456789012345678901234
   S ustr0=(S)"\xce\x9e\xce\xb5\xcf\x83\xce\xba\xce\xb5\xcf\x80\xce\xac\xce\xb6"
              "\xcf\x89\x20\xcf\x84\xe1\xbd\xb4\xce\xbd\x20\xcf\x88\xcf\x85\xcf"
              "\x87\xce\xbf\xcf\x86\xce\xb8\xcf\x8c\xcf\x81\xce\xb1\x20\xce\xb2"
              "\xce\xb4\xce\xb5\xce\xbb\xcf\x85\xce\xb3\xce\xbc\xce\xaf\xce\xb1",
              //i uncover the soul-destroying abhorrence

     ustr1=(S)"イロハニホヘト チリヌルヲ ワカヨタレソ ツネナラム ウヰノオクヤマ ケフコエテ アサキユメミシ ヱヒモセスン ";
   CP ustr1cp[]={0x30a4,0x30ed,0x30cf,0x30cb,0x30db,0x30d8,0x30c8,0x20,0x30c1,0x30ea,0x30cc,0x30eb,0x30f2,0x20,
                 0x30ef,0x30ab,0x30e8,0x30bf,0x30ec,0x30bd,0x20,0x30c4,0x30cd,0x30ca,0x30e9,0x30e0,0x20,0x30a6,
                 0x30f0,0x30ce,0x30aa,0x30af,0x30e4,0x30de,0x20,0x30b1,0x30d5,0x30b3,0x30a8,0x30c6,0x20,0x30a2,
                 0x30b5,0x30ad,0x30e6,0x30e1,0x30df,0x30b7,0x20,0x30f1,0x30d2,0x30e2,0x30bb,0x30b9,0x30f3,0x20};

   //! ul()
   EQ_I(ul(t[0]),            1,     "single 1-byte codepoint should have length 1")
   EQ_I(ul(t[1]),            1,     "single 2-byte codepoint should have length 1")
   EQ_I(ul(t[2]),            1,     "single 3-byte codepoint should have length 1")
   EQ_I(ul(t[3]),            1,     "single 4-byte codepoint should have length 1")
   EQ_I(ul(t[4]),            7,     "test vector length should match expected")
   EQ_I(ul(gr),             25,     "test vector length should match expected")
   EQ_I(ul(cy),             25,     "test vector length should match expected")
   EQ_I(ul(ustr0),          33,     "test vector length should match expected")
   EQ_I(ul(ustr1),          56,     "test vector length should match expected")

   //! at()
   EQ_I(at(cy,0),       0x041c,     "utf indexing test #1") // M
   EQ_I(at(cy,7),       0x0449,     "utf indexing test #2") // щ
   EQ_I(at(cy,24),      0x043c,     "utf indexing test #3") // м
   EQ_I(at(gr,15),      0x03c0,     "utf indexing test #4") // π
   EQ_I(at(gr,100),          0,     "utf indexing test #5") // 0
   EQ_I(at(gr,-100),         0,     "utf indexing test #6") // 0

   //! us()
   EQ_I(us(gr,(S)"λ")-gr,   20,     "position of λ must be 20")
   EQ_I(us(cy,(S)"дам")-cy, 39,     "position of 'дам' must be 39")

   //! cp()
   S r=cp(cy,&c0);r=cp(r,&c1);r=cp(r,&c2);
   EQ_I(c0,             0x041c,     "codepoint scan #1")// M
   EQ_I(c1,             0x043d,     "codepoint scan #2")// н
   EQ_I(c2,             0x0435,     "codepoint scan #3")// e

   //! uc()
   EQ_I(uc(gr,0x03c0)-gr,   30,    "position of π should be 30")
   EQ_I(uc(cy,',')-cy,      23,    "position of comma must be 23")

  //! cw()
  I tvec[7]={4,4,4,1,2,2,2};
  I n=0;S tp=t[4],last=tp;N(7,tp=cp(tp,&c0);I exp=tp-last;last=tp;TRUE(exp==tvec[i]&&tvec[i]==cw(c0),"codepoint byte width should match expected"))

  //! ul()
  I LAPS=1000;n=ul(ustr1);UI res=0;TN("ul()",LAPS,N(n,c1=at(ustr1,i);res+=c1==ustr1cp[i]))EQ_I(n,res/LAPS,"ul() implementation should be sane");

  //! UC()
  char*rng="ΑωАяĀɏ∀⋿⌀⍺𝑗";C rcl[]={Ug,Ug,Uc,Uc,Ul,Ul,Um,Um,Ua,Ua,UQ};
  CP c,i=0;tp=(S)rng;W((tp=cp(tp,&c))&&c)EQ_I(UC(c),rcl[i++],"unicode range classes should match expected");
)

//:~
