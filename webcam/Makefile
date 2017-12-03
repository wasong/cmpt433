CC_C = arm-linux-gnueabihf-gcc
CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror
LFLAGS = -L$(HOME)/cmpt433/work/webcam/libs 
AFLAGS = -L$(HOME)/cmpt433/public/asound_lib_BBB
OUTFILE = main
OUTDIR = $(HOME)/cmpt433/public/myApps

SRC = main.c grabber.c wave_player.c server.c
OBJ = $(addsuffix .o, $(basename $(SRC)))

all: wav
	$(CC_C) $(CFLAGS) $(SRC) -o $(OUTFILE) -lpthread $(LFLAGS) -lv4l2 -lv4lconvert -ljpeg $(AFLAGS) -lasound

	cp $(OUTFILE) $(OUTDIR)

# Copy wave files to the shared folder
wav:
	mkdir -p $(OUTDIR)/wave-files/
	cp wave-files/* $(OUTDIR)/wave-files/ 

%.o: %c
	$(CC_C) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OUTDIR)/$(OUTFILE)

