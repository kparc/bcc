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
	$(Q)clang -Os -g r.c -o b/r && b/r
	@#objdump -d b/r

##
## wip unit
##
wip: cleanwip
	@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
	@$(TESTC) $O $(TOPTS) t/t.c t/lib/unity.c $(SRC) -o w $(LF) $(CF) $(FIXME)
	@echo

w: wip
	@./w

wl: wip
	lldb --source-on-crash t/dat/t.lldb -b -o run ./w

all: l g t

##
## incremental test build
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
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c #build b source

t/obj/t.%.o: t/t.%.c
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c #build test units

$(UOBJ): $(USRC)
	$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c #build unity

b/t.%: t/obj/t.%.o $(BOBJ)
	$(TESTC)  $(BOBJ)  $(UOBJ) $< -o $@ $(LF) #link
	@ls -1 $@

##
## phony
##
cleanwip:
	@rm -f w

clean:
	@rm -f test b/bl b/bg b/bt b/r

.PHONY: clean all cleanwip syms ucl uprep urun u b l g t r