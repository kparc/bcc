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
	@$C $O $S $T $(LF) -o m $(CF) $(GNU)

clean:
	@rm -f m

t:
	@./m

all: clean m t

.PHONY: clean all