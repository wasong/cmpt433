SRC=philos.c door_sensor.c keypad.c

all:
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -pthread -Werror ${SRC} -o philos
	mv philos $(HOME)/cmpt433/public/myApps/

