CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-pointer-sign -Wno-strict-aliasing -Wno-parentheses -Wno-unused-value -Wno-misleading-indentation -Wno-unused-function
#LF=-nostdlib -c s.S
SRC=a.c b.c p.c
O=-O0 -g

# llvm
l:
	clang -pagezero_size 1000 -Wno-empty-body $O $(LF) $(SRC) -o bl $(CF)
	./bl t.b

# gcc
g:
	gcc -pagezero_size 1000 $O $(LF) $(SRC) -o bg $(CF)
	./bg t.b

# tcc
t:
	tcc -std=c99 $O $(SRC) -o bt
	./bt t.b

# ref
r:
	clang -Os -g r.c -o r&&./r
	@#objdump -d r

all: l g t

clean:
	@rm -f bl bg bt r
