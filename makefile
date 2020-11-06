CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-parentheses -Wno-pointer-sign
#LF=-nostdlib -c a.S
SRC=[abmph].c
O=-O0 -g
T=t.b

ifeq ($(ISOMRPH),1)
 O+=-DISOMRPH
 T=tiso.b
endif

ifeq ($(shell uname),Darwin)
 CF+= -pagezero_size 1000
endif

# llvm
l:
	clang $O $(LF) $(SRC) -o bl $(CF)
	./bl $T

# gcc
g:
	gcc $O $(LF) $(SRC) -o bg $(CF) -Wno-unused-value -Wno-misleading-indentation
	./bg $T

# tcc
t:
	tcc -std=c99 $O $(SRC) -o bt
	./bt $T

# ref
r:
	clang -Os -g r.c -o r&&./r
	@#objdump -d r

TESTCC=clang -std=gnu11
FIXME=-Wno-pointer-to-int-cast
test: cleantest
	@$(TESTCC) -DUSE_AW_MALLOC -DTST $O $(LF) t/t.c t/lib/unity.c $(SRC) -o test $(CF) -fmacro-backtrace-limit=0 \
	-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -Wno-int-conversion $(FIXME)
	@./test

syms: cleansyms
	@$(TESTCC) -DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $O $(LF) t/t.c t/lib/unity.c $(SRC) -o syms $(CF) \
	-fmacro-backtrace-limit=0 -Wno-int-conversion $(FIXME)
	@./syms

cleantest:
	@rm -f test

cleansyms:
	@rm -f syms

all: l g test syms t

clean:
	@rm -f test bl bg bt r

.PHONY: t clean all cleansyms cleantest t