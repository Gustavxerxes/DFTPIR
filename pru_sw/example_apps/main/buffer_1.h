#ifndef buff_h
#define buff_h

#include <pthread.h>
#include "kiss_fftr.h"
#include "define.h"

kiss_fft_scalar channels[N_PIR][RINGBUFFER_SIZE];
int first; //Pointer to next sampel to start FFT
int currentSample[N_PIR]; // where to add next value
int last_FFT; // how many samples sinse last FFT
int ready; // Indicates when to start FFT
kiss_fft_scalar value[N_PIR][N_SAMPLES];


int createBuffer();



int addInBuffer(int channel, int value);

void getBuffer();

#endif
