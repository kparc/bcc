CF=-Wall -Wextra -pedantic -fno-asynchronous-unwind-tables
GNU=-Wno-variadic-macros -Wno-dollar-in-identifier-extension -Wno-gnu-statement-expression -Wno-unused-parameter -Wno-format-pedantic
S=m.c
O=-std=gnu11 -O0 -g
T=-DTA_TEST
C=clang

ifeq ($(shell uname),Darwin)
 CF+= -pagezero_size 1000
endif

m:
	@$C $O $S -DTA_MAIN $(LF) -o m $(CF) $(GNU)

clean:
	@rm -f m leak stress

t:
	@./m

stress: clean
	@$C -DNO_REALLOC -DUSE_TINY_MALLOC -DSTRESS $O $S stress.c $T $(LF) -o stress $(CF) $(GNU)

leak: clean
	@$C -DNO_REALLOC -DUSE_TINY_MALLOC          $O $S stress.c $T $(LF) -o leak $(CF) $(GNU)
	@#threads scale iter
	lldb ./leak 1 10 50

all: clean m t

.PHONY: clean all
