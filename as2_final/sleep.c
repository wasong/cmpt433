#include "sleep.h"
#include <time.h>

void slip(long sec, long nano) {
	long seconds = sec;
	long nanoseconds = nano;
	struct timespec reqDelay = {seconds, nanoseconds};
	nanosleep(&reqDelay, (struct timespec *) NULL);
}
