a `b` compiler
==============

`bcc` is an interactive compiler of a language called `b`.

it produces compact and fast object code that uses very little stack.

b aims to offer same types, ops and control as c.

t.b and t.c:

```
         run  compile(ms) runsize
     b   230     .06       1K
gcc-O1   320   60.00       3K
gcc-O2   230   90.00       3K
gcc-O9   230  200.00       8K
```

b syntax is more compact than c and has no precedence rules:

```
b : +-*%^&|<> =  /  \   $[c;t;f]
c = +-*/^&|<> == << >>  if(c)t;else f;
```

argtypes for x,y,z are declared, local types and result type are inferred.

bsearch:

```
b: b[Ii]{h:#x;l:0;W(h>l)$[y>x[i:/l+h];l:i+1;h:i];l}
c: I b(I*x,I y){I h=x[-1],i,l=0;while(h>l)if(y>x[i=l+h>>1])l=i+1;else h=i;R l;}
```

ackermann:

```
b: a[ii]$[x;a[-x;$[y;a[x;-y];1]];+y]
c: I a(I x,I y){R x?a(x-1,y?a(x,y-1):1):y+1;}

b:        85ff741c85f6740e83ee0157e8efffffff5f8bf0eb05be0100000083ef01ebe08d4601c3 (36)
clang -Os 534889f04885ff7423488d5fff4885c0740d48ffc84889c6e8e3ffffffeb05b8010000004889df4885db75dd48ffc05bc3 (49)
```

that is:

```<a>:
0:  85 ff                   test   edi,edi
2:  74 1c                   je     0x20
4:  85 f6                   test   esi,esi
6:  74 0e                   je     0x16
8:  83 ee 01                sub    esi,0x1
b:  57                      push   rdi
c:  e8 ef ff ff ff          call   0
11: 5f                      pop    rdi
12: 8b f0                   mov    esi,eax
14: eb 05                   jmp    0x1b
16: be 01 00 00 00          mov    esi,0x1
1b: 83 ef 01                sub    edi,0x1
1e: eb e0                   jmp    0
20: 8d 46 01                lea    eax,[rsi+0x1]
23: c3                      ret

<a>:
564:   53                   push   %rbx
565:   48 89 f0             mov    %rsi,%rax
568:   48 85 ff             test   %rdi,%rdi
56b:   74 23                je     590 <a+0x2c>
56d:   48 8d 5f ff          lea    -0x1(%rdi),%rbx
571:   48 85 c0             test   %rax,%rax
574:   74 0d                je     583 <a+0x1f>
576:   48 ff c8             dec    %rax
579:   48 89 c6             mov    %rax,%rsi
57c:   e8 e3 ff ff ff       callq  564 <a>
581:   eb 05                jmp    588 <a+0x24>
583:   b8 01 00 00 00       mov    $0x1,%eax
588:   48 89 df             mov    %rbx,%rdi
58b:   48 85 db             test   %rbx,%rbx
58e:   75 dd                jne    56d <a+0x9>
590:   48 ff c0             inc    %rax
593:   5b                   pop    %rbx
594:   c3                   retq
```

source code:

`a.S`  kernel interface
`a.c`  runtime
`p.c`  parser
`b.c`  compiler
 
`p()`  parse
`d()`  to register (constant or global)
`e()`  to register
`f()`  force

`ex()` run

for riscv, arm, xtensa we need:

```
jmp() tst() cmp()  o2()
ret() cll() psh() pop()
```

faq

there is no license.

the [original](http://kparc.com/b) software was apparently meant as a friendly joke.

the name of this project is an insider pun and stands for `blind carbon copy`.

this work is prompted by a formidable anonymous [effort](https://docs.google.com/document/d/1W83ME5JecI2hd5hAUqQ1BVF32wtCel8zxb7WPq-D4f8/mobilebasic?urp=gmail_link&gxids=7628).

`/:~`
