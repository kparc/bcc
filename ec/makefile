O=-Os -std=gnu11 -DTST -pedantic -Wno-gnu-statement-expression -Wno-variadic-macros e.c

#C=$(shell env which gcc-9||env which gcc-8||echo gcc)
C=clang
ifeq ($(shell uname),Darwin)
 O+= -I$(shell xcrun --show-sdk-path)/usr/include
endif

e32:
	$C $O -m32 -o e32&&./e32
e64:
	$C $O -o e64&&./e64

install:
	go install golang.org/x/crypto/curve25519 encoding/hex

go:
	go build e.go
	./e

all: e64

.PHONY: all e32 e64 clean
