C=clang -std=gnu11

#-fvisibility=hidden
CF=-Wall -Wextra -pedantic -fno-asynchronous-unwind-tables -fno-stack-protector -fno-common -fvisibility=default
GNU=-Wno-variadic-macros -Wno-dollar-in-identifier-extension -Wno-gnu-statement-expression -Wno-unused-parameter -Wno-format-pedantic
SRC=m.c
OREL=-O0
ODBG=-O0 -g
OTST=-O0 -DTA_TEST -DNDEBUG

#TINYOPTS=-DTA_NO_COMPACT -DTA_NO_SPLIT
TINYOPTS=-DTA_TEST

STRESSOPTS=1 100 16

OSO=-shared -lpthread -fPIC
TSO=libtm.so
ifeq ($(shell uname),Darwin)
 OSO=-dynamiclib -undefined dynamic_lookup
 TSO=libtm.dylib
 #CF+= -pagezero_size 1000
endif

m:
	@$C $(ODBG) $(SRC) -DTA_MAIN -o m $(CF) $(GNU)

so:
	$C $(OREL) $(SRC) -o $(TSO) $(OSO) $(CF) $(GNU) $(TINYOPTS)
	@ls -la $(TSO)

t:
	@./m

stress: clean
	$C $(OTST) -DUSE_TM_MALLOC -DSTRESS $(SRC) stress.c -o stress $(CF) $(GNU) $(MI)
	$(TM) ./stress $(STRESSOPTS)

stresssys: clean
	$C $(OTST) -DUSE_STD_MALLOC -DSTRESS $(SRC) stress.c -o stress $(CF) $(GNU) $(MI)
	$(TM) ./stress $(STRESSOPTS)

stressmi: clean
	$C $(OTST) -DUSE_MI_MALLOC  -DSTRESS $(SRC) stress.c -o stress $(CF) $(GNU) $(MI)
	$(TM) ./stress $(STRESSOPTS)

##############
# memleak test
##############

NBLK=128
LEAKCFG=1 100 40000
OLEAK=-O2 -DTA_TEST -DNDEBUG -DNO_MI_STATS -lpthread
OMI=-Ibench/extern/mimalloc/include -Lbench/extern/mimalloc/out/release -lmimalloc -Wno-int-conversion -Wno-extra-semi
TM=LD_LIBRARY_PATH=bench/extern/mimalloc/out/release time
TM=TA_NBLK=$(NBLK) LD_LIBRARY_PATH=bench/extern/mimalloc/out/release time

leak: clean
	@$C $(OLEAK) -DUSE_TA_MALLOC  $(SRC) stress.c -o leak_ta      $(CF) $(GNU)
	@$C $(OLEAK) -DUSE_TA_MALLOC  $(SRC) stress.c -o leak_ta_chk  $(CF) $(GNU) -DTA_CHECK
	@$C $(OLEAK) -DUSE_TA_MALLOC  $(SRC) stress.c -o leak_ta_ns   $(CF) $(GNU) -DTA_NO_SPLIT
	@$C $(OLEAK) -DUSE_STD_MALLOC $(SRC) stress.c -o leak_sys     $(CF) $(GNU)
	@$C $(OLEAK) -DUSE_MI_MALLOC  $(SRC) stress.c -o leak_mi      $(CF) $(GNU) $(OMI)

	@echo;echo "leak ta_malloc (split+compact)";echo
	@$ $(TM) ./leak_ta  $(LEAKCFG)

	@echo;echo "leak ta_malloc (no split)";echo
	@TA_NBLK=32 $(TM) ./leak_ta  $(LEAKCFG)

	@echo;echo "leak ta_malloc (w/check)";echo
	@TA_NBLK=32 $(TM) ./leak_ta  $(LEAKCFG)

	@echo;echo "leak malloc";echo
	@$(TM) ./leak_sys $(LEAKCFG)

	@echo;echo "leak mi_malloc";echo
	@$(TM) ./leak_mi  $(LEAKCFG)

############
# cfrac test
############

OCFRAC=-w -Os -DNDEBUG -std=gnu89 -DNOMEMOPT cfrac/*.c -lm
OCFRAC_TA=-DCUSTOM_FREE=ta_free -DCUSTOM_MALLOC=ta_malloc -DCUSTOM_MALLOC_INIT=ta_test_init -DTA_TEST
OCFRAC_IN=175451865205073170563711388363

cfrac: clean
	@clang $(OCFRAC)                  -o cf_sys
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_ta
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_ta_nc  -DTA_NO_COMPACT
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_ta_ns  -DTA_NO_SPLIT
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_ta_ncs -DTA_NO_COMPACT -DTA_NO_SPLIT

	@echo;echo "cfrac malloc";echo
	@             time ./cf_sys    $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (split+compact)";echo	          
	@TA_NBLK=2048 time ./cf_ta     $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no split)";echo
	@TA_NBLK=2048 time ./cf_ta_ns  $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no compact)";echo
	@TA_NBLK=4096 time ./cf_ta_nc  $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no split/compact)";echo
	@TA_NBLK=4096 time ./cf_ta_ncs $(OCFRAC_IN)

all: clean m t so 

clean:
	@rm -f m stress libtm.so libtm.dylib cf_* leak_*

.PHONY: clean all cfrac
