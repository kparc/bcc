a `b` compiler
==============

`bcc` is an interactive compiler of a language `b`.

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

argtypes for x,y,z are declared, local types and result type are automatic.

e.g. bsearch:

```
b: b[Ii]{h:#x;l:0;while(h>l)$[y>x[i:/l+h];l:i+1;h:i];l}
c: I b(I*x,I y){I h=x[-1],i,l=0;while(h>l)if(y>x[i=l+h>>1])l=i+1;else h=i;R l;}
```

bcc source code:

A.S  kernel interface
a.c  event loop, syscalls, printer, i/o

p.c  parser of b
b.c  compiler of b
 
p()  parse
d()  to register (constant or global)
e()  to register
f()  force

ex() exec

for riscv, arm, xtensa, etc we need:

```
jmp() tst() cmp()  o2()
ret() cll() psh() pop()
```


see also:

https://docs.google.com/document/d/1W83ME5JecI2hd5hAUqQ1BVF32wtCel8zxb7WPq-D4f8/mobilebasic?urp=gmail_link&gxids=7628)

`//!~`
