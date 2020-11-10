CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-unknown-warning-option -Wno-parentheses -Wno-pointer-sign
LF=-rdynamic
#LF=+-nostdlib -c a.S
SRC=[abmphu].c

BSRC=$(shell ls -1 $(SRC) | sed s/.c/.o/ | xargs)
BOBJ=$(patsubst %,t/obj/%,$(BSRC))
TSRC=$(shell basename t/t.*.c | sed s/.c// | xargs)
TOBJ=$(patsubst %,t/obj/%,$(TSRC),%.o%)
TBIN=$(patsubst %,t/bin/%,$(TSRC))
USRC=t/lib/unity.c
UOBJ=t/obj/unity.o
T=t.b

QUIET=@
O=-O0 -g -std=gnu11
TESTC=$(QUIET)clang $O
FIXME=-Wno-int-conversion -Wno-pointer-to-int-cast -Wno-unused-value -Wno-misleading-indentation -Wno-pragmas
TOPTS=-DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $(FIXME)

ifeq ($(ISOMRPH),1)
 O+=-DISOMRPH
 T=tiso.b
endif

ifeq ($(CI),1)
 O=-O0 -DCI
 QUIET=
endif

ifeq ($(shell uname),Darwin)
 LF+= -pagezero_size 1000
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
	$(QUIET)$(TESTC) -DUSE_AW_MALLOC -DTST $O $(LF) t/t.c t/lib/unity.c $(SRC) -o test $(CF) $(FIXME)
	@echo
	@./test

syms: cleansyms
	$(TESTC) -DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $O $(LF) $(SRC) t/t.c t/lib/unity.c -o syms $(CF) $(FIXME)
	@lldb --source-on-crash t/dat/t.lldb -b -o run ./syms

cleantest:
	@rm -f test

cleansyms:
	@rm -f syms

all: l g test syms t

##
## modularized test build
##

u: uprep urun

ucl:
	rm -rf t/bin t/obj

uprep:
	mkdir -p t/bin t/obj

urun: $(BOBJ) $(UOBJ) $(TBIN)

#@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
t/obj/%.o: %.c
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

t/obj/t.%.o: t/t.%.c
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

$(UOBJ): $(USRC)
	@$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

t/bin/t.%: t/obj/t.%.o $(BOBJ)
	@$(TESTC)  $(BOBJ)  $(UOBJ) $< -o $@ $(LF)
	@ls -1 $@


clean:
	@rm -f test bl bg bt r

.PHONY: t clean all cleansyms cleantest t syms ucl uprep urun u