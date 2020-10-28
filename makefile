CF=-minline-all-stringops -fno-asynchronous-unwind-tables -fno-stack-protector -Wall -Wno-pointer-sign -Wno-strict-aliasing -Wno-parentheses -Wno-unused-function
LF=-s -nostdlib A.S

/bin/b: a.c b.c *.h makefile
	sudo $(CC) -Os -o $@ $(LF) a.c b.c $(CF)

/bin/k: a.c k.c *.h makefile
	sudo $(CC) -Os -o $@ $(LF) a.c k.c $(CF)

all: /bin/b /bin/k

