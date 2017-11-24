CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
LFLAGS = -L$(HOME)/cmpt433/work/webcam/libs 
OUTFILE = grabber
OUTDIR = $(HOME)/cmpt433/public/myApps

SRC = grabber.c
OBJ = $(addsuffix .o, $(basename $(SRC)))

all:
	$(CC_C) $(CFLAGS) $(LFLAGS) $(SRC) -o $(OUTFILE) -lv4l2 -lv4lconvert -ljpeg

	cp $(OUTFILE) $(OUTDIR)

%.o: %c
	$(CC_C) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OUTDIR)/$(OUTFILE)

