CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall
#-Wno-unused-command-line-argument -Wno-unknown-warning-option -Wno-parentheses -Wno-pointer-sign
LF=-rdynamic
#LF=+-nostdlib -c a.S
SRC=[abmphu].c

BSRC=$(shell ls -1 $(SRC) | sed s/.c/.o/ | xargs)
BOBJ=$(patsubst %,t/obj/%,$(BSRC))
TSRC=$(shell basename t/t.*.c | sed s/.c// | xargs)
TOBJ=$(patsubst %,t/obj/%,$(TSRC),%.o%)
TBIN=$(patsubst %,b/%,$(TSRC))
USRC=t/lib/unity.c
UOBJ=t/obj/unity.o

#Q=@
O=-O0 -g -std=gnu11
TESTC=$(Q)clang $O
#FIXME=-Wno-int-conversion -Wno-pointer-to-int-cast -Wno-unused-value -Wno-misleading-indentation -Wno-pragmas
TOPTS=-DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $(FIXME)
T=t.b

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
ci: test
	$(TESTC) $O $(LF) $(SRC) -o b/ci $(CF) $(FIXME)
	file b/ci
	@#lldb --one-line-on-crash bt -b -o run ./bl t.b
	@#gdb -ex r -ex bt -ex detach -ex quit --args ./bl t.b
	@b/ci $T

# llvm
l: uprep
	$(Q)clang $O $(LF) $(SRC) -o b/bl $(CF)
	b/bl $T

# gcc
g: uprep
	$(Q)gcc  $O $(LF) $(SRC) -o b/bg $(CF) $(FIXME)
	b/bg $T

# tcc
t: uprep
	$(Q)tcc  $O $(SRC) -o b/bt
	b/bt $T

# ref
r:
	$(Q)clang -Os -g r.c -o r&&./r
	@#objdump -d r

test: cleantest
	@echo
	@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
	$(TESTC) -DUSE_AW_MALLOC -DTST $O $(LF) t/t.c t/lib/unity.c $(SRC) -o test $(CF) $(FIXME)
	@echo
	@./test

syms: cleansyms
	$(TESTC) -DISOMRPH -DUSE_AW_MALLOC -DTST -DSYMS $O $(LF) $(SRC) t/t.c t/lib/unity.c -o syms $(CF) $(FIXME)
	@lldb --source-on-crash t/dat/t.lldb -b -o run ./syms

all: l g test syms t

##
## modularized test build
##
u: uprep udep urun

ucl:
	@rm -rf b t/obj

uprep:
	@mkdir -p b t/obj

udep: $(BOBJ) $(UOBJ)

urun: $(TBIN)
	$<

#@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
t/obj/%.o: %.c
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

t/obj/t.%.o: t/t.%.c
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

$(UOBJ): $(USRC)
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c

b/t.%: t/obj/t.%.o $(BOBJ)
	$(TESTC)  $(BOBJ)  $(UOBJ) $< -o $@ $(LF)
	@ls -1 $@

##
## phony
##
cleantest:
	@rm -f test

cleansyms:
	@rm -f syms

clean:
	@rm -f test bl bg bt r

.PHONY: t clean all cleansyms cleantest t syms ucl uprep urun u