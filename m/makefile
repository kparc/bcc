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

MI=-lpthread -Ibench/extern/mimalloc/include -Lbench/extern/mimalloc/out/release -lmimalloc -Wno-int-conversion -Wno-extra-semi
LEAKOPTS=1 100 10000
STRESSOPTS=1 100 16
TM=LD_LIBRARY_PATH=bench/extern/mimalloc/out/release

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

leak: clean
	$C $(OTST) -DUSE_TM_MALLOC         $(SRC) stress.c -o leak $(CF) $(GNU) $(MI)
	$(TM) ./leak $(LEAKOPTS)

leaksys: clean
	$C $(OTST) -DUSE_STD_MALLOC        $(SRC) stress.c -o leak $(CF) $(GNU) $(MI)
	@#threads scale iter
	$(TM) ./leak $(LEAKOPTS)

leakmi: clean
	$C $(OTST) -DUSE_MI_MALLOC         $(SRC) stress.c -o leak $(CF) $(GNU) $(MI)
	@#threads scale iter
	$(TM) ./leak $(LEAKOPTS)

OCFRAC=-w -Os -DNDEBUG -std=gnu89 -DNOMEMOPT cfrac/*.c -lm
OCFRAC_TA=-DCUSTOM_FREE=ta_free -DCUSTOM_MALLOC=ta_malloc -DCUSTOM_MALLOC_INIT=ta_test_init -DTA_TEST
OCFRAC_IN=175451865205073170563711388363

cfrac: clean
	@clang $(OCFRAC)                  -o cf_sys
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_tm
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_tm_nc  -DTA_NO_COMPACT
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_tm_ns  -DTA_NO_SPLIT
	@clang $(OCFRAC) $(OCFRAC_TA) m.c -o cf_tm_ncs -DTA_NO_COMPACT -DTA_NO_SPLIT

	@echo;echo "cfrac malloc";echo
	@             time ./cf_sys    $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (split+compact)";echo	          
	@TA_NBLK=2048 time ./cf_tm     $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no split)";echo
	@TA_NBLK=2048 time ./cf_tm_ns  $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no compact)";echo
	@TA_NBLK=4096 time ./cf_tm_nc  $(OCFRAC_IN)
	@echo;echo "cfrac ta_malloc (no split/compact)";echo
	@TA_NBLK=4096 time ./cf_tm_ncs $(OCFRAC_IN)

all: clean m t so

clean:
	@rm -f m leak stress libtm.so libtm.dylib cf

.PHONY: clean all cfrac
