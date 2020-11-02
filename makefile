CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-parentheses -Wno-pointer-sign
#LF=-nostdlib -c a.S
SRC=a.c b.c p.c
O=-O0 -g

ifeq ($(shell uname),Darwin)
 CF+= -pagezero_size 1000
endif

# llvm
l:
	clang $O $(LF) $(SRC) -o bl $(CF)
	./bl t.b

# gcc
g:
	gcc $O $(LF) $(SRC) -o bg $(CF)
	./bg t.b

# tcc
t:
	tcc -std=c99 $O $(SRC) -o bt
	./bt t.b

# ref
r:
	clang -Os -g r.c -o r&&./r
	@#objdump -d r

test: cleantest
	@clang -std=gnu99 -DTST $O $(LF) t/t.c t/lib/unity.c $(SRC) -o test $(CF) -fmacro-backtrace-limit=0 \
	-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -Wno-int-conversion
	@./test

syms: cleansyms
	@clang -std=gnu99 -DTST -DSYMS $O $(LF) t/t.c t/lib/unity.c $(SRC) -o syms $(CF) -fmacro-backtrace-limit=0 -Wno-int-conversion
	@./syms

cleantest:
	@rm -f test
cleansyms:
	@rm -f syms

all: l g t

clean:
	@rm -f test bl bg bt r
