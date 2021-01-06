CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-pragmas -Wno-unused-value
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

Q=@
# -DSYMS
O=-O0 -g -std=gnu11 -DUSE_AW_MALLOC -DQUIET
LVM=clang
GCC=$(shell env which gcc-9||env which gcc-8||echo gcc)
#GCC+= -Wno-unused-value
TCC=tcc
TESTC=$(LVM) $O

#FIXME=-Wno-int-conversion -Wno-pointer-to-int-cast -Wno-unused-value -Wno-misleading-indentation -Wno-pragmas
FIXME=-Wno-format -Wno-pointer-sign
TOPTS=-UISOMRPH -DTST -DSYMS $(FIXME)
T=tiso.b

ifeq ($(shell uname),Darwin)
 LF+= -pagezero_size 1000
 CF+= -I$(shell xcrun --show-sdk-path)/usr/include
endif

# llvm
l: uprep
	$(LVM) $O $(LF) $(SRC) -o b/bl $(CF)
	@b/bl $T
	@#@echo
	@#@objdump -b binary -m i386 -M intel,x86-64 -D lnk.bin | tail -n+8
	@#@echo


# llvm syms
s: uprep
	$(Q)$(LVM) $O $(LF) $(SRC) -o b/wip $(CF) -DSYMS
	@b/wip

# gcc
g: uprep
	$(Q)$(GCC) $O $(LF) $(SRC) -o b/bg $(CF) $(FIXME)
	b/bg $T

# tcc
t: uprep
	$(Q)$(TCC) $O $(SRC) -o b/bt
	b/bt $T

# ref
r:
	$(Q)$(TESTC) -Os -g r.c -o b/r && b/r
	@#objdump -d b/r

##
## wip unit
##
wip: cleanwip
	@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
	$(Q)$(TESTC) $O $(TOPTS) t/t.c t/lib/unity.c $(SRC) -o w $(LF) $(CF) $(FIXME) -fmacro-backtrace-limit=0
	@echo

w: wip
	@./w

wl: wip
	lldb --source-on-crash t/dat/t.lldb -b -o run ./w
	@echo
	@objdump -b binary -m i386 -M intel,x86-64 -D raw.bin | tail -n+8
	@echo
	@echo
	@objdump -b binary -m i386 -M intel,x86-64 -D lnk.bin | tail -n+8
	@echo

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

#@#-fprofile-instr-generate -fcoverage-mapping -fdebug-macro -fmacro-backtrace-limit=0
t/obj/%.o: %.c
	$(Q)$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c    # build b source

t/obj/t.%.o: t/t.%.c
	$(Q)$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c    # build test units

$(UOBJ): $(USRC)
	$(Q)$(TESTC) $O $(CF) $(TOPTS) $< -o $@ -c    # build unity

b/t.%: t/obj/t.%.o
	$(Q)$(TESTC)  $(BOBJ)  $(UOBJ) $< -o $@ $(LF) # link
	@#ls -la $@
	@#$@

##
## phony
##
all: l g t

cleanwip:
	@rm -f w

clean:
	@rm -f test b/bl b/bg b/bt b/r

.PHONY: clean all cleanwip syms ucl uprep urun u b l g t r w
