C=clang -std=gnu11

CF=-Wall -Wextra -pedantic -fno-asynchronous-unwind-tables -fvisibility=hidden -fno-stack-protector -fno-common
GNU=-Wno-variadic-macros -Wno-dollar-in-identifier-extension -Wno-gnu-statement-expression -Wno-unused-parameter -Wno-format-pedantic
SRC=m.c
OREL=-O0
ODBG=-O0 -g
OTST=-O0 -DTA_TEST -DNDEBUG

#TINYOPTS=-DTA_NO_COMPACT -DTA_NO_SPLIT

MI=-lpthread -Ibench/extern/mimalloc/include -Lbench/extern/mimalloc/out/release -lmimalloc -Wno-int-conversion -Wno-extra-semi
LEAKOPTS=1 100 10000
STRESSOPTS=1 100 16
TM=LD_LIBRARY_PATH=bench/extern/mimalloc/out/release

OSO=-shared -lpthread
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


all: clean m t so

clean:
	@rm -f m leak stress libtm.so libtm.dylib

.PHONY: clean all
