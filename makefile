CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-unknown-warning-option -Wno-parentheses -Wno-pointer-sign -rdynamic
#LF=-nostdlib -c a.S
SRC=[abmphu].c
O=-O0 -g
T=t.b
QUIET=@
FIXME=-Wno-int-conversion -Wno-pointer-to-int-cast -Wno-unused-value -Wno-misleading-indentation -Wno-pragmas
TESTCC=gcc -std=gnu11 $(FIXME)

ifeq ($(ISOMRPH),1)
 O+=-DISOMRPH
 T=tiso.b
endif

ifeq ($(CI),1)
 O=-O0 -DCI
 QUIET=
endif

ifeq ($(shell uname),Darwin)
 CF+= -pagezero_size 1000
endif

# ci
ci:
	@CI=1 make test
	$(TESTCC) $O $(LF) $(SRC) -o b $(CF) $(FIXME)
	file ./b
	@#lldb --one-line-on-crash bt -b -o run ./bl t.b
	@#gdb -ex r -ex bt -ex detach -ex quit --args ./bl t.b
	@./b $T
	

# llvm
l:
	clang $O $(LF) $(SRC) -o bl $(CF)
	./bl $T

# gcc
g:
	gcc $O $(LF) $(SRC) -o bg $(CF) $(FIXME)
	./bg $T

# tcc
t:
	tcc -std=c99 $O $(SRC) -o bt
	./bt $T

# ref
r:
	clang -Os -g r.c -o r&&./r
	@#objdump -d r

test: cleantest
	@echo
	@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
	$(QUIET)$(TESTCC) -DUSE_AW_MALLOC -DTST $O $(LF) t/t.c t/lib/unity.c $(SRC) -o test $(CF) $(FIXME)
	@echo
	@./test

syms: cleansyms
	@$(TESTCC) -DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $O $(LF) t/t.c t/lib/unity.c $(SRC) -o syms $(CF) \
	-fmacro-backtrace-limit=0 $(FIXME)
	@./syms

cleantest:
	@rm -f test

cleansyms:
	@rm -f syms

all: l g test syms t

clean:
	@rm -f test bl bg bt r

.PHONY: t clean all cleansyms cleantest t syms