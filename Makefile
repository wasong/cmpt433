all:
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror $(file).c -o $(file)

	cp $(file) $(HOME)/cmpt433/public/myApps/

a2d:
	arm-linux-gnueabihf-gcc -std=c99 -D _POSIX_C_SOURCE=200809L $(file).c -lm -o $(file)
	
	cp $(file) $(HOME)/cmpt433/public/myApps/
