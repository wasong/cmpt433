#ifndef BEATS_H
#define BEATS_H
#include <time.h>

//Prototypes
void noBeat();						//returns nothing
void rock();						//plays standard rock beat
void custom();						//plays custom beat
void* beatThread(void* arg);				//Beat threading	

#endif
