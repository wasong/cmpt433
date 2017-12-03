#ifndef _GRABBER_H_
#define _GRABBER_H_

void webcam_init(void);
void webcam_join(void);

void* webcamThread(void* arg);

int working;

#endif

