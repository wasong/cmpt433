CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
OUTDIR = $(HOME)/cmpt433/public/myApps/

all:
	$(CC_C) $(CFLAGS) $(file).c -o $(file)

	cp $(file) $(OUTDIR)

a2d:
	$(CC_C) -std=c99 -D _POSIX_C_SOURCE=200809L $(file).c -lm -o $(file)
	
	cp $(file) $(OUTDIR)
