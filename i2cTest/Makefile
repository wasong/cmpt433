CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
OUTFILE = i2c
OUTDIR = $(HOME)/cmpt433/public/myApps

SRC = sleep.c fileHandler.c display.c I2C.c reader.c sorter.c server.c run.c main.c
OBJ = $(addsuffix .o, $(basename $(SRC)))

all:
	$(CC_C) $(CFLAGS) $(file).c -o $(file)

	cp $(file) $(OUTDIR)

i2c:
	$(CC_C) $(CFLAGS) $(SRC) -lm -lpthread -o $(OUTFILE)
	
	cp $(OUTFILE) $(OUTDIR)

clean:
	rm -f $(OUTFILE)
	rm -f $(OUTDIR)/$(OUTFILE)

.PHONY: i2c clean
