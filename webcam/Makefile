CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
LFLAGS = -L$(HOME)/cmpt433/work/webcam/libs 
AFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB
OUTFILE = main
OUTDIR = $(HOME)/cmpt433/public/myApps

SRC = main.c grabber.c wave_player.c
OBJ = $(addsuffix .o, $(basename $(SRC)))

all: wav
	$(CC_C) $(CFLAGS) $(LFLAGS) $(AFLAGS) $(SRC) -o $(OUTFILE) -lv4l2 -lv4lconvert -ljpeg -lpthread -lasound

	cp $(OUTFILE) $(OUTDIR)

# Copy wave files to the shared folder
wav:
	mkdir -p $(PUBDIR)/wave-files/
	cp wave-files/* $(PUBDIR)/wave-files/ 

%.o: %c
	$(CC_C) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OUTDIR)/$(OUTFILE)

