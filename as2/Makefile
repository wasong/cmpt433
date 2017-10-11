CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
OUTFILE = reader
OUTDIR = $(HOME)/cmpt433/public/myApps

SRC = reader.c main.c
OBJ = $(addsuffix .o, $(basename $(SRC)))

all:
	$(CC_C) $(CFLAGS) $(file).c -o $(file)

	cp $(file) $(OUTDIR)

a2d:
	$(CC_C) -std=c99 -D _POSIX_C_SOURCE=200809L $(file).c -lm -o $(file)
	
	cp $(file) $(OUTDIR)

reader: $(OBJ)
	$(CC_C) $(CFLAGS) -o $(OUTDIR)/$(OUTFILE) $(OBJ)

%.o: %c
	$(CC_C) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OUTDIR)/$(OUTFILE)
